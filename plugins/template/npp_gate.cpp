/*
 * add by armite@126.com
 */

#include "pluginbase.h"
#include "log.h"

NPError NPP_New(NPMIMEType pluginType, NPP instance, uint16_t mode, int16_t argc, char* argn[], char* argv[], NPSavedData* saved)
{
    if (!instance)
        return NPERR_INVALID_INSTANCE_ERROR;

    CPlugin *pPlugin = CPlugin::getPluginInstance(instance, argc, argn, argv);
    instance->pdata = (void *)pPlugin;
    return NPERR_NO_ERROR;
}

NPError NPP_Destroy(NPP instance, NPSavedData** save)
{
    if (!instance || !instance->pdata)
        return NPERR_INVALID_INSTANCE_ERROR;

    CPlugin::delPluginInstance(instance);
    instance->pdata = 0;
    return NPERR_NO_ERROR;
}

NPError NPP_GetValue(NPP instance, NPPVariable variable, void *value)
{
    if(NPPVpluginScriptableNPObject != variable)
        return NPERR_INVALID_PARAM;
    if(!instance || !instance->pdata)
        return NPERR_INVALID_INSTANCE_ERROR;

    CPlugin *pPlugin = (CPlugin *)instance->pdata;
    *(NPObject **)value = pPlugin->getScriptableObject();
    return NPERR_NO_ERROR;
}

int16_t NPP_HandleEvent(NPP instance, void* event)
{
    if(!instance || !instance->pdata)
        return 0;

    CPlugin * pPlugin = (CPlugin *)instance->pdata;
    return pPlugin->handleEvent(event);
}

NPError NPP_SetWindow (NPP instance, NPWindow* pNPWindow)
{
    if(!instance || !instance->pdata)
        return 0;

    CPlugin * pPlugin = (CPlugin *)instance->pdata;
    return pPlugin->setWindow(pNPWindow);
}

NPError NPP_NewStream(NPP instance, NPMIMEType type, NPStream* stream, NPBool seekable, uint16_t* stype)
{
    UNIMPLEMENTED();
    return NPERR_NO_ERROR;
}

int32_t NPP_WriteReady (NPP instance, NPStream *stream)
{
    UNIMPLEMENTED();
    return 0;
}

int32_t NPP_Write (NPP instance, NPStream *stream, int32_t offset, int32_t len, void *buffer)
{
    UNIMPLEMENTED();
    return 0;
}

NPError NPP_DestroyStream (NPP instance, NPStream *stream, NPError reason)
{
    UNIMPLEMENTED();
    return NPERR_NO_ERROR;
}

void NPP_StreamAsFile (NPP instance, NPStream* stream, const char* fname)
{
    UNIMPLEMENTED();
}

void NPP_Print (NPP instance, NPPrint* printInfo)
{
    UNIMPLEMENTED();
}

void NPP_URLNotify(NPP instance, const char* url, NPReason reason, void* notifyData)
{
    UNIMPLEMENTED();
}

NPError NPP_SetValue(NPP instance, NPNVariable variable, void *value)
{
    UNIMPLEMENTED();
    return NPERR_NO_ERROR;
}

NPBool NPP_GotFocus(NPP instance, NPFocusDirection direction)
{
    UNIMPLEMENTED();
    return false;
}

void NPP_LostFocus(NPP instance)
{
    UNIMPLEMENTED();
}

void NPP_URLRedirectNotify(NPP instance, const char* url, int32_t status, void* notifyData)
{
    UNIMPLEMENTED();
}

NPError NPP_ClearSiteData(const char* site, uint64_t flags, uint64_t maxAge)
{
    UNIMPLEMENTED();
    return NPERR_NO_ERROR;
}

char** NPP_GetSitesWithData(void)
{
    UNIMPLEMENTED();
    return NULL;
}

NPError NPP_Initialize(void)
{
    UNIMPLEMENTED();
    return NPERR_NO_ERROR;
}

void NPP_Shutdown(void)
{
    UNIMPLEMENTED();
}



