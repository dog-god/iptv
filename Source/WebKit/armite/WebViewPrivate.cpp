/*
 * Copyright (C) 2012 armite@126.com.
 *
 */

#include "config.h"
#include "WebViewPrivate.h"
#include "IntRect.h"
#include "FrameView.h"
#include "Frame.h"
#include "GraphicsContext.h"
#include "Page.h"
#include "EventHandler.h"
#include "FocusController.h"
#include "HitTestResult.h"
#include "HitTestRequest.h"
#include <wtf/MainThread.h>
#include <PlatformKeyboardEvent.h>
#include <SharedTimer.h>
#include "Editor.h"
#include "PopupMenu.h"
#include "WebFrame.h"
#include "WebView.h"
#include <NotImplemented.h>
#include "SubstituteData.h"
#include "Settings.h"
#include "BackForwardList.h"
#include "KeyboardEvent.h"
#include "PluginView.h"
#include "PluginDatabase.h"
#include "c_instance.h"
#include "DocumentLoader.h"
#include "ResourceBuffer.h"
#include "CachedResourceLoader.h"

namespace WebCore {
    double getSharedTimerFireTime(void);
    void fireSharedTimerFunction(void);
}

using namespace WebCore;
using namespace JSC;
using namespace JSC::Bindings;

WebViewPrivate::WebViewPrivate(WebView *webView)
    : m_webView(webView)
    , m_rect(IntRect())
    , m_backingStoreDirtyRegion(IntRect())
    , m_cairo(0)
    , m_isStoreResource(false)
    , m_isHookHtml(false)
#ifdef ANDROID
    , m_jniEnv(NULL)
    , m_class(NULL)
    , m_object(NULL)
    , m_isStoreMethodID(NULL)
    , m_isHookMethodID(NULL)
    , m_hookMethodID(NULL)
    , m_startHtmlMethodID(NULL)
    , m_endHtmlMethodID(NULL)
    , m_startResMethodID(NULL)
    , m_endResMethodID(NULL)
    , m_storeResourceMethodID(NULL)
    , m_errorMsgToConsole(NULL)
    , m_inputMethod(NULL)
#endif
{
    m_chromeClient = new ChromeClientArmite(webView); 
    m_editorClient = new EditorClientArmite(webView);
}

WebViewPrivate::~WebViewPrivate() 
{
    delete m_chromeClient;
    delete m_editorClient;
}

double WebViewPrivate::getNextSharedTimerFireTime()
{
    return getSharedTimerFireTime();
}

void WebViewPrivate::fireWebKitTimerEvents()
{
    fireSharedTimerFunction();
}

void WebViewPrivate::fireWebKitThreadEvents()
{
    WTF::dispatchFunctionsFromMainThread();
}

