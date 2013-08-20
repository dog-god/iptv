/*
 * add by armite@126.com
 */

#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include "jni.h"
#include "pluginbase.h"

class CiPanelPlugin : CPlugin {
public:
    CiPanelPlugin(NPP pNPInstance);
    ~CiPanelPlugin();

    virtual bool hasProperty(NPIdentifier name);
    virtual bool setProperty(NPIdentifier name, const NPVariant *value);
    virtual bool getProperty(NPIdentifier name, const NPVariant *result);

    virtual bool hasMethod(NPIdentifier name);
    virtual bool invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result);
    virtual bool invokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result);

private:
    JNIEnv* m_jniEnv;
    jclass m_class;
    jobject m_object;

    NPIdentifier m_debugName;
    jmethodID m_debugMethod;
    NPIdentifier m_ioctlWriteName;
    jmethodID m_ioctlWriteMethod;
};

#endif // __PLUGIN_H__



