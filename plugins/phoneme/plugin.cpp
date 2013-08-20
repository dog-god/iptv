/*
 * add by armite@126.com
 */

#include "log.h"
#include "object.h"
#include "plugin.h"
#include "advanced.h"

#include <string.h>
#include <stdio.h>
#include "android/bitmap.h"

const char *CPlugin::getMIMEDescription()
{
    return "j2me-midp2::phoneme";
}

const char *CPlugin::getPluginName()
{
    return "phoneme";
}

CPlugin* CPlugin::getPluginInstance(NPP instance, int16_t argc, char* argn[], char* argv[])
{
    const char *url = NULL;
    for (int i=0; i<argc; i++) {
        //NP_TRACE("getPluginInstance para %d: %s = %s", i, argn[i], argv[i]);
        if (!strcmp(argn[i], "jar"))
            url = argv[i];
    }
    return (CPlugin*)new CPhonemePlugin(instance, url);
}

void CPlugin::delPluginInstance(NPP instance)
{
    CPhonemePlugin* pPlugin = (CPhonemePlugin*)instance->pdata;
    delete pPlugin;
}

#define PHONEME_CLASS "com/armite/webkit/Phoneme"
static CPhonemePlugin* phoneme = NULL;
static void AN_getBitmap(int width, int height, int *stride, void **data)
{
    *stride = 0;
    *data = NULL;
    if (phoneme)
        phoneme->getBitmap(width, height, stride, data);
}

static void AN_refreshBitmap()
{
    if (phoneme)
        phoneme->refreshBitmap();
}

static void AN_releaseBitmap()
{
    if (phoneme)
        phoneme->releaseBitmap();
}

CPhonemePlugin::CPhonemePlugin(NPP pNPInstance, const char* url)
    : CPlugin(pNPInstance)
    , m_jarUrl(url)
    , m_jvm(NULL)
    , m_refreshMethod(NULL)
    , m_releaseMethod(NULL)
{
    if (m_jarUrl == NULL) {
        NP_TRACE("CPhonemePlugin::CPhonemePlugin url is NULL!!!");
        m_jarUrl = "file:////data/local/tmp/suite.jar";
    }
    NP_TRACE("CPhonemePlugin::CPhonemePlugin url is %s", m_jarUrl);

    m_jniEnv = (JNIEnv*)NPN_GetJavaEnv();
    jclass clazz = m_jniEnv->FindClass(PHONEME_CLASS);
    m_class = (jclass)m_jniEnv->NewGlobalRef(clazz);

    jobject object = m_jniEnv->AllocObject(m_class);
    m_object = (jobject)m_jniEnv->NewGlobalRef(object);

    jmethodID getMethod = m_jniEnv->GetMethodID(m_class, "getJarFile", "(Ljava/lang/String;)Ljava/lang/String;");
    jstring jurl = m_jniEnv->NewStringUTF(m_jarUrl);
    jstring ret = (jstring)m_jniEnv->CallObjectMethod(m_object, getMethod, jurl);
    const char* v = (const char*)m_jniEnv->GetStringUTFChars(ret, JNI_FALSE);
    m_localJar = strdup(v);
    m_jniEnv->ReleaseStringUTFChars(ret, v);

    m_jvm = (JavaVM*)NPN_GetJavaPeer(NULL);
    phoneme = this;
    setBitmapFuns(AN_getBitmap, AN_refreshBitmap, AN_releaseBitmap);
    startCVM(m_localJar);
}

CPhonemePlugin::~CPhonemePlugin()
{
    phoneme = NULL;
    if (m_class)
        m_jniEnv->DeleteGlobalRef(m_class);
    if (m_object)
        m_jniEnv->DeleteGlobalRef(m_object);
    if (m_localJar)
        free(m_localJar);
}

void CPhonemePlugin::getBitmap(int width, int height, int *stride, void **data)
{
    JNIEnv* env = NULL;
    m_jvm->AttachCurrentThread(&env, NULL);
    if (!env)
        return;

    jmethodID fun = env->GetStaticMethodID(m_class, "getBitmap","(II)Landroid/graphics/Bitmap;");
    jobject bitmap = env->CallStaticObjectMethod(m_class, fun, width, height);

    AndroidBitmapInfo  info;
    unsigned char*     pixels;
    int                ret;

    if ((ret = AndroidBitmap_getInfo(env, bitmap, &info)) < 0) {
        NP_TRACE("getBitmap AndroidBitmap_getInfo() failed ! error=%d", ret);
        return;
    }
    if (info.format != ANDROID_BITMAP_FORMAT_RGB_565) {
        NP_TRACE("getBitmap Bitmap format is not RGB_565!");
        return;
    }
    if ((ret = AndroidBitmap_lockPixels(env, bitmap, (void**)&pixels)) < 0) {
        NP_TRACE("getBitmap AndroidBitmap_lockPixels() failed ! error=%d", ret);
        return;
    }
    AndroidBitmap_unlockPixels(env, bitmap);

    NP_TRACE("getBitmap:w=%d,h=%d,s=%d,data:%p", info.width, info.height, info.stride, pixels);
    *stride = info.stride;
    *data = pixels;
    m_jvm->DetachCurrentThread();
}

void CPhonemePlugin::refreshBitmap()
{
    JNIEnv* env = NULL;
    m_jvm->AttachCurrentThread(&env, NULL);
    if (!env)
        return;

    if (!m_refreshMethod)
        m_refreshMethod = env->GetStaticMethodID(m_class, "refreshBitmap","()V");
    env->CallStaticVoidMethod(m_class, m_refreshMethod);
    m_jvm->DetachCurrentThread();
}

void CPhonemePlugin::releaseBitmap()
{
    JNIEnv* env = NULL;
    m_jvm->AttachCurrentThread(&env, NULL);
    if (!env)
        return;

    if (!m_releaseMethod)
        m_releaseMethod = env->GetStaticMethodID(m_class, "releaseBitmap","()V");
    env->CallStaticVoidMethod(m_class, m_releaseMethod);
    m_jvm->DetachCurrentThread();
}



