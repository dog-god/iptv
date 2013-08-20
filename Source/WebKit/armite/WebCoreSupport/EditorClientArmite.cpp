/*
 * Copyright (C) 2012 armite@126.com.
 *
 */

#include "config.h"
#include "EditorClientArmite.h"

#include "WebView.h"

#include <wtf/text/WTFString.h>
#include <Document.h>
#include <EditCommand.h>
#include <HTMLElement.h>
#include <HTMLInputElement.h>
#include <HTMLNames.h>
#include <KeyboardEvent.h>
#include <PlatformKeyboardEvent.h>
#include <NotImplemented.h>
#include <Range.h>
#include <TextCheckerClient.h>
#include "WindowsKeyboardCodes.h"
#include "Editor.h"
#include "Frame.h"

using namespace WebCore;
using namespace HTMLNames;


class WebEditorUndoCommand
{
public:
    WebEditorUndoCommand(PassRefPtr<EditCommand> editCommand, bool isUndo);
    void execute();
    bool isUndo() { return m_isUndo; }

private:
    RefPtr<EditCommand> m_editCommand;
    bool m_isUndo;
};

WebEditorUndoCommand::WebEditorUndoCommand(PassRefPtr<EditCommand> editCommand, bool isUndo)
    : m_editCommand(editCommand)
    , m_isUndo(isUndo)
{
}

void WebEditorUndoCommand::execute()
{
    notImplemented();
}

class WebEditorUndoTarget
{
public:
    WebEditorUndoTarget();
    ~WebEditorUndoTarget();
    void invoke(String actionName, WebEditorUndoCommand* obj);
    void append(String actionName, WebEditorUndoCommand* obj);
    void clear();
    bool canUndo();
    bool canRedo();
    void undo();
    void redo();

private:
    Vector<WebEditorUndoCommand*> m_undoCommandList;
    Vector<String> m_actionName;
};

WebEditorUndoTarget::WebEditorUndoTarget()
{
    notImplemented();
}

WebEditorUndoTarget::~WebEditorUndoTarget()
{
    clear();
}

void WebEditorUndoTarget::invoke(String actionName, WebEditorUndoCommand *undoCommand)
{
    if(undoCommand) {
        undoCommand->execute();
    }
}


void WebEditorUndoTarget::append(String actionName, WebEditorUndoCommand *undoCommand)
{
    m_undoCommandList.append(undoCommand);
    m_actionName.append(actionName);
}

void WebEditorUndoTarget::clear()
{
    m_undoCommandList.clear();
    m_actionName.clear();
}

bool WebEditorUndoTarget::canUndo()
{
    for (unsigned i = 0; i < m_undoCommandList.size(); ++i) {
        if (m_undoCommandList[i]->isUndo())
            return true;
    }
    return false;
}

bool WebEditorUndoTarget::canRedo()
{
    for (unsigned i = 0; i < m_undoCommandList.size(); ++i) {
        if (!m_undoCommandList[i]->isUndo())
            return true;
    }
    return false;
}


void WebEditorUndoTarget::undo()
{
    for (int i = m_undoCommandList.size() - 1; i >= 0; --i) {
        if (m_undoCommandList[i]->isUndo()) {
            m_undoCommandList[i]->execute();
            m_undoCommandList.remove(i);
            return;
        }
    }
}

void WebEditorUndoTarget::redo()
{
    for (int i = m_undoCommandList.size() - 1; i >= 0; --i) {
        if (!m_undoCommandList[i]->isUndo()) {
            m_undoCommandList[i]->execute();
            m_undoCommandList.remove(i);
            return;
        }
    }
}

EditorClientArmite::EditorClientArmite(WebView* webView)
    : m_webView(webView)
    , m_undoTarget(0)
    , m_isInputMethodOn(false)
{
    m_undoTarget = new WebEditorUndoTarget();
}

EditorClientArmite::~EditorClientArmite()
{
    delete m_undoTarget;
}

void EditorClientArmite::pageDestroyed()
{
}

bool EditorClientArmite::isContinuousSpellCheckingEnabled()
{
    return false;
}

void EditorClientArmite::toggleContinuousSpellChecking()
{
    notImplemented();
}

bool EditorClientArmite::isGrammarCheckingEnabled()
{
    return false;
}

void EditorClientArmite::toggleGrammarChecking()
{
    notImplemented();
}

