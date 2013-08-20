/*
* Copyright (C) 2012 armite@126.com.
*/

#include <stdlib.h>
#include <string.h>
#include "browser.h"

//#define Home_Url "http://www.baidu.com/"
//#define Home_Url "http://localhost:8080/input.html"
#define Home_Url "http://localhost:8080/index.html"
//#define Home_Url "http://182.138.31.29:8080/cnrHdEpg/page/search/index.do"
//#define Home_Url "file:///home/armite/www/sms/test.html"

static WebView* browserWebView = NULL;
int main (int argc, char* argv[])
{
    const char * url = 0;
    int quit = 0;

    if(argc > 2)
        url = argv[2];
    else if(argc > 1)
        url = argv[1];
    else
        url = Home_Url;

    ArmiteRect rect = {0, 0, 1280, 720};
    browserWebView = WebView::getStaticInstance();
    ArmiteSurface* surface = GraphicsDriverInit(rect.w, rect.h);

    RemoterDriverInit();
    browserWebView->initGraphic(surface, rect, GraphicsDriverExpose);
    browserWebView->setUserAgentString("Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/536.6 (KHTML, like Gecko) Chrome/20.0.1092.0 Safari/536.6");
    browserWebView->setSpatialNavigationEnabled(true);
    browserWebView->setFocusRingColor(255, 0, 0, 255);
    browserWebView->setFocusRingWidth(10);
    browserWebView->startBrowser(url);

    browserWebView = 0;
    return 0;
}

int BrowserSendExitEvent()
{
    ArmiteEvent event;
    event.type = ARMITE_BROWSER_EXIT;
    if (browserWebView)
        browserWebView->sendEvent2Browser(&event);
    return 0;
}

int BrowserSendKeyboardEvent(char vkey, int unicode)
{
    ArmiteEvent event;
    event.type = ARMITE_KEYBOARDEVENT;
    event.data.key.vkey = vkey;
    event.data.key.unicode = unicode;
    if (browserWebView)
        browserWebView->sendEvent2Browser(&event);
    return 0;
}

static int BrowserSendMouseEvent(char type, int x, int y)
{
    ArmiteEvent event;
    event.type = ARMITE_MOUSEEVENT;
    event.data.mouse.type = type;
    event.data.mouse.x = x;
    event.data.mouse.y = y;
    if(browserWebView)
        browserWebView->sendEvent2Browser(&event);
    return 0;
}

int BrowserSendMouseEvent(const char *type, int x, int y)
{
    if(!strcmp(type, "mouse-down"))
        BrowserSendMouseEvent(ARMITE_MOUSEEVENT_DOWN, x, y);
    else if(!strcmp(type, "mouse-up"))
        BrowserSendMouseEvent(ARMITE_MOUSEEVENT_UP, x, y);
    else if(!strcmp(type, "mouse-move"))
        BrowserSendMouseEvent(ARMITE_MOUSEEVENT_MOVE, x, y);
}






