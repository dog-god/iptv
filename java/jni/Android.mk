ROOT_LOCAL_PATH := $(call my-dir)

LOCAL_PATH := $(ROOT_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE    := webkit-browser
LOCAL_SRC_FILES := ../../neon/lib/libmywebkit.so
LOCAL_EXPORT_C_INCLUDES := $(ROOT_LOCAL_PATH)/../../Source/WebKit/armite
LOCAL_EXPORT_C_INCLUDES += $(ROOT_LOCAL_PATH)/../../Source/ThirdParty/cairo-1.12.8
include $(PREBUILT_SHARED_LIBRARY)

LOCAL_PATH := $(ROOT_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE    := plugin-iPanel
LOCAL_SRC_FILES := ../../neon/lib/libiPanel.so
include $(PREBUILT_SHARED_LIBRARY)

LOCAL_PATH := $(ROOT_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE    := plugin-Authentication
LOCAL_SRC_FILES := ../../neon/lib/libAuthentication.so
include $(PREBUILT_SHARED_LIBRARY)

LOCAL_PATH := $(ROOT_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE    := plugin-Navigation
LOCAL_SRC_FILES := ../../neon/lib/libNavigation.so
include $(PREBUILT_SHARED_LIBRARY)

LOCAL_PATH := $(ROOT_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE    := plugin-MediaPlayer
LOCAL_SRC_FILES := ../../neon/lib/libMediaPlayer.so
include $(PREBUILT_SHARED_LIBRARY)

LOCAL_PATH := $(ROOT_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE    := plugin-Utility
LOCAL_SRC_FILES := ../../neon/lib/libUtility.so
include $(PREBUILT_SHARED_LIBRARY)

LOCAL_PATH := $(ROOT_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE    := plugin-J2ME
LOCAL_SRC_FILES := ../../neon/lib/libPhoneme.so
include $(PREBUILT_SHARED_LIBRARY)

LOCAL_PATH := $(ROOT_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE    := cdc-J2ME
LOCAL_SRC_FILES := ../../advanced/cdc/build/linux-arm-generic/bin/libcvm.so
include $(PREBUILT_SHARED_LIBRARY)

LOCAL_PATH := $(ROOT_LOCAL_PATH)
include $(CLEAR_VARS)
LOCAL_MODULE    := armite-webview
LOCAL_SRC_FILES := WebView.cpp
LOCAL_LDLIBS    := -llog -ljnigraphics
LOCAL_SHARED_LIBRARIES := webkit-browser
include $(BUILD_SHARED_LIBRARY)



