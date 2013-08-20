/*
 * Copyright (C) 2012 armite@126.com.
 *
 */

#ifndef FrameLoaderClientArmite_h
#define FrameLoaderClientArmite_h

#include <FrameLoaderClient.h>
#include <wtf/Vector.h>
#include <wtf/PassOwnPtr.h>

#ifdef BENCH_LOAD_TIME
#include <sys/time.h>
#endif

namespace WebCore {
    class CachedPage;
    class DocumentLoader;
    class KURL;
    class PluginView;
    class FrameLoader;
    class Widget;
    class StringWithDirection;
    class FrameNetworkingContext;
}

class WebObjectApplicationManager;
class WebFrame;
class WebFramePolicyListener;
class WebHistory;

class FrameLoaderClientArmite : public WebCore::FrameLoaderClient {
public:
    FrameLoaderClientArmite(WebFrame*);
    virtual ~FrameLoaderClientArmite();

    virtual void frameLoaderDestroyed();

    virtual bool hasWebView() const;

    virtual void makeRepresentation(WebCore::DocumentLoader*);
    virtual void forceLayout();
    virtual void forceLayoutForNonHTML();

    virtual void setCopiesOnScroll();

    virtual void detachedFromParent2();
    virtual void detachedFromParent3();

    virtual void assignIdentifierToInitialRequest(unsigned long identifier, WebCore::DocumentLoader*, const WebCore::ResourceRequest&);

    virtual void dispatchWillSendRequest(WebCore::DocumentLoader*, unsigned long identifier, WebCore::ResourceRequest&, const WebCore::ResourceResponse& redirectResponse);
    virtual bool shouldUseCredentialStorage(WebCore::DocumentLoader*, unsigned long identifier);
    virtual void dispatchDidReceiveAuthenticationChallenge(WebCore::DocumentLoader*, unsigned long identifier, const WebCore::AuthenticationChallenge&);
    virtual void dispatchDidCancelAuthenticationChallenge(WebCore::DocumentLoader*, unsigned long identifier, const WebCore::AuthenticationChallenge&);
    virtual void dispatchDidReceiveResponse(WebCore::DocumentLoader*, unsigned long identifier, const WebCore::ResourceResponse&);
    virtual void dispatchDidReceiveContentLength(WebCore::DocumentLoader*, unsigned long identifier, int lengthReceived);
    virtual void dispatchDidFinishLoading(WebCore::DocumentLoader*, unsigned long identifier, WebCore::ResourceLoader*);
    virtual void dispatchDidFailLoading(WebCore::DocumentLoader*, unsigned long identifier, const WebCore::ResourceError&, WebCore::ResourceLoader* resource);
    virtual bool shouldCacheResponse(WebCore::DocumentLoader*, unsigned long identifier, const WebCore::ResourceResponse&, const unsigned char* data, unsigned long long length);
    virtual bool dispatchDidLoadResourceFromMemoryCache(WebCore::DocumentLoader*, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&, int length);

    virtual void dispatchDidHandleOnloadEvents();
    virtual void dispatchDidReceiveServerRedirectForProvisionalLoad();
    virtual void dispatchDidCancelClientRedirect();
    virtual void dispatchWillPerformClientRedirect(const WebCore::KURL&, double interval, double fireDate);
    virtual void dispatchDidChangeLocationWithinPage();
    virtual void dispatchDidPushStateWithinPage();
    virtual void dispatchDidReplaceStateWithinPage();
    virtual void dispatchDidPopStateWithinPage();
    virtual void dispatchWillClose();
    virtual void dispatchDidReceiveIcon();
    virtual void dispatchDidStartProvisionalLoad();
    virtual void dispatchDidReceiveTitle(const WebCore::StringWithDirection&);
    virtual void dispatchDidChangeIcons(WebCore::IconType);
    virtual void dispatchDidCommitLoad();
    virtual void dispatchDidFailProvisionalLoad(const WebCore::ResourceError&);
    virtual void dispatchDidFailLoad(const WebCore::ResourceError&);
    virtual void dispatchDidFinishDocumentLoad();
    virtual void dispatchDidFinishLoad();
    virtual void dispatchDidFirstLayout();
    virtual void dispatchDidFirstVisuallyNonEmptyLayout();

