/*
 * Copyright (C) 2012 armite@126.com.
 */

#include "config.h"
#include "EventHandler.h"

#include "EventNames.h"
#include "FloatPoint.h"
#include "FocusController.h"
#include "Frame.h"
#include "FrameView.h"
#include "KeyboardEvent.h"
#include "MouseEventWithHitTestResults.h"
#include "NotImplemented.h"
#include "Page.h"
#include "PlatformKeyboardEvent.h"
#include "PlatformWheelEvent.h"
#include "RenderWidget.h"
#include "Scrollbar.h"

namespace WebCore {

#if ENABLE(DRAG_SUPPORT)
const double EventHandler::TextDragDelay = 0.0;

bool EventHandler::passWidgetMouseDownEventToWidget(RenderWidget* renderWidget)
{
    notImplemented();
    return false;
}

bool EventHandler::passMouseDownEventToWidget(Widget* widget)
{
    notImplemented();
    return false;
}

PassRefPtr<Clipboard> EventHandler::createDraggingClipboard() const
{
    notImplemented();
    return NULL;
}
#endif

bool EventHandler::passMouseMoveEventToSubframe(MouseEventWithHitTestResults& mev, Frame* subframe, HitTestResult* hoveredNode)
{
    notImplemented();
    return false;
}

bool EventHandler::eventActivatedView(const PlatformMouseEvent&) const
{
    notImplemented();
    return false;
}

bool EventHandler::passWidgetMouseDownEventToWidget(const MouseEventWithHitTestResults& event)
{
    notImplemented();
    return false;
}

bool EventHandler::tabsToAllFormControls(KeyboardEvent* event) const
{
    return false;
}

bool EventHandler::passWheelEventToWidget(const PlatformWheelEvent& event, Widget* widget)
{
    notImplemented();
    return false;
}

void EventHandler::focusDocumentView()
{
    if (Page* page = m_frame->page())
        page->focusController()->setFocusedFrame(m_frame);
}

bool EventHandler::passMousePressEventToSubframe(MouseEventWithHitTestResults& mev, Frame* subframe)
{
    notImplemented();
    return false;
}

bool EventHandler::passMouseReleaseEventToSubframe(MouseEventWithHitTestResults& mev, Frame* subframe)
{
    notImplemented();
    return false;
}

unsigned EventHandler::accessKeyModifiers()
{
    return PlatformKeyboardEvent::AltKey;
}

}



