/*
 * Copyright (C) 2012 armite@126.com.
 *
 */

#include "config.h"
#include "WebView.h"
#include "wtf/NullPtr.h"

#include "BackForwardList.h"
#include "ChromeClientArmite.h"
#include "EditorClientArmite.h"
#include "FrameLoaderClientArmite.h"
#include "WebFrame.h"
#include "WebViewPrivate.h"
#include "WebUtils.h"
#include "Settings.h"
#include "RenderTheme.h"

#include <Chrome.h>
#include <wtf/MainThread.h>
#include <InitializeThreading.h>
#include <Page.h>
#include <PageGroup.h>
#include <PageCache.h>
#include <MemoryCache.h>
#include <DocumentLoader.h>
#include <FocusController.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

class SocketEvent {
public:
    SocketEvent(int);
    ~SocketEvent();
    int receiveEvent(ArmiteEvent*, double);
    int sendEvent(ArmiteEvent*);
private:
    int m_socketfd;
    int m_socketport;
};

SocketEvent::SocketEvent(int port)
{
    struct sockaddr_in sa;
    m_socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    m_socketport = port;

    bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(m_socketport);
    sa.sin_addr.s_addr = htons(INADDR_ANY);
    bzero(&(sa.sin_zero), 8);
    bind(m_socketfd, (struct sockaddr *)&sa, sizeof(sa));
}

SocketEvent::~SocketEvent()
{
    close(m_socketfd);
}

int SocketEvent::receiveEvent(ArmiteEvent* event, double timeout)
{
    fd_set rfds;
    struct timeval tv;

    FD_ZERO(&rfds);
    FD_SET(m_socketfd, &rfds);

    if (timeout <= 0.000001) {
        tv.tv_sec = 0;
        tv.tv_usec = 1;
    } else {
        tv.tv_sec = static_cast<long>(timeout);
        tv.tv_usec = static_cast<long>((timeout - tv.tv_sec) * 1000000.0);
    }

    if(select(m_socketfd+1, &rfds, NULL, NULL, &tv) <= 0)
        return 0;
    return recvfrom(m_socketfd, (void*)event, sizeof(ArmiteEvent),MSG_DONTWAIT, NULL, NULL);
}

int SocketEvent::sendEvent(ArmiteEvent* event)
{
    int socketfd;
    struct sockaddr_in sa;

    bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(m_socketport);
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(sa.sin_zero), 8);

    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    sendto(socketfd,(void*)event,sizeof(ArmiteEvent),MSG_NOSIGNAL,(struct sockaddr *)&sa,sizeof(struct sockaddr_in));
    close(socketfd);

    return 0;
}

using namespace WebCore;
static WebView *globalWebView = NULL;
static SocketEvent *globalSocket = NULL;

WebView::WebView()
    : d(new WebViewPrivate(this))
    , m_mainPage(0)
    , m_mainFrame(0)
    , m_userAgent(0)
#ifdef ANDROID
    , m_javaVM(0)
    , m_class(NULL)
    , m_object(NULL)
    , m_alertMethodID(NULL)
    , m_confirmMethodID(NULL)
    , m_promptMethodID(NULL)
#endif
{
    JSC::initializeThreading();
    WTF::initializeMainThread();

    int totalBytes,minDeadBytes,maxDeadBytes;
    armiteConfigGetCacheCapacities(&minDeadBytes,&maxDeadBytes,&totalBytes);
    memoryCache()->setCapacities(minDeadBytes, maxDeadBytes, totalBytes);
    pageCache()->setCapacity(armiteConfigGetPageCacheCapacity());

    Page::PageClients pageClients;
    pageClients.chromeClient = d->chromeClient();
    pageClients.editorClient = d->editorClient();
    pageClients.dragClient = 0;
    pageClients.inspectorClient = 0;
    pageClients.backForwardClient = 0;

    m_mainPage = new Page(pageClients);
    d->initDefalultSetting(m_mainPage->settings());

    m_mainFrame = WebFrame::createInstance();
    m_mainFrame->init(this, m_mainPage, 0);

    globalSocket = new SocketEvent(17080);
}

WebView::~WebView()
{
    if (!m_mainPage)
        return;

    Frame* frame = m_mainPage->mainFrame();
    if (frame)
        frame->loader()->detachFromParent();

    delete m_mainFrame;
    delete m_mainPage;
    delete d;
    m_mainFrame = 0;
    m_mainPage = 0;
    d = 0;
    globalWebView = 0;
    globalSocket = 0;
}

