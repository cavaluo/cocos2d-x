#include "AnalyticsProtocol.h"
#include "jni/JniHelper.h"
#include <android/log.h>
#include "AnalyticsUtils.h"

#if 1
#define  LOG_TAG    "AnalyticsProtocol"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

namespace cocos2d { namespace plugin {

static void callJavaFunctionWithName_string_map(const char* funcName, const char* keyParam, const LogEventParamMap* pParamMap)
{
	return_if_fails(funcName != NULL && strlen(funcName) > 0);
	return_if_fails(keyParam != NULL && strlen(keyParam) > 0);

	JniMethodInfo t;
    if (NULL == pParamMap)
    {
    	if (JniHelper::getStaticMethodInfo(t
    		, "org/cocos2dx/plugin/AnalyticsWrapper"
    		, funcName
    		, "(Ljava/lang/String;)V"))
    	{
    		jstring jeventId = t.env->NewStringUTF(keyParam);
    		t.env->CallStaticVoidMethod(t.classID, t.methodID, jeventId);
    		t.env->DeleteLocalRef(jeventId);
    		t.env->DeleteLocalRef(t.classID);
    	}
    }
    else
    {
    	if (JniHelper::getStaticMethodInfo(t
    		, "org/cocos2dx/plugin/AnalyticsWrapper"
    		, funcName
    		, "(Ljava/lang/String;Ljava/util/Hashtable;)V"))
    	{
    		jstring jeventId = t.env->NewStringUTF(keyParam);
    		jobject obj_Map = createJavaMapObject(t, pParamMap);
    		t.env->CallStaticVoidMethod(t.classID, t.methodID, jeventId, obj_Map);
    		t.env->DeleteLocalRef(jeventId);
    		t.env->DeleteLocalRef(obj_Map);
            t.env->DeleteLocalRef(t.classID);
    	}
    }
}

template <typename T>
static void callJavaFunctionWithName_oneBaseType(const char* funcName, const char* paramCode, T param)
{
	return_if_fails(funcName != NULL && strlen(funcName) > 0);
	return_if_fails(paramCode != NULL && strlen(paramCode) > 0);
	JniMethodInfo t; 
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsWrapper"
		, funcName
		, paramCode))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, param);
		t.env->DeleteLocalRef(t.classID);
	}
}

AnalyticsProtocol::AnalyticsProtocol()
{ 
}

AnalyticsProtocol::~AnalyticsProtocol()
{
}

void AnalyticsProtocol::startSession(const char* appKey)
{
	callJavaFunctionWithName_string_map("startSession", appKey, NULL);
}

void AnalyticsProtocol::stopSession()
{
    JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t
        , "org/cocos2dx/plugin/AnalyticsWrapper"
        , "stopSession"
        , "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void AnalyticsProtocol::setSessionContinueMillis(long millis)
{
	callJavaFunctionWithName_oneBaseType("setSessionContinueMillis", "(I)V", millis);
}

void AnalyticsProtocol::setCaptureUncaughtException(bool isEnabled)
{
	callJavaFunctionWithName_oneBaseType("setCaptureUncaughtException", "(Z)V", isEnabled);
}

void AnalyticsProtocol::setDebugMode(bool isDebugMode)
{
	callJavaFunctionWithName_oneBaseType("setDebugMode", "(Z)V", isDebugMode);
}

void AnalyticsProtocol::logError(const char* errorId, const char* message, const LogEventParamMap* pParams/* = NULL */)
{
	return_if_fails(errorId != NULL && strlen(errorId) > 0);
	return_if_fails(message != NULL && strlen(message) > 0);

    JniMethodInfo t;
    if (NULL == pParams)
    {
    	if (JniHelper::getStaticMethodInfo(t
    		, "org/cocos2dx/plugin/AnalyticsWrapper"
    		, "logError"
    		, "(Ljava/lang/String;Ljava/lang/String;)V"))
    	{
    		jstring jerrorId = t.env->NewStringUTF(errorId);
    		jstring jmessage = t.env->NewStringUTF(message);

    		t.env->CallStaticVoidMethod(t.classID, t.methodID, jerrorId, jmessage);
    		t.env->DeleteLocalRef(jerrorId);
    		t.env->DeleteLocalRef(jmessage);
    		t.env->DeleteLocalRef(t.classID);
    	}
	}
	else
	{
    	if (JniHelper::getStaticMethodInfo(t
    		, "org/cocos2dx/plugin/AnalyticsWrapper"
    		, "logError"
    		, "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Hashtable;)V"))
    	{
    		jstring jerrorId = t.env->NewStringUTF(errorId);
    		jstring jmessage = t.env->NewStringUTF(message);

    		jobject jobjMap = createJavaMapObject(t, pParams);
    		t.env->CallStaticVoidMethod(t.classID, t.methodID, jerrorId, jmessage, jobjMap);
    		t.env->DeleteLocalRef(jerrorId);
    		t.env->DeleteLocalRef(jmessage);
    		t.env->DeleteLocalRef(jobjMap);
            t.env->DeleteLocalRef(t.classID);
    	}
	}
}



void AnalyticsProtocol::logEvent(const char* eventId, const LogEventParamMap* pParams/* = NULL */)
{
	callJavaFunctionWithName_string_map("logEvent", eventId, pParams);
}

void AnalyticsProtocol::logTimedEventBegin(const char* eventId)
{
	callJavaFunctionWithName_string_map("logTimedEventBegin", eventId, NULL);
}

void AnalyticsProtocol::logTimedEventEnd(const char* eventId)
{
	callJavaFunctionWithName_string_map("logTimedEventEnd", eventId, NULL);
}

}} //namespace cocos2d { namespace plugin {
