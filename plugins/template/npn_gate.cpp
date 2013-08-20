/*
 * add by armite@126.com
 */

#include "npapi.h"
#include "npfunctions.h"
#include "log.h"

extern NPNetscapeFuncs NPNFuncs;

void NPN_Version(int* plugin_major, int* plugin_minor, int* netscape_major, int* netscape_minor)
{
    *plugin_major   = NP_VERSION_MAJOR;
    *plugin_minor   = NP_VERSION_MINOR;
    *netscape_major = HIBYTE(NPNFuncs.version);
    *netscape_minor = LOBYTE(NPNFuncs.version);
}

NPIdentifier NPN_GetStringIdentifier(const NPUTF8 *name)
{
    return NPNFuncs.getstringidentifier(name);
}

void NPN_GetStringIdentifiers(const NPUTF8 **names, uint32_t nameCount, NPIdentifier *identifiers)
{
    return NPNFuncs.getstringidentifiers(names, nameCount, identifiers);
}

NPIdentifier NPN_GetStringIdentifier(int32_t intid)
{
    return NPNFuncs.getintidentifier(intid);
}

bool NPN_IdentifierIsString(NPIdentifier identifier)
{
    return NPNFuncs.identifierisstring(identifier);
}

NPUTF8 *NPN_UTF8FromIdentifier(NPIdentifier identifier)
{
    return NPNFuncs.utf8fromidentifier(identifier);
}

int32_t NPN_IntFromIdentifier(NPIdentifier identifier)
{
    return NPNFuncs.intfromidentifier(identifier);
}

NPObject *NPN_CreateObject(NPP npp, NPClass *aClass)
{
    return NPNFuncs.createobject(npp, aClass);
}

NPObject *NPN_RetainObject(NPObject *obj)
{
    return NPNFuncs.retainobject(obj);
}

void NPN_ReleaseObject(NPObject *obj)
{
    return NPNFuncs.releaseobject(obj);
}

bool NPN_Invoke(NPP npp, NPObject* obj, NPIdentifier methodName, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    return NPNFuncs.invoke(npp, obj, methodName, args, argCount, result);
}

bool NPN_InvokeDefault(NPP npp, NPObject* obj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    return NPNFuncs.invokeDefault(npp, obj, args, argCount, result);
}

bool NPN_Evaluate(NPP npp, NPObject* obj, NPString *script, NPVariant *result)
{
    return NPNFuncs.evaluate(npp, obj, script, result);
}

bool NPN_GetProperty(NPP npp, NPObject* obj, NPIdentifier propertyName, NPVariant *result)
{
    return NPNFuncs.getproperty(npp, obj, propertyName, result);
}

bool NPN_SetProperty(NPP npp, NPObject* obj, NPIdentifier propertyName, const NPVariant *value)
{
    return NPNFuncs.setproperty(npp, obj, propertyName, value);
}

bool NPN_RemoveProperty(NPP npp, NPObject* obj, NPIdentifier propertyName)
{
    return NPNFuncs.removeproperty(npp, obj, propertyName);
}

bool NPN_Enumerate(NPP npp, NPObject *obj, NPIdentifier **identifier, uint32_t *count)
{
    return NPNFuncs.enumerate(npp, obj, identifier, count);
}

bool NPN_Construct(NPP npp, NPObject *obj, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    return NPNFuncs.construct(npp, obj, args, argCount, result);
}

bool NPN_HasProperty(NPP npp, NPObject* obj, NPIdentifier propertyName)
{
    return NPNFuncs.hasproperty(npp, obj, propertyName);
}

bool NPN_HasMethod(NPP npp, NPObject* obj, NPIdentifier methodName)
{
    return NPNFuncs.hasmethod(npp, obj, methodName);
}

void NPN_ReleaseVariantValue(NPVariant *variant)
{
    NPNFuncs.releasevariantvalue(variant);
}

void NPN_SetException(NPObject* obj, const NPUTF8 *message)
{
    NPNFuncs.setexception(obj, message);
}

void NP_LOADDS NPN_PluginThreadAsyncCall(NPP instance, void (*func) (void *), void *userData)
{
    NPNFuncs.pluginthreadasynccall(instance, func, userData);
}

void* NPN_GetJavaEnv()
{
    return NPNFuncs.getJavaEnv();
}

void* NPN_GetJavaPeer(NPP p)
{
    return NPNFuncs.getJavaPeer(p);
}

void* NPN_MemAlloc(uint32_t size)
{
    void * rv = NULL;
    rv = NPNFuncs.memalloc(size);
    return rv;
}

void NPN_MemFree(void* ptr)
{
    NPNFuncs.memfree(ptr);
}