int EditorClientArmite::spellCheckerDocumentTag()
{
    notImplemented();
    return 0;
}

bool EditorClientArmite::shouldBeginEditing(Range* range)
{
    notImplemented();
    return false;
}

bool EditorClientArmite::shouldEndEditing(Range* range)
{
    notImplemented();
    return false;
}

void EditorClientArmite::didBeginEditing()
{
    notImplemented();
}

void EditorClientArmite::respondToChangedContents()
{
    notImplemented();
}

void EditorClientArmite::respondToChangedSelection(WebCore::Frame*)
{
    notImplemented();
}

void EditorClientArmite::didEndEditing()
{
    notImplemented();
}

void EditorClientArmite::didWriteSelectionToPasteboard()
{
    notImplemented();
}

void EditorClientArmite::didSetSelectionTypesForPasteboard()
{
    notImplemented();
}

bool EditorClientArmite::shouldDeleteRange(Range* range)
{
    notImplemented();
    return true;
}

bool EditorClientArmite::shouldInsertNode(WebCore::Node* node, Range* replacingRange, EditorInsertAction givenAction)
{
    notImplemented();
    return true;
}

bool EditorClientArmite::shouldInsertText(const String& str, Range* replacingRange, EditorInsertAction givenAction)
{
    notImplemented();
    return true;
}

bool EditorClientArmite::isSelectTrailingWhitespaceEnabled(void)
{
    return false;
}

bool EditorClientArmite::shouldApplyStyle(StylePropertySet* style, Range* toElementsInDOMRange)
{
    notImplemented();
    return false;
}

bool EditorClientArmite::shouldMoveRangeAfterDelete(Range* /*range*/, Range* /*rangeToBeReplaced*/)
{
    notImplemented();
    return false;
}

void EditorClientArmite::webViewDidChangeTypingStyle(WebNotification* /*notification*/)
{
    notImplemented();
}

void EditorClientArmite::webViewDidChangeSelection(WebNotification* /*notification*/)
{
    notImplemented();
}

bool EditorClientArmite::shouldShowDeleteInterface(HTMLElement* element)
{
    notImplemented();
    return false;
}

bool EditorClientArmite::smartInsertDeleteEnabled(void)
{
    notImplemented();
    return false;
}

bool EditorClientArmite::shouldChangeSelectedRange(WebCore::Range* current, WebCore::Range* proposed, WebCore::EAffinity selection, bool stillSelected)
{
    notImplemented();
    return true;
}

void EditorClientArmite::textFieldDidBeginEditing(Element* e)
{
    notImplemented();
}

void EditorClientArmite::textFieldDidEndEditing(Element* e)
{
    notImplemented();
}

void EditorClientArmite::textDidChangeInTextField(Element* e)
{
    notImplemented();
}

bool EditorClientArmite::doTextFieldCommandFromEvent(Element* e, KeyboardEvent* ke)
{
    notImplemented();
    return false;
}

void EditorClientArmite::textWillBeDeletedInTextField(Element* e)
{
    notImplemented();
}

void EditorClientArmite::textDidChangeInTextArea(Element* e)
{
    notImplemented();
}

static String undoNameForEditAction(EditAction editAction)
{
    switch (editAction) {
        case EditActionUnspecified: return "";
        case EditActionSetColor: return "Set Color";
        case EditActionSetBackgroundColor: return "Set Background Color";
        case EditActionTurnOffKerning: return "Turn Off Kerning";
        case EditActionTightenKerning: return "Tighten Kerning";
        case EditActionLoosenKerning: return "Loosen Kerning";
        case EditActionUseStandardKerning: return "Use Standard Kerning";
        case EditActionTurnOffLigatures: return "Turn Off Ligatures";
        case EditActionUseStandardLigatures: return "Use Standard Ligatures";
        case EditActionUseAllLigatures: return "Use All Ligatures";
        case EditActionRaiseBaseline: return "Raise Baseline";
        case EditActionLowerBaseline: return "Lower Baseline";
        case EditActionSetTraditionalCharacterShape: return "Set Traditional Character Shape";
        case EditActionSetFont: return "Set Font";
        case EditActionChangeAttributes: return "Change Attributes";
        case EditActionAlignLeft: return "Align Left";
        case EditActionAlignRight: return "Align Right";
        case EditActionCenter: return "Center";
        case EditActionJustify: return "Justify";
        case EditActionSetWritingDirection: return "Set Writing Direction";
        case EditActionSubscript: return "Subscript";
        case EditActionSuperscript: return "Superscript";
        case EditActionUnderline: return "Underline";
        case EditActionOutline: return "Outline";
        case EditActionUnscript: return "Unscript";
        case EditActionDrag: return "Drag";
        case EditActionCut: return "Cut";
        case EditActionPaste: return "Paste";
        case EditActionPasteFont: return "Paste Font";
        case EditActionPasteRuler: return "Paste Ruler";
        case EditActionTyping: return "Typing";
        case EditActionCreateLink: return "Create Link";
        case EditActionUnlink: return "Unlink";
        case EditActionInsertList: return "Insert List";
        case EditActionFormatBlock: return "Formatting";
        case EditActionIndent: return "Indent";
        case EditActionOutdent: return "Outdent";
    }
    return String();
}

