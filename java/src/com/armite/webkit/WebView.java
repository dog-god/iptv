/*
 * Copyright (C) 2012 armite@126.com
 *
 */
package com.armite.webkit;

import android.app.Activity;
import android.os.Bundle;
import android.content.Context;
import android.view.View;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.content.pm.ApplicationInfo;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.Surface;
import android.view.KeyEvent;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.PorterDuff.Mode;
import android.graphics.PorterDuffXfermode;

public class WebView {
    /* implementend by libarmite-webview.so */
    public static native void StartBrowser(Bitmap bitmap, String url);
    public static native void ExitBrowser();
    public static native void SendKeyEvent(int key, int unicode);
    public static native void SendMouseEvent(String type, int x, int y);
    public static native void setSpatialNavigationEnabled(boolean enable);
    public static native void setFocusRingColor(int r, int g, int b, int a);
    public static native void setFocusRingWidth(int w);
    public static native void setExtraDefaultCSS(String jstr);
    public static native void setGlobalJavaScript(String jstr);
    public static native void setUserAgentString(String jstr);
    public static native void setPluginDir(String jstr);
    public static native void setCurlTimeout(String jstr);
    public static native boolean canGoBack();
    public static native boolean goBack();
    public static native boolean canGoForward();
    public static native boolean goForward();
    public static native void stop();
    public static native void refresh();
    public static native void load(String url);
    public static native String getUrl();
    public static native boolean isFrameSet();
    public static native void sendEvent2cvm(int e);

    /* load our native library */
    static {
        try {
            System.loadLibrary("mywebkit");
        } catch (Error e) {
            Log.i("loadLibrary", "load library error:libmywebkit.so");
        }

        try {
            System.loadLibrary("armite-webview");
        } catch (Error e) {
            Log.i("loadLibrary", "load library error:libarmite-webview.so");
        }
    }

    /* this is only one instance */
    private static final String TAG = "WebView";
    private static WebView mInstance = null;
    public WebView() { }
    public static synchronized WebView getInstance() {
        if (mInstance == null) {
            mInstance = new WebView();
            Phoneme.loadCVMLib();
        }
        return mInstance;
    }

