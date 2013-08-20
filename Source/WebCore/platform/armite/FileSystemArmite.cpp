/*
 * Copyright (C) 2012 armite@126.com. All rights reserved.
 */

#include "config.h"
#include "FileSystem.h"

#include "NotImplemented.h"

#include <dirent.h>
#include <dlfcn.h>
#include <errno.h>
#include <fnmatch.h>
#include <limits.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wtf/text/CString.h>

namespace WebCore {

CString fileSystemRepresentation(const String& path)
{
    return path.utf8();
}

bool unloadModule(PlatformModule module)
{
    return !dlclose(module);
}

String homeDirectoryPath()
{
    const char *home = getenv("ARMITE_PLUGINS_DIR");
    if (!home) {
        home = getenv("PWD");
        if (!home)
            home = "/data/data/com.armite.webkit/lib";
    }
    return String::fromUTF8(home);
}

}



