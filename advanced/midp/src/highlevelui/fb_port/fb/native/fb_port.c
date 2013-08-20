/*
 * add by armite@126.com
 */

#include <errno.h>
#include <sys/ipc.h>
#include <linux/shm.h>
#include <sys/ioctl.h>
#include <sys/mman.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gxj_putpixel.h>
#include <gxj_screen_buffer.h>
#include <midp_logging.h>
#include <midpMalloc.h>
#include <midp_constants_data.h>

#include <fbapp_device_type.h>
#include <fbapp_export.h>
#include "fb_port.h"
#include "advanced.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

static int mouseFd = -1;
static int keyboardFd = -1;

static LinuxFbDeviceType linuxFbDeviceType = LINUX_FB_VERSATILE_INTEGRATOR; 

int getKeyboardFd() {
    return keyboardFd;
}

int getMouseFd() {
    return mouseFd;
}

gxj_screen_buffer gxj_system_screen_buffer;

/** Allocate system screen buffer according to the screen geometry */
void initScreenBuffer(int width, int height) {
    if (gxj_init_screen_buffer(width, height) != ALL_OK) {
        MYLOGI("Failed to allocate screen buffer\n");
        pthread_exit(NULL);
    }
}

/** Inits keyboard device */
static void initKeyboard() {
    struct sockaddr_in sa;
    keyboardFd = socket(AF_INET, SOCK_DGRAM, 0);

    bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(17081);
    sa.sin_addr.s_addr = htons(INADDR_ANY);
    bzero(&(sa.sin_zero), 8);
    bind(keyboardFd, (struct sockaddr *)&sa, sizeof(sa));
}

static getBitmap android_getBitmap = NULL;
static refreshBitmap android_refreshBitmap = NULL;
static releaseBitmap android_releaseBitmap = NULL;
void setBitmapFuns(getBitmap g, refreshBitmap f, releaseBitmap l) {
    android_getBitmap = g;
    android_refreshBitmap = f;
    android_releaseBitmap = l;
}

/** Inits frame buffer device */
void initFrameBuffer() {
    if (!android_getBitmap)
        return;
    int stride = 0;
    unsigned short *data = NULL;
    android_getBitmap(gxj_system_screen_buffer.width, gxj_system_screen_buffer.height, &stride, &data);

    fb.xoff  = 0;
    fb.yoff  = 0;
    fb.dataoffset = 0;
    fb.depth = 16;
    fb.lstep = stride;
    fb.width = gxj_system_screen_buffer.width;
    fb.height= gxj_system_screen_buffer.height;
    fb.mapsize = gxj_system_screen_buffer.height * stride;
    fb.data = data;
    fb.data += fb.dataoffset;
}

void reverseScreenOrientation() {
    gxj_rotate_screen_buffer(KNI_FALSE);
}

/** Initialize frame buffer video device */
void connectFrameBuffer() {
    initKeyboard();
    initFrameBuffer();
}

/** Clear screen content */
void clearScreen() {
    int n;
    gxj_pixel_type *p = fb.data;
    gxj_pixel_type color = (gxj_pixel_type)GXJ_RGB2PIXEL(0xa0, 0xa0, 0x80);
    for (n = fb.width * fb.height; n > 0; n--) {
        *p ++ = color;
    }
}

void resizeScreenBuffer(int width, int height) {
    if (gxj_resize_screen_buffer(width, height) != ALL_OK) {
        MYLOGI("Failed to reallocate screen buffer\n");
        pthread_exit(NULL);
    }
}

/** Get x-coordinate of screen origin */
int getScreenX(int screenRotated) {
    int bufWidth = gxj_system_screen_buffer.width;
    int x = 0;
    int LCDwidth = screenRotated ? fb.height : fb.width;
    if (LCDwidth > bufWidth) {
        x = (LCDwidth - bufWidth) / 2;
    }
    return x;
}

/** Get y-coordinate of screen origin */
int getScreenY(int screenRotated) {
    int bufHeight = gxj_system_screen_buffer.height;
    int y = 0;
    int LCDheight = screenRotated ? fb.width : fb.height;
    if (LCDheight > bufHeight) {
        y = (LCDheight - bufHeight) / 2;
    }
    return y;
}

