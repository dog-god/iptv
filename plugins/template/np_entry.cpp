/*
 * add by armite@126.com
 */
#include "npapi.h"
#include "npfunctions.h"
#include "log.h"
#include "pluginbase.h"

NPNetscapeFuncs NPNFuncs;

extern "C" const char* NP_GetMIMEDescription();
const char* NP_GetMIMEDescription()
{
    return CPlugin::getMIMEDescription();
}

extern "C" NPError NP_GetValue(void* future, NPPVariable variable, void *value);
NPError NP_GetValue(void* future, NPPVariable variable, void *value)
{
    if (NPPVpluginNameString != variable && NPPVpluginDescriptionString != variable)
        return NPERR_INVALID_PARAM;
    *((const char **)value) = CPlugin::getPluginName();
    return NPERR_NO_ERROR;
}

extern "C" const char* NP_GetPluginVersion();
const char* NP_GetPluginVersion()
{
    return "1.2.3.4";
}

extern "C" NPError NP_Initialize(NPNetscapeFuncs* pFuncs , NPPluginFuncs* pluginFuncs);
NPError NP_Initialize(NPNetscapeFuncs* pFuncs , NPPluginFuncs* pluginFuncs)
{
    if(pFuncs == NULL)
        return NPERR_INVALID_FUNCTABLE_ERROR;

    if(HIBYTE(pFuncs->version) > NP_VERSION_MAJOR)
        return NPERR_INCOMPATIBLE_VERSION_ERROR;

    if(pFuncs->size < sizeof(NPNetscapeFuncs))
        return NPERR_INVALID_FUNCTABLE_ERROR;

    NPNFuncs.size                    = pFuncs->size;
    NPNFuncs.version                 = pFuncs->version;
    NPNFuncs.geturlnotify            = pFuncs->geturlnotify;
    NPNFuncs.geturl                  = pFuncs->geturl;
    NPNFuncs.posturlnotify           = pFuncs->posturlnotify;
    NPNFuncs.posturl                 = pFuncs->posturl;
    NPNFuncs.requestread             = pFuncs->requestread;
    NPNFuncs.newstream               = pFuncs->newstream;
    NPNFuncs.write                   = pFuncs->write;
    NPNFuncs.destroystream           = pFuncs->destroystream;
    NPNFuncs.status                  = pFuncs->status;
    NPNFuncs.uagent                  = pFuncs->uagent;
    NPNFuncs.memalloc                = pFuncs->memalloc;
    NPNFuncs.memfree                 = pFuncs->memfree;
    NPNFuncs.memflush                = pFuncs->memflush;
    NPNFuncs.reloadplugins           = pFuncs->reloadplugins;
    NPNFuncs.getJavaEnv              = pFuncs->getJavaEnv;
    NPNFuncs.getJavaPeer             = pFuncs->getJavaPeer;
    NPNFuncs.getvalue                = pFuncs->getvalue;
    NPNFuncs.setvalue                = pFuncs->setvalue;
    NPNFuncs.invalidaterect          = pFuncs->invalidaterect;
    NPNFuncs.invalidateregion        = pFuncs->invalidateregion;
    NPNFuncs.forceredraw             = pFuncs->forceredraw;
    NPNFuncs.getstringidentifier     = pFuncs->getstringidentifier;
    NPNFuncs.getstringidentifiers    = pFuncs->getstringidentifiers;
    NPNFuncs.getintidentifier        = pFuncs->getintidentifier;
    NPNFuncs.identifierisstring      = pFuncs->identifierisstring;
    NPNFuncs.utf8fromidentifier      = pFuncs->utf8fromidentifier;
    NPNFuncs.intfromidentifier       = pFuncs->intfromidentifier;
    NPNFuncs.createobject            = pFuncs->createobject;
    NPNFuncs.retainobject            = pFuncs->retainobject;
    NPNFuncs.releaseobject           = pFuncs->releaseobject;
    NPNFuncs.invoke                  = pFuncs->invoke;
    NPNFuncs.invokeDefault           = pFuncs->invokeDefault;
    NPNFuncs.evaluate                = pFuncs->evaluate;
    NPNFuncs.getproperty             = pFuncs->getproperty;
    NPNFuncs.setproperty             = pFuncs->setproperty;
    NPNFuncs.removeproperty          = pFuncs->removeproperty;
    NPNFuncs.hasproperty             = pFuncs->hasproperty;
    NPNFuncs.hasmethod               = pFuncs->hasmethod;
    NPNFuncs.releasevariantvalue     = pFuncs->releasevariantvalue;
    NPNFuncs.setexception            = pFuncs->setexception;
    NPNFuncs.pluginthreadasynccall   = pFuncs->pluginthreadasynccall;

    pluginFuncs->version            = (NP_VERSION_MAJOR << 8) + NP_VERSION_MINOR;
    pluginFuncs->size               = sizeof(NPPluginFuncs);
    pluginFuncs->newp               = (NPP_NewProcPtr)(NPP_New);
    pluginFuncs->destroy            = (NPP_DestroyProcPtr)(NPP_Destroy);
    pluginFuncs->setwindow          = (NPP_SetWindowProcPtr)(NPP_SetWindow);
    pluginFuncs->newstream          = (NPP_NewStreamProcPtr)(NPP_NewStream);
    pluginFuncs->destroystream      = (NPP_DestroyStreamProcPtr)(NPP_DestroyStream);
    pluginFuncs->asfile             = (NPP_StreamAsFileProcPtr)(NPP_StreamAsFile);
    pluginFuncs->writeready         = (NPP_WriteReadyProcPtr)(NPP_WriteReady);
    pluginFuncs->write              = (NPP_WriteProcPtr)(NPP_Write);
    pluginFuncs->print              = (NPP_PrintProcPtr)(NPP_Print);
    pluginFuncs->urlnotify          = (NPP_URLNotifyProcPtr)(NPP_URLNotify);
    pluginFuncs->event              = (NPP_HandleEventProcPtr)(NPP_HandleEvent);
    pluginFuncs->getvalue           = (NPP_GetValueProcPtr)(NPP_GetValue);
    pluginFuncs->setvalue           = (NPP_SetValueProcPtr)(NPP_SetValue);
    pluginFuncs->javaClass          = NULL;
    pluginFuncs->gotfocus           = (NPP_GotFocusPtr)NPP_GotFocus;
    pluginFuncs->lostfocus          = (NPP_LostFocusPtr)NPP_LostFocus;
    pluginFuncs->urlredirectnotify  = (NPP_URLRedirectNotifyPtr)NPP_URLRedirectNotify;
    pluginFuncs->clearsitedata      = (NPP_ClearSiteDataPtr)NPP_ClearSiteData;
    pluginFuncs->getsiteswithdata   = (NPP_GetSitesWithDataPtr)NPP_GetSitesWithData;

    return NPERR_NO_ERROR;
}

extern "C" void  NP_Shutdown();
void  NP_Shutdown()
{
}



