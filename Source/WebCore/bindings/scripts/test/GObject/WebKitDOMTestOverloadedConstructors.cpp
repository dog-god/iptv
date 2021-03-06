/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#include "config.h"
#include "WebKitDOMTestOverloadedConstructors.h"

#include "DOMObjectCache.h"
#include "ExceptionCode.h"
#include "JSMainThreadExecState.h"
#include "WebKitDOMBinding.h"
#include "WebKitDOMTestOverloadedConstructorsPrivate.h"
#include "gobject/ConvertToUTF8String.h"
#include "webkitglobalsprivate.h"
#include <wtf/GetPtr.h>
#include <wtf/RefPtr.h>

namespace WebKit {

WebKitDOMTestOverloadedConstructors* kit(WebCore::TestOverloadedConstructors* obj)
{
    g_return_val_if_fail(obj, 0);

    if (gpointer ret = DOMObjectCache::get(obj))
        return static_cast<WebKitDOMTestOverloadedConstructors*>(ret);

    return static_cast<WebKitDOMTestOverloadedConstructors*>(DOMObjectCache::put(obj, WebKit::wrapTestOverloadedConstructors(obj)));
}

WebCore::TestOverloadedConstructors* core(WebKitDOMTestOverloadedConstructors* request)
{
    g_return_val_if_fail(request, 0);

    WebCore::TestOverloadedConstructors* coreObject = static_cast<WebCore::TestOverloadedConstructors*>(WEBKIT_DOM_OBJECT(request)->coreObject);
    g_return_val_if_fail(coreObject, 0);

    return coreObject;
}

WebKitDOMTestOverloadedConstructors* wrapTestOverloadedConstructors(WebCore::TestOverloadedConstructors* coreObject)
{
    g_return_val_if_fail(coreObject, 0);

    // We call ref() rather than using a C++ smart pointer because we can't store a C++ object
    // in a C-allocated GObject structure. See the finalize() code for the matching deref().
    coreObject->ref();

    return WEBKIT_DOM_TEST_OVERLOADED_CONSTRUCTORS(g_object_new(WEBKIT_TYPE_DOM_TEST_OVERLOADED_CONSTRUCTORS, "core-object", coreObject, NULL));
}

} // namespace WebKit

G_DEFINE_TYPE(WebKitDOMTestOverloadedConstructors, webkit_dom_test_overloaded_constructors, WEBKIT_TYPE_DOM_OBJECT)

enum {
    PROP_0,
};

static void webkit_dom_test_overloaded_constructors_finalize(GObject* object)
{

    WebKitDOMObject* domObject = WEBKIT_DOM_OBJECT(object);
    
    if (domObject->coreObject) {
        WebCore::TestOverloadedConstructors* coreObject = static_cast<WebCore::TestOverloadedConstructors*>(domObject->coreObject);

        WebKit::DOMObjectCache::forget(coreObject);
        coreObject->deref();

        domObject->coreObject = 0;
    }


    G_OBJECT_CLASS(webkit_dom_test_overloaded_constructors_parent_class)->finalize(object);
}

static void webkit_dom_test_overloaded_constructors_set_property(GObject* object, guint propertyId, const GValue* value, GParamSpec* pspec)
{
    WebCore::JSMainThreadNullState state;
    switch (propertyId) {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, propertyId, pspec);
        break;
    }
}


static void webkit_dom_test_overloaded_constructors_get_property(GObject* object, guint propertyId, GValue* value, GParamSpec* pspec)
{
    WebCore::JSMainThreadNullState state;
    switch (propertyId) {
    default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, propertyId, pspec);
        break;
    }
}


static void webkit_dom_test_overloaded_constructors_constructed(GObject* object)
{

    if (G_OBJECT_CLASS(webkit_dom_test_overloaded_constructors_parent_class)->constructed)
        G_OBJECT_CLASS(webkit_dom_test_overloaded_constructors_parent_class)->constructed(object);
}

static void webkit_dom_test_overloaded_constructors_class_init(WebKitDOMTestOverloadedConstructorsClass* requestClass)
{
    GObjectClass* gobjectClass = G_OBJECT_CLASS(requestClass);
    gobjectClass->finalize = webkit_dom_test_overloaded_constructors_finalize;
    gobjectClass->set_property = webkit_dom_test_overloaded_constructors_set_property;
    gobjectClass->get_property = webkit_dom_test_overloaded_constructors_get_property;
    gobjectClass->constructed = webkit_dom_test_overloaded_constructors_constructed;



}

static void webkit_dom_test_overloaded_constructors_init(WebKitDOMTestOverloadedConstructors* request)
{
}

