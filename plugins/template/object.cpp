/*
 * add by armite@126.com
 */

#include "object.h"
#include "log.h"

#include <string.h>
#include <stdio.h>

void ScriptablePluginObjectBase::Invalidate()
{
    UNIMPLEMENTED();
}

bool ScriptablePluginObjectBase::HasMethod(NPIdentifier name)
{
    UNIMPLEMENTED();
    return false;
}

bool ScriptablePluginObjectBase::Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    UNIMPLEMENTED();
    return false;
}

bool ScriptablePluginObjectBase::InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    UNIMPLEMENTED();
    return false;
}

bool ScriptablePluginObjectBase::HasProperty(NPIdentifier name)
{
    UNIMPLEMENTED();
    return false;
}

bool ScriptablePluginObjectBase::GetProperty(NPIdentifier name, NPVariant *result)
{
    UNIMPLEMENTED();
    return false;
}

bool ScriptablePluginObjectBase::SetProperty(NPIdentifier name, const NPVariant *value)
{
    UNIMPLEMENTED();
    return false;
}

bool ScriptablePluginObjectBase::RemoveProperty(NPIdentifier name)
{
    UNIMPLEMENTED();
    return false;
}

bool ScriptablePluginObjectBase::Enumerate(NPIdentifier **identifier, uint32_t *count)
{
    UNIMPLEMENTED();
    return false;
}

bool ScriptablePluginObjectBase::Construct(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    UNIMPLEMENTED();
    return false;
}

// static
void ScriptablePluginObjectBase::_Deallocate(NPObject *npobj)
{
    delete (ScriptablePluginObjectBase *)npobj;
}

// static
void ScriptablePluginObjectBase::_Invalidate(NPObject *npobj)
{
    ((ScriptablePluginObjectBase *)npobj)->Invalidate();
}

// static
bool ScriptablePluginObjectBase::_HasMethod(NPObject *npobj, NPIdentifier name)
{
    return ((ScriptablePluginObjectBase *)npobj)->HasMethod(name);
}

// static
bool ScriptablePluginObjectBase::_Invoke(NPObject *npobj, NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    return ((ScriptablePluginObjectBase *)npobj)->Invoke(name, args, argCount, result);
}

// static
bool ScriptablePluginObjectBase::_InvokeDefault(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    return ((ScriptablePluginObjectBase *)npobj)->InvokeDefault(args, argCount, result);
}

// static
bool ScriptablePluginObjectBase::_HasProperty(NPObject * npobj, NPIdentifier name)
{
    return ((ScriptablePluginObjectBase *)npobj)->HasProperty(name);
}

// static
bool ScriptablePluginObjectBase::_GetProperty(NPObject *npobj, NPIdentifier name, NPVariant *result)
{
    return ((ScriptablePluginObjectBase *)npobj)->GetProperty(name, result);
}

// static
bool ScriptablePluginObjectBase::_SetProperty(NPObject *npobj, NPIdentifier name, const NPVariant *value)
{
    return ((ScriptablePluginObjectBase *)npobj)->SetProperty(name, value);
}

// static
bool ScriptablePluginObjectBase::_RemoveProperty(NPObject *npobj, NPIdentifier name)
{
    return ((ScriptablePluginObjectBase *)npobj)->RemoveProperty(name);
}

// static
bool ScriptablePluginObjectBase::_Enumerate(NPObject *npobj, NPIdentifier **identifier, uint32_t *count)
{
    return ((ScriptablePluginObjectBase *)npobj)->Enumerate(identifier, count);
}

// static
bool ScriptablePluginObjectBase::_Construct(NPObject *npobj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    return ((ScriptablePluginObjectBase *)npobj)->Construct(args, argCount, result);
}

bool ScriptablePluginObject::HasProperty(NPIdentifier name)
{
    if(!m_npp || !m_npp->pdata)
        return false;
    CPlugin * pPlugin = (CPlugin *)m_npp->pdata;
    return pPlugin->hasProperty(name);
}

bool ScriptablePluginObject::GetProperty(NPIdentifier name, NPVariant *result)
{
    if(!m_npp || !m_npp->pdata)
        return false;
    CPlugin * pPlugin = (CPlugin *)m_npp->pdata;
    return pPlugin->getProperty(name, result);
}

bool ScriptablePluginObject::SetProperty(NPIdentifier name, const NPVariant *value)
{
    if(!m_npp || !m_npp->pdata)
        return false;
    CPlugin * pPlugin = (CPlugin *)m_npp->pdata;
    return pPlugin->setProperty(name, value);

}

bool ScriptablePluginObject::HasMethod(NPIdentifier name)
{
    if(!m_npp || !m_npp->pdata)
        return false;
    CPlugin * pPlugin = (CPlugin *)m_npp->pdata;
    return pPlugin->hasMethod(name);
}

bool ScriptablePluginObject::Invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    if(!m_npp || !m_npp->pdata)
        return false;
    CPlugin * pPlugin = (CPlugin *)m_npp->pdata;
    return pPlugin->invoke(name, args, argCount, result);
}

bool ScriptablePluginObject::Construct(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    return InvokeDefault(args, argCount, result);
}

bool ScriptablePluginObject::InvokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    if(!m_npp || !m_npp->pdata)
        return false;
    CPlugin * pPlugin = (CPlugin *)m_npp->pdata;
    return pPlugin->invokeDefault(args, argCount, result);
}



