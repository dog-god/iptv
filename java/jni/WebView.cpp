/*
 * Copyright (C) 2012 armite@126.com
 *
 */

#include <jni.h>
#include <time.h>
#include <android/log.h>
#include <android/bitmap.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <sys/system_properties.h>

#include "WebView.h"
#include "cairo.h"
#include "VirtualKeyboardCodes.h"

#define ARMITE_WEBVIEW_CLASS "com/armite/webkit/WebView"

typedef struct _JavaEnv{
    JavaVM *javaVM;
    jclass  browserClass;
    jobject browserObject;
}JavaEnv;
static JavaEnv java_env;

static JNIEnv* getJNIEnv()
{
    static JNIEnv* jniEnv = NULL;
    if (jniEnv  != NULL)
        return jniEnv;

    if(java_env.javaVM->GetEnv((void**)(&jniEnv), JNI_VERSION_1_6) != JNI_OK)
        if(java_env.javaVM->GetEnv((void**)(&jniEnv), JNI_VERSION_1_4) != JNI_OK)
            if(java_env.javaVM->GetEnv((void**)(&jniEnv), JNI_VERSION_1_2) != JNI_OK)
                LOGI("in getJNIEnv(). get env error");
    return jniEnv;
}

static jmethodID getUpdateMethodID()
{
    static jmethodID updateWindowFromJava = NULL;

    if(!updateWindowFromJava){
        JNIEnv* env = getJNIEnv();
        if(env)
            updateWindowFromJava = env->GetMethodID(java_env.browserClass, "updateWindow","(IIII)V");
    }
    return updateWindowFromJava;
}

void updateWindowJNI(int x, int y, int w, int h)
{
    JNIEnv* env = getJNIEnv();
    jmethodID updateWindowFromJava = getUpdateMethodID();
    if(updateWindowFromJava)
        env->CallVoidMethod(java_env.browserObject, updateWindowFromJava, x, y, w, h);
    else
        LOGI("updateWindowJNI fails");
}

static WebView *globalWebView = 0;
static void ExitBrowser(JNIEnv* env, jobject obj)
{
    ArmiteEvent event;
    event.type = ARMITE_BROWSER_EXIT;
    event.data.key.vkey = ARMITE_BROWSER_EXIT;
    event.data.key.unicode = ARMITE_BROWSER_EXIT;

    if (globalWebView) {
        globalWebView->sendEvent2Browser(&event);
        globalWebView = 0;
    }
}

static void StartBrowser(JNIEnv* env, jobject obj, jobject bitmap, jstring url)
{
    jmethodID fun = env->GetStaticMethodID(java_env.browserClass, "getInstance","()L"ARMITE_WEBVIEW_CLASS";");
    jobject browser = env->CallStaticObjectMethod(java_env.browserClass, fun);
    java_env.browserObject = env->NewGlobalRef(browser);

    jboolean jret;
    const char *browserURL = 0;
    browserURL = env->GetStringUTFChars(url, &jret);

    char propURL[PROP_VALUE_MAX];
    __system_property_get("armite.test.url", propURL);
    if(strlen(propURL) > 16)
        browserURL = propURL;
    LOGI("browserURL:%s", browserURL);

    AndroidBitmapInfo  info;
    unsigned char*     pixels;
    int                ret;

    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
        LOGI("AndroidBitmap_getInfo() failed ! error=%d", ret);
        return;
    }
    if (info.format != ANDROID_BITMAP_FORMAT_RGBA_8888) {
        LOGI("Bitmap format is not RGBA_8888 !");
        return;
    }
    if ((ret = AndroidBitmap_lockPixels(env, bitmap, (void**)&pixels)) < 0) {
        LOGI("AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return;
    }
    AndroidBitmap_unlockPixels(env, bitmap);

    globalWebView = WebView::getStaticInstance();
    globalWebView->setJavaVM(java_env.javaVM);
    globalWebView->setJavaWebView(java_env.browserClass, java_env.browserObject);

    ArmiteRect rect = {0, 0, info.width, info.height};
    ArmiteSurface *surface = cairo_image_surface_create_for_data(pixels, CAIRO_FORMAT_ARGB32, info.width, info.height, info.stride);
    globalWebView->initGraphic(surface, rect, updateWindowJNI);
    globalWebView->setFocusRingColor(255, 0, 0, 255);
    globalWebView->setFocusRingWidth(3);
    globalWebView->startBrowser(browserURL);
}

