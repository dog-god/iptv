/*
 * add by armite@126.com
 */

#include "log.h"
#include "object.h"
#include "plugin.h"

#include <string.h>
#include <stdio.h>

const char *CPlugin::getMIMEDescription()
{
    return "application/Utility::Utility";
}

const char *CPlugin::getPluginName()
{
    return "Utility";
}

CPlugin* CPlugin::getPluginInstance(NPP instance, int16_t argc, char* argn[], char* argv[])
{
    return (CPlugin*)new CUtilityPlugin(instance);
}

void CPlugin::delPluginInstance(NPP instance)
{
    CUtilityPlugin* pPlugin = (CUtilityPlugin*)instance->pdata;
    delete pPlugin;
}

CUtilityPlugin::CUtilityPlugin(NPP pNPInstance) 
    : CPlugin(pNPInstance)
{
    m_jniEnv = (JNIEnv*)NPN_GetJavaEnv();
    jclass clazz = m_jniEnv->FindClass("com/armite/webkit/plug/Utility");
    m_class = (jclass)m_jniEnv->NewGlobalRef(clazz);

    jobject object = m_jniEnv->AllocObject(m_class);
    m_object = (jobject)m_jniEnv->NewGlobalRef(object);

//setBrowserWindowAlpha
    m_setBrowserWindowAlphaName = NPN_GetStringIdentifier("setBrowserWindowAlpha");
    m_setBrowserWindowAlphaMethod = m_jniEnv->GetMethodID(m_class, "setBrowserWindowAlpha", "(I)V");

//startLocalCfg
    m_startLocalCfgName = NPN_GetStringIdentifier("startLocalCfg");
    m_startLocalCfgMethod = m_jniEnv->GetMethodID(m_class, "startLocalCfg", "()V");

//getEvent
   m_getEventName = NPN_GetStringIdentifier("getEvent");
    m_getEventMethod=m_jniEnv->GetMethodID(m_class, "getEvent", "()Ljava/lang/String;");

//showExit
    m_showExitName = NPN_GetStringIdentifier("showExit");
    m_showExitMethod = m_jniEnv->GetMethodID(m_class, "showExit", "()V");

//quit
    m_quitName = NPN_GetStringIdentifier("quit");
    m_quitMethod = m_jniEnv->GetMethodID(m_class, "quit", "(Ljava/lang/String;Ljava/lang/String;)V");

   m_startApkName = NPN_GetStringIdentifier("startApk");
    m_startApkMethod = m_jniEnv->GetMethodID(m_class, "startApk", "(Ljava/lang/String;Ljava/lang/String;)V");

    m_startPlayerName = NPN_GetStringIdentifier("startPlayer");
    m_startPlayerMethod = m_jniEnv->GetMethodID(m_class, "startPlayer", "(Ljava/lang/String;Ljava/lang/String;)V");


 m_showProgressName = NPN_GetStringIdentifier("showProgress");
    m_showProgressMethod = m_jniEnv->GetMethodID(m_class, "showProgress", "(I)V");


 m_debugName = NPN_GetStringIdentifier("debug");
    m_debugMethod = m_jniEnv->GetMethodID(m_class, "debug", "(Ljava/lang/String;)V");

 m_setPlayerName = NPN_GetStringIdentifier("setPlayer");
    m_setPlayerMethod = m_jniEnv->GetMethodID(m_class, "setPlayer", "(Ljava/lang/String;)V");



}

CUtilityPlugin::~CUtilityPlugin()
{
    if (m_class)
        m_jniEnv->DeleteGlobalRef(m_class);
    if (m_object)
        m_jniEnv->DeleteGlobalRef(m_object);
}

bool CUtilityPlugin::setProperty(NPIdentifier name, const NPVariant *value)
{
    UNIMPLEMENTED();
    return false;
}

bool CUtilityPlugin::hasProperty(NPIdentifier name)
{
    return false;
}

bool CUtilityPlugin::getProperty(NPIdentifier name,  NPVariant *result)
{
    UNIMPLEMENTED();
    return false;
}

bool CUtilityPlugin::hasMethod(NPIdentifier name)
{
    NP_TRACE("CUtilityPlugin hasMethod:%s\n",NPN_UTF8FromIdentifier(name));
    if (name == m_setBrowserWindowAlphaName)
        return true;
    else if (name == m_startLocalCfgName)
        return true;
    else if (name==m_getEventName)
        return true;
   else if (name==m_showExitName)
        return true;
   else if (name==m_quitName)
        return true;
 else if (name==m_startApkName)
        return true;
   else if (name==m_startPlayerName)
        return true;
   else if(name==m_showProgressName)
	return true;
   else if(name==m_debugName)
	return true;
  else if(name==m_setPlayerName)
	return true;
    return false;
}

