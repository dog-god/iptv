/*
 * Copyright (C) 2012 armite@126.com.
 *
 */

#ifndef EditorClientArmite_H
#define EditorClientArmite_H

#include <EditorClient.h>
#include <wtf/OwnPtr.h>

class WebView;
class WebNotification;
class WebEditorUndoTarget;

class EditorClientArmite : public WebCore::EditorClient {
public:
    EditorClientArmite(WebView*);
    virtual ~EditorClientArmite();

    virtual void pageDestroyed();
    virtual void frameWillDetachPage(WebCore::Frame*) { }

    virtual bool isContinuousSpellCheckingEnabled();
    virtual void toggleGrammarChecking();
    virtual bool isGrammarCheckingEnabled();
    virtual void toggleContinuousSpellChecking();
    virtual int spellCheckerDocumentTag();

    virtual bool isEditable();

    virtual bool shouldBeginEditing(WebCore::Range*);
    virtual bool shouldEndEditing(WebCore::Range*);
    virtual bool shouldInsertText(const WTF::String&, WebCore::Range*, WebCore::EditorInsertAction);

    virtual void didBeginEditing();
    virtual void didEndEditing();
    virtual void didWriteSelectionToPasteboard();
    virtual void didSetSelectionTypesForPasteboard();

    virtual void respondToChangedContents();
    virtual void respondToChangedSelection(WebCore::Frame*);

    bool shouldShowDeleteInterface(WebCore::HTMLElement*);
    bool shouldDeleteRange(WebCore::Range*);

    bool shouldInsertNode(WebCore::Node*, WebCore::Range* replacingRange, WebCore::EditorInsertAction);
    bool shouldApplyStyle(WebCore::StylePropertySet*, WebCore::Range*);
    bool shouldMoveRangeAfterDelete(WebCore::Range*, WebCore::Range*);

    void webViewDidChangeTypingStyle(WebNotification*);
    void webViewDidChangeSelection(WebNotification*);

    bool smartInsertDeleteEnabled();
    bool isSelectTrailingWhitespaceEnabled();

    virtual void registerUndoStep(PassRefPtr<WebCore::UndoStep>);
    virtual void registerRedoStep(PassRefPtr<WebCore::UndoStep>);
    void clearUndoRedoOperations();

    virtual bool canCopyCut(WebCore::Frame*, bool defaultValue) const {return false;}
    virtual bool canPaste(WebCore::Frame*, bool defaultValue) const {return false;}
    bool canUndo() const;
    bool canRedo() const;

    void undo();
    void redo();

    virtual bool shouldChangeSelectedRange(WebCore::Range* fromRange, WebCore::Range* toRange, WebCore::EAffinity, bool stillSelecting);
    virtual void textFieldDidBeginEditing(WebCore::Element*);
    virtual void textFieldDidEndEditing(WebCore::Element*);
    virtual void textDidChangeInTextField(WebCore::Element*);
    virtual bool doTextFieldCommandFromEvent(WebCore::Element*, WebCore::KeyboardEvent*);
    virtual void textWillBeDeletedInTextField(WebCore::Element* input);
    virtual void textDidChangeInTextArea(WebCore::Element*);

    bool handleEditingKeyboardEvent(WebCore::KeyboardEvent*);
    void handleKeyboardEvent(WebCore::KeyboardEvent*);
    void handleInputMethodKeydown(WebCore::KeyboardEvent*);

    virtual void ignoreWordInSpellDocument(const WTF::String&);
    virtual void learnWord(const WTF::String&);
    virtual WTF::String getAutoCorrectSuggestionForMisspelledWord(const WTF::String&);

    virtual WebCore::TextCheckerClient* textChecker() {return 0;}

    enum AutocorrectionResponseType {
        AutocorrectionEdited,
        AutocorrectionReverted
    };
    virtual void updateSpellingUIWithGrammarString(const WTF::String&, const WebCore::GrammarDetail& detail);
    virtual void updateSpellingUIWithMisspelledWord(const WTF::String&);
    virtual void showSpellingUI(bool show);
    virtual bool spellingUIIsShowing();
    virtual void getGuessesForWord(const WTF::String&, Vector<WTF::String>& guesses);
    virtual void willSetInputMethodState() {}

    virtual void setInputMethodState(bool);

private:
    WebView* m_webView;
    WebEditorUndoTarget* m_undoTarget;
    bool m_isInputMethodOn;
};

#endif // EditorClientArmite_H



