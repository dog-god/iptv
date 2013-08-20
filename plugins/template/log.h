/*
 * add by armite@126.com
 */

#ifndef PLUGIN_LOG_H_
#define PLUGIN_LOG_H_

#ifndef LOG_TAG
#define LOG_TAG "armite-plugin"
#ifdef ANDROID
#include <android/log.h>
#define  NP_TRACE(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG, __VA_ARGS__)
#else
#define  NP_TRACE(...)  do{printf("I/"LOG_TAG":");printf(__VA_ARGS__);printf("\n");}while(0);
#endif
#define UNIMPLEMENTED() NP_TRACE("Unimplemented: [%s]in file[%s]at line[%d].\n" , __FUNCTION__, __FILE__, __LINE__);
#endif

#define CHECK_ARG_TYPE(condition) if (!(condition)) {\
    NP_TRACE("CHECK_ARG_TYPE falied: improper argument type. %s , %d\n", __FUNCTION__, __LINE__);\
    return false;\
}

#ifndef HIBYTE
#define HIBYTE(x) ((((uint32_t)(x)) & 0xff00) >> 8)
#endif

#ifndef LOBYTE
#define LOBYTE(W) ((W) & 0xFF)
#endif

#endif



