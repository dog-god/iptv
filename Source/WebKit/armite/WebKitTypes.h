/*
 * Copyright (C) 2012 armite.
 *
 */

#ifndef WebKitTypes_h
#define WebKitTypes_h

#include <stdint.h>

#define EXPORT __attribute__((visibility("default")))

#ifndef LOG_TAG
#define  LOG_TAG "armite-browser"
#ifdef ANDROID
#include <android/log.h>
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG, __VA_ARGS__)
#else
#include <stdio.h>
#define  LOGI(...)  do{printf("I/"LOG_TAG":");printf(__VA_ARGS__);}while(0);
#endif
#endif

struct _cairo_surface;
typedef struct _cairo_surface cairo_surface_t;

typedef cairo_surface_t ArmiteWidget;
typedef cairo_surface_t ArmiteSurface;

enum {
    ARMITE_EXPOSEEVENT = 1,
    ARMITE_KEYBOARDEVENT,

    ARMITE_MOUSEEVENT,
    ARMITE_MOUSEEVENT_DOWN,
    ARMITE_MOUSEEVENT_MOVE,
    ARMITE_MOUSEEVENT_UP,

    ARMITE_BROWSER_EXIT = 50,
    ARMITE_CUSTOMEVENT_LOAD,
    ARMITE_CUSTOMEVENT = 0xff
};

typedef struct _ArmiteExposeEvent {
    int w, h;
} ArmiteExposeEvent;

typedef struct _ArmiteKeyboardEvent {
    uint16_t vkey;
    uint16_t unicode;
} ArmiteKeyboardEvent;

typedef struct _ArmiteMouseEvent {
    uint8_t type;
    uint16_t x;
    uint16_t y;
} ArmiteMouseEvent;

typedef struct _ArmiteEvent {
    uint8_t type;
    union {
        ArmiteExposeEvent   expose;
        ArmiteKeyboardEvent key;
        ArmiteMouseEvent    mouse;
    } data;
} ArmiteEvent;

typedef struct _ArmiteRect {
    uint16_t x, y;
    uint16_t w, h;
} ArmiteRect;

#endif