/** Refresh screen from offscreen buffer */
void refreshScreenNormal(int x1, int y1, int x2, int y2) {
    gxj_pixel_type *src = gxj_system_screen_buffer.pixelData;
    gxj_pixel_type *dst = (gxj_pixel_type*)fb.data;
    int srcWidth, srcHeight;
    int dstWidth = fb.width;
    int dstHeight = fb.height;

    // System screen buffer geometry
    int bufWidth = gxj_system_screen_buffer.width;
    int bufHeight = gxj_system_screen_buffer.height;

    // Make sure the copied lines are 4-byte aligned for faster memcpy
    if ((x1 & 1) == 1) x1 -= 1;
    if ((x2 & 1) == 1) x2 += 1;
    
    srcWidth = x2 - x1;
    srcHeight = y2 - y1;

    if (bufWidth < dstWidth || bufHeight < dstHeight) {
        // We are drawing into a frame buffer that's larger than what MIDP
        // needs. Center it.
        dst += ((dstHeight - bufHeight) / 2) * dstWidth;
        dst += (dstWidth - bufWidth) / 2;
    }

    if (srcWidth == dstWidth && srcHeight == dstHeight &&
        x1 == 0 && y1 == 0) {
        // copy the entire screen with one memcpy
        memcpy(dst, src, srcWidth * sizeof(gxj_pixel_type) * srcHeight);
    } else {
        src += y1 * bufWidth + x1;
        dst += y1 * dstWidth + x1;

        for (; y1 < y2; y1++) {
            memcpy(dst, src, srcWidth * sizeof(gxj_pixel_type));
            src += bufWidth;
            dst += dstWidth;
        }
    }

    if (android_refreshBitmap)
        android_refreshBitmap();
}

static void fast_copy_rotated(short *src, short *dst, int x1, int y1, int x2, int y2,
        int bufWidth, int dstWidth, int srcInc, int dstInc) {

  int x;
  unsigned a, b;
  while(y1 < y2) {
    y1 += 2;
    for (x = x1; x < x2; x += 2) {
      a = *(unsigned*)src;
      b = *(unsigned*)(src + bufWidth);
      src += 2;
      
      *(unsigned*)dst = (b << 16) | (a & 0x0000ffff);
      dst -= dstWidth;
      *(unsigned*)dst = (b & 0xffff0000) | (a >> 16);
      dst -= dstWidth;
    }
    dst += dstInc + 1;
    src += srcInc + bufWidth;
  }
}

/** Refresh rotated screen with offscreen buffer content */
void refreshScreenRotated(int x1, int y1, int x2, int y2) {

    gxj_pixel_type *src = gxj_system_screen_buffer.pixelData;
    gxj_pixel_type *dst = (gxj_pixel_type*)fb.data;
    int srcWidth, srcHeight;
    int dstWidth = fb.width;
    int dstHeight = fb.height;

    int srcInc;
    int dstInc;

    // System screen buffer geometry
    int bufWidth = gxj_system_screen_buffer.width;
    int bufHeight = gxj_system_screen_buffer.height;

    // Make sure the copied lines are 4-byte aligned for faster memcpy
    if ((x1 & 1) == 1) x1 -= 1;
    if ((x2 & 1) == 1) x2 += 1;
    if ((y1 & 1) == 1) y1 -= 1;
    if ((y2 & 1) == 1) y2 += 1;

    srcWidth = x2 - x1;
    srcHeight = y2 - y1;

    if (bufWidth < dstHeight || bufHeight < dstWidth) {
            // We are drawing into a frame buffer that's larger than what MIDP
            // needs. Center it.
            dst += (dstHeight - bufWidth) / 2 * dstWidth;
            dst += ((dstWidth - bufHeight) / 2);
        }

    src += x1 + y1 * bufWidth;
    dst += y1 + (bufWidth - x1 - 1) * dstWidth;

    srcInc = bufWidth - srcWidth;      // increment for src pointer at the end of row
    dstInc = srcWidth * dstWidth + 1;  // increment for dst pointer at the end of column

    fast_copy_rotated(src, dst, x1, y1, x2, y2, bufWidth, dstWidth, srcInc, dstInc);
}

/** Frees allocated resources and restore system state */
void finalizeFrameBuffer() {
    gxj_free_screen_buffer();
    if (android_releaseBitmap)
        android_releaseBitmap();
    if (keyboardFd != -1)
        close(keyboardFd);
    keyboardFd = -1;
    android_releaseBitmap = NULL;
    android_refreshBitmap = NULL;
    android_getBitmap = NULL;
}



