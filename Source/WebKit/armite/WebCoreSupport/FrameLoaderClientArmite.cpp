/*
 * Copyright (C) 2012 armite@126.com.
 *
 */

#include "config.h"
#include "FrameLoaderClientArmite.h"

#include "NotImplemented.h"
#include "ChromeClientArmite.h"
#include "WebFrame.h"
#include "WebView.h"
#include "WebViewPrivate.h"
#include "FrameNetworkingContext.h"

#include <CachedFrame.h>
#include <DocumentLoader.h>
#include <FormState.h>
#include <Frame.h>
#include <FrameLoader.h>
#include <FrameTree.h>
#include <FrameView.h>
#include <HTMLAppletElement.h>
#include <HTMLFormElement.h>
#include <HTMLFrameElement.h>
#include <HTMLFrameOwnerElement.h>
#include <HTMLNames.h>
#include <HTMLObjectElement.h>
#include <HTMLPlugInElement.h>
#include <HistoryItem.h>
#include <Logging.h>
#include <MIMETypeRegistry.h>
#include <Page.h>
#include <PluginDatabase.h>
#include <PluginPackage.h>
#include <PluginView.h>
#include <RenderPart.h>
#include <ResourceHandle.h>
#include <ScriptSourceCode.h>
#include "ScriptValue.h"
using namespace WebCore;
using namespace HTMLNames;

enum {
    WebKitErrorCannotShowMIMEType =                             100,
    WebKitErrorCannotShowURL =                                  101,
    WebKitErrorFrameLoadInterruptedByPolicyChange =             102,
    WebKitErrorCannotUseRestrictedPort =                        103,
};

enum {
    WebKitErrorCannotFindPlugIn =                               200,
    WebKitErrorCannotLoadPlugIn =                               201,
    WebKitErrorJavaUnavailable =                                202,
};

enum
{
    WebURLErrorUnknown =                         -1,
    WebURLErrorCancelled =                       -999,
    WebURLErrorBadURL =                          -1000,
    WebURLErrorTimedOut =                        -1001,
    WebURLErrorUnsupportedURL =                  -1002,
    WebURLErrorCannotFindHost =                  -1003,
    WebURLErrorCannotConnectToHost =             -1004,
    WebURLErrorNetworkConnectionLost =           -1005,
    WebURLErrorDNSLookupFailed =                 -1006,
    WebURLErrorHTTPTooManyRedirects =            -1007,
    WebURLErrorResourceUnavailable =             -1008,
    WebURLErrorNotConnectedToInternet =          -1009,
    WebURLErrorRedirectToNonExistentLocation =   -1010,
    WebURLErrorBadServerResponse =               -1011,
    WebURLErrorUserCancelledAuthentication =     -1012,
    WebURLErrorUserAuthenticationRequired =      -1013,
    WebURLErrorZeroByteResource =                -1014,
    WebURLErrorFileDoesNotExist =                -1100,
    WebURLErrorFileIsDirectory =                 -1101,
    WebURLErrorNoPermissionsToReadFile =         -1102,
    WebURLErrorSecureConnectionFailed =          -1200,
    WebURLErrorServerCertificateHasBadDate =     -1201,
    WebURLErrorServerCertificateUntrusted =      -1202,
    WebURLErrorServerCertificateHasUnknownRoot = -1203,
    WebURLErrorServerCertificateNotYetValid =    -1204,
    WebURLErrorClientCertificateRejected =       -1205,
    WebURLErrorClientCertificateRequired =       -1206,
    WebURLErrorCannotLoadFromNetwork =           -2000,

    // Download and file I/O errors
    WebURLErrorCannotCreateFile =                -3000,
    WebURLErrorCannotOpenFile =                  -3001,
    WebURLErrorCannotCloseFile =                 -3002,
    WebURLErrorCannotWriteToFile =               -3003,
    WebURLErrorCannotRemoveFile =                -3004,
    WebURLErrorCannotMoveFile =                  -3005,
    WebURLErrorDownloadDecodingFailedMidStream = -3006,
    WebURLErrorDownloadDecodingFailedToComplete =-3007,
};

