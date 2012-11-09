LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := analytics_static

LOCAL_MODULE_FILENAME := libanalytics_static

LOCAL_SRC_FILES := Analytics.cpp 

LOCAL_CFLAGS := 

LOCAL_EXPORT_CFLAGS := 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include 

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include  

LOCAL_LDLIBS := -landroid
LOCAL_LDLIBS += -llog

include $(BUILD_STATIC_LIBRARY)