    virtual void dispatchDecidePolicyForResponse(WebCore::FramePolicyFunction, const WebCore::ResourceResponse&, const WebCore::ResourceRequest&) {}
    virtual WebCore::Frame* dispatchCreatePage(const WebCore::NavigationAction&);
    virtual void dispatchShow();

    virtual void dispatchDecidePolicyForMIMEType(WebCore::FramePolicyFunction, const WTF::String& MIMEType, const WebCore::ResourceRequest&);
    virtual void dispatchDecidePolicyForNewWindowAction(WebCore::FramePolicyFunction, const WebCore::NavigationAction&, const WebCore::ResourceRequest&, PassRefPtr<WebCore::FormState>, const WTF::String& frameName);
    virtual void dispatchDecidePolicyForNavigationAction(WebCore::FramePolicyFunction, const WebCore::NavigationAction&, const WebCore::ResourceRequest&, PassRefPtr<WebCore::FormState>);
    virtual void cancelPolicyCheck();

    virtual void dispatchUnableToImplementPolicy(const WebCore::ResourceError&);

    virtual void dispatchWillSendSubmitEvent(PassRefPtr<WebCore::FormState>) { }
    virtual void dispatchWillSubmitForm(WebCore::FramePolicyFunction, PassRefPtr<WebCore::FormState>);

    virtual void revertToProvisionalState(WebCore::DocumentLoader*);
    virtual void setMainDocumentError(WebCore::DocumentLoader*, const WebCore::ResourceError&);

    virtual void postProgressStartedNotification();
    virtual void postProgressEstimateChangedNotification();
    virtual void postProgressFinishedNotification();

    virtual void setMainFrameDocumentReady(bool);

    virtual void startDownload(const WebCore::ResourceRequest&, const WTF::String& suggestedName = WTF::String());

    virtual void willChangeTitle(WebCore::DocumentLoader*);
    virtual void didChangeTitle(WebCore::DocumentLoader*);

    virtual void committedLoad(WebCore::DocumentLoader*, const char*, int);
    virtual void finishedLoading(WebCore::DocumentLoader*);

    virtual void updateGlobalHistory();
    virtual void updateGlobalHistoryRedirectLinks();
    virtual bool shouldGoToHistoryItem(WebCore::HistoryItem*) const {return true;}
    virtual bool shouldStopLoadingForHistoryItem(WebCore::HistoryItem*) const {return true;}
    virtual void dispatchDidAddBackForwardItem(WebCore::HistoryItem*) const;
    virtual void dispatchDidRemoveBackForwardItem(WebCore::HistoryItem*) const;
    virtual void dispatchDidChangeBackForwardIndex() const;

    virtual void didDisplayInsecureContent();
    virtual void didRunInsecureContent(WebCore::SecurityOrigin*, const WebCore::KURL&);
    virtual void didDetectXSS(const WebCore::KURL&, bool didBlockEntirePage) { }

    virtual WebCore::ResourceError cancelledError(const WebCore::ResourceRequest&);
    virtual WebCore::ResourceError blockedError(const WebCore::ResourceRequest&);
    virtual WebCore::ResourceError cannotShowURLError(const WebCore::ResourceRequest&);
    virtual WebCore::ResourceError interruptedForPolicyChangeError(const WebCore::ResourceRequest&);

    virtual WebCore::ResourceError cannotShowMIMETypeError(const WebCore::ResourceResponse&);
    virtual WebCore::ResourceError fileDoesNotExistError(const WebCore::ResourceResponse&);
    virtual WebCore::ResourceError pluginWillHandleLoadError(const WebCore::ResourceResponse&);

    virtual bool shouldFallBack(const WebCore::ResourceError&);

