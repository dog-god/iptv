/*
 * Copyright (C) 2012 armite@126.com.  All rights reserved.
 */

#include "config.h"
#include "Image.h"

#include "BitmapImage.h"
#include "SharedBuffer.h"
#include "NotImplemented.h"

#include <wtf/text/StringConcatenate.h>
#include <cairo.h>

namespace WebCore {

void BitmapImage::invalidatePlatformData()
{
    notImplemented();
}

PassRefPtr<Image> Image::loadPlatformResource(const char* name)
{
    notImplemented();
    return NULL;
}

}