    public boolean sendKeyEvent(int KeyCode, int unicode) {
        Log.i(TAG, unicode+" sendKeyEvent:"+KeyCode);
        int vKey = KeyCode;
        switch (KeyCode) {
            case KeyEvent.KEYCODE_DPAD_LEFT:        vKey = 0x0025; unicode=0;break;
            case KeyEvent.KEYCODE_DPAD_UP:          vKey = 0x0026; unicode=0;break;
            case KeyEvent.KEYCODE_DPAD_RIGHT:       vKey = 0x0027; unicode=0;break;
            case KeyEvent.KEYCODE_DPAD_DOWN:        vKey = 0x0028; unicode=0;break;
            case KeyEvent.KEYCODE_ENTER:
            case KeyEvent.KEYCODE_DPAD_CENTER:      vKey = 0x000D; unicode=0;break;
            case KeyEvent.KEYCODE_DEL:              vKey = 0x002E; unicode=0;break;
            case KeyEvent.KEYCODE_POUND:
            case KeyEvent.KEYCODE_BACK:             vKey = 0x0008; unicode=0;break;
            case KeyEvent.KEYCODE_MEDIA_PREVIOUS:
            case KeyEvent.KEYCODE_PAGE_UP:          vKey = 0x0021; unicode=vKey;break;
            case KeyEvent.KEYCODE_MEDIA_NEXT://有些机顶盒是公用快进快退的
            case KeyEvent.KEYCODE_PAGE_DOWN:        vKey = 0x0022; unicode=vKey;break;
            case KeyEvent.KEYCODE_0:                vKey = 0x0030; unicode = '0'; break;
            case KeyEvent.KEYCODE_1:                vKey = 0x0031; unicode = '1'; break;
            case KeyEvent.KEYCODE_2:                vKey = 0x0032; unicode = '2'; break;
            case KeyEvent.KEYCODE_3:                vKey = 0x0033; unicode = '3'; break;
            case KeyEvent.KEYCODE_4:                vKey = 0x0034; unicode = '4'; break;
            case KeyEvent.KEYCODE_5:                vKey = 0x0035; unicode = '5'; break;
            case KeyEvent.KEYCODE_6:                vKey = 0x0036; unicode = '6'; break;
            case KeyEvent.KEYCODE_7:                vKey = 0x0037; unicode = '7'; break;
            case KeyEvent.KEYCODE_8:                vKey = 0x0038; unicode = '8'; break;
            case KeyEvent.KEYCODE_9:                vKey = 0x0039; unicode = '9'; break;
            
            /*
             * 对于有个网讯科技的android4.0机顶盒，他的1 是8: 2,9 ..
             */
       
            case KeyEvent.KEYCODE_POWER:            vKey = 0x0100; unicode=vKey;break;
            case KeyEvent.KEYCODE_CHANNEL_UP:       vKey = 0x0101; unicode=vKey;break;
            case KeyEvent.KEYCODE_CHANNEL_DOWN:     vKey = 0x0102; unicode=vKey;break;
            case KeyEvent.KEYCODE_VOLUME_UP:        vKey = 0x0103; unicode=vKey;break;
            case KeyEvent.KEYCODE_VOLUME_DOWN:      vKey = 0x0104; unicode=vKey;break;
            case KeyEvent.KEYCODE_MUTE:             vKey = 0x0105; unicode=vKey;break;
            case KeyEvent.KEYCODE_MEDIA_PLAY_PAUSE: vKey = 0x0107; unicode=vKey;break;
            case KeyEvent.KEYCODE_AVR_POWER:        vKey = 0x0110; unicode=vKey;break;
            case KeyEvent.KEYCODE_PROG_RED:         vKey = 0x0113; unicode=vKey;break;
            case KeyEvent.KEYCODE_PROG_GREEN:       vKey = 0x0114; unicode=vKey;break;
            case KeyEvent.KEYCODE_PROG_YELLOW:      vKey = 0x0115; unicode=vKey;break;
            case KeyEvent.KEYCODE_PROG_BLUE:        vKey = 0x0116; unicode=vKey;break;
            case KeyEvent.KEYCODE_AVR_INPUT:        vKey = 0x0118; unicode=vKey;break;
            case KeyEvent.KEYCODE_SETTINGS:         vKey = 0x0119; unicode=vKey;break;
            case KeyEvent.KEYCODE_MUSIC:            vKey = 0x011E; unicode=vKey;break;
            case KeyEvent.KEYCODE_STAR:             vKey = 0x011B; unicode=vKey;break;
            case KeyEvent.KEYCODE_GUIDE:            vKey = 0x0117; unicode=vKey;break;
            case KeyEvent.KEYCODE_HOME:             vKey = 0x011F; unicode=vKey;break;
            case KeyEvent.KEYCODE_MENU:             vKey = 0x0121; unicode=vKey;break;
        }
        Log.i(TAG, unicode+" sendKeyEvent Target:"+vKey+" unicode:"+unicode);
        SendKeyEvent(vKey, unicode);
        return true;
    }

    //update window surface
    public interface WindowExpose {
        void updateWindow(int x, int y, int w, int h);
    }
    private WindowExpose mWindowExpose = null;
    public void setWindowExpose(WindowExpose expose) {
        if (mWindowExpose == null)
            mWindowExpose = expose;
    }
    private void updateWindow(int x, int y, int w, int h) {
        if (mWindowExpose == null)
            Log.i(TAG, "WindowExpose interface not set");
        else
            mWindowExpose.updateWindow(x, y, w, h);
    }

    private void alert(String msg) {
        Log.i(TAG, "WebView alert:"+msg);
    }

    private boolean confirm(String msg) {
        Log.i(TAG, "WebView confirm:"+msg);
        return true;
    }

    private boolean prompt(String msg) {
        Log.i(TAG, "WebView prompt:"+msg);
        return true;
    }
}




