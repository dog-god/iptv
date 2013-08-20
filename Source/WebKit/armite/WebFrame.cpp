/*
 * Copyright (C) 2012 armite@126.com.
 *
 */

#include "config.h"
#include "WebFrame.h"
#include <string.h>

#include "FrameLoaderClientArmite.h"
#include "WebView.h"
#include "WebUtils.h"

#include <FrameLoader.h>
#include <FrameLoadRequest.h>
#include <Frame.h>
#include <Page.h>

using namespace WebCore;
using namespace HTMLNames;

WebFrame::WebFrame()
    : m_webview(0)
    , m_frame(0)
    , m_loadClient(0)
{
}

WebFrame::~WebFrame()
{
    if (core(this))
        core(this)->loader()->cancelAndClear();
}

WebFrame* WebFrame::createInstance()
{
    WebFrame* instance = new WebFrame();
    return instance;
}

void WebFrame::stop()
{
    Frame* coreFrame = core(this);
    if (!coreFrame)
        return;
    coreFrame->loader()->stopForUserCancel();
}

void WebFrame::reload()
{
    Frame* coreFrame = core(this);
    if (!coreFrame)
        return;
    coreFrame->loader()->reload();
}

void WebFrame::loadURL(const char* url)
{
    Frame* coreFrame = core(this);
    if (!coreFrame)
        return;
    coreFrame->loader()->load(ResourceRequest(KURL(KURL(), String::fromUTF8(url))), false);
}

Frame* WebFrame::init(WebView* webView, Page* page, HTMLFrameOwnerElement* ownerElement)
{
    m_webview = webView;
    if (!m_loadClient)
        m_loadClient = new FrameLoaderClientArmite(this);

    RefPtr<Frame> frameRef;
    frameRef = Frame::create(page, ownerElement, m_loadClient);
    m_frame = frameRef.get();
    m_frame->init();
    return m_frame;
}

WebFrame* kit(Frame* frame)
{
    if (!frame)
        return 0;

    FrameLoaderClient* frameLoaderClient = frame->loader()->client();
    if (frameLoaderClient)
        return static_cast<FrameLoaderClientArmite*>(frameLoaderClient)->webFrame();
    return 0;
}

Frame* core(WebFrame* webFrame)
{
    if (!webFrame)
        return 0;
    return webFrame->m_frame;
}

Frame* core(const WebFrame* webFrame)
{
    if (!webFrame)
        return 0;
    return const_cast<WebFrame*>(webFrame)->m_frame;
}





