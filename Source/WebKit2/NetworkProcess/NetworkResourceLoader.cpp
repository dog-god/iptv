/*
 * Copyright (C) 2012 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "NetworkResourceLoader.h"

#if ENABLE(NETWORK_PROCESS)

#include "BlockingResponseMap.h"
#include "Logging.h"
#include "NetworkConnectionToWebProcess.h"
#include "NetworkProcess.h"
#include "NetworkProcessConnectionMessages.h"
#include "NetworkResourceLoadParameters.h"
#include "RemoteNetworkingContext.h"
#include "SharedMemory.h"
#include "WebCoreArgumentCoders.h"
#include <WebCore/NotImplemented.h>
#include <WebCore/ResourceBuffer.h>
#include <WebCore/ResourceHandle.h>
#include <wtf/MainThread.h>

using namespace WebCore;

namespace WebKit {

NetworkResourceLoader::NetworkResourceLoader(const NetworkResourceLoadParameters& requestParameters, ResourceLoadIdentifier identifier, NetworkConnectionToWebProcess* connection)
    : m_requestParameters(requestParameters)
    , m_identifier(identifier)
    , m_connection(connection)
{
    ASSERT(isMainThread());
    connection->registerObserver(this);
}

NetworkResourceLoader::~NetworkResourceLoader()
{
    ASSERT(isMainThread());

    if (m_connection)
        m_connection->unregisterObserver(this);
}

ResourceLoadPriority NetworkResourceLoader::priority() const
{
    return m_requestParameters.priority();
}

void NetworkResourceLoader::start()
{
    ASSERT(isMainThread());

    // Explicit ref() balanced by a deref() in NetworkResourceLoader::stop()
    ref();
    
    // FIXME (NetworkProcess): Create RemoteNetworkingContext with actual settings.
    m_networkingContext = RemoteNetworkingContext::create(false, false);

    // FIXME (NetworkProcess): Pass an actual value for defersLoading
    m_handle = ResourceHandle::create(m_networkingContext.get(), m_requestParameters.request(), this, false /* defersLoading */, m_requestParameters.contentSniffingPolicy() == SniffContent);
}

static bool stopRequestsCalled = false;

static Mutex& requestsToStopMutex()
{
    DEFINE_STATIC_LOCAL(Mutex, mutex, ());
    return mutex;
}

static HashSet<NetworkResourceLoader*>& requestsToStop()
{
    DEFINE_STATIC_LOCAL(HashSet<NetworkResourceLoader*>, requests, ());
    return requests;
}

void NetworkResourceLoader::scheduleStopOnMainThread()
{
    MutexLocker locker(requestsToStopMutex());

    requestsToStop().add(this);
    if (!stopRequestsCalled) {
        stopRequestsCalled = true;
        callOnMainThread(NetworkResourceLoader::performStops, 0);
    }
}

void NetworkResourceLoader::performStops(void*)
{
    ASSERT(stopRequestsCalled);

    Vector<NetworkResourceLoader*> requests;
    {
        MutexLocker locker(requestsToStopMutex());
        copyToVector(requestsToStop(), requests);
        requestsToStop().clear();
        stopRequestsCalled = false;
    }
    
    for (size_t i = 0; i < requests.size(); ++i)
        requests[i]->stop();
}

void NetworkResourceLoader::stop()
{
    ASSERT(isMainThread());

    // Remove this load identifier soon so we can start more network requests.
    NetworkProcess::shared().networkResourceLoadScheduler().scheduleRemoveLoadIdentifier(m_identifier);
    
    // Explicit deref() balanced by a ref() in NetworkResourceLoader::stop()
    // This might cause the NetworkResourceLoader to be destroyed and therefore we do it last.
    deref();
}

void NetworkResourceLoader::connectionToWebProcessDidClose(NetworkConnectionToWebProcess* connection)
{
    ASSERT_ARG(connection, connection == m_connection.get());
    m_connection->unregisterObserver(this);
    m_connection = 0;
}

void NetworkResourceLoader::didReceiveResponse(ResourceHandle*, const ResourceResponse& response)
{
    // FIXME (NetworkProcess): Cache the response.
    connectionToWebProcess()->connection()->send(Messages::NetworkProcessConnection::DidReceiveResponse(m_identifier, response), 0);
}

void NetworkResourceLoader::didReceiveData(ResourceHandle*, const char* data, int length, int /*encodedDataLength*/)
{
    // FIXME (NetworkProcess): We have to progressively notify the WebProcess as data is received.
    if (!m_buffer)
        m_buffer = ResourceBuffer::create();
    m_buffer->append(data, length);
}

void NetworkResourceLoader::didFinishLoading(ResourceHandle*, double finishTime)
{
    // FIXME (NetworkProcess): Currently this callback can come in on a non-main thread.
    // This is okay for now since resource buffers are per-NetworkResourceLoader.
    // Once we manage memory in an actual memory cache that also includes SharedMemory blocks this will get complicated.
    // Maybe we should marshall it to the main thread?

    ShareableResource::Handle handle;

    if (m_buffer && m_buffer->size()) {
        // FIXME (NetworkProcess): We shouldn't be creating this SharedMemory on demand here.
        // SharedMemory blocks need to be managed as part of the cache backing store.
        RefPtr<SharedMemory> sharedBuffer = SharedMemory::create(m_buffer->size());
        memcpy(sharedBuffer->data(), m_buffer->data(), m_buffer->size());

        RefPtr<ShareableResource> shareableResource = ShareableResource::create(sharedBuffer.release(), 0, m_buffer->size());

        // FIXME (NetworkProcess): Handle errors from createHandle();
        if (!shareableResource->createHandle(handle))
            LOG_ERROR("Failed to create handle to shareable resource memory\n");
    }

    connectionToWebProcess()->connection()->send(Messages::NetworkProcessConnection::DidReceiveResource(m_identifier, handle, finishTime), 0);
    scheduleStopOnMainThread();
}

