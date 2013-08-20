/*
 * Copyright (C) 2011 armite@126.com.
 *
 */
#ifndef WebUtils_H
#define WebUtils_H

void armiteConfigGetCacheCapacities(int*,int*,int*);
int armiteConfigGetCurlTimeout();
int armiteConfigGetMaxHTTPConnect();
int armiteConfigGetCurlRetryTimes();
int armiteConfigGetPageCacheCapacity();
int armiteConfigGetHistoryCapacity();

#endif
