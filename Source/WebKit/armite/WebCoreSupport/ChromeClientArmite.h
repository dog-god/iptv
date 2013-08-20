/*
 * Copyright (C) 2012 armite@126.com.
 *
 */

#ifndef ChromeClientArmite_H
#define ChromeClientArmite_H

#include <ChromeClient.h>
#include <FocusDirection.h>
#include <GraphicsContext.h>
#include <ScrollTypes.h>
#include <wtf/Forward.h>

class WebDesktopNotificationsDelegate;
class WebView;

namespace WebCore {
    class Geolocation;
#if USE(ACCELERATED_COMPOSITING)
    class GraphicsLayer;
#endif
}

using namespace WebCore;
class ChromeClientArmite : public WebCore::ChromeClient {
public:
    ChromeClientArmite(WebView*);
    ~ChromeClientArmite();

    virtual void chromeDestroyed();

    virtual void setWindowRect(const WebCore::FloatRect&);
    virtual WebCore::FloatRect windowRect();

    virtual WebCore::FloatRect pageRect();

    virtual float scaleFactor();

    virtual void focus();
    virtual void unfocus();

    virtual bool canTakeFocus(WebCore::FocusDirection);
    virtual void takeFocus(WebCore::FocusDirection);

    void focusedNodeChanged(WebCore::Node*);
    virtual void focusedFrameChanged(WebCore::Frame*){}

    virtual WebCore::Page* createWindow(WebCore::Frame*, const WebCore::FrameLoadRequest&, const WebCore::WindowFeatures&, const WebCore::NavigationAction&);
    virtual void show();

    virtual bool canRunModal();
    virtual void runModal();

    virtual void setToolbarsVisible(bool);
    virtual bool toolbarsVisible();

    virtual void setStatusbarVisible(bool);
    virtual bool statusbarVisible();

    virtual void setScrollbarsVisible(bool);
    virtual bool scrollbarsVisible();

    virtual void setMenubarVisible(bool);
    virtual bool menubarVisible();

    virtual void setResizable(bool);

    virtual void addMessageToConsole(WebCore::MessageSource source, WebCore::MessageType type, WebCore::MessageLevel level, const WTF::String& message, unsigned line, const WTF::String& url);

    virtual bool canRunBeforeUnloadConfirmPanel();
    virtual bool runBeforeUnloadConfirmPanel(const WTF::String& message, WebCore::Frame* frame);

    virtual void closeWindowSoon();

    virtual void runJavaScriptAlert(WebCore::Frame*, const WTF::String&);
    virtual bool runJavaScriptConfirm(WebCore::Frame*, const WTF::String&);
    virtual bool runJavaScriptPrompt(WebCore::Frame*, const WTF::String& message, const WTF::String& defaultValue, WTF::String& result);
    virtual void setStatusbarText(const WTF::String&);
    virtual bool shouldInterruptJavaScript();
    virtual KeyboardUIMode keyboardUIMode(){return KeyboardAccessTabsToLinks;}

    virtual bool tabsToLinks() const;
    virtual WebCore::IntRect windowResizerRect() const;

    virtual void invalidateRootView(const WebCore::IntRect&, bool);
    virtual void invalidateContentsAndRootView(const WebCore::IntRect&, bool);
    virtual void invalidateContentsForSlowScroll(const WebCore::IntRect&, bool);
    virtual void scroll(const WebCore::IntSize& scrollDelta, const WebCore::IntRect& rectToScroll, const WebCore::IntRect& clipRect);

    virtual WebCore::IntPoint screenToRootView(const WebCore::IntPoint& p) const ;
    virtual WebCore::IntRect rootViewToScreen(const WebCore::IntRect& r) const;
    virtual PlatformPageClient platformPageClient() const;
    virtual void contentsSizeChanged(WebCore::Frame*, const WebCore::IntSize&) const;

    virtual void scrollbarsModeDidChange() const;
    virtual void mouseDidMoveOverElement(const WebCore::HitTestResult&, unsigned modifierFlags);

