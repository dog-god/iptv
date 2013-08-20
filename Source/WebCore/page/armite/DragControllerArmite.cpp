/*
 * Copyright (C) 2012 armite@126.com.
 */

#include "config.h"
#include "DragController.h"

#include "DragData.h"
#include "Frame.h"
#include "FrameView.h"
#include "Page.h"
#include "NotImplemented.h"

namespace WebCore {

const int DragController::LinkDragBorderInset = 2;
const int DragController::MaxOriginalImageArea = 1500 * 1500;
const int DragController::DragIconRightInset = 7;
const int DragController::DragIconBottomInset = 3;

const float DragController::DragImageAlpha = 0.75f;

bool DragController::isCopyKeyDown(DragData*)
{
    notImplemented();
    return false;
}

DragOperation DragController::dragOperation(DragData* dragData)
{
    notImplemented();
    return DragOperationNone;
}

const IntSize& DragController::maxDragImageSize()
{
    notImplemented();
    static const IntSize maxDragImageSize(0, 0);
    return maxDragImageSize;
}

void DragController::cleanupAfterSystemDrag()
{
    notImplemented();
}

}



