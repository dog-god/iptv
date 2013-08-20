/*
 * Copyright (C) 2012 armite@126.com All Rights Reserved.
 */

#include "config.h"
#include "PluginPackage.h"

#include "MIMETypeRegistry.h"
#include "NotImplemented.h"
#include "npruntime_impl.h"
#include "PluginDebug.h"
#include "WebKitTypes.h"

#include "dlfcn.h"

namespace WebCore {

bool PluginPackage::fetchInfo()
{
    if (!load())
        return false;

    NP_GetMIMEDescriptionFuncPtr NP_GetMIMEDescription = 0;
    NPP_GetValueProcPtr NPP_GetValue = 0;

    NP_GetMIMEDescription = (NP_GetMIMEDescriptionFuncPtr)dlsym(m_module,"NP_GetMIMEDescription");
    NPP_GetValue = (NPP_GetValueProcPtr)dlsym(m_module,"NP_GetValue");

    if (!NP_GetMIMEDescription || !NPP_GetValue)
        return false;

    char* buffer = 0;
    NPError err = NPP_GetValue(0, NPPVpluginNameString, &buffer);
    if (err != NPERR_NO_ERROR)
        return false;
    m_name = String::fromUTF8(buffer);

    buffer = 0;
    err = NPP_GetValue(0, NPPVpluginDescriptionString, &buffer);
    if (err != NPERR_NO_ERROR)
        return false;
    m_description = String::fromUTF8(buffer);
    determineModuleVersionFromDescription();

    String description = String::fromUTF8(NP_GetMIMEDescription());
    Vector<String> types;
    description.split(UChar(';'), false, types);
    for (unsigned i = 0; i < types.size(); ++i) {
        Vector<String> mime;
        types[i].split(UChar(':'), true, mime);
        if (mime.size() > 0) {
            Vector<String> exts;
            if (mime.size() > 1)
                mime[1].split(UChar(','), false, exts);
            m_mimeToExtensions.add(mime[0], exts);
            if (mime.size() > 2)
                m_mimeToDescriptions.add(mime[0], mime[2]);
        }
    }

    return true;
}

bool PluginPackage::load()
{
    if (m_isLoaded) {
        m_loadCount++;
        return true;
    }

    m_module = dlopen(m_path.utf8().data(), RTLD_LAZY);
    if (!m_module) {
        LOGI("Module Load Failed :%s, Error:%s\n", (m_path.utf8()).data(), dlerror());
        return false;
    }
    m_isLoaded = true;

    NP_InitializeFuncPtr NP_Initialize = 0;
    m_NPP_Shutdown = 0;

    NPError npErr;

    NP_Initialize = (NP_InitializeFuncPtr)dlsym(m_module,"NP_Initialize");
    m_NPP_Shutdown = (NPP_ShutdownProcPtr)dlsym(m_module,"NP_Shutdown");

    if (!NP_Initialize || !m_NPP_Shutdown)
        goto abort;

    memset(&m_pluginFuncs, 0, sizeof(m_pluginFuncs));
    m_pluginFuncs.size = sizeof(m_pluginFuncs);

    initializeBrowserFuncs();

    npErr = NP_Initialize(&m_browserFuncs, &m_pluginFuncs);

    if (npErr != NPERR_NO_ERROR)
        goto abort;

    m_loadCount++;
    return true;

abort:
    unloadWithoutShutdown();
    return false;
}

#if ENABLE(NETSCAPE_PLUGIN_API)
uint16_t PluginPackage::NPVersion() const
{
    return 5;
}
#endif

}



