/*
 * Copyright (C) 2012 armite@126.com.
 *
 */
#ifndef WebViewPrivate_H
#define WebViewPrivate_H

#include "cairo.h"
#include "WebKitTypes.h"
#include "Frame.h"
#include "FrameView.h"
#include "IntRect.h"
#include "WebView.h"
#include "ChromeClientArmite.h"
#include "EditorClientArmite.h"
#include "PropertyName.h"
#include "PropertySlot.h"

class WebViewPrivate {
public:
    WebViewPrivate(WebView *webView);
    ~WebViewPrivate();

    WebCore::IntRect frameRect() { return m_rect; }
    void setFrameRect(ArmiteRect& r) { m_rect = WebCore::IntRect(r); }
    void setWebRect(const WebCore::IntRect& r);

    WebCore::IntRect dirtyRegion() { return m_backingStoreDirtyRegion; }
    void addToDirtyRegion(const WebCore::IntRect& dirtyRect)
    {
        m_backingStoreDirtyRegion.unite(dirtyRect);
    }
    void clearDirtyRegion()
    {
        m_backingStoreDirtyRegion.setX(0);
        m_backingStoreDirtyRegion.setY(0);
        m_backingStoreDirtyRegion.setWidth(0);
        m_backingStoreDirtyRegion.setHeight(0);
    }

    bool onKeyDown(ArmiteKeyboardEvent &event);
    bool onMouseEvent(ArmiteMouseEvent &event);

    ArmiteRect onExpose(ArmiteExposeEvent &event);
    void sendExposeEvent(WebCore::IntRect&);
    void repaint(const WebCore::IntRect&, bool contentChanged, bool immediate = false, bool repaintContentOnly = false);

    void fireWebKitTimerEvents();
    void fireWebKitThreadEvents();
    double getNextSharedTimerFireTime();

    void initViewWindow(ArmiteSurface*, GraphicExpose);

    ChromeClientArmite* chromeClient() { return m_chromeClient; }
    EditorClientArmite* editorClient() { return m_editorClient; }
    void initDefalultSetting(Settings* settings);

    void committedLoad(WebCore::DocumentLoader* loader, const char* data, int length);
    void beforeDownloadResource(WebCore::DocumentLoader* loader, WebCore::ResourceRequest& request);
    void afterDownloadResource(WebCore::DocumentLoader* loader, WebCore::ResourceLoader* resource);
    void errorMsg(const char *msg, const char *url, int line);

    void inputMethod(WTF::String &value);

    static bool getPluginJSValue(WebCore::JSDOMWindow* thisObject, JSC::ExecState* exec, JSC::PropertyName propertyName, JSC::PropertySlot& slot);

private:
    void updateView(WebCore::IntRect& rect);

    ChromeClientArmite* m_chromeClient; 
    EditorClientArmite* m_editorClient;

    WebView* m_webView;
    WebCore::IntRect m_rect;
    WebCore::IntRect m_webRect;
    WebCore::IntRect m_backingStoreDirtyRegion;
    cairo_t* m_cairo;
    GraphicExpose m_expose;
    bool m_isStoreResource;
    bool m_isHookHtml;
#ifdef ANDROID
    JNIEnv* m_jniEnv;
    jclass m_class;
    jobject m_object;

    jmethodID m_isHookMethodID;
    jmethodID m_isStoreMethodID;
    jmethodID m_hookMethodID;
    jmethodID m_startHtmlMethodID;
    jmethodID m_endHtmlMethodID;
    jmethodID m_startResMethodID;
    jmethodID m_endResMethodID;
    jmethodID m_storeResourceMethodID;
    jmethodID m_errorMsgToConsole;
    jmethodID m_inputMethod;
#endif
};


#endif