void WebViewPrivate::initViewWindow(ArmiteSurface* surface, GraphicExpose expose)
{
    if(!m_cairo && surface)
        m_cairo = cairo_create(surface);
    m_expose = expose;
#ifdef ANDROID
    if (!m_jniEnv)
        m_jniEnv = m_webView->getJavaEnv();

    if (m_jniEnv && !m_class) {
        jclass clazz = m_jniEnv->FindClass("com/armite/webkit/DownloadManager");
        m_class = (jclass)m_jniEnv->NewGlobalRef(clazz);
    }

    if (m_jniEnv && !m_object) {
        jobject object = m_jniEnv->AllocObject(m_class);
        m_object = m_jniEnv->NewGlobalRef(object);
    }

    if (m_jniEnv && !m_isStoreMethodID)
        m_isStoreMethodID = m_jniEnv->GetMethodID(m_class, "isStore", "()Z");

    if (m_isStoreMethodID)
        m_isStoreResource = m_jniEnv->CallBooleanMethod(m_object, m_isStoreMethodID);

    if (m_jniEnv && !m_isHookMethodID)
        m_isHookMethodID = m_jniEnv->GetMethodID(m_class, "isHook", "()Z");

    if (m_isHookMethodID)
        m_isHookHtml = m_jniEnv->CallBooleanMethod(m_object, m_isHookMethodID);

    if (m_jniEnv && !m_hookMethodID)
        m_hookMethodID = m_jniEnv->GetMethodID(m_class, "hookHtmlString","(Ljava/lang/String;[B)Ljava/lang/String;");

    if (m_jniEnv && !m_startHtmlMethodID)
        m_startHtmlMethodID = m_jniEnv->GetMethodID(m_class, "startHtmlDown","()V");

    if (m_jniEnv && !m_endHtmlMethodID)
        m_endHtmlMethodID = m_jniEnv->GetMethodID(m_class, "endHtmlDown","(I)V");

    if (m_jniEnv && !m_startResMethodID)
        m_startResMethodID = m_jniEnv->GetMethodID(m_class, "startResourceDown","(Ljava/lang/String;)Z");

    if (m_jniEnv && !m_endResMethodID)
        m_endResMethodID = m_jniEnv->GetMethodID(m_class, "endResourceDown","(Ljava/lang/String;I)V");

    if (m_jniEnv && m_isStoreResource && !m_storeResourceMethodID)
        m_storeResourceMethodID = m_jniEnv->GetMethodID(m_class, "storeResource","(Ljava/lang/String;[B)V");

    if (m_jniEnv && !m_errorMsgToConsole)
        m_errorMsgToConsole = m_jniEnv->GetMethodID(m_class, "errorMsg","(Ljava/lang/String;Ljava/lang/String;I)V");

    if (m_jniEnv && !m_inputMethod)
        m_inputMethod = m_jniEnv->GetMethodID(m_class, "inputMethod","()Ljava/lang/String;");
#endif
}

ArmiteRect WebViewPrivate::onExpose(ArmiteExposeEvent &event)
{
    Frame* frame = NULL;
    frame = core(m_webView->m_mainFrame);
    if (!frame)
        return IntRect();

    if (m_cairo && frame->contentRenderer() && frame->view()) {
        frame->view()->updateLayoutAndStyleIfNeededRecursive();

        IntRect dirty = dirtyRegion();
        clearDirtyRegion();

        if (dirty.isEmpty())
            return IntRect();

        dirty.expand(20, 20);
        dirty.intersect(m_webRect);

        GraphicsContext ctx(m_cairo);
        ctx.save();
        ctx.clip(dirty);
        ctx.clearRect(dirty);
        frame->view()->paint(&ctx, dirty);
        ctx.restore();

        updateView(dirty);
        return dirty;
    }
    return IntRect();
}

bool WebViewPrivate::onKeyDown(ArmiteKeyboardEvent &event)
{
    Frame* frame = NULL;
    frame = m_webView->m_mainPage->focusController()->focusedOrMainFrame();
    if (!frame)
        return false;

    PlatformKeyboardEvent keyboardEvent(&event);
    bool handled = frame->eventHandler()->keyEvent(keyboardEvent);
    return handled;
}

bool WebViewPrivate::onMouseEvent(ArmiteMouseEvent &event)
{
    Frame* frame;
    frame = m_webView->m_mainPage->focusController()->focusedOrMainFrame();
    if (!frame)
        return false;

    PlatformMouseEvent mouseEvent(&event);
    bool handled = false;
    switch(event.type) {
        case ARMITE_MOUSEEVENT_MOVE:
            handled = frame->eventHandler()->handleMouseMoveEvent(mouseEvent);
            break;
        case ARMITE_MOUSEEVENT_DOWN:
            handled = frame->eventHandler()->handleMousePressEvent(mouseEvent);
            break;
        case ARMITE_MOUSEEVENT_UP:
            handled = frame->eventHandler()->handleMouseReleaseEvent(mouseEvent);
            break;
    }
    return handled;
}

void WebViewPrivate::setWebRect(const WebCore::IntRect& r)
{
    LOGI("setWebRect:%d,%d,%d,%d\n",r.x(),r.y(),r.width(),r.height());
    if (r.x() == 0 && r.y() == 0 && !r.isEmpty()) 
        m_webRect = r;
}

void WebViewPrivate::updateView(IntRect& rect)
{
    if (rect.isEmpty() || !m_expose)
        return;
    m_expose(m_webRect.x(), m_webRect.y(), m_webRect.width(), m_webRect.height());
}

