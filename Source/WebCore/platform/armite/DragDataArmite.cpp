/*
 *  Copyright (C) 2012 armite@126.com
 */

#include "config.h"
#include "DragData.h"

#include "Document.h"
#include "NotImplemented.h"
#include "DocumentFragment.h"

namespace WebCore {

bool DragData::canSmartReplace() const
{
    notImplemented();
    return false;
}

bool DragData::containsColor() const
{
    notImplemented();
    return false;
}

bool DragData::containsFiles() const
{
    notImplemented();
    return false;
}

unsigned DragData::numberOfFiles() const
{
    notImplemented();
    return 0;
}

void DragData::asFilenames(Vector<String>& result) const
{
    notImplemented();
}

bool DragData::containsPlainText() const
{
    notImplemented();
    return false;
}

String DragData::asPlainText(Frame*) const
{
    notImplemented();
    return String();
}

Color DragData::asColor() const
{
    notImplemented();
    return Color();
}

bool DragData::containsCompatibleContent() const
{
    notImplemented();
    return false;
}

bool DragData::containsURL(Frame*, FilenameConversionPolicy filenamePolicy) const
{
    notImplemented();
    return false;
}

String DragData::asURL(Frame*, FilenameConversionPolicy filenamePolicy, String* title) const
{
    notImplemented();
    return String();
}

PassRefPtr<DocumentFragment> DragData::asFragment(Frame*, PassRefPtr<Range>, bool, bool&) const
{
    notImplemented();
    return 0;
}

}



