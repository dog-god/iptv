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
    return "application/iPanel::iPanel";
}

const char *CPlugin::getPluginName()
{
    return "iPanel";
}

CPlugin* CPlugin::getPluginInstance(NPP instance, int16_t argc, char* argn[], char* argv[])
{
    return (CPlugin*)new CiPanelPlugin(instance);
}

void CPlugin::delPluginInstance(NPP instance)
{
    CiPanelPlugin* pPlugin = (CiPanelPlugin*)instance->pdata;
    delete pPlugin;
}

CiPanelPlugin::CiPanelPlugin(NPP pNPInstance) 
    : CPlugin(pNPInstance)
{
    m_jniEnv = (JNIEnv*)NPN_GetJavaEnv();
    jclass clazz = m_jniEnv->FindClass("com/armite/webkit/plug/iPanel");
    m_class = (jclass)m_jniEnv->NewGlobalRef(clazz);

    jobject object = m_jniEnv->AllocObject(m_class);
    m_object = (jobject)m_jniEnv->NewGlobalRef(object);

    m_debugName = NPN_GetStringIdentifier("debug");
    m_debugMethod = m_jniEnv->GetMethodID(m_class, "debug", "(Ljava/lang/String;)V");
    m_ioctlWriteName = NPN_GetStringIdentifier("ioctlWrite");
    m_ioctlWriteMethod = m_jniEnv->GetMethodID(m_class, "ioctlWrite", "(Ljava/lang/String;Ljava/lang/String;)V");
}

CiPanelPlugin::~CiPanelPlugin()
{
    if (m_class)
        m_jniEnv->DeleteGlobalRef(m_class);
    if (m_object)
        m_jniEnv->DeleteGlobalRef(m_object);
}

bool CiPanelPlugin::setProperty(NPIdentifier name, const NPVariant *value)
{
    UNIMPLEMENTED();
    return false;
}

bool CiPanelPlugin::hasProperty(NPIdentifier name)
{
    return false;
}

bool CiPanelPlugin::getProperty(NPIdentifier name, const NPVariant *result)
{
    UNIMPLEMENTED();
    return false;
}

bool CiPanelPlugin::hasMethod(NPIdentifier name)
{
    if (name == m_debugName)
        return true;
    if (name == m_ioctlWriteName)
        return true;
    return false;
}

bool CiPanelPlugin::invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    if (name == m_debugName) {
        if (argCount != 1 || !NPVARIANT_IS_STRING(args[0]))
            return false;
        NPString msg = NPVARIANT_TO_STRING(args[0]);
        jstring jmsg = m_jniEnv->NewStringUTF(msg.UTF8Characters);
        m_jniEnv->CallVoidMethod(m_object, m_debugMethod, jmsg);
        m_jniEnv->DeleteLocalRef(jmsg);
        return true;
    }
    if (name == m_ioctlWriteName) {
        if (argCount != 2 || !NPVARIANT_IS_STRING(args[0]) || !NPVARIANT_IS_STRING(args[1]))
            return false;
        NPString msg1 = NPVARIANT_TO_STRING(args[0]);
        jstring jmsg1 = m_jniEnv->NewStringUTF(msg1.UTF8Characters);
        NPString msg2 = NPVARIANT_TO_STRING(args[1]);
        jstring jmsg2 = m_jniEnv->NewStringUTF(msg2.UTF8Characters);
        m_jniEnv->CallVoidMethod(m_object, m_ioctlWriteMethod, jmsg1, jmsg2);
        m_jniEnv->DeleteLocalRef(jmsg1);
        m_jniEnv->DeleteLocalRef(jmsg2);
        return true;
    }
    return false;
}

bool CiPanelPlugin::invokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    return true;
}