WebView* WebView::getStaticInstance()
{
    if (!globalWebView)
        globalWebView = new WebView();
    return globalWebView;
}

void WebView::initGraphic(ArmiteSurface *surface, ArmiteRect& rect, GraphicExpose expose)
{
    d->setFrameRect(rect);
    d->initViewWindow(surface, expose);

    RefPtr<Frame> coreFrame = core(m_mainFrame);
    PageGroup::setShouldTrackVisitedLinks(false);
    m_mainPage->focusController()->setFocusedFrame(coreFrame);
    m_mainPage->focusController()->setActive(true);
    m_mainPage->focusController()->setFocused(true);
    coreFrame->selection()->setFocused(true);
}

static char *webLoadURL = NULL;
void WebView::startBrowser(const char *url)
{
    m_mainFrame->loadURL(url);

    bool browserRunning = true;
    double timeout = 0;
    ArmiteEvent event;

    while(browserRunning) {
        timeout = d->getNextSharedTimerFireTime();
        if(globalSocket->receiveEvent(&event, timeout) > 0) {
            switch(event.type){
                case ARMITE_EXPOSEEVENT:
                    d->onExpose(event.data.expose);
                    break;
                case ARMITE_KEYBOARDEVENT:
                    d->onKeyDown(event.data.key);
                    break;
                case ARMITE_MOUSEEVENT:
                    d->onMouseEvent(event.data.mouse);
                    break;
                case ARMITE_CUSTOMEVENT:
                    if (event.data.key.unicode == ARMITE_CUSTOMEVENT_LOAD && m_mainFrame)
                        m_mainFrame->loadURL(webLoadURL);
                    break;
                case ARMITE_BROWSER_EXIT:
                    browserRunning = false;
                    break;
            }
        }
        d->fireWebKitTimerEvents();
    }

    printf("browser exit\n");
    delete globalWebView;
}

void WebView::sendEvent2Browser(ArmiteEvent* event)
{
    globalSocket->sendEvent(event);
}

void WebView::setSpatialNavigationEnabled(bool value)
{
    m_mainPage->settings()->setSpatialNavigationEnabled(value);
}

void WebView::setFocusRingColor(int r, int g, int b, int a)
{
    RenderTheme::setCustomFocusRingColor(makeRGBA(r, g, b, a));
}

namespace WebCore {
    void setFocusRingLineWidth(int);
    void setExtraDefaultStyleSheetString(const char *);
}

void WebView::setFocusRingWidth(int w)
{
    setFocusRingLineWidth(w);
}

void WebView::setExtraDefaultCSS(const char *str)
{
    setExtraDefaultStyleSheetString(str);
}

void WebView::setGlobalJavaScript(const char *str)
{
    FrameLoaderClientArmite::setGlobalJavaScript(str);
}

#ifdef ANDROID
static JNIEnv* getJNIEnv(JavaVM* javaVM)
{
    JNIEnv* jniEnv = NULL;
    if(javaVM->GetEnv((void**)(&jniEnv), JNI_VERSION_1_6) != JNI_OK)
        if(javaVM->GetEnv((void**)(&jniEnv), JNI_VERSION_1_4) != JNI_OK)
            if(javaVM->GetEnv((void**)(&jniEnv), JNI_VERSION_1_2) != JNI_OK)
                LOGI("in webview getJNIEnv(). get env error");
    return jniEnv;
}
#endif

void WebView::javaScriptAlert(const char* message)
{
#ifdef ANDROID
    JNIEnv* env = getJNIEnv(m_javaVM);
    if (!env)
        return;

    if (!m_alertMethodID)
        m_alertMethodID = env->GetMethodID(m_class, "alert","(Ljava/lang/String;)V");
    jstring jmsg = env->NewStringUTF(message);
    env->CallVoidMethod(m_object, m_alertMethodID, jmsg);
    env->DeleteLocalRef(jmsg);
#else
    LOGI("[js alert][%s]\n",message);
#endif
}

