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
    return "application/Navigation::Navigation";
}

const char *CPlugin::getPluginName()
{
    return "Navigation";
}

CPlugin* CPlugin::getPluginInstance(NPP instance, int16_t argc, char* argn[], char* argv[])
{
    return (CPlugin*)new CNavigationPlugin(instance);
}

void CPlugin::delPluginInstance(NPP instance)
{
    CNavigationPlugin* pPlugin = (CNavigationPlugin*)instance->pdata;
    delete pPlugin;
}

CNavigationPlugin::CNavigationPlugin(NPP pNPInstance) 
    : CPlugin(pNPInstance)
{
    m_jniEnv = (JNIEnv*)NPN_GetJavaEnv();
    jclass clazz = m_jniEnv->FindClass("com/armite/webkit/plug/Navigation");
    m_class = (jclass)m_jniEnv->NewGlobalRef(clazz);

    jobject object = m_jniEnv->AllocObject(m_class);
    m_object = m_jniEnv->NewGlobalRef(object);

//disableDefaultNavigation
    m_disableDefaultNavigationName = NPN_GetStringIdentifier("disableDefaultNavigation");
    m_disableDefaultNavigationMethod = m_jniEnv->GetMethodID(m_class, "disableDefaultNavigation", "()V");

//disableHighlight
    m_disableHighlightName = NPN_GetStringIdentifier("disableHighlight");
    m_disableHighlightMethod = m_jniEnv->GetMethodID(m_class, "disableHighlight", "()V");

//enableDefaultNavigation
    m_enableDefaultNavigationName = NPN_GetStringIdentifier("enableDefaultNavigation");
    m_enableDefaultNavigationMethod = m_jniEnv->GetMethodID(m_class, "enableDefaultNavigation", "()V");

//enableHighlight
    m_enableHighlightName = NPN_GetStringIdentifier("enableHighlight");
    m_enableHighlightMethod = m_jniEnv->GetMethodID(m_class, "enableHighlight", "()V");
//focusElement
	m_focusElementName= NPN_GetStringIdentifier("focusElement");
//    jmethodID m_focusElementMethod;
//getCurrentElement
   m_getCurrentElementName = NPN_GetStringIdentifier("getCurrentElement");
   //m_getCurrentElementMethod = m_jniEnv->GetMethodID(m_class, "getCurrentElement", "()Z");
//getDefaultNavigation
   m_getDefaultNavigationName = NPN_GetStringIdentifier("getDefaultNavigation");
   m_getDefaultNavigationMethod = m_jniEnv->GetMethodID(m_class, "getDefaultNavigation", "()Z");
//getHighlight
   m_getHighlightName = NPN_GetStringIdentifier("getHighlight");
   m_getHighlightMethod = m_jniEnv->GetMethodID(m_class, "getHighlight", "()Z");

}

CNavigationPlugin::~CNavigationPlugin()
{
    if (m_class)
        m_jniEnv->DeleteGlobalRef(m_class);
    if (m_object)
        m_jniEnv->DeleteGlobalRef(m_object);
}

bool CNavigationPlugin::setProperty(NPIdentifier name, const NPVariant *value)
{
    UNIMPLEMENTED();
    return false;
}

bool CNavigationPlugin::hasProperty(NPIdentifier name)
{
    return false;
}

bool CNavigationPlugin::getProperty(NPIdentifier name, const NPVariant *result)
{
    UNIMPLEMENTED();
    return false;
}

bool CNavigationPlugin::hasMethod(NPIdentifier name)
{
    if (name == m_disableDefaultNavigationName)
        return true;
    else if (name == m_disableHighlightName)
        return true;
    else if (name == m_enableDefaultNavigationName)
        return true;
    else if (name == m_enableHighlightName)
        return true;
    else if (name == m_focusElementName)
        return true;
    else if (name == m_getCurrentElementName)
        return true;
  else if (name == m_getDefaultNavigationName)
        return true;
  else if (name == m_getHighlightName)
        return true;
    return false;
}

bool CNavigationPlugin::invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    if (name == m_disableDefaultNavigationName){
        m_jniEnv->CallVoidMethod(m_object, m_disableDefaultNavigationMethod);
	return true;
    }
    else if (name == m_disableHighlightName){
 	m_jniEnv->CallVoidMethod(m_object, m_disableHighlightMethod);
	return true;
    }
    else if (name == m_enableDefaultNavigationName){
	m_jniEnv->CallVoidMethod(m_object, m_enableDefaultNavigationMethod);	
        return true;
    }
    else if (name == m_enableHighlightName){
	m_jniEnv->CallVoidMethod(m_object, m_enableHighlightMethod);	
        return true;
    }
    else if (name == m_focusElementName){
        return true;
    }
    else if (name == m_getCurrentElementName){
        return true;
    }
    else if (name == m_getDefaultNavigationName){
	m_jniEnv->CallBooleanMethod(m_object, m_getDefaultNavigationMethod);
        return true;
    }
    else if (name == m_getHighlightName){
	m_jniEnv->CallBooleanMethod(m_object, m_getHighlightMethod);
        return true;
    }
    return false;
}

bool CNavigationPlugin::invokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    return true;
}






