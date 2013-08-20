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
    return "application/demo::demo";
}

const char *CPlugin::getPluginName()
{
    return "demo";
}

CPlugin* CPlugin::getPluginInstance(NPP instance, int16_t argc, char* argn[], char* argv[])
{
    return (CPlugin*)new CDemoPlugin(instance);
}

void CPlugin::delPluginInstance(NPP instance)
{
    CDemoPlugin* pPlugin = (CDemoPlugin*)instance->pdata;
    delete pPlugin;
}

CDemoPlugin::CDemoPlugin(NPP pNPInstance) 
    : CPlugin(pNPInstance)
{
    m_jniEnv = (JNIEnv*)NPN_GetJavaEnv();
    jclass clazz = m_jniEnv->FindClass("com/armite/webkit/demo");
    m_class = (jclass)m_jniEnv->NewGlobalRef(clazz);

    jobject object = m_jniEnv->AllocObject(m_class);
    m_object = (jobject)m_jniEnv->NewGlobalRef(object);

    m_printName = NPN_GetStringIdentifier("print");
    m_printMethod = m_jniEnv->GetMethodID(m_class, "print", "(Ljava/lang/String;)Z");
}

CDemoPlugin::~CDemoPlugin()
{
    if (m_class)
        m_jniEnv->DeleteGlobalRef(m_class);
    if (m_object)
        m_jniEnv->DeleteGlobalRef(m_object);
}

bool CDemoPlugin::setProperty(NPIdentifier name, const NPVariant *value)
{
    UNIMPLEMENTED();
    return false;
}

bool CDemoPlugin::hasProperty(NPIdentifier name)
{
    return false;
}

bool CDemoPlugin::getProperty(NPIdentifier name, const NPVariant *result)
{
    UNIMPLEMENTED();
    return false;
}

bool CDemoPlugin::hasMethod(NPIdentifier name)
{
    if (name == m_printName)
        return true;
    return false;
}

bool CDemoPlugin::invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    if (name == m_printName) {
        if (argCount != 1 || !NPVARIANT_IS_STRING(args[0]))
            return false;
        NPString msg = NPVARIANT_TO_STRING(args[0]);
        jstring jmsg = m_jniEnv->NewStringUTF(msg.UTF8Characters);
        return m_jniEnv->CallBooleanMethod(m_object, m_printMethod, jmsg);
    }
    return false;
}

bool CDemoPlugin::invokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    return true;
}