// FIXME: We should have better names! Also those should be localized.
#define WebKitCannotShowURL " WebKitCannotShowURL"
#define WebKitErrorDomain "WebKitErrorDomain"
#define WebURLErrorDomain "URLErrorDomain"
#define WebKitErrorMIMETypeKey "WebKitErrorMIMETypeKey"
#define WebKitErrorMIMETypeError "WebKitErrorMIMETypeError"
#define WebKitErrorPlugInNameKey "WebKitErrorPlugInNameKey"
#define WebKitErrorPlugInPageURLStringKey "WebKitErrorPlugInPageURLStringKey"
#define WebPOSIXErrorDomain "NSPOSIXErrorDomain"
#define WebKitFileDoesNotExist "WebKitFileDoesNotExist"

FrameLoaderClientArmite::FrameLoaderClientArmite(WebFrame* webFrame)
    : m_webFrame(webFrame)
{
}

FrameLoaderClientArmite::~FrameLoaderClientArmite()
{
    if (m_webFrame)
        m_webFrame = 0;
}

bool FrameLoaderClientArmite::hasWebView() const
{
    return m_webFrame->webView();
}

void FrameLoaderClientArmite::forceLayout()
{
    Frame* frame = core(m_webFrame);
    if (!frame)
        return;

    if (frame->document() && frame->document()->inPageCache())
        return;

    FrameView* view = frame->view();
    if (!view)
        return;

    view->setNeedsLayout();
    view->forceLayout(true);
}

void FrameLoaderClientArmite::assignIdentifierToInitialRequest(unsigned long identifier, DocumentLoader* loader, const ResourceRequest& request)
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidReceiveAuthenticationChallenge(DocumentLoader* loader, unsigned long identifier, const AuthenticationChallenge& challenge)
{
    challenge.authenticationClient()->receivedRequestToContinueWithoutCredential(challenge);
}

void FrameLoaderClientArmite::dispatchDidFirstVisuallyNonEmptyLayout()
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidCancelAuthenticationChallenge(DocumentLoader* loader, unsigned long identifier, const AuthenticationChallenge& challenge)
{
    notImplemented();
}

bool FrameLoaderClientArmite::shouldUseCredentialStorage(DocumentLoader* loader, unsigned long identifier)
{
    return false;
}

void FrameLoaderClientArmite::dispatchWillSendRequest(DocumentLoader* loader, unsigned long identifier, ResourceRequest& request, const ResourceResponse& redirectResponse)
{
    m_webFrame->webView()->webViewPrivate()->beforeDownloadResource(loader, request);
}

void FrameLoaderClientArmite::dispatchDidReceiveResponse(DocumentLoader* loader, unsigned long identifier, const ResourceResponse& response)
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidReceiveContentLength(DocumentLoader* loader, unsigned long identifier, int length)
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidFinishLoading(DocumentLoader* loader, unsigned long identifier, ResourceLoader* resource)
{
    m_webFrame->webView()->webViewPrivate()->afterDownloadResource(loader, resource);
}

void FrameLoaderClientArmite::dispatchDidFailLoading(DocumentLoader* loader, unsigned long identifier, const ResourceError& error, ResourceLoader* resource)
{
    if(!error.isNull() && !error.isCancellation()){
        LOGI("url:%s error:%d\n", error.failingURL().utf8().data(), error.errorCode());
        LOGI("domain:%s des:%s\n", error.domain().utf8().data(), error.localizedDescription().utf8().data());
    }
    if (resource)
        m_webFrame->webView()->webViewPrivate()->afterDownloadResource(loader, resource);
}

bool FrameLoaderClientArmite::shouldCacheResponse(DocumentLoader* loader, unsigned long identifier, const ResourceResponse& response, const unsigned char* data, const unsigned long long length)
{
    return false;
}

