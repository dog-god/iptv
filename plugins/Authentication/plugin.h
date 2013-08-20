/*
 * add by armite@126.com
 */

#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include "jni.h"
#include "pluginbase.h"

class CAuthenticationPlugin : CPlugin {
public:
    CAuthenticationPlugin(NPP pNPInstance);
    ~CAuthenticationPlugin();

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

//CTCGetAuthInfo
    NPIdentifier m_CTCGetAuthInfoName;
    jmethodID m_CTCGetAuthInfoMethod;

//CTCGetConfig
    NPIdentifier m_CTCGetConfigName;
    jmethodID m_CTCGetConfigMethod;

//CTCSetConfig
    NPIdentifier m_CTCSetConfigName;
    jmethodID m_CTCSetConfigMethod;

//CTCStartUpdate
  NPIdentifier m_CTCStartUpdateName;
    jmethodID m_CTCStartUpdateMethod;
//setAuthParam
 NPIdentifier m_setAuthParamName;
 jmethodID m_setAuthParamMethod;
	
//login
 NPIdentifier m_loginName;
 jmethodID m_loginMethod;

};

#endif // __PLUGIN_H__