static void SendKeyEvent(JNIEnv * env, jobject obj, jint key, jint unicode)
{
    if (!globalWebView)
        return;
    ArmiteEvent event;
    event.type = ARMITE_KEYBOARDEVENT;
    event.data.key.unicode = unicode;
    event.data.key.vkey = key;
    globalWebView->sendEvent2Browser(&event);
}

static void SendMouseEvent(JNIEnv * env, jobject obj, jstring jtype, jint x, jint y)
{
    if (!globalWebView)
        return;
    ArmiteEvent event;
    event.type = ARMITE_MOUSEEVENT;

    jboolean jret;
    const char* type = env->GetStringUTFChars(jtype, &jret);
    if (!strcmp(type, "mouse-down"))
        event.data.mouse.type = ARMITE_MOUSEEVENT_DOWN;
    else if (!strcmp(type, "mouse-up"))
        event.data.mouse.type = ARMITE_MOUSEEVENT_UP;
    else if (!strcmp(type, "mouse-move"))
        event.data.mouse.type = ARMITE_MOUSEEVENT_MOVE;
    if(jret)
        env->ReleaseStringUTFChars(jtype, type);

    event.data.mouse.x = x;
    event.data.mouse.y = y;
    globalWebView->sendEvent2Browser(&event);
}

static void setSpatialNavigationEnabled(JNIEnv * env, jobject obj, jboolean enable)
{
    if (globalWebView)
        globalWebView->setSpatialNavigationEnabled(enable);
}

static void setFocusRingColor(JNIEnv * env, jobject obj, jint r, jint g, jint b, jint a)
{
    if (globalWebView)
        globalWebView->setFocusRingColor(r, g, b, a);
}

static void sendEvent2cvm(JNIEnv * env, jobject obj, jint e)
{
    unsigned char event = e;
    if (globalWebView)
        globalWebView->sendEvent2cvm(event);
}

static void setFocusRingWidth(JNIEnv * env, jobject obj, jint w)
{
    if (globalWebView)
        globalWebView->setFocusRingWidth(w);
}

static void setExtraDefaultCSS(JNIEnv * env, jobject obj, jstring jstr)
{
    jboolean jret = false;
    const char* str = env->GetStringUTFChars(jstr, &jret);
    if(!jret)
        return;

    if (globalWebView)
        globalWebView->setExtraDefaultCSS(str);
}

static void setUserAgentString(JNIEnv * env, jobject obj, jstring jstr)
{
    jboolean jret = false;
    const char* str = env->GetStringUTFChars(jstr, &jret);
    if(!jret)
        return;

    if (globalWebView)
        globalWebView->setUserAgentString(str);
}

static void setPluginDir(JNIEnv * env, jobject obj, jstring jstr)
{
    jboolean jret = false;
    const char* str = env->GetStringUTFChars(jstr, &jret);
    if(!jret)
        return;
    setenv("ARMITE_PLUGINS_DIR", str, 1);
}

static void setCurlTimeout(JNIEnv * env, jobject obj, jstring jstr)
{
    jboolean jret = false;
    const char* str = env->GetStringUTFChars(jstr, &jret);
    if(!jret)
        return;
    setenv("ARMITE_CURL_TIMEOUT", str, 1);
}

static void setGlobalJavaScript(JNIEnv * env, jobject obj, jstring jstr)
{
    jboolean jret = false;
    const char* str = env->GetStringUTFChars(jstr, &jret);
    if(!jret)
        return;

    if (globalWebView)
        globalWebView->setGlobalJavaScript(str);
}

static bool canGoBack(JNIEnv * env, jobject obj)
{
    if (!globalWebView)
        return false;
    return globalWebView->canGoBack();
}

static bool goBack(JNIEnv * env, jobject obj)
{
    if (!globalWebView)
        return false;
    return globalWebView->goBack();
}

static bool canGoForward(JNIEnv * env, jobject obj)
{
    if (!globalWebView)
        return false;
    return globalWebView->canGoForward();
}