void FrameLoaderClientArmite::dispatchDidHandleOnloadEvents()
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidReceiveServerRedirectForProvisionalLoad()
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidCancelClientRedirect()
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchWillPerformClientRedirect(const KURL& url, double delay, double fireDate)
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidChangeLocationWithinPage()
{
    notImplemented();
}
void FrameLoaderClientArmite::dispatchDidPushStateWithinPage()
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidReplaceStateWithinPage()
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidPopStateWithinPage()
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchWillClose()
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidReceiveIcon()
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidStartProvisionalLoad()
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidReceiveTitle(const StringWithDirection& title)
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidChangeIcons(WebCore::IconType)
{
    notImplemented();
}

static const char *globalJavaScriptString = NULL;
void FrameLoaderClientArmite::setGlobalJavaScript(const char *str)
{
    globalJavaScriptString = str;
}

void FrameLoaderClientArmite::dispatchDidCommitLoad()
{
    if (globalJavaScriptString != NULL) {
        Frame* frame = core(m_webFrame);
        frame->script()->executeScript(ScriptSourceCode(String::fromUTF8(globalJavaScriptString)));
    }
}

void FrameLoaderClientArmite::dispatchDidFinishDocumentLoad()
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidFinishLoad()
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidFirstLayout()
{
    notImplemented();
}

Frame* FrameLoaderClientArmite::dispatchCreatePage(const WebCore::NavigationAction&)
{
    notImplemented();
    return 0;
}

void FrameLoaderClientArmite::dispatchShow()
{
    notImplemented();
}

void FrameLoaderClientArmite::setMainDocumentError(DocumentLoader*, const ResourceError& error)
{
    notImplemented();
}

void FrameLoaderClientArmite::postProgressStartedNotification()
{
#ifdef BENCH_LOAD_TIME
    gettimeofday(&m_timerStart, NULL);
#endif
}

void FrameLoaderClientArmite::postProgressEstimateChangedNotification()
{
    notImplemented();
}

void FrameLoaderClientArmite::postProgressFinishedNotification()
{
    notImplemented();
#ifdef BENCH_LOAD_TIME
    gettimeofday(&m_timerStop, NULL);
    if (m_timerStart.tv_sec == m_timerStop.tv_sec)
        printf("load time: %06d us\n", static_cast<uint32_t> (m_timerStop.tv_usec - m_timerStart.tv_usec));
    else {
        int seconds = m_timerStop.tv_sec - m_timerStart.tv_sec;
        int microseconds = m_timerStop.tv_usec - m_timerStart.tv_usec;
        if (microseconds < 0) {
            seconds -= 1;
            microseconds = 1000000 + microseconds;
        }
        printf("load time: %d s %06d us\n", seconds, microseconds);
    }
    fflush(stdout);
#endif
}

void FrameLoaderClientArmite::committedLoad(DocumentLoader* loader, const char* data, int length)
{
    m_webFrame->webView()->webViewPrivate()->committedLoad(loader, data, length);
}

void FrameLoaderClientArmite::finishedLoading(DocumentLoader* loader)
{
    committedLoad(loader, 0, 0);
}

void FrameLoaderClientArmite::updateGlobalHistory()
{
    notImplemented();
}

void FrameLoaderClientArmite::updateGlobalHistoryRedirectLinks()
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidAddBackForwardItem(HistoryItem*) const
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidRemoveBackForwardItem(HistoryItem*) const
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidChangeBackForwardIndex() const
{
    notImplemented();
}


void FrameLoaderClientArmite::didDisplayInsecureContent()
{
    notImplemented();
}

void FrameLoaderClientArmite::didRunInsecureContent(SecurityOrigin* origin, const WebCore::KURL&)
{
    notImplemented();
}

