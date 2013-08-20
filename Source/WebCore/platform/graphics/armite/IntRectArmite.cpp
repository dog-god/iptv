/*
 * Copyright (C) 2012 armite@126.com.  All rights reserved.
 *
 */
#include "config.h"
#include "IntRect.h"
#include "WebKitTypes.h"

namespace WebCore {

IntRect::IntRect(const ArmiteRect& r)
    : m_location(IntPoint(r.x, r.y))
    , m_size(r.w, r.h)
{
}

IntRect::operator ArmiteRect() const
{
    ArmiteRect r = { x(), y(), width(), height() };
    return r;
}

}