bool CUtilityPlugin::invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    NP_TRACE("CUtilityPlugin invoke:%s\n",NPN_UTF8FromIdentifier(name));
    if (name == m_setBrowserWindowAlphaName){
	if (argCount != 1 || !NPVARIANT_IS_DOUBLE(args[0]))
            return false;
        int tmpalpha = NPVARIANT_TO_DOUBLE(args[0]);
        m_jniEnv->CallVoidMethod(m_object, m_setBrowserWindowAlphaMethod, tmpalpha);
	return true;
    }
    else if (name == m_startLocalCfgName){
        m_jniEnv->CallVoidMethod(m_object, m_startLocalCfgMethod);
	return true;
    }
     else if (name == m_getEventName) {    
        jstring ret = (jstring)m_jniEnv->CallObjectMethod(m_object, m_getEventMethod);
        const char* v = (char*)m_jniEnv->GetStringUTFChars(ret, JNI_FALSE);
        /*const char* s = strdup(v);
        m_jniEnv->ReleaseStringUTFChars(ret, v);
        STRINGZ_TO_NPVARIANT(s, *result);*/
	uint32_t len = strlen(v) + 1;
	char *s = (char*)NPN_MemAlloc(len);
	strncpy(s, v, len);
	STRINGZ_TO_NPVARIANT(s, *result);
        m_jniEnv->ReleaseStringUTFChars(ret, v);
	//m_jniEnv->DeleteLocalRef(ret);
        return true;
     } 
    else if (name==m_showExitName){
        m_jniEnv->CallVoidMethod(m_object, m_showExitMethod);
	return true;
    }
    else if (name==m_quitName){
	if (argCount != 2 || !NPVARIANT_IS_STRING(args[0])||!NPVARIANT_IS_STRING(args[1]))
            return false;
	
	        NPString msg1 = NPVARIANT_TO_STRING(args[0]);
            jstring jmsg1 = m_jniEnv->NewStringUTF(msg1.UTF8Characters);

            NPString msg2 = NPVARIANT_TO_STRING(args[1]);
            jstring jmsg2 = m_jniEnv->NewStringUTF(msg2.UTF8Characters);
            m_jniEnv->CallVoidMethod(m_object, m_quitMethod, jmsg1,jmsg2);
            m_jniEnv->DeleteLocalRef(jmsg1);
            m_jniEnv->DeleteLocalRef(jmsg2);
            return true;
    }
  else if (name==m_startApkName){
	if (argCount != 2 || !NPVARIANT_IS_STRING(args[0])||!NPVARIANT_IS_STRING(args[1]))
            return false;
	
	        NPString msg1 = NPVARIANT_TO_STRING(args[0]);
            jstring jmsg1 = m_jniEnv->NewStringUTF(msg1.UTF8Characters);

            NPString msg2 = NPVARIANT_TO_STRING(args[1]);
            jstring jmsg2 = m_jniEnv->NewStringUTF(msg2.UTF8Characters);
            m_jniEnv->CallVoidMethod(m_object, m_startApkMethod, jmsg1,jmsg2);
            m_jniEnv->DeleteLocalRef(jmsg1);
            m_jniEnv->DeleteLocalRef(jmsg2);
            return true;
    }
  else if (name==m_startPlayerName){
	if (argCount != 2 || !NPVARIANT_IS_STRING(args[0])||!NPVARIANT_IS_STRING(args[1]))
            return false;
	
	        NPString msg1 = NPVARIANT_TO_STRING(args[0]);
            jstring jmsg1 = m_jniEnv->NewStringUTF(msg1.UTF8Characters);

            NPString msg2 = NPVARIANT_TO_STRING(args[1]);
            jstring jmsg2 = m_jniEnv->NewStringUTF(msg2.UTF8Characters);
            m_jniEnv->CallVoidMethod(m_object, m_startPlayerMethod, jmsg1,jmsg2);
            m_jniEnv->DeleteLocalRef(jmsg1);
            m_jniEnv->DeleteLocalRef(jmsg2);
            return true;
    }
 if (name == m_showProgressName){
	if (argCount != 1 || !NPVARIANT_IS_DOUBLE(args[0])||!NPVARIANT_IS_INT32(args[0]))
            return false;
        int tmptype = NPVARIANT_TO_INT32(args[0]);
        m_jniEnv->CallVoidMethod(m_object, m_showProgressMethod, tmptype);
	return true;
    }
 else if (name==m_debugName){
	if (argCount != 1 || !NPVARIANT_IS_STRING(args[0]))
            return false;
	
	    NPString msg1 = NPVARIANT_TO_STRING(args[0]);
            jstring jmsg1 = m_jniEnv->NewStringUTF(msg1.UTF8Characters);
            m_jniEnv->CallVoidMethod(m_object, m_debugMethod, jmsg1);
            m_jniEnv->DeleteLocalRef(jmsg1);
            return true;
    }
else if (name==m_setPlayerName){
	if (argCount != 1 || !NPVARIANT_IS_STRING(args[0]))
            return false;
	
	    NPString msg1 = NPVARIANT_TO_STRING(args[0]);
            jstring jmsg1 = m_jniEnv->NewStringUTF(msg1.UTF8Characters);
            m_jniEnv->CallVoidMethod(m_object, m_setPlayerMethod, jmsg1);
            m_jniEnv->DeleteLocalRef(jmsg1);
            return true;
    }
    return false;
}

bool CUtilityPlugin::invokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    return true;
}






