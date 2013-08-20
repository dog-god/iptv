/*
* Copyright (c) 2011 armite. All rights reserved.
*
*/


#include <stdlib.h>
#include <unistd.h>

#include "browser.h"
#include "VirtualKeyboardCodes.h"
#include "cairo.h"

#include <SDL/SDL.h>
static SDL_Surface *screen = NULL;
static SDL_Surface *sdl_surface = NULL;
static SDL_Thread *thread = NULL;

typedef struct eventMapStruct{
    unsigned int keycode;
    char vkey;
    unsigned int unicode;
}eventMapStruct;

static eventMapStruct eventMap[] = {
    {SDLK_UP,VK_UP,0},
    {SDLK_DOWN,VK_DOWN,0},
    {SDLK_LEFT,VK_LEFT,0},
    {SDLK_RIGHT,VK_RIGHT,0},
    {SDLK_RETURN,VK_RETURN,0},
    {SDLK_ESCAPE,VK_ESCAPE,0},
    {SDLK_BACKSPACE,VK_BACK,0},
    {SDLK_TAB,VK_TAB,0},
    {SDLK_a,VK_A,'a'},
    {SDLK_b,VK_B,'b'},
    {SDLK_c,VK_C,'c'},
    {SDLK_d,VK_D,'d'},
    {SDLK_e,VK_E,'e'},
    {SDLK_f,VK_F,'f'},
    {SDLK_g,VK_G,'g'},
    {SDLK_h,VK_H,'h'},
    {SDLK_i,VK_I,'i'},
    {SDLK_j,VK_J,'j'},
    {SDLK_k,VK_K,'k'},
    {SDLK_l,VK_I,'l'},
    {SDLK_m,VK_J,'m'},
    {SDLK_n,VK_K,'n'},
    {SDLK_o,VK_O,'o'},
    {SDLK_p,VK_P,'p'},
    {SDLK_q,VK_Q,'q'},
    {SDLK_r,VK_R,'r'},
    {SDLK_s,VK_S,'s'},
    {SDLK_t,VK_T,'t'},
    {SDLK_u,VK_U,'u'},
    {SDLK_v,VK_V,'v'},
    {SDLK_w,VK_W,'w'},
    {SDLK_x,VK_X,'x'},
    {SDLK_y,VK_Y,'y'},
    {SDLK_z,VK_Z,'z'},
    {SDLK_0,VK_0,'0'},
    {SDLK_1,VK_1,'1'},
    {SDLK_2,VK_2,'2'},
    {SDLK_3,VK_3,'3'},
    {SDLK_4,VK_4,'4'},
    {SDLK_5,VK_5,'5'},
    {SDLK_6,VK_6,'6'},
    {SDLK_7,VK_7,'7'},
    {SDLK_8,VK_8,'8'},
    {SDLK_9,VK_9,'9'},
    {0,0,0}
};

int RemoteThreadStart(void *ptr)
{
    while (1) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if (SDL_KEYDOWN == event.type){
                for(int i=0;;i++){
                    if (eventMap[i].keycode == 0)
                        break;
                    if (eventMap[i].keycode == event.key.keysym.sym){
                        BrowserSendKeyboardEvent(eventMap[i].vkey, eventMap[i].unicode);
                        break;
                    }
                }
            } else if(SDL_MOUSEBUTTONDOWN == event.type) {
                BrowserSendMouseEvent("mouse-down", event.button.x, event.button.y);
            } else if(SDL_MOUSEBUTTONUP == event.type) {
                BrowserSendMouseEvent("mouse-up", event.button.x, event.button.y);
            } else if(SDL_MOUSEMOTION == event.type) {
                BrowserSendMouseEvent("mouse-move", event.button.x, event.button.y);
            } else if(SDL_QUIT == event.type)
                BrowserSendExitEvent();
        }
    }
}

ArmiteSurface* GraphicsDriverInit(int width, int height)
{
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        return NULL;
    screen = SDL_SetVideoMode(width, height, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
    sdl_surface = SDL_CreateRGBSurface(0, width, height, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
    return cairo_image_surface_create_for_data((unsigned char*)sdl_surface->pixels, CAIRO_FORMAT_ARGB32, width, height, sdl_surface->pitch);
}

void GraphicsDriverExpose(int x, int y, int w, int h)
{
    SDL_BlitSurface(sdl_surface, NULL, screen, NULL);
    SDL_Flip(screen);
}

void RemoterDriverInit()
{
    thread = SDL_CreateThread(RemoteThreadStart, (void *)NULL);
}


