/*
 * Copyright (C) 2012 armite@126.com.  All rights reserved.
 */

#include "config.h"
#include "Language.h"

#include <wtf/text/WTFString.h>
#include <locale.h>
#include <wtf/Vector.h>

namespace WebCore {

Vector<String> platformUserPreferredLanguages()
{
    Vector<String> userPreferredLanguages;
    userPreferredLanguages.append(String("c"));
    return userPreferredLanguages;
}


}



