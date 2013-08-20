/*
 * add by armite@126.com
 */

#include "object.h"
#include "pluginbase.h"

CPlugin::CPlugin(NPP instance)
    : m_pNPInstance(instance)
    , m_pScriptableObject(0)
{
}

CPlugin::~CPlugin()
{
    if (m_pScriptableObject)
        NPN_ReleaseObject(m_pScriptableObject);
}

static NPObject *AllocateScriptablePluginObject(NPP npp, NPClass *)
{
    return new ScriptablePluginObject(npp);
}

DECLARE_NPOBJECT_CLASS_WITH_BASE(ScriptablePluginObject, AllocateScriptablePluginObject);

NPObject* CPlugin::getScriptableObject()
{
    if (!m_pScriptableObject)
        m_pScriptableObject = NPN_CreateObject(m_pNPInstance, GET_NPOBJECT_CLASS(ScriptablePluginObject));
    return m_pScriptableObject;
}




