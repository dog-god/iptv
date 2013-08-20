/*
 *  Copyright (C) 2012 armite@126.com
 */

#include "config.h"
#include "Clipboard.h"

#include "DOMStringList.h"
#include "DataTransferItemList.h"
#include "Editor.h"
#include "FileList.h"
#include "NotImplemented.h"
#include <wtf/text/StringHash.h>

namespace WebCore {
PassRefPtr<Clipboard> Editor::newGeneralClipboard(ClipboardAccessPolicy policy, Frame*)
{
    notImplemented();
    return NULL;
}

}