    virtual void setToolTip(const WTF::String&, WebCore::TextDirection);

    virtual void print(WebCore::Frame*);
    virtual bool shouldRubberBandInDirection(WebCore::ScrollDirection) const {return false;}

    virtual void exceededDatabaseQuota(WebCore::Frame*, const WTF::String&);

    virtual void reachedMaxAppCacheSize(int64_t spaceNeeded) {}
    virtual void reachedApplicationCacheOriginQuota(SecurityOrigin*, int64_t totalSpaceNeeded) {}

#if ENABLE(DASHBOARD_SUPPORT)
    virtual void dashboardRegionsChanged();
#endif

    virtual void populateVisitedLinks();

    virtual bool paintCustomScrollbar(WebCore::GraphicsContext*, const WebCore::FloatRect&, WebCore::ScrollbarControlSize,
                                        WebCore::ScrollbarControlState, WebCore::ScrollbarPart pressedPart, bool vertical,
                                        float value, float proportion, WebCore::ScrollbarControlPartMask);
    virtual bool paintCustomScrollCorner(WebCore::GraphicsContext*, const WebCore::FloatRect&);

    virtual void runOpenPanel(WebCore::Frame*, PassRefPtr<WebCore::FileChooser>);
    virtual void loadIconForFiles(const Vector<String>&, WebCore::FileIconLoader*) { }

    virtual void chooseIconForFiles(const Vector<WTF::String>&, WebCore::FileChooser*);

    virtual void setCursor(const WebCore::Cursor& cursor);
    virtual void setCursorHiddenUntilMouseMoves(bool) { }

    WebView* webView() const { return m_webView; }

    virtual void formStateDidChange(const WebCore::Node*) { }

    virtual void scrollRectIntoView(const WebCore::IntRect&, const WebCore::ScrollView*) const {}

    virtual void requestGeolocationPermissionForFrame(WebCore::Frame*, WebCore::Geolocation*);
    virtual void cancelGeolocationPermissionRequestForFrame(WebCore::Frame*, WebCore::Geolocation*) { }

#if ENABLE(VIDEO)
    virtual bool supportsFullscreenForNode(const WebCore::Node*);
    virtual void enterFullscreenForNode(WebCore::Node*);
    virtual void exitFullscreenForNode(WebCore::Node*);
#endif

#if ENABLE(NOTIFICATIONS)
    virtual WebCore::NotificationPresenter* notificationPresenter() const { return reinterpret_cast<WebCore::NotificationPresenter*>(m_notificationsDelegate.get()); }
#endif

#if USE(ACCELERATED_COMPOSITING)
    // Pass 0 as the GraphicsLayer to detatch the root layer.
    virtual void attachRootGraphicsLayer(WebCore::Frame*, WebCore::GraphicsLayer*);
    // Sets a flag to specify that the next time content is drawn to the window,
    // the changes appear on the screen in synchrony with updates to GraphicsLayers.
    virtual void setNeedsOneShotDrawingSynchronization();
    // Sets a flag to specify that the view needs to be updated, so we need
    // to do an eager layout before the drawing.
    virtual void scheduleCompositingLayerSync();
#endif

#if ENABLE(TOUCH_EVENTS)
    virtual void needTouchEvents(bool);
#endif

    virtual bool selectItemWritingDirectionIsNatural(){return false;}
    virtual bool selectItemAlignmentFollowsMenuWritingDirection(){return false;}
    virtual bool hasOpenedPopup() const{return false;}
    virtual PassRefPtr<PopupMenu> createPopupMenu(PopupMenuClient*) const {return NULL;}
    virtual PassRefPtr<SearchPopupMenu> createSearchPopupMenu(PopupMenuClient*) const {return NULL;}

    virtual void numWheelEventHandlersChanged(unsigned){}
    virtual void numTouchEventHandlersChanged(unsigned){}

private:
    WebView* m_webView;
#if ENABLE(NOTIFICATIONS)
    OwnPtr<WebDesktopNotificationsDelegate> m_notificationsDelegate;
#endif
};

#endif //ChromeClientArmite_H



