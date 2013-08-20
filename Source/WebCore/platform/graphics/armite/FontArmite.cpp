/*
 * Copyright (C) 2012 armite@126.com.
 *
 */

#include "config.h"
#include "Font.h"

#include "GraphicsContext.h"
#include "NotImplemented.h"
#include "SimpleFontData.h"

#include <cairo.h>

namespace WebCore {

void Font::drawComplexText(GraphicsContext*, const TextRun&, const FloatPoint&, int from, int to) const
{
    notImplemented();
}

void Font::drawEmphasisMarksForComplexText(GraphicsContext* /* context */, const TextRun& /* run */, const AtomicString& /* mark */, const FloatPoint& /* point */, int /* from */, int /* to */) const
{
    notImplemented();
}

bool Font::canReturnFallbackFontsForComplexText()
{
    return false;
}

bool Font::canExpandAroundIdeographsInComplexText()
{
    return false;
}

float Font::floatWidthForComplexText(const TextRun&, HashSet<const SimpleFontData*>*, GlyphOverflow*) const
{
    notImplemented();
    return 0.0f;
}

int Font::offsetForPositionForComplexText(const TextRun&, float, bool) const
{
    notImplemented();
    return 0;
}

FloatRect Font::selectionRectForComplexText(const TextRun&, const FloatPoint&, int, int, int) const
{
    notImplemented();
    return FloatRect();
}

}



