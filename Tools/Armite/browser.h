/*
* Copyright (c) 2012 armite@126.com.
*
*/


#ifndef BROWSER_H
#define BROWSER_H

#include "WebView.h"

ArmiteSurface* GraphicsDriverInit(int width, int height);
void GraphicsDriverExpose(int x, int y, int w, int h);

void RemoterDriverInit();
int BrowserSendKeyboardEvent(char vkey, int unicode);
int BrowserSendMouseEvent(const char *type, int x, int y);
int BrowserSendExitEvent();

#endif