static bool goForward(JNIEnv * env, jobject obj)
{
    if (!globalWebView)
        return false;
    return globalWebView->goForward();
}

static void stop(JNIEnv * env, jobject obj)
{
    if (globalWebView)
        globalWebView->stop();
}

static void refresh(JNIEnv * env, jobject obj)
{
    if (globalWebView)
        globalWebView->refresh();
}

static void load(JNIEnv * env, jobject obj, jstring jurl)
{
    if (!globalWebView)
        return;
    jboolean jret;
    const char* url = env->GetStringUTFChars(jurl, &jret);
    if(!jret)
        return;
    globalWebView->load(url);
    env->ReleaseStringUTFChars(jurl, url);
}

static jstring getUrl(JNIEnv * env, jobject obj)
{
    if (!globalWebView)
        return NULL;
    const uint16_t* url = NULL;
    int len = 0;
    globalWebView->getUrl(url, len);
    if (url == NULL || len == 0)
        return NULL;
    return env->NewString(url, len);
}

static bool isFrameSet(JNIEnv * env, jobject obj)
{
    return globalWebView->isMainFrameSet();
}

static const JNINativeMethod gMethods[] = {
    {"StartBrowser", "(Landroid/graphics/Bitmap;Ljava/lang/String;)V", (void *)StartBrowser},
    {"ExitBrowser", "()V", (void *)ExitBrowser},
    {"SendKeyEvent", "(II)V",(void *)SendKeyEvent},
    {"SendMouseEvent", "(Ljava/lang/String;II)V",(void *)SendMouseEvent},
    {"setSpatialNavigationEnabled", "(Z)V",(void *)setSpatialNavigationEnabled},
    {"setFocusRingColor", "(IIII)V",(void *)setFocusRingColor},
    {"setFocusRingWidth", "(I)V",(void *)setFocusRingWidth},
    {"setExtraDefaultCSS", "(Ljava/lang/String;)V",(void *)setExtraDefaultCSS},
    {"setGlobalJavaScript", "(Ljava/lang/String;)V",(void *)setGlobalJavaScript},
    {"setUserAgentString", "(Ljava/lang/String;)V",(void *)setUserAgentString},
    {"setPluginDir", "(Ljava/lang/String;)V",(void *)setPluginDir},
    {"setCurlTimeout", "(Ljava/lang/String;)V",(void *)setCurlTimeout},
    {"setGlobalJavaScript", "(Ljava/lang/String;)V",(void *)setGlobalJavaScript},
    {"canGoBack", "()Z",(void *)canGoBack},
    {"goBack", "()Z",(void *)goBack},
    {"canGoForward", "()Z",(void *)canGoForward},
    {"goForward", "()Z",(void *)goForward},
    {"stop", "()V",(void *)stop},
    {"refresh", "()V",(void *)refresh},
    {"load", "(Ljava/lang/String;)V",(void *)load},
    {"getUrl", "()Ljava/lang/String;",(void *)getUrl},
    {"isFrameSet", "()Z",(void *)isFrameSet},
    {"sendEvent2cvm", "(I)V",(void *)sendEvent2cvm},
};

extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env;
    if(vm->GetEnv((void**)(&env), JNI_VERSION_1_6) != JNI_OK) {
        if(vm->GetEnv((void**)(&env), JNI_VERSION_1_4) != JNI_OK) {
            if(vm->GetEnv((void**)(&env), JNI_VERSION_1_2) != JNI_OK) {
                LOGI("in JNI_OnLoad(). get env error");
                return -1;
            } else
                LOGI("in JNI_OnLoad(). ver: 1.2");
        } else
            LOGI("in JNI_OnLoad(). ver: 1.4");
    } else
        LOGI("in JNI_OnLoad(). ver: 1.6");

    java_env.javaVM = vm;
    jclass clazz = env->FindClass(ARMITE_WEBVIEW_CLASS);
    java_env.browserClass = reinterpret_cast<jclass>(env->NewGlobalRef(clazz));

    if(env->RegisterNatives(java_env.browserClass, gMethods, sizeof(gMethods) / sizeof(gMethods[0])) != JNI_OK) {
        LOGI("Failed registering methods for WebView\n");
        return -1;
    }

    return JNI_VERSION_1_6;
}