void EditorClientArmite::registerUndoStep(PassRefPtr<UndoStep>)
{
    notImplemented();
}

void EditorClientArmite::registerRedoStep(PassRefPtr<UndoStep>)
{
    notImplemented();
}

void EditorClientArmite::clearUndoRedoOperations()
{
    m_undoTarget->clear();
}

bool EditorClientArmite::canUndo() const
{
    return m_undoTarget->canUndo();
}

bool EditorClientArmite::canRedo() const
{
    return m_undoTarget->canRedo();
}

void EditorClientArmite::undo()
{
    m_undoTarget->undo();
}

void EditorClientArmite::redo()
{
    m_undoTarget->redo();
}

static const char *interpretKeyEvent(int key)
{
    const char *cmd = NULL;
    switch(key) {
        case VK_LEFT:
            cmd = "MoveLeft"; break;
        case VK_RIGHT:
            cmd = "MoveRight"; break;
        case VK_DELETE:
            cmd = "DeleteBackward"; break;
    }

    return cmd;
}

bool EditorClientArmite::handleEditingKeyboardEvent(KeyboardEvent* evt)
{
    const PlatformKeyboardEvent* keyEvent = evt->keyEvent();
    if (!keyEvent)
        return false;
    Frame* frame = evt->target()->toNode()->document()->frame();
    if (!frame)
        return false;

    const char *cmd = interpretKeyEvent(evt->keyCode());
    if (keyEvent->type() == PlatformEvent::RawKeyDown && cmd != NULL) {
        Editor::Command command = frame->editor()->command(cmd);
        command.execute(evt);
        if (m_isInputMethodOn)
            return true;
        return false;
    }

    if (evt->charCode() < ' ')
        return false;
    if (keyEvent->nativeVirtualKeyCode() >= VK_LEFT && keyEvent->nativeVirtualKeyCode() <= VK_DOWN)
        return true;

    return frame->editor()->insertText(keyEvent->text(), evt);
}

void EditorClientArmite::handleKeyboardEvent(KeyboardEvent* evt)
{
    if (handleEditingKeyboardEvent(evt))
        evt->setDefaultHandled();
}

void EditorClientArmite::handleInputMethodKeydown(KeyboardEvent* )
{
    notImplemented();
}

bool EditorClientArmite::isEditable()
{
    return true;
}

void EditorClientArmite::ignoreWordInSpellDocument(const String& word)
{
    notImplemented();
}

void EditorClientArmite::learnWord(const String& word)
{
    notImplemented();
}

String EditorClientArmite::getAutoCorrectSuggestionForMisspelledWord(const String& inputWord)
{
    notImplemented();
    return String();
}

void EditorClientArmite::updateSpellingUIWithGrammarString(const String& string, const WebCore::GrammarDetail& detail)
{
    notImplemented();
}

void EditorClientArmite::updateSpellingUIWithMisspelledWord(const String& word)
{
    notImplemented();
}

void EditorClientArmite::showSpellingUI(bool show)
{
    notImplemented();
}

bool EditorClientArmite::spellingUIIsShowing()
{
    return false;
}

void EditorClientArmite::getGuessesForWord(const String& word, Vector<String>& guesses)
{
    notImplemented();
}

void EditorClientArmite::setInputMethodState(bool enabled)
{
    m_isInputMethodOn = enabled;
}