    virtual bool canHandleRequest(const WebCore::ResourceRequest&) const;
    virtual bool canShowMIMEType(const WTF::String& MIMEType) const;
    virtual bool canShowMIMETypeAsHTML(const WTF::String& MIMEType) const {return false;}
    virtual bool representationExistsForURLScheme(const WTF::String& URLScheme) const;
    virtual WTF::String generatedMIMETypeForURLScheme(const WTF::String& URLScheme) const;

    virtual void frameLoadCompleted();
    virtual void saveViewStateToItem(WebCore::HistoryItem *);
    virtual void restoreViewState();
    virtual void provisionalLoadStarted();
    virtual void didFinishLoad();
    virtual void prepareForDataSourceReplacement();

    virtual PassRefPtr<WebCore::DocumentLoader> createDocumentLoader(const WebCore::ResourceRequest&, const WebCore::SubstituteData&);
    virtual void setTitle(const WebCore::StringWithDirection& title, const WebCore::KURL&);

    virtual WTF::String userAgent(const WebCore::KURL&);

    virtual void savePlatformDataToCachedFrame(WebCore::CachedFrame*);
    virtual void transitionToCommittedFromCachedFrame(WebCore::CachedFrame*);
    virtual void transitionToCommittedFromCachedPage(WebCore::CachedPage*);
    virtual void transitionToCommittedForNewPage();

    virtual void didSaveToPageCache() {}
    virtual void didRestoreFromPageCache() {}

    virtual void dispatchDidBecomeFrameset(bool) {} // Can change due to navigation or DOM modification.

    virtual bool canCachePage() const {return true;}
    virtual void download(WebCore::ResourceHandle*, const WebCore::ResourceRequest&, const WebCore::ResourceResponse&);

    virtual PassRefPtr<WebCore::Frame> createFrame(const WebCore::KURL& url, const WTF::String& name, WebCore::HTMLFrameOwnerElement* ownerElement, const WTF::String& referrer, bool allowsScrolling, int marginWidth, int marginHeight);
    virtual void didTransferChildFrameToNewDocument(WebCore::Page*);
    virtual void transferLoadingResourceFromPage(WebCore::ResourceLoader*, const WebCore::ResourceRequest&, WebCore::Page*) { }
    virtual PassRefPtr<WebCore::Widget> createPlugin(const WebCore::IntSize&, WebCore::HTMLPlugInElement*, const WebCore::KURL&, const Vector<WTF::String>&, const Vector<WTF::String>&, const WTF::String&, bool loadManually);
    virtual void recreatePlugin(WebCore::Widget*) { }
    virtual void redirectDataToPlugin(WebCore::Widget* pluginWidget);
    virtual PassRefPtr<WebCore::Widget> createJavaAppletWidget(const WebCore::IntSize&, WebCore::HTMLAppletElement*, const WebCore::KURL& baseURL, const Vector<WTF::String>& paramNames, const Vector<WTF::String>& paramValues);

    virtual WebCore::ObjectContentType objectContentType(const WebCore::KURL& url, const WTF::String& mimeType, bool shouldPreferPlugInsForImages);
    virtual WTF::String overrideMediaType() const;

    virtual void dispatchDidClearWindowObjectInWorld(WebCore::DOMWrapperWorld*);
    virtual void documentElementAvailable();
    virtual void didPerformFirstNavigation() const;

    virtual void registerForIconNotification(bool listen);

    virtual bool shouldUsePluginDocument(const WTF::String& /*mimeType*/) const ;

    WebFrame* webFrame() { return m_webFrame; }

    virtual PassRefPtr<WebCore::FrameNetworkingContext> createNetworkingContext() ;

    virtual bool shouldPaintBrokenImage(const WebCore::KURL&) const { return false; }

    static void setGlobalJavaScript(const char *);
private:
    PassRefPtr<WebCore::Frame> createFrame(const WebCore::KURL&, const WTF::String& name, WebCore::HTMLFrameOwnerElement*, const WTF::String& referrer);

    WebFrame* m_webFrame;

#ifdef BENCH_LOAD_TIME
    struct timeval m_timerStart;
    struct timeval m_timerStop;
#endif
};

#endif // FrameLoaderClientArmite_h



