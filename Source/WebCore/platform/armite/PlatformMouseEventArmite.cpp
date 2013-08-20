/*
 * Copyright (C) 2012 armite@126.com. All rights reserved.
 */

#include "config.h"
#include "WebKitTypes.h"
#include "PlatformMouseEvent.h"

#include <wtf/CurrentTime.h>

namespace WebCore {

PlatformMouseEvent::PlatformMouseEvent(ArmiteMouseEvent* event)
    : m_button(LeftButton)
    , m_clickCount(0)
    , m_modifierFlags(0)
{
    if (!event)
        return;

    IntPoint point(event->x, event->y);
    m_position = point;
    m_globalPosition = point;
    m_type = PlatformEvent::NoType;

    if (event->type == ARMITE_MOUSEEVENT_DOWN) {
        m_type = PlatformEvent::MousePressed;
        m_clickCount = 1;
    } else if (event->type == ARMITE_MOUSEEVENT_UP)
        m_type = PlatformEvent::MouseReleased;
    else if (event->type == ARMITE_MOUSEEVENT_MOVE)
        m_type = PlatformEvent::MouseMoved;
}


}


