/*
 * Copyright (C) 2012 armite@126.com
 */

#include "config.h"
#include "Cursor.h"

#include "NotImplemented.h"

#include <stdio.h>
#include <wtf/Assertions.h>

namespace WebCore {

Cursor::Cursor(const Cursor& other)
    : m_platformCursor(other.m_platformCursor)
{
    notImplemented();
}

Cursor::~Cursor()
{
    notImplemented();
}

Cursor& Cursor::operator=(const Cursor& other)
{
    notImplemented();
    m_platformCursor = other.m_platformCursor;
    return *this;
}

void Cursor::ensurePlatformCursor() const
{
    notImplemented();
    m_platformCursor = NULL;
}

}



