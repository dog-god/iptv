/*
 * Copyright (C) 2012 armite@126.com.
 *
 */

#ifndef WebFrame_H
#define WebFrame_H

#include "WebKitTypes.h"

namespace WebCore {
    class Frame;
    class HTMLFrameOwnerElement;
    class Page;
}

class WebFrame;
class FrameLoaderClientArmite;
class WebView;

WebFrame* kit(WebCore::Frame*);
WebCore::Frame* core(WebFrame*);

class EXPORT WebFrame {
public:
    static WebFrame* createInstance();
    virtual ~WebFrame();

    WebView* webView() const { return m_webview; }
    void loadURL(const char* url);
    void stop();
    void reload();

protected:
    WebFrame();

private:
    friend WebCore::Frame* core(WebFrame*);
    friend WebCore::Frame* core(const WebFrame*);
    friend class WebView;
    friend class WebViewPrivate;
    friend class FrameLoaderClientArmite;

    WebCore::Frame* init(WebView*, WebCore::Page*, WebCore::HTMLFrameOwnerElement*);

    WebView* m_webview;
    WebCore::Frame* m_frame;
    FrameLoaderClientArmite* m_loadClient;
};

#endif



