/*
 * Copyright (C) 2012 armite@126.com.
 *
 */

#include "config.h"
#include "ChromeClientArmite.h"

#include "WebFrame.h"
#include "WebView.h"
#include "WebViewPrivate.h"

#include <wtf/text/WTFString.h>
#include <ContextMenu.h>
#include <Console.h>
#include <FileChooser.h>
#include <FloatRect.h>
#include <Frame.h>
#include <FrameLoadRequest.h>
#include <FrameView.h>
#include <HTMLNames.h>
#include <Icon.h>
#include <IntRect.h>
#include <NotImplemented.h>
#include <Page.h>
#include <WindowFeatures.h>

using namespace WebCore;

ChromeClientArmite::ChromeClientArmite(WebView* webView)
    : m_webView(webView)
#if ENABLE(NOTIFICATIONS)
    , m_notificationsDelegate(new WebDesktopNotificationsDelegate(webView))
#endif
{
}

ChromeClientArmite::~ChromeClientArmite()
{
}

void ChromeClientArmite::chromeDestroyed()
{
}

void ChromeClientArmite::setWindowRect(const FloatRect& r)
{
    notImplemented();
}

FloatRect ChromeClientArmite::windowRect()
{
    return pageRect();
}

FloatRect ChromeClientArmite::pageRect()
{
    return FloatRect(m_webView->webViewPrivate()->frameRect());
}

float ChromeClientArmite::scaleFactor()
{
    return 1.0;
}

void ChromeClientArmite::focus()
{
    notImplemented();
}

void ChromeClientArmite::unfocus()
{
    notImplemented();
}

bool ChromeClientArmite::canTakeFocus(FocusDirection direction)
{
    notImplemented();
    return false;
}

void ChromeClientArmite::takeFocus(FocusDirection direction)
{
    notImplemented();
}

void ChromeClientArmite::focusedNodeChanged(WebCore::Node*)
{
    notImplemented();
}

Page* ChromeClientArmite::createWindow(Frame*, const FrameLoadRequest& frameLoadRequest, const WindowFeatures& features, const WebCore::NavigationAction&)
{
    notImplemented();
    return NULL;
}

void ChromeClientArmite::show()
{
    notImplemented();
}

bool ChromeClientArmite::canRunModal()
{
    return false;
}

void ChromeClientArmite::runModal()
{
    notImplemented();
}

void ChromeClientArmite::setToolbarsVisible(bool visible)
{
    notImplemented();
}

bool ChromeClientArmite::toolbarsVisible()
{
    return false;
}

void ChromeClientArmite::setStatusbarVisible(bool visible)
{
    notImplemented();
}

bool ChromeClientArmite::statusbarVisible()
{
    return false;
}

void ChromeClientArmite::setScrollbarsVisible(bool b)
{
    notImplemented();
}

bool ChromeClientArmite::scrollbarsVisible()
{
    return false;
}

void ChromeClientArmite::setMenubarVisible(bool visible)
{
    notImplemented();
}

bool ChromeClientArmite::menubarVisible()
{
    return false;
}

void ChromeClientArmite::setResizable(bool resizable)
{
    notImplemented();
}

void ChromeClientArmite::addMessageToConsole(MessageSource source, MessageType type, MessageLevel level, const String& message, unsigned line, const String& url)
{
    switch(level){
        case TipMessageLevel:
            LOGI("[tip][%s]\n",message.utf8().data());
            break;
        case LogMessageLevel:
            LOGI("[log][%s]\n",message.utf8().data());
            break;
        case WarningMessageLevel:
            LOGI("[warning][%s]\n",message.utf8().data());
            break;
        case ErrorMessageLevel:
            LOGI("[error][%s]\n",message.utf8().data());
            LOGI("[%s][%d]\n",url.utf8().data(), line);
            m_webView->webViewPrivate()->errorMsg(message.utf8().data(), url.utf8().data(), line);
            break;
        case DebugMessageLevel:
            LOGI("[debug][%s]\n",message.utf8().data());
            LOGI("[%s][%d]\n",url.utf8().data(), line);
            break;
        default:
            LOGI("[info][%s]\n",message.utf8().data());
    }
}

bool ChromeClientArmite::canRunBeforeUnloadConfirmPanel()
{
    return false;
}

bool ChromeClientArmite::runBeforeUnloadConfirmPanel(const String& message, Frame* frame)
{
    return false;
}

void ChromeClientArmite::closeWindowSoon()
{
    notImplemented();
}

void ChromeClientArmite::runJavaScriptAlert(Frame* frame, const String& message)
{
    m_webView->javaScriptAlert(message.utf8().data());
}

bool ChromeClientArmite::runJavaScriptConfirm(Frame *frame, const String& message)
{
    return m_webView->javaScriptConfirm(message.utf8().data());
}

