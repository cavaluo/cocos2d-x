#include "AnalyticsProtocol.h"
#include "jni/JniHelper.h"
#include <android/log.h>
#include "AnalyticsUtils.h"
#include "AnalyticsData_android.h"

#if 1
#define  LOG_TAG    "AnalyticsProtocol"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

static cocos2d::plugin::AnalyticsProtocol* s_pAnalyticsInstance = NULL;

extern "C" {

JNIEXPORT void JNICALL Java_org_cocos2dx_plugin_AnalyticsWrapper_nativeInitAnalytics(JNIEnv*  env, jobject thiz, jobject obj, jstring className)
{
    if (s_pAnalyticsInstance != NULL) {
        cocos2d::plugin::AnalyticsData* pUserData = new cocos2d::plugin::AnalyticsData();
        pUserData->jobj = env->NewGlobalRef(obj);
        pUserData->jclassName = cocos2d::JniHelper::jstring2string(className);
        s_pAnalyticsInstance->setUserData(pUserData);
    }
}

}

namespace cocos2d { namespace plugin {

static void callJavaFunctionWithName_string_map(AnalyticsProtocol* thiz, const char* funcName, const char* keyParam, const LogEventParamMap* paramMap)
{
	return_if_fails(funcName != NULL && strlen(funcName) > 0);
	return_if_fails(keyParam != NULL);

    AnalyticsData* pData = (AnalyticsData*)thiz->getUserData();

	JniMethodInfo t;
    if (NULL == paramMap)
    {
    	if (JniHelper::getMethodInfo(t
    		, pData->jclassName.c_str()
    		, funcName
    		, "(Ljava/lang/String;)V"))
    	{
    		jstring jeventId = t.env->NewStringUTF(keyParam);
    		t.env->CallVoidMethod(pData->jobj, t.methodID, jeventId);
    		t.env->DeleteLocalRef(jeventId);
    		t.env->DeleteLocalRef(t.classID);
    	}
    }
    else
    {
    	if (JniHelper::getMethodInfo(t
    		, pData->jclassName.c_str()
    		, funcName
    		, "(Ljava/lang/String;Ljava/util/Hashtable;)V"))
    	{
    		jstring jeventId = t.env->NewStringUTF(keyParam);
    		jobject obj_Map = AnalyticsUtils::createJavaMapObject(t, paramMap);
    		t.env->CallVoidMethod(pData->jobj, t.methodID, jeventId, obj_Map);
    		t.env->DeleteLocalRef(jeventId);
    		t.env->DeleteLocalRef(obj_Map);
            t.env->DeleteLocalRef(t.classID);
    	}
    }
}

template <typename T>
static void callJavaFunctionWithName_oneBaseType(AnalyticsProtocol* thiz, const char* funcName, const char* paramCode, T param)
{
	return_if_fails(funcName != NULL && strlen(funcName) > 0);
	return_if_fails(paramCode != NULL && strlen(paramCode) > 0);
    AnalyticsData* pData = (AnalyticsData*)thiz->getUserData();

	JniMethodInfo t; 
	if (JniHelper::getMethodInfo(t
		, pData->jclassName.c_str()
		, funcName
		, paramCode))
	{
		t.env->CallVoidMethod(pData->jobj, t.methodID, param);
		t.env->DeleteLocalRef(t.classID);
	}
}

AnalyticsProtocol::AnalyticsProtocol()
{
    s_pAnalyticsInstance = this;
}

AnalyticsProtocol::~AnalyticsProtocol()
{
    if (m_pUserData != NULL)
    {
        AnalyticsData* pData = (AnalyticsData*)m_pUserData;
        jobject jobj = pData->jobj;
        JNIEnv* pEnv = JniHelper::getEnv();
        LOGD("Delete global reference.");
        pEnv->DeleteGlobalRef(jobj);
        delete pData;
        m_pUserData = NULL;
    }
}

void AnalyticsProtocol::startSession(const char* appKey)
{
	callJavaFunctionWithName_string_map(this, "startSession", appKey, NULL);
}

void AnalyticsProtocol::stopSession()
{
    AnalyticsData* pData = (AnalyticsData*)this->getUserData();
    JniMethodInfo t;
    if (JniHelper::getMethodInfo(t
        , pData->jclassName.c_str()
        , "stopSession"
        , "()V"))
    {
        t.env->CallVoidMethod(pData->jobj, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

void AnalyticsProtocol::setSessionContinueMillis(long millis)
{
	callJavaFunctionWithName_oneBaseType(this, "setSessionContinueMillis", "(I)V", millis);
}

void AnalyticsProtocol::setCaptureUncaughtException(bool isEnabled)
{
	callJavaFunctionWithName_oneBaseType(this, "setCaptureUncaughtException", "(Z)V", isEnabled);
}

void AnalyticsProtocol::setDebugMode(bool isDebugMode)
{
	callJavaFunctionWithName_oneBaseType(this, "setDebugMode", "(Z)V", isDebugMode);
}

void AnalyticsProtocol::logError(const char* errorId, const char* message, const LogEventParamMap* pParams/* = NULL */)
{
	return_if_fails(errorId != NULL && strlen(errorId) > 0);
	return_if_fails(message != NULL && strlen(message) > 0);

    AnalyticsData* pData = (AnalyticsData*)this->getUserData();
    JniMethodInfo t;
    if (NULL == pParams)
    {
    	if (JniHelper::getMethodInfo(t
    		, pData->jclassName.c_str()
    		, "logError"
    		, "(Ljava/lang/String;Ljava/lang/String;)V"))
    	{
    		jstring jerrorId = t.env->NewStringUTF(errorId);
    		jstring jmessage = t.env->NewStringUTF(message);

    		t.env->CallVoidMethod(pData->jobj, t.methodID, jerrorId, jmessage);
    		t.env->DeleteLocalRef(jerrorId);
    		t.env->DeleteLocalRef(jmessage);
    		t.env->DeleteLocalRef(t.classID);
    	}
	}
	else
	{
    	if (JniHelper::getMethodInfo(t
    		, pData->jclassName.c_str()
    		, "logError"
    		, "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Hashtable;)V"))
    	{
    		jstring jerrorId = t.env->NewStringUTF(errorId);
    		jstring jmessage = t.env->NewStringUTF(message);

    		jobject jobjMap = AnalyticsUtils::createJavaMapObject(t, pParams);
    		t.env->CallVoidMethod(pData->jobj, t.methodID, jerrorId, jmessage, jobjMap);
    		t.env->DeleteLocalRef(jerrorId);
    		t.env->DeleteLocalRef(jmessage);
    		t.env->DeleteLocalRef(jobjMap);
            t.env->DeleteLocalRef(t.classID);
    	}
	}
}



void AnalyticsProtocol::logEvent(const char* eventId, const LogEventParamMap* pParams/* = NULL */)
{
	callJavaFunctionWithName_string_map(this, "logEvent", eventId, pParams);
}

void AnalyticsProtocol::logTimedEventBegin(const char* eventId)
{
	callJavaFunctionWithName_string_map(this, "logTimedEventBegin", eventId, NULL);
}

void AnalyticsProtocol::logTimedEventEnd(const char* eventId)
{
	callJavaFunctionWithName_string_map(this, "logTimedEventEnd", eventId, NULL);
}

}} //namespace cocos2d { namespace plugin {