void WebViewPrivate::sendExposeEvent(IntRect&)
{
    ArmiteEvent event = {ARMITE_EXPOSEEVENT, {{0,0}}};
    m_webView->sendEvent2Browser(&event);
}

void WebViewPrivate::repaint(const WebCore::IntRect& windowRect, bool contentChanged, bool immediate, bool repaintContentOnly)
{
    if (windowRect.isEmpty())
        return;
    IntRect rect = windowRect;
    rect.intersect(m_rect);

    if (rect.isEmpty())
        return;

    if (contentChanged)
        addToDirtyRegion(rect);

    if (!repaintContentOnly)
        sendExposeEvent(rect);
}

void WebViewPrivate::initDefalultSetting(Settings* settings)
{
    settings->setDefaultFontSize(20);
    settings->setDefaultTextEncodingName("utf-8");
    settings->setUsesEncodingDetector(true);
    settings->setJavaEnabled(true);
    settings->setScriptEnabled(true);
    settings->setXSSAuditorEnabled(true);
    settings->setJavaScriptCanOpenWindowsAutomatically(false);
    settings->setMinimumFontSize(10);
    settings->setMinimumLogicalFontSize(20);
    settings->setPluginsEnabled(true);
    settings->setPrivateBrowsingEnabled(false);
    settings->setLoadsImagesAutomatically(true);
    settings->setUserStyleSheetLocation(KURL());
    settings->setShouldPrintBackgrounds(false);
    settings->setUsesPageCache(false);
    settings->setForceFTPDirectoryListings(false);
    settings->setOfflineWebApplicationCacheEnabled(false);
    settings->setWebSecurityEnabled(true);
    settings->setJavaScriptCanAccessClipboard(false);
    settings->setWebGLEnabled(false);
    settings->setAcceleratedCompositingEnabled(false);
    settings->setLocalStorageEnabled(false);
    settings->setAllowScriptsToCloseWindows(true);
    settings->setSpatialNavigationEnabled(true);
    settings->setMediaEnabled(false);
}

typedef HashMap<StringImpl*, NPObject*> PluginMap;
static PluginMap* pluginMap()
{
    static PluginMap* map = NULL;
    if (map)
        return map;

    map = new PluginMap;
    PluginDatabase* database = PluginDatabase::installedPlugins();
    const Vector<PluginPackage*> plugins = database->plugins();

    for (unsigned i = 0; i < plugins.size(); ++i) {
        NPError npErr;
        NPP instance = new NPP_t;
        npErr = plugins[i]->pluginFuncs()->newp((NPMIMEType)"object", instance, NP_FULL, 0, NULL, NULL, NULL);
        if (npErr != NPERR_NO_ERROR)
            continue;

        NPObject* object = 0;
        npErr = plugins[i]->pluginFuncs()->getvalue(instance, NPPVpluginScriptableNPObject, &object);
        if (npErr != NPERR_NO_ERROR)
            continue;
        map->add(plugins[i]->name().impl(), object);
    }

    return map;
}

bool WebViewPrivate::getPluginJSValue(JSDOMWindow* thisObject, ExecState* exec, PropertyName propertyName, PropertySlot& slot)
{
    NPObject* obj = pluginMap()->get(propertyName.uid());
    if (!obj)
        return false;

    RootObject* rootObject = thisObject->impl()->frame()->script()->cacheableBindingRootObject();
    JSValue value = CInstance::create(obj, rootObject)->createRuntimeObject(exec);
    slot.setValue(thisObject, value);

    PutPropertySlot putSlot;
    thisObject->put(thisObject, exec, propertyName, value, putSlot);
    return true;
}