bool WebView::javaScriptConfirm(const char* message)
{
#ifdef ANDROID
    JNIEnv* env = getJNIEnv(m_javaVM);
    if (!env)
        return false;

    if (!m_confirmMethodID)
        m_confirmMethodID = env->GetMethodID(m_class, "confirm","(Ljava/lang/String;)Z");
    jstring jmsg = env->NewStringUTF(message);
    bool ret = env->CallBooleanMethod(m_object, m_confirmMethodID, jmsg);
    env->DeleteLocalRef(jmsg);
    return ret;
#else
    LOGI("[js confirm][%s]\n",message);
    return true;
#endif
}

bool WebView::javaScriptPrompt(const char* message)
{
#ifdef ANDROID
    JNIEnv* env = getJNIEnv(m_javaVM);
    if (!env)
        return false;

    if (!m_promptMethodID)
        m_promptMethodID = env->GetMethodID(m_class, "prompt","(Ljava/lang/String;)Z");
    jstring jmsg = env->NewStringUTF(message);
    bool ret = env->CallBooleanMethod(m_object, m_confirmMethodID, jmsg);
    env->DeleteLocalRef(jmsg);
    return ret;
#else
    LOGI("[js prompt][%s]\n",message);
    return true;
#endif
}

bool WebView::canGoBack()
{
    if (!m_mainPage)
        return false;
    return m_mainPage->canGoBackOrForward(-1);
}

bool WebView::goBack()
{
    if (!m_mainPage)
        return false;
    return m_mainPage->goBack();
}

bool WebView::canGoForward()
{
    if (!m_mainPage)
        return false;
    return m_mainPage->canGoBackOrForward(1);
}

bool WebView::goForward()
{
    if (!m_mainPage)
        return false;
    return m_mainPage->goForward();
}

void WebView::stop()
{
    if (m_mainFrame)
        m_mainFrame->stop();
}

void WebView::refresh()
{
    if (m_mainFrame)
        m_mainFrame->reload();
}

void WebView::load(const char *url)
{
    ArmiteEvent event;
    event.type = ARMITE_CUSTOMEVENT;
    event.data.key.vkey = ARMITE_CUSTOMEVENT;
    event.data.key.unicode = ARMITE_CUSTOMEVENT_LOAD;

    if (webLoadURL)
        free(webLoadURL);
    webLoadURL = strdup(url);
    globalSocket->sendEvent(&event);
}

#ifdef ANDROID
JNIEnv* WebView::getJavaEnv()
{
    if (!m_javaVM)
        return NULL;

    JNIEnv* javaEnv = NULL;
    if(m_javaVM->GetEnv((void**)(&javaEnv), JNI_VERSION_1_6) != JNI_OK) {
        if(m_javaVM->GetEnv((void**)(&javaEnv), JNI_VERSION_1_4) != JNI_OK) {
            if(m_javaVM->GetEnv((void**)(&javaEnv), JNI_VERSION_1_2) != JNI_OK) {
                LOGI("in WebView::getJavaEnv(). get env error");
            } else
                LOGI("in WebView::getJavaEnv(). ver: 1.2");
        } else
            LOGI("in WebView::getJavaEnv(). ver: 1.4");
    } else
        LOGI("in WebView::getJavaEnv(). ver: 1.6 %p", javaEnv);

    return javaEnv;
}

void WebView::sendEvent2cvm(unsigned char event)
{
    int socketfd;
    struct sockaddr_in sa;

    bzero(&sa, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(17081);
    sa.sin_addr.s_addr = inet_addr("127.0.0.1");
    bzero(&(sa.sin_zero), 8);

    socketfd = socket(AF_INET, SOCK_DGRAM, 0);
    sendto(socketfd,(void*)&event,sizeof(unsigned char),MSG_NOSIGNAL,(struct sockaddr *)&sa,sizeof(struct sockaddr_in));
    close(socketfd);
}
#endif

void WebView::getUrl(const uint16_t* &url, int &len)
{
    len = 0;
    if (!m_mainFrame || !core(m_mainFrame)->loader() || !core(m_mainFrame)->loader()->documentLoader())
        return;
    String uri = core(m_mainFrame)->loader()->documentLoader()->url().string();
    len = uri.length();
    url = uri.characters16();
}

bool WebView::isMainFrameSet()
{
    RefPtr<Frame> coreFrame = core(m_mainFrame);
    if (!coreFrame)
        return false;
    if (!coreFrame->document())
        return false;
    return coreFrame->document()->isFrameSet();
}





