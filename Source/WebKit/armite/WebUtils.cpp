/*
 * Copyright (C) 2011 armite@126.com.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "WebUtils.h"
#include "WebKitTypes.h"

void armiteConfigGetCacheCapacities(int* minDeadBytes, int* maxDeadBytes, int* totalBytes)
{
    *totalBytes = 80 * 1024 *1024;
    const char *total = getenv("ARMITE_CACHE_TOTAL");
    if(total)
        *totalBytes = atoi(total);
    const char *max = getenv("ARMITE_CACHE_MAXDEAD");
    *maxDeadBytes = *totalBytes/2;
    if(max)
        *maxDeadBytes = atoi(max);
    *minDeadBytes = *totalBytes/16;
    const char *min = getenv("ARMITE_CACHE_MINDEAD");
    if(min)
        *minDeadBytes = atoi(min);
    LOGI("***armite config cache capacities***total:%dbite,max:%dbite,min:%dbite\n", *totalBytes, *maxDeadBytes, *minDeadBytes);
    return;
}

int armiteConfigGetCurlTimeout()
{
    static int curlTimeout = 0;
    if(curlTimeout <= 0){
        const char *time = getenv("ARMITE_CURL_TIMEOUT");
        if(time)
            curlTimeout = atoi(time);
        else
            curlTimeout = 60;
        LOGI("***armite config curl timeout***timeout:%ds\n", curlTimeout);
    }
    return curlTimeout;
}

int armiteConfigGetCurlRetryTimes()
{
    static int curlRetryTimes = 0;
    if(curlRetryTimes <= 0){
        const char *time = getenv("ARMITE_CURL_RETRYTIMES");
        if(time)
            curlRetryTimes = atoi(time);
        else
            curlRetryTimes = 5;
        LOGI("***armite config curl retry times***times:%d\n", curlRetryTimes);
    }
    return curlRetryTimes;
}

int armiteConfigGetMaxHTTPConnect()
{
    int maxHTTPConnect = 0;
    const char *count = getenv("ARMITE_MAX_HTTP_CONNECT");
    if(count)
        maxHTTPConnect = atoi(count);
    else
        maxHTTPConnect = 8;
    LOGI("***armite config max http connect***max:%d\n", maxHTTPConnect);
    return maxHTTPConnect;
}

int armiteConfigGetPageCacheCapacity()
{
    int pageCacheCapacity = 0;
    const char *count = getenv("ARMITE_PAGE_CACHE_CAPACITY");
    if(count)
        pageCacheCapacity = atoi(count);
    else
        pageCacheCapacity = 3;
    LOGI("***armite config page cache capacity***capacity:%d\n", pageCacheCapacity);
    return pageCacheCapacity;
}

int armiteConfigGetHistoryCapacity()
{
    int historyCapacity = 0;
    const char *count = getenv("ARMITE_HISTORY_CAPACITY");
    if(count)
        historyCapacity = atoi(count);
    else
        historyCapacity = 5;
    LOGI("***armite config history capacity***capacity:%d\n", historyCapacity);
    return historyCapacity;
}