PassRefPtr<DocumentLoader> FrameLoaderClientArmite::createDocumentLoader(const ResourceRequest& request, const SubstituteData& substituteData)
{
    RefPtr<DocumentLoader> loader = DocumentLoader::create(request, substituteData);
    if (substituteData.isValid())
        loader->setDeferMainResourceDataLoad(false);
    return loader.release();
}

void FrameLoaderClientArmite::setTitle(const StringWithDirection& title, const KURL& url)
{
    notImplemented();
}

void FrameLoaderClientArmite::savePlatformDataToCachedFrame(CachedFrame* cachedFrame)
{
    notImplemented();
}

void FrameLoaderClientArmite::transitionToCommittedFromCachedFrame(CachedFrame*)
{
    notImplemented();
}

void FrameLoaderClientArmite::transitionToCommittedForNewPage()
{
    WebView* view = m_webFrame->webView();

    IntRect rect = view->webViewPrivate()->frameRect();
    Color backgroundColor = Color::transparent;
    core(m_webFrame)->createView(rect.size(), backgroundColor, true, IntSize(), IntRect(), false, ScrollbarAlwaysOff, true, ScrollbarAlwaysOff, true);
}

PassRefPtr<Frame> FrameLoaderClientArmite::createFrame(const KURL& url, const String& name, HTMLFrameOwnerElement* ownerElement, const String& referrer, bool /*allowsScrolling*/, int /*marginWidth*/, int /*marginHeight*/)
{
    RefPtr<Frame> result = createFrame(url, name, ownerElement, referrer);
    if (!result)
        return 0;

    return result.release();
}

PassRefPtr<Frame> FrameLoaderClientArmite::createFrame(const KURL& url, const String& name, HTMLFrameOwnerElement* ownerElement, const String& referrer)
{
    if (url.string().isEmpty())
        return 0;

    Frame* coreFrame = core(m_webFrame);
    ASSERT(coreFrame);

    WebFrame* webFrame = WebFrame::createInstance();
    RefPtr<Frame> childFrame = webFrame->init(m_webFrame->webView(), coreFrame->page(), ownerElement);

    coreFrame->tree()->appendChild(childFrame);
    childFrame->tree()->setName(name);

    if (!childFrame->page()) {
        delete webFrame;
        return 0;
    }

    childFrame->loader()->loadURLIntoChildFrame(url, referrer, childFrame.get());

    if (!childFrame->tree()->parent()) {
        delete webFrame;
        return 0;
    }

    return childFrame.release();
}

void FrameLoaderClientArmite::didTransferChildFrameToNewDocument(WebCore::Page*)
{
    notImplemented();
}

PassRefPtr<Widget> FrameLoaderClientArmite::createPlugin(const IntSize& pluginSize, HTMLPlugInElement* element, const KURL& url, const Vector<String>& paramNames, const Vector<String>& paramValues, const String& mimeType, bool loadManually)
{
    Frame* frame = core(m_webFrame);
    PassRefPtr<PluginView> pluginView = PluginView::create(frame, pluginSize, element, url, paramNames, paramValues, mimeType, true);

    if (pluginView->status() == PluginStatusLoadedSuccessfully)
        return pluginView;

    return pluginView;
}

void FrameLoaderClientArmite::redirectDataToPlugin(Widget* pluginWidget)
{
    notImplemented();
}

void FrameLoaderClientArmite::forceLayoutForNonHTML()
{
    notImplemented();
}

void FrameLoaderClientArmite::setCopiesOnScroll()
{
    notImplemented();
}

void FrameLoaderClientArmite::detachedFromParent2()
{
    notImplemented();
}

void FrameLoaderClientArmite::detachedFromParent3()
{
    notImplemented();
}

void FrameLoaderClientArmite::cancelPolicyCheck()
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchWillSubmitForm(FramePolicyFunction function, PassRefPtr<FormState> formState)
{
    Frame* coreFrame = core(m_webFrame);
    (coreFrame->loader()->policyChecker()->*function)(PolicyUse);
}

