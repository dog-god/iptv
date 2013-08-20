/*
 * Copyright (C) 2012 arimite@126.com. All rights reserved.
 */

#include "config.h"
#include "PlatformScreen.h"

#include "NotImplemented.h"
#include "wtf/text/WTFString.h"
#include "Widget.h"
#include <wtf/text/CString.h>

namespace WebCore {

int screenHorizontalDPI(Widget* widget)
{
    notImplemented();
    return 0;
}

int screenVerticalDPI(Widget* widget)
{
    notImplemented();
    return 0;
}

int screenDepth(Widget* widget)
{
    notImplemented();
    return 8;
}

int screenDepthPerComponent(Widget*)
{
    notImplemented();
    return 8;
}

bool screenIsMonochrome(Widget*)
{
    notImplemented();
    return false;
}

FloatRect screenRect(Widget* widget)
{
    int x = 0, y = 0, w = 0, h = 0;

    return FloatRect(x, y, w, h);
}

FloatRect screenAvailableRect(Widget* widget)
{
    notImplemented();
    return screenRect(widget);
}

}
