/*
 * Copyright (C) 2012 armite@126.com
 */

#include "config.h"
#include "Widget.h"

#include "ChromeClient.h"
#include "Cursor.h"
#include "Frame.h"
#include "FrameView.h"
#include "GraphicsContext.h"
#include "IntRect.h"
#include "NotImplemented.h"
#include "Page.h"
#include "WebView.h"
#include "WebViewPrivate.h"

#include <wtf/HashMap.h>
#include <wtf/text/CString.h>

namespace WebCore {

Widget::Widget(PlatformWidget widget)
    : m_parent(0)
    , m_widget(0)
    , m_selfVisible(false)
    , m_parentVisible(false)
    , m_frame(0, 0, 0, 0)
{
    init(widget);
}

Widget::~Widget()
{
}

IntRect Widget::frameRect() const
{
    return m_frame;
}

void Widget::setFrameRect(const IntRect& rect)
{
    m_frame = rect;
    Widget::frameRectsChanged();
}

void Widget::setFocus(bool focused)
{
    notImplemented();
}

void Widget::setCursor(const Cursor& cursor)
{
    notImplemented();
}

void Widget::show()
{
    notImplemented();
}

void Widget::hide()
{
    notImplemented();
}

void Widget::paint(GraphicsContext* context, const IntRect&)
{
    notImplemented();
}

void Widget::setIsSelected(bool)
{
    notImplemented();
}

}



