/*
 * add by armite@126.com
 */

#ifndef __PLUGINBASE_H__
#define __PLUGINBASE_H__

#include "npapi.h"
#include "npruntime.h"

class CPlugin {
public:
    CPlugin(NPP);
    ~CPlugin();

    NPObject *getScriptableObject();
    virtual int16_t handleEvent(void* event) { return 0; }
    virtual NPError setWindow(NPWindow* pNPWindow) { return NPERR_NO_ERROR; }

    virtual bool hasProperty(NPIdentifier name) { return false; }
    virtual bool setProperty(NPIdentifier name, const NPVariant *value) { return false; }
    virtual bool getProperty(NPIdentifier name, const NPVariant *result) { return false; }

    virtual bool hasMethod(NPIdentifier name) { return false; }
    virtual bool invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result) {return false;}
    virtual bool invokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result) { return false; }

    static const char *getMIMEDescription();
    static const char *getPluginName();
    static CPlugin* getPluginInstance(NPP instance, int16_t argc, char* argn[], char* argv[]);
    static void delPluginInstance(NPP instance);

protected:
    NPP m_pNPInstance;
    NPObject *m_pScriptableObject;
};

#endif // __PLUGIN_H__