void FrameLoaderClientArmite::revertToProvisionalState(DocumentLoader*)
{
    notImplemented();
}

void FrameLoaderClientArmite::setMainFrameDocumentReady(bool)
{
    notImplemented();
}

void FrameLoaderClientArmite::willChangeTitle(DocumentLoader*)
{
    notImplemented();
}

void FrameLoaderClientArmite::didChangeTitle(DocumentLoader* loader)
{
    notImplemented();
}

bool FrameLoaderClientArmite::canHandleRequest(const ResourceRequest& request) const
{
    return true;
}

bool FrameLoaderClientArmite::canShowMIMEType(const String& type) const
{
    return MIMETypeRegistry::isSupportedImageMIMEType(type) || MIMETypeRegistry::isSupportedNonImageMIMEType(type) ||
            PluginDatabase::installedPlugins()->isMIMETypeRegistered(type);
}

bool FrameLoaderClientArmite::representationExistsForURLScheme(const String& /*URLScheme*/) const
{
    return false;
}

String FrameLoaderClientArmite::generatedMIMETypeForURLScheme(const String& /*URLScheme*/) const
{
    notImplemented();
    return String();
}

void FrameLoaderClientArmite::frameLoadCompleted()
{
    notImplemented();
}

void FrameLoaderClientArmite::restoreViewState()
{
    notImplemented();
}

void FrameLoaderClientArmite::provisionalLoadStarted()
{
    notImplemented();
}

void FrameLoaderClientArmite::didFinishLoad()
{
    notImplemented();
}

void FrameLoaderClientArmite::prepareForDataSourceReplacement()
{
    notImplemented();
}

String FrameLoaderClientArmite::userAgent(const KURL& url)
{
    return String(WebView::getStaticInstance()->getUserAgentString());
}

void FrameLoaderClientArmite::transitionToCommittedFromCachedPage(CachedPage*)
{
    notImplemented();
}

void FrameLoaderClientArmite::saveViewStateToItem(HistoryItem*)
{
    notImplemented();
}

ResourceError FrameLoaderClientArmite::cancelledError(const ResourceRequest& request)
{
    return ResourceError(String(WebURLErrorDomain), WebURLErrorCancelled, request.url().string(), String());
}

ResourceError FrameLoaderClientArmite::blockedError(const ResourceRequest& request)
{
    return ResourceError(String(WebKitErrorDomain), WebKitErrorCannotUseRestrictedPort, request.url().string(), String());
}

ResourceError FrameLoaderClientArmite::cannotShowURLError(const ResourceRequest& request)
{
    return ResourceError(String(WebKitCannotShowURL), WebURLErrorBadURL, request.url().string(), String());
}

ResourceError FrameLoaderClientArmite::interruptedForPolicyChangeError(const ResourceRequest& request)
{
    return ResourceError(String(WebKitErrorDomain), WebKitErrorFrameLoadInterruptedByPolicyChange, request.url().string(), String());
}

ResourceError FrameLoaderClientArmite::cannotShowMIMETypeError(const ResourceResponse& response)
{
    return ResourceError(String(WebKitErrorMIMETypeKey), WebKitErrorCannotShowMIMEType, response.url().string(), String());
}

ResourceError FrameLoaderClientArmite::fileDoesNotExistError(const ResourceResponse& response)
{
    return ResourceError(String(WebKitFileDoesNotExist), WebURLErrorFileDoesNotExist, response.url().string(), String());
}

ResourceError FrameLoaderClientArmite::pluginWillHandleLoadError(const ResourceResponse& response)
{
    return ResourceError(String(WebKitErrorDomain), 204, response.url().string(), String());
}


bool FrameLoaderClientArmite::shouldFallBack(const ResourceError& error)
{
    return error.errorCode() != WebURLErrorCancelled;
}

void FrameLoaderClientArmite::dispatchDecidePolicyForMIMEType(FramePolicyFunction function, const String& mimeType, const ResourceRequest& request)
{
    Frame* coreFrame = core(m_webFrame);
    if (coreFrame)
        (coreFrame->loader()->policyChecker()->*function)(PolicyUse);
}

