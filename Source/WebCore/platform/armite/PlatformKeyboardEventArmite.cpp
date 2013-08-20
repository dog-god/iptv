/*
 * Copyright (C) 2012 armite@126.com. All rights reserved.
 */

#include "config.h"

#include "PlatformKeyboardEvent.h"

#include "NotImplemented.h"
#include "TextEncoding.h"
#include "WindowsKeyboardCodes.h"
#include "WebKitTypes.h"
#include "Logging.h"
#include "TextEncoding.h"

#include <stdio.h>
#include <wtf/HashMap.h>
#include <wtf/text/StringConcatenate.h>
#include <wtf/text/StringHash.h>

namespace WebCore {

static WTF::String keyIdentifierForVKeyCode(ArmiteKeyboardEvent* keyCode)
{
    switch (keyCode->vkey) {
        case VK_MENU:
            return "Alt";
        case VK_CLEAR:
            return "Clear";
        case VK_DOWN:
            return "Down";
        case VK_END:
            return "End";
        case VK_RETURN:
            return "Enter";
        case VK_F1:
            return "F1";
        case VK_F2:
            return "F2";
        case VK_F3:
            return "F3";
        case VK_F4:
            return "F4";
        case VK_F5:
            return "F5";
        case VK_F6:
            return "F6";
        case VK_F7:
            return "F7";
        case VK_F8:
            return "F8";
        case VK_F9:
            return "F9";
        case VK_F10:
            return "F10";
        case VK_F11:
            return "F11";
        case VK_F12:
            return "F12";
        case VK_F13:
            return "F13";
        case VK_F14:
            return "F14";
        case VK_F15:
            return "F15";
        case VK_HELP:
            return "Help";
        case VK_HOME:
            return "Home";
        case VK_INSERT:
            return "Insert";
        case VK_LEFT:
            return "Left";
        case VK_PRIOR:
            return "PageDown";
        case VK_NEXT:
            return "PageUp";
        case VK_PAUSE:
            return "Pause";
        case VK_RIGHT:
            return "Right";
        case VK_UP:
            return "Up";
        case VK_DELETE:
            return "U+00007F";
        default:
            return WTF::String::format("U+%04X", WTF::Unicode::toUpper(keyCode->vkey));
    }
}

PlatformKeyboardEvent::PlatformKeyboardEvent(ArmiteKeyboardEvent* event)
    : PlatformEvent(PlatformEvent::KeyDown)
    , m_autoRepeat(false)
    , m_windowsVirtualKeyCode(event->vkey)
    , m_isKeypad(false)
{
    UChar aSrc[2];
    aSrc[0] = event->unicode;
    aSrc[1] = 0;

    WTF::String aText(aSrc);
    WTF::String aUnmodifiedText(aSrc);
    WTF::String aKeyIdentifier = keyIdentifierForVKeyCode(event);

    m_text = aText;
    m_unmodifiedText = aUnmodifiedText;
    m_keyIdentifier = aKeyIdentifier;
}

void PlatformKeyboardEvent::disambiguateKeyDownEvent(Type type, bool)
{
    ASSERT(m_type == KeyDown);
    m_type = type;

    if (type == RawKeyDown) {
        m_text = String();
        m_unmodifiedText = String();
    } else {
        m_keyIdentifier = String();
        m_nativeVirtualKeyCode = m_windowsVirtualKeyCode;
        m_windowsVirtualKeyCode = 0;
    }
}

bool PlatformKeyboardEvent::currentCapsLockState()
{
    notImplemented();
    return false;
}

void PlatformKeyboardEvent::getCurrentModifierState(bool& shiftKey, bool& ctrlKey, bool& altKey, bool& metaKey)
{
    notImplemented();
    shiftKey = false;
    ctrlKey = false;
    altKey = false;
    metaKey = false;
}

}