void NetworkResourceLoader::didFail(ResourceHandle*, const ResourceError& error)
{
    connectionToWebProcess()->connection()->send(Messages::NetworkProcessConnection::DidFailResourceLoad(m_identifier, error), 0);
    scheduleStopOnMainThread();
}

// FIXME (NetworkProcess): Many of the following ResourceHandleClient methods definitely need implementations. A few will not.
// Once we know what they are they can be removed.


static BlockingResponseMap<ResourceRequest*>& responseMap()
{
    AtomicallyInitializedStatic(BlockingResponseMap<ResourceRequest*>&, responseMap = *new BlockingResponseMap<ResourceRequest*>);
    return responseMap;
}

static uint64_t generateWillSendRequestID()
{
    static int64_t uniqueWillSendRequestID;
    return OSAtomicIncrement64Barrier(&uniqueWillSendRequestID);
}

void didReceiveWillSendRequestHandled(uint64_t requestID, const ResourceRequest& request)
{
    responseMap().didReceiveResponse(requestID, adoptPtr(new ResourceRequest(request)));
}

void NetworkResourceLoader::willSendRequest(ResourceHandle*, ResourceRequest& request, const ResourceResponse& redirectResponse)
{
    // We only expect to get the willSendRequest callback from ResourceHandle as the result of a redirect
    ASSERT(!redirectResponse.isNull());

    uint64_t requestID = generateWillSendRequestID();

    if (!connectionToWebProcess()->connection()->send(Messages::NetworkProcessConnection::WillSendRequest(requestID, m_identifier, request, redirectResponse), 0)) {
        // FIXME (NetworkProcess): What should we do if we can't send the message?
        return;
    }
    
    OwnPtr<ResourceRequest> newRequest = responseMap().waitForResponse(requestID);
    request = *newRequest;

    RunLoop::main()->dispatch(WTF::bind(&NetworkResourceLoadScheduler::receivedRedirect, &NetworkProcess::shared().networkResourceLoadScheduler(), m_identifier, request.url()));
}

void NetworkResourceLoader::didSendData(WebCore::ResourceHandle*, unsigned long long /*bytesSent*/, unsigned long long /*totalBytesToBeSent*/)
{
    notImplemented();
}

void NetworkResourceLoader::didReceiveCachedMetadata(WebCore::ResourceHandle*, const char*, int)
{
    notImplemented();
}

void NetworkResourceLoader::wasBlocked(WebCore::ResourceHandle*)
{
    notImplemented();
}

void NetworkResourceLoader::cannotShowURL(WebCore::ResourceHandle*)
{
    notImplemented();
}

void NetworkResourceLoader::willCacheResponse(WebCore::ResourceHandle*, WebCore::CacheStoragePolicy&)
{
    notImplemented();
}

bool NetworkResourceLoader::shouldUseCredentialStorage(WebCore::ResourceHandle*)
{
    notImplemented();
    return false;
}

void NetworkResourceLoader::didReceiveAuthenticationChallenge(WebCore::ResourceHandle*, const WebCore::AuthenticationChallenge&)
{
    notImplemented();
}

void NetworkResourceLoader::didCancelAuthenticationChallenge(WebCore::ResourceHandle*, const WebCore::AuthenticationChallenge&)
{
    notImplemented();
}

void NetworkResourceLoader::receivedCancellation(WebCore::ResourceHandle*, const WebCore::AuthenticationChallenge&)
{
    notImplemented();
}

#if USE(PROTECTION_SPACE_AUTH_CALLBACK)
bool NetworkResourceLoader::canAuthenticateAgainstProtectionSpace(WebCore::ResourceHandle*, const WebCore::ProtectionSpace&)
{
    notImplemented();
    return false;
}
#endif

#if HAVE(NETWORK_CFDATA_ARRAY_CALLBACK)
bool NetworkResourceLoader::supportsDataArray()
{
    notImplemented();
    return false;
}

void NetworkResourceLoader::didReceiveDataArray(WebCore::ResourceHandle*, CFArrayRef)
{
    notImplemented();
}
#endif

#if PLATFORM(MAC)
#if USE(CFNETWORK)
CFCachedURLResponseRef NetworkResourceLoader::willCacheResponse(WebCore::ResourceHandle*, CFCachedURLResponseRef response)
{
    notImplemented();
    return response;
}
#else
NSCachedURLResponse* NetworkResourceLoader::willCacheResponse(WebCore::ResourceHandle*, NSCachedURLResponse* response)
{
    notImplemented();
    return response;
}
#endif

void NetworkResourceLoader::willStopBufferingData(WebCore::ResourceHandle*, const char*, int)
{
    notImplemented();
}
#endif // PLATFORM(MAC)

#if ENABLE(BLOB)
WebCore::AsyncFileStream* NetworkResourceLoader::createAsyncFileStream(WebCore::FileStreamClient*)
{
    notImplemented();
    return 0;
}
#endif

} // namespace WebKit

#endif // ENABLE(NETWORK_PROCESS)
