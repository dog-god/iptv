/*
 * Copyright (C) 2012 armite@126.com. All Rights Reserved.
 *
 */

#include "config.h"
#include "PluginView.h"

#include "Document.h"
#include "DocumentLoader.h"
#include "Element.h"
#include "EventNames.h"
#include "FrameLoader.h"
#include "FrameLoadRequest.h"
#include "FrameTree.h"
#include "Frame.h"
#include "FrameView.h"
#include "GraphicsContext.h"
#include "Image.h"
#include "HTMLNames.h"
#include "HTMLPlugInElement.h"
#include "KeyboardEvent.h"
#include "MouseEvent.h"
#include "NotImplemented.h"
#include "Page.h"
#include "PlatformMouseEvent.h"
#include "PluginDebug.h"
#include "PluginPackage.h"
#include "Settings.h"
#include "JSDOMBinding.h"
#include "ScriptController.h"
#include "npruntime_impl.h"
#include "runtime_root.h"
#include "NotImplemented.h"

#include <sys/stat.h>
#include <fcntl.h>
#if USE(JSC)
#include "BridgeJSC.h"
#include <runtime/JSObject.h>
#endif

using namespace WTF;

namespace WebCore {

void PluginView::setFocus(bool)
{
    notImplemented();
}

void PluginView::show()
{
    notImplemented();
    setSelfVisible(true);
}

void PluginView::hide()
{
    notImplemented();
    setSelfVisible(false);
}

void PluginView::paint(GraphicsContext*, const IntRect&)
{
    notImplemented();
}

void PluginView::handleKeyboardEvent(KeyboardEvent* event)
{
    NPEvent npEvent;

    if (!m_plugin->pluginFuncs()->event(m_instance, &npEvent))
        event->setDefaultHandled();
}

void PluginView::handleMouseEvent(MouseEvent*)
{
    notImplemented();
}

void PluginView::setParent(ScrollView* parent)
{
    Widget::setParent(parent);
    if (parent)
        init();
}

void PluginView::setNPWindowRect(const IntRect& rect)
{
    if (!m_isStarted || !parent())
        return;

    IntPoint p = static_cast<FrameView*>(parent())->contentsToWindow(rect.location());
    m_npWindow.x = p.x();
    m_npWindow.y = p.y();

    m_npWindow.width = rect.width();
    m_npWindow.height = rect.height();

    m_npWindow.clipRect.left = 0;
    m_npWindow.clipRect.top = 0;
    m_npWindow.clipRect.right = rect.width();
    m_npWindow.clipRect.bottom = rect.height();

    if (m_npWindow.x < 0 || m_npWindow.y < 0 || m_npWindow.width <= 0 || m_npWindow.height <= 0)
        return;

    if (m_plugin->pluginFuncs()->setwindow) {
        PluginView::setCurrentPluginView(this);
        setCallingPlugin(true);
        m_plugin->pluginFuncs()->setwindow(m_instance, &m_npWindow);
        setCallingPlugin(false);
        PluginView::setCurrentPluginView(0);
    }
}

#if ENABLE(NETSCAPE_PLUGIN_API)
NPError PluginView::handlePostReadFile(Vector<char>&, uint32_t, const char*)
{
    notImplemented();
    return 0;
}

bool PluginView::platformGetValue(NPNVariable, void*, NPError*)
{
    notImplemented();
    return false;
}

bool PluginView::platformGetValueStatic(NPNVariable, void*, NPError*)
{
    notImplemented();
    return false;
}

void PluginView::invalidateRect(NPRect*)
{
    notImplemented();
}
#endif

void PluginView::invalidateRect(const IntRect&)
{
    notImplemented();
}

#if ENABLE(NETSCAPE_PLUGIN_API)
void PluginView::invalidateRegion(NPRegion)
{
    notImplemented();
}
#endif

void PluginView::forceRedraw()
{
    notImplemented();
}

bool PluginView::platformStart()
{
    return true;
}

void PluginView::platformDestroy()
{
    notImplemented();
}

void PluginView::setParentVisible(bool)
{
    notImplemented();
}

bool PluginView::dispatchNPEvent(NPEvent& event)
{
    // sanity check
    if (!m_plugin->pluginFuncs()->event)
        return true;

    PluginView::setCurrentPluginView(this);
    JSC::JSLock::DropAllLocks dropAllLocks(JSDOMWindowBase::commonJSGlobalData());
    setCallingPlugin(true);

    bool accepted = m_plugin->pluginFuncs()->event(m_instance, &event);

    setCallingPlugin(false);
    PluginView::setCurrentPluginView(0);
    return accepted;
}

void PluginView::setNPWindowIfNeeded()
{
    if (!m_isStarted || !parent() || !m_plugin->pluginFuncs()->setwindow)
        return;

    // On Unix, only call plugin if it's full-page or windowed
    if (m_mode != NP_FULL && m_mode != NP_EMBED)
        return;

    // FLASH WORKAROUND: Only set initially. Multiple calls to
    // setNPWindow() cause the plugin to crash.
    if (m_npWindow.width == -1 || m_npWindow.height == -1) {
        m_npWindow.width = m_windowRect.width();
        m_npWindow.height = m_windowRect.height();
    }

    m_npWindow.x = m_windowRect.x();
    m_npWindow.y = m_windowRect.y();
    m_npWindow.width = m_windowRect.width();
    m_npWindow.height = m_windowRect.height();

    m_npWindow.clipRect.left = m_clipRect.x();
    m_npWindow.clipRect.top = m_clipRect.y();
    m_npWindow.clipRect.right = m_clipRect.width();
    m_npWindow.clipRect.bottom = m_clipRect.height();

    PluginView::setCurrentPluginView(this);
    JSC::JSLock::DropAllLocks dropAllLocks(JSDOMWindowBase::commonJSGlobalData());
    setCallingPlugin(true);
    m_plugin->pluginFuncs()->setwindow(m_instance, &m_npWindow);
    setCallingPlugin(false);
    PluginView::setCurrentPluginView(0);
}

void PluginView::updatePluginWidget()
{
    if (!parent() || !m_isWindowed)
        return;

    ASSERT(parent()->isFrameView());
    FrameView* frameView = static_cast<FrameView*>(parent());

    IntRect oldWindowRect = m_windowRect;
    IntRect oldClipRect = m_clipRect;

    m_windowRect = IntRect(frameView->contentsToWindow(frameRect().location()), frameRect().size());
    m_clipRect = windowClipRect();
    m_clipRect.move(-m_windowRect.x(), -m_windowRect.y());

    if (platformPluginWidget() && (m_windowRect != oldWindowRect || m_clipRect != oldClipRect))
        setNPWindowIfNeeded();
}

#if defined(XP_UNIX) && ENABLE(NETSCAPE_PLUGIN_API)
void PluginView::handleFocusInEvent()
{
    notImplemented();
}

void PluginView::handleFocusOutEvent()
{
    notImplemented();
}
#endif

} // namespace WebCore




