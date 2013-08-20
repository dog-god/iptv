/*
 * add by armite@126.com
 */

#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include "jni.h"
#include "pluginbase.h"

class CUtilityPlugin : CPlugin {
public:
    CUtilityPlugin(NPP pNPInstance);
    ~CUtilityPlugin();

    virtual bool hasProperty(NPIdentifier name);
    virtual bool setProperty(NPIdentifier name, const NPVariant *value);
    virtual bool getProperty(NPIdentifier name, NPVariant *result);

    virtual bool hasMethod(NPIdentifier name);
    virtual bool invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result);
    virtual bool invokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result);

private:
    JNIEnv* m_jniEnv;
    jclass m_class;
    jobject m_object;

//setBrowserWindowAlpha
    NPIdentifier m_setBrowserWindowAlphaName;
    jmethodID m_setBrowserWindowAlphaMethod;
//startLocalCfg
    NPIdentifier m_startLocalCfgName;
    jmethodID m_startLocalCfgMethod;
//getEvent

    NPIdentifier m_getEventName;
    jmethodID m_getEventMethod;
//showExit 
    NPIdentifier m_showExitName;
    jmethodID m_showExitMethod;

//quit
    NPIdentifier m_quitName;
    jmethodID m_quitMethod;

//startapk
    NPIdentifier m_startApkName;
    jmethodID m_startApkMethod;
//startPlayer
    NPIdentifier m_startPlayerName;
    jmethodID m_startPlayerMethod;
//show presss
  NPIdentifier m_showProgressName;
    jmethodID m_showProgressMethod;
//debug
NPIdentifier m_debugName;
    jmethodID m_debugMethod;

//setPlayer
  NPIdentifier m_setPlayerName;
    jmethodID m_setPlayerMethod;
};

#endif // __PLUGIN_H__



