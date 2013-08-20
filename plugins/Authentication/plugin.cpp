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
    return "application/Authentication::Authentication";
}

const char *CPlugin::getPluginName()
{
    return "Authentication";
}

CPlugin* CPlugin::getPluginInstance(NPP instance, int16_t argc, char* argn[], char* argv[])
{
    return (CPlugin*)new CAuthenticationPlugin(instance);
}

void CPlugin::delPluginInstance(NPP instance)
{
    CAuthenticationPlugin* pPlugin = (CAuthenticationPlugin*)instance->pdata;
    delete pPlugin;
}

CAuthenticationPlugin::CAuthenticationPlugin(NPP pNPInstance) 
    : CPlugin(pNPInstance)
{
    m_jniEnv = (JNIEnv*)NPN_GetJavaEnv();
    jclass clazz = m_jniEnv->FindClass("com/armite/webkit/plug/Authentication");
    m_class = (jclass)m_jniEnv->NewGlobalRef(clazz);

    jobject object = m_jniEnv->AllocObject(m_class);
    m_object = m_jniEnv->NewGlobalRef(object);

    //CTCGetAuthInfo
    m_CTCGetAuthInfoName = NPN_GetStringIdentifier("CTCGetAuthInfo");
    m_CTCGetAuthInfoMethod=m_jniEnv->GetMethodID(m_class, "CTCGetAuthInfo", "(Ljava/lang/String;)Ljava/lang/String;");

    //CTCGetConfig
    m_CTCGetConfigName = NPN_GetStringIdentifier("CTCGetConfig");
    m_CTCGetConfigMethod=m_jniEnv->GetMethodID(m_class, "CTCGetConfig", "(Ljava/lang/String;)Ljava/lang/String;");
    //CTCSetConfig
    m_CTCSetConfigName = NPN_GetStringIdentifier("CTCSetConfig");
    m_CTCSetConfigMethod=m_jniEnv->GetMethodID(m_class, "CTCSetConfig", "(Ljava/lang/String;Ljava/lang/String;)V");
    //CTCStartUpdate
    m_CTCStartUpdateName = NPN_GetStringIdentifier("CTCStartUpdate");
    m_CTCStartUpdateMethod=m_jniEnv->GetMethodID(m_class, "CTCStartUpdate", "()Z");

    //setAuthParam
    m_setAuthParamName = NPN_GetStringIdentifier("setAuthParam");
    //String userID,String password,String stbID,String mac,String reserved
    m_setAuthParamMethod=m_jniEnv->GetMethodID(m_class, "setAuthParam", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");

    //login use in local config
    m_loginName = NPN_GetStringIdentifier("login");
    m_loginMethod=m_jniEnv->GetMethodID(m_class, "login", "()V");

}

CAuthenticationPlugin::~CAuthenticationPlugin()
{
    if (m_class)
        m_jniEnv->DeleteGlobalRef(m_class);
    if (m_object)
        m_jniEnv->DeleteGlobalRef(m_object);
}

bool CAuthenticationPlugin::setProperty(NPIdentifier name, const NPVariant *value)
{
    UNIMPLEMENTED();
    return false;
}

bool CAuthenticationPlugin::hasProperty(NPIdentifier name)
{
    return false;
}

bool CAuthenticationPlugin::getProperty(NPIdentifier name, const NPVariant *result)
{
    UNIMPLEMENTED();
    return false;
}

bool CAuthenticationPlugin::hasMethod(NPIdentifier name)
{
    NP_TRACE("CAuthenticationPlugin::hasMethod:%s\n", NPN_UTF8FromIdentifier(name));
    if (name == m_CTCGetAuthInfoName)
        return true;
    else if (name == m_CTCGetConfigName)
        return true;
    else if (name == m_CTCSetConfigName)
        return true;
    else if (name == m_CTCStartUpdateName)
        return true;
    else if (name == m_setAuthParamName)
        return true;
    else if (name == m_loginName)
        return true;   

    return false;
}

bool CAuthenticationPlugin::invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    NP_TRACE("CAuthenticationPlugin::invoke:%s\n", NPN_UTF8FromIdentifier(name));
    if (name == m_CTCGetAuthInfoName) {
        if (argCount != 1 || !NPVARIANT_IS_STRING(args[0]))
            return false;
        NPString msg = NPVARIANT_TO_STRING(args[0]);
        jstring jmsg = m_jniEnv->NewStringUTF(msg.UTF8Characters);
        jstring ret=(jstring)m_jniEnv->CallObjectMethod(m_object, m_CTCGetAuthInfoMethod, jmsg);
        m_jniEnv->DeleteLocalRef(jmsg);

        const char* v = (char*)m_jniEnv->GetStringUTFChars(ret, JNI_FALSE);
        const char* s = strdup(v);
        m_jniEnv->ReleaseStringUTFChars(ret, v);
        STRINGZ_TO_NPVARIANT(s, *result);
        return true;
    } else if (name == m_CTCGetConfigName) {
        if (argCount != 1 || !NPVARIANT_IS_STRING(args[0]))
            return false;
        NPString msg = NPVARIANT_TO_STRING(args[0]);
        jstring jmsg = m_jniEnv->NewStringUTF(msg.UTF8Characters);
        jstring ret = (jstring)m_jniEnv->CallObjectMethod(m_object, m_CTCGetConfigMethod, jmsg);
        m_jniEnv->DeleteLocalRef(jmsg);
        const char* v = (char*)m_jniEnv->GetStringUTFChars(ret, JNI_FALSE);
        const char* s = strdup(v);
        m_jniEnv->ReleaseStringUTFChars(ret, v);
        STRINGZ_TO_NPVARIANT(s, *result);
        return true;
    } else if (name == m_CTCSetConfigName) {
        if (argCount != 2 || !NPVARIANT_IS_STRING(args[0])||!NPVARIANT_IS_STRING(args[1]))
            return false;
        NPString msg = NPVARIANT_TO_STRING(args[0]);
        jstring jmsg = m_jniEnv->NewStringUTF(msg.UTF8Characters);

        NPString msg1 = NPVARIANT_TO_STRING(args[1]);
        jstring jmsg1 = m_jniEnv->NewStringUTF(msg1.UTF8Characters);

        m_jniEnv->CallVoidMethod(m_object, m_CTCSetConfigMethod, jmsg,jmsg1);
        m_jniEnv->DeleteLocalRef(jmsg);
        m_jniEnv->DeleteLocalRef(jmsg1);
        VOID_TO_NPVARIANT(*result);
        return true;
    } else if (name == m_CTCStartUpdateName) {
        m_jniEnv->CallBooleanMethod(m_object, m_CTCStartUpdateMethod);
        BOOLEAN_TO_NPVARIANT(true,*result);
        return true;
    } else if (name == m_setAuthParamName) {
        if (argCount != 5 || !NPVARIANT_IS_STRING(args[0])
                || !NPVARIANT_IS_STRING(args[1])
                || !NPVARIANT_IS_STRING(args[2])
                || !NPVARIANT_IS_STRING(args[3])
                || !NPVARIANT_IS_STRING(args[4])
           )
            return false;
        jstring jmsg[5];
        NPString msg[5];
        for(int i=0;i<5;i++){
            msg[i] = NPVARIANT_TO_STRING(args[i]);
            jmsg[i] = m_jniEnv->NewStringUTF(msg[i].UTF8Characters);
        }
        m_jniEnv->CallBooleanMethod(m_object, m_setAuthParamMethod, jmsg[0],jmsg[1],jmsg[2],jmsg[3],jmsg[4]);
        for(int i=0;i<5;i++){
            msg[i] = NPVARIANT_TO_STRING(args[i]);
            m_jniEnv->DeleteLocalRef(jmsg[i]);
        }
        BOOLEAN_TO_NPVARIANT(true,*result);
        return true;
    } else if (name == m_loginName) {
        m_jniEnv->CallBooleanMethod(m_object, m_loginMethod);
        VOID_TO_NPVARIANT(*result);
        return true;
    }
    return false;
}

bool CAuthenticationPlugin::invokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    return true;
}





