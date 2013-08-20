/*
 * add by armite@126.com
 */

#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include "jni.h"
#include "pluginbase.h"

class CNavigationPlugin : CPlugin {
public:
    CNavigationPlugin(NPP pNPInstance);
    ~CNavigationPlugin();

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

//disableDefaultNavigation
    NPIdentifier m_disableDefaultNavigationName;
    jmethodID m_disableDefaultNavigationMethod;
//disableHighlight
    NPIdentifier m_disableHighlightName;
    jmethodID m_disableHighlightMethod;
//enableDefaultNavigation
    NPIdentifier m_enableDefaultNavigationName;
    jmethodID m_enableDefaultNavigationMethod;
//enableHighlight
    NPIdentifier m_enableHighlightName;
    jmethodID m_enableHighlightMethod;
//focusElement
    NPIdentifier m_focusElementName;
    jmethodID m_focusElementMethod;
//getCurrentElement
    NPIdentifier m_getCurrentElementName;
    jmethodID m_getCurrentElementMethod;
//getDefaultNavigation
    NPIdentifier m_getDefaultNavigationName;
    jmethodID m_getDefaultNavigationMethod;
//getHighlight
    NPIdentifier m_getHighlightName;
    jmethodID m_getHighlightMethod;

};

#endif // __PLUGIN_H__



