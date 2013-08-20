/*
 * Copyright (C) 2012 armite@126.com
 */

#include "config.h"
#include "MIMETypeRegistry.h"
#include "NotImplemented.h"

#include <wtf/Assertions.h>
#include <wtf/MainThread.h>

namespace WebCore {

String MIMETypeRegistry::getMIMETypeForExtension(const String &ext)
{
    notImplemented();
    return String();
}

bool MIMETypeRegistry::isApplicationPluginMIMEType(const String&)
{
    notImplemented();
    return false;
}

}


