/*
 * Copyright (C) 2012 armite.
 *
 */

#ifndef WebView_H
#define WebView_H

#include "WebKitTypes.h"
#ifdef ANDROID
#include <jni.h>
#endif

class WebViewPrivate;
class WebFrame;
class WebChromeClient;
class WebEditorClient;

namespace WebCore {
    class Page;
    class DocumentLoader;
}

typedef void (*GraphicExpose)(int, int, int, int);

class EXPORT WebView {
public:
    WebViewPrivate *webViewPrivate() const { return d; }
    static WebView* getStaticInstance();
    virtual ~WebView();

    void initGraphic(ArmiteSurface*, ArmiteRect&, GraphicExpose);
    void startBrowser(const char*);
    void sendEvent2Browser(ArmiteEvent*);

#ifdef ANDROID
    JNIEnv* getJavaEnv();
    JavaVM* getJavaVM() { return m_javaVM; }
    void setJavaVM(JavaVM *javaVM) { m_javaVM = javaVM; }
    void setJavaWebView(jclass clazz, jobject object) { m_class = clazz; m_object = object; }
    void sendEvent2cvm(unsigned char event);
#endif

    const char *getUserAgentString() { return  m_userAgent ? m_userAgent : "armite(webkit)"; }
    void setUserAgentString(const char *ua) { m_userAgent = ua; }

    void setSpatialNavigationEnabled(bool);
    void setFocusRingColor(int r, int g, int b, int a);
    void setFocusRingWidth(int w);
    void setExtraDefaultCSS(const char *str);
    void setGlobalJavaScript(const char *str);

    void javaScriptAlert(const char* message);
    bool javaScriptConfirm(const char* message);
    bool javaScriptPrompt(const char* message);

    bool canGoBack();
    bool goBack();
    bool canGoForward();
    bool goForward();
    void stop();
    void refresh();
    void load(const char *);
    void getUrl(const uint16_t* &url, int &len);

    bool isMainFrameSet();
protected:
    WebView();

private:
    friend class WebViewPrivate;
    WebViewPrivate* d;

    WebCore::Page* m_mainPage;
    WebFrame* m_mainFrame;

    const char *m_userAgent;
#ifdef ANDROID
    JavaVM* m_javaVM;
    jclass m_class;
    jobject m_object;

    jmethodID m_alertMethodID;
    jmethodID m_confirmMethodID;
    jmethodID m_promptMethodID;
#endif
};

#endif



