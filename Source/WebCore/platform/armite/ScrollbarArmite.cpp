/*
 *  Copyright (C) 2012 armite@126.com
 */

#include "config.h"
#include "Scrollbar.h"

#include "ChromeClient.h"
#include "Frame.h"
#include "FrameView.h"
#include "GraphicsContext.h"
#include "HostWindow.h"
#include "IntRect.h"
#include "NotImplemented.h"
#include "Page.h"
#include "ScrollbarTheme.h"

#include <string>
#include <wtf/text/CString.h>

using namespace std;
using namespace WebCore;

PassRefPtr<Scrollbar> Scrollbar::createNativeScrollbar(ScrollableArea* scrollableArea, ScrollbarOrientation orientation, ScrollbarControlSize size)
{
    notImplemented();
    return NULL;
}