bool ChromeClientArmite::runJavaScriptPrompt(Frame *frame, const String& message, const String& defaultValue, String& result)
{
    return m_webView->javaScriptPrompt(message.utf8().data());
}

void ChromeClientArmite::setStatusbarText(const String& statusText)
{
    notImplemented();
}

bool ChromeClientArmite::shouldInterruptJavaScript()
{
    return false;
}

bool ChromeClientArmite::tabsToLinks() const
{
    return false;
}

IntRect ChromeClientArmite::windowResizerRect() const
{
    notImplemented();
    return IntRect();
}

void ChromeClientArmite::invalidateRootView(const IntRect& windowRect, bool immediate)
{
    m_webView->webViewPrivate()->repaint(windowRect, false /*contentChanged*/, immediate, false /*repaintContentOnly*/);
}

void ChromeClientArmite::invalidateContentsAndRootView(const IntRect& windowRect, bool immediate)
{
    m_webView->webViewPrivate()->repaint(windowRect, true /*contentChanged*/, immediate /*immediate*/, false /*repaintContentOnly*/);
}

void ChromeClientArmite::invalidateContentsForSlowScroll(const IntRect& windowRect, bool immediate)
{
    m_webView->webViewPrivate()->repaint(windowRect, true /*contentChanged*/, immediate, true /*repaintContentOnly*/);
}

void ChromeClientArmite::scroll(const IntSize& delta, const IntRect& scrollViewRect, const IntRect& clipRect)
{
    notImplemented();
}

IntRect ChromeClientArmite::rootViewToScreen(const IntRect& rect) const
{
    notImplemented();
    return rect;
}

PlatformPageClient ChromeClientArmite::platformPageClient() const
{
    notImplemented();
    return 0;
}

void ChromeClientArmite::contentsSizeChanged(Frame*, const IntSize&) const
{
    notImplemented();
}

void ChromeClientArmite::mouseDidMoveOverElement(const HitTestResult& result, unsigned modifierFlags)
{
    notImplemented();
}

void ChromeClientArmite::setToolTip(const String& toolTip, TextDirection)
{
    notImplemented();
}

void ChromeClientArmite::print(Frame* frame)
{
    notImplemented();
}

void ChromeClientArmite::exceededDatabaseQuota(Frame* frame, const String& databaseIdentifier)
{
    notImplemented();
}

void ChromeClientArmite::populateVisitedLinks()
{
    notImplemented();
}

bool ChromeClientArmite::paintCustomScrollbar(GraphicsContext* context, const FloatRect& rect, ScrollbarControlSize size,
                                        ScrollbarControlState state, ScrollbarPart pressedPart, bool vertical,
                                        float value, float proportion, ScrollbarControlPartMask parts)
{
    notImplemented();
    return false;
}

bool ChromeClientArmite::paintCustomScrollCorner(GraphicsContext* context, const FloatRect& rect)
{
    notImplemented();
    return false;
}
void ChromeClientArmite::runOpenPanel(Frame*, PassRefPtr<FileChooser> prpFileChooser)
{
    notImplemented();
}

void ChromeClientArmite::chooseIconForFiles(const Vector<WTF::String>& filenames, WebCore::FileChooser* chooser)
{
    notImplemented();
}

void ChromeClientArmite::setCursor(const WebCore::Cursor& cursor)
{
    notImplemented();
}

IntPoint ChromeClientArmite::screenToRootView(const WebCore::IntPoint& p) const 
{
    return p;
}

void ChromeClientArmite::requestGeolocationPermissionForFrame(Frame* frame, Geolocation* geolocation)
{
    notImplemented();
}

void ChromeClientArmite::scrollbarsModeDidChange() const
{
    notImplemented();
}

#if USE(ACCELERATED_COMPOSITING)
void ChromeClientArmite::scheduleCompositingLayerSync()
{
    notImplemented();
}

void ChromeClientArmite::attachRootGraphicsLayer(WebCore::Frame* frame, WebCore::GraphicsLayer* layer)
{
    notImplemented();
}

void ChromeClientArmite::setNeedsOneShotDrawingSynchronization()
{
    notImplemented();
}
#endif

#if ENABLE(VIDEO)

bool ChromeClientArmite::supportsFullscreenForNode(const Node* node)
{
    return node->hasTagName(HTMLNames::videoTag);
}

void ChromeClientArmite::enterFullscreenForNode(Node* node)
{
    notImplemented();
}

void ChromeClientArmite::exitFullscreenForNode(Node*)
{
    notImplemented();
}

#endif

#if ENABLE(TOUCH_EVENTS)
void ChromeClientArmite::needTouchEvents(bool)
{
    notImplemented();
}
#endif