void FrameLoaderClientArmite::dispatchDecidePolicyForNewWindowAction(FramePolicyFunction function, const NavigationAction& action, const ResourceRequest& request, PassRefPtr<FormState> formState, const String& frameName)
{
    Frame* coreFrame = core(m_webFrame);
    if (coreFrame)
        (coreFrame->loader()->policyChecker()->*function)(PolicyIgnore);
}

void FrameLoaderClientArmite::dispatchDecidePolicyForNavigationAction(FramePolicyFunction function, const NavigationAction& action, const ResourceRequest& request, PassRefPtr<FormState> formState)
{
    Frame* coreFrame = core(m_webFrame);
    if (coreFrame)
        (coreFrame->loader()->policyChecker()->*function)(PolicyUse);
}

void FrameLoaderClientArmite::dispatchUnableToImplementPolicy(const ResourceError& error)
{
    notImplemented();
}

void FrameLoaderClientArmite::download(ResourceHandle* handle, const ResourceRequest&, const ResourceResponse& response)
{
    notImplemented();
}

bool FrameLoaderClientArmite::dispatchDidLoadResourceFromMemoryCache(DocumentLoader*, const ResourceRequest&, const ResourceResponse&, int /*length*/)
{
    return false;
}

void FrameLoaderClientArmite::dispatchDidFailProvisionalLoad(const ResourceError& error)
{
    notImplemented();
}

void FrameLoaderClientArmite::dispatchDidFailLoad(const ResourceError& error)
{
    notImplemented();
}

void FrameLoaderClientArmite::startDownload(const ResourceRequest&, const String& suggestedName)
{
    notImplemented();
}

PassRefPtr<Widget> FrameLoaderClientArmite::createJavaAppletWidget(const IntSize& pluginSize, HTMLAppletElement* element, const KURL& /*baseURL*/, const Vector<String>& paramNames, const Vector<String>& paramValues)
{
    RefPtr<PluginView> pluginView = PluginView::create(core(m_webFrame), pluginSize, element, KURL(), paramNames, paramValues, "application/x-java-applet", false);

    // Check if the plugin can be loaded successfully
    if (pluginView->plugin() && pluginView->plugin()->load())
        return pluginView;

    return pluginView;
}

ObjectContentType FrameLoaderClientArmite::objectContentType(const KURL& url, const String& mimeType, bool shouldPreferPlugInsForImages)
{
    return FrameLoader::defaultObjectContentType(url, mimeType,shouldPreferPlugInsForImages);
}

String FrameLoaderClientArmite::overrideMediaType() const
{
    notImplemented();
    return String();
}

void FrameLoaderClientArmite::dispatchDidClearWindowObjectInWorld(DOMWrapperWorld* world)
{
    notImplemented();
}

void FrameLoaderClientArmite::documentElementAvailable()
{
    notImplemented();
}

void FrameLoaderClientArmite::didPerformFirstNavigation() const
{
    notImplemented();
}

void FrameLoaderClientArmite::frameLoaderDestroyed()
{
    delete this;
}

void FrameLoaderClientArmite::registerForIconNotification(bool listen)
{
    notImplemented();
}

void FrameLoaderClientArmite::makeRepresentation(DocumentLoader*)
{
    notImplemented();
}

PassRefPtr<WebCore::FrameNetworkingContext>FrameLoaderClientArmite::createNetworkingContext()
{
    notImplemented();
    return PassRefPtr<FrameNetworkingContext>();
}
 
bool FrameLoaderClientArmite::shouldUsePluginDocument(const String& mimeType) const
{
    return false;
}

#if USE(CURL_OPENSSL)
void FrameLoaderClientArmite::didReceiveSSLSecurityExtension(const ResourceRequest& request, const char* securityExtension)
{
    notImplemented();
}
#endif



