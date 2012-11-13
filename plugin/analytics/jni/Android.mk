LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := analytics_static

LOCAL_MODULE_FILENAME := libanalytics_static

LOCAL_SRC_FILES := AnalyticsProtocol.cpp Analytics_umeng.cpp Analytics_flurry.cpp AnalyticsUtils.cpp  

LOCAL_CFLAGS := 

LOCAL_EXPORT_CFLAGS := 

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include 

LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/../include  

LOCAL_LDLIBS := -landroid
LOCAL_LDLIBS += -llog

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static

include $(BUILD_STATIC_LIBRARY)

$(call import-module,cocos2dx)