void WebViewPrivate::committedLoad(DocumentLoader* loader, const char* data, int length)
{
    if (!loader)
        return;
#ifdef ANDROID
    if (m_isHookHtml && m_jniEnv && data && length > 0 && m_hookMethodID) {
        const char *url = loader->request().url().string().utf8().data();
        jstring jstr = m_jniEnv->NewStringUTF(url);

        jbyte* bytes = (jbyte*)data;
        jbyteArray jbytes = m_jniEnv->NewByteArray(length);
        m_jniEnv->SetByteArrayRegion(jbytes, 0, length, bytes);

        jstring retStr = (jstring)m_jniEnv->CallObjectMethod(m_object, m_hookMethodID, jstr, jbytes);
        m_jniEnv->DeleteLocalRef(jstr);
        if (retStr) {
            jboolean ret;
            const char *str = m_jniEnv->GetStringUTFChars(retStr, &ret);
            int len = strlen(str);
            if (len > 0)
                loader->commitData(str, len);
            if (ret)
                m_jniEnv->ReleaseStringUTFChars(retStr, str);
            return;
        }
    }
#endif
    loader->commitData(data, length);
}

void WebViewPrivate::beforeDownloadResource(DocumentLoader* loader, ResourceRequest& request)
{
#ifdef ANDROID
    if (loader->request() == request) {
        if (m_jniEnv && m_startHtmlMethodID) {
            m_jniEnv->CallVoidMethod(m_object, m_startHtmlMethodID);
        }
    }

    if (m_jniEnv && m_startResMethodID) {
        const char *url = request.url().string().utf8().data();
        jstring jstr = m_jniEnv->NewStringUTF(url);
        if (m_jniEnv->CallBooleanMethod(m_object, m_startResMethodID, jstr))
            request.setURL(KURL());
        m_jniEnv->DeleteLocalRef(jstr);
    }
#endif
}

void WebViewPrivate::errorMsg(const char *msg, const char *url, int line)
{
#ifdef ANDROID
    if (m_jniEnv && m_errorMsgToConsole) {
        jstring jmsg = m_jniEnv->NewStringUTF(msg);
        jstring jurl = m_jniEnv->NewStringUTF(url);
        m_jniEnv->CallVoidMethod(m_object, m_errorMsgToConsole, jmsg, jurl, line);
        m_jniEnv->DeleteLocalRef(jmsg);
        m_jniEnv->DeleteLocalRef(jurl);
    }
#endif
}

void WebViewPrivate::afterDownloadResource(DocumentLoader* loader, ResourceLoader* resource)
{
    if (!loader || !resource || resource->url().isNull())
        return;
#ifdef ANDROID
    if (m_jniEnv && m_endResMethodID) {
        const char *url = resource->url().string().utf8().data();
        jstring jstr = m_jniEnv->NewStringUTF(url);
        int starusCode = resource->response().httpStatusCode();
        m_jniEnv->CallVoidMethod(m_object, m_endResMethodID, jstr, starusCode);
        m_jniEnv->DeleteLocalRef(jstr);
    }

    if (m_isStoreResource) {
        if (m_jniEnv && m_isStoreResource && m_storeResourceMethodID) {
            const char *url = resource->url().string().utf8().data();
            jstring jstr = m_jniEnv->NewStringUTF(url);

            jsize size = resource->resourceData()->size();
            jbyte* bytes = (jbyte*)resource->resourceData()->data();
            jbyteArray jbytes = m_jniEnv->NewByteArray(size);
            m_jniEnv->SetByteArrayRegion(jbytes, 0, size, bytes);

            m_jniEnv->CallVoidMethod(m_object, m_storeResourceMethodID, jstr, jbytes);
            m_jniEnv->DeleteLocalRef(jstr);
        }
    }

    if (loader->cachedResourceLoader()->requestCount() <= 1){
        if (m_jniEnv && m_endHtmlMethodID) {
            int starusCode = resource->response().httpStatusCode();
            m_jniEnv->CallVoidMethod(m_object, m_endHtmlMethodID, starusCode);
        }
    }
#endif
}

void WebViewPrivate::inputMethod(String& value)
{
    LOGI("inputMethod invoked\n");
#ifdef ANDROID
    if (m_jniEnv && m_inputMethod) {
        jstring retStr = (jstring)m_jniEnv->CallObjectMethod(m_object, m_inputMethod);
        if (retStr) {
            jboolean ret;
            const char *str = m_jniEnv->GetStringUTFChars(retStr, &ret);
            value = String::fromUTF8(str);
            if (ret)
                m_jniEnv->ReleaseStringUTFChars(retStr, str);
            return;
        }
    }
#endif
}




