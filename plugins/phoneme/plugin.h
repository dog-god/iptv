/*
 * add by armite@126.com
 */

#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include "jni.h"
#include "pluginbase.h"
#include "pthread.h"

class CPhonemePlugin : CPlugin {
public:
    CPhonemePlugin(NPP pNPInstance, const char* url);
    ~CPhonemePlugin();

    void getBitmap(int w, int h, int *s, void **data);
    void refreshBitmap();
    void releaseBitmap();

private:
    JNIEnv* m_jniEnv;
    jclass m_class;
    jobject m_object;

    const char* m_jarUrl;
    char* m_localJar;

    JavaVM* m_jvm;
    jmethodID m_refreshMethod;
    jmethodID m_releaseMethod;
};

#endif // __PLUGIN_H__



