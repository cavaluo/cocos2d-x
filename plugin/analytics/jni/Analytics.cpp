#include "Analytics.h"

namespace cocos2d { namespace plugin {

#define return_if_fails(cond) if (!(cond)) return; 

static jobject createJavaMapObject(const EventParamMap* pParams)
{
	jclass class_Hashtable = t.env->FindClass("java/util/Hashtable"); 
	jmethodID construct_method = t.env->GetMethodID( class_Hashtable, "<init>","()V"); 
	jobject obj_Map = t.env->NewObject( class_Hashtable, construct_method, ""); 

	jmethodID add_method= t.env->GetMethodID( class_Hashtable,"put","(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;"); 

	for (LogEventParametersType::iterator it = pParams->begin(); it != pParams->end(); ++it)
	{
		t.env->CallObjectMethod(obj_Map,add_method, t.env->NewStringUTF(it->first.c_str()), t.env->NewStringUTF(it->second.c_str()));  
	}

    t.env->DeleteLocalRef(class_Hashtable);

    return obj_Map;
}

static void callJavaFunctionWithName_string_map(const char* funcName, const char* keyParam, const EventParamMap pParamMap)
{
	return_if_fails(funcName == NULL && strlen(funcName) > 0);
	return_if_fails(keyParam == NULL && strlen(keyParam) > 0);

	JniMethodInfo t;
    if (NULL == pParams)
    {
    	if (JniHelper::getStaticMethodInfo(t
    		, "org/cocos2dx/plugin/Analytics"
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
    		, "org/cocos2dx/plugin/Analytics"
    		, funcName
    		, "(Ljava/lang/String;Ljava/util/Hashtable;)V"))
    	{
    		jstring jeventId = t.env->NewStringUTF(keyParam);
    		jobject obj_Map = createJavaMapObject(pParamMap);
    		t.env->CallStaticVoidMethod(t.classID, t.methodID, jeventId, obj_Map);
    		t.env->DeleteLocalRef(jeventId);
    		t.env->DeleteLocalRef(obj_Map);
            t.env->DeleteLocalRef(t.classID);
    	}
    }
}

static void callJavaFunctionWithName(const char* funcName)
{
	return_if_fails(funcName == NULL && strlen(funcName) > 0);
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/Analytics"
		, funcName
		, "(V)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

template <typename T>
static void callJavaFunctionWithName_oneBaseType(const char* funcName, const char* paramCode, T param)
{
	return_if_fails(funcName == NULL && strlen(funcName) > 0);
	return_if_fails(paramCode == NULL && strlen(paramCode) > 0);
	JniMethodInfo t; 
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/Analytics"
		, funcName
		, paramCode))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, param);
		t.env->DeleteLocalRef(t.classID);
	}
}

AnalyticsProtocol::~AnalyticsProtocol()
{

}

void AnalyticsProtocol::beginSession(const char* appKey)
{
	callJavaFunctionWithName_string_map("beginSession", appKey, NULL);
}

void AnalyticsProtocol::endSession()
{
	callJavaFunctionWithName("endSession");
}

void AnalyticsProtocol::setSessionContinueMillis(long millis)
{
	callJavaFunctionWithName_oneBaseType("setSessionContinueMillis", "(J)V", millis);
}

void AnalyticsProtocol::setCaptureUncaughtException(bool isEnabled)
{
	callJavaFunctionWithName_oneBaseType("setSessionContinueMillis", "(Z)V", isEnabled);
}

void AnalyticsProtocol::setDebugMode(bool isDebugMode)
{
	callJavaFunctionWithName_oneBaseType("setSessionContinueMillis", "(Z)V", isDebugMode);
}

void AnalyticsProtocol::logError(const char* errorId, const char* message, const EventParamMap* pParams/* = NULL */)
{
	return_if_fails(errorId == NULL && strlen(errorId) > 0);
	return_if_fails(message == NULL && strlen(message) > 0);

    JniMethodInfo t;
    if (NULL == pParams)
    {
    	if (JniHelper::getStaticMethodInfo(t
    		, "org/cocos2dx/plugin/Analytics"
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
    		, "org/cocos2dx/plugin/Analytics"
    		, "logError"
    		, "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Hashtable;)V"))
    	{
    		jstring jerrorId = t.env->NewStringUTF(errorId);
    		jstring jmessage = t.env->NewStringUTF(message);

    		jobject jobjMap = createJavaMapObject(pParams);
    		t.env->CallStaticVoidMethod(t.classID, t.methodID, jerrorId, jmessage, jobjMap);
    		t.env->DeleteLocalRef(jerrorId);
    		t.env->DeleteLocalRef(jmessage);
    		t.env->DeleteLocalRef(jobjMap);
            t.env->DeleteLocalRef(t.classID);
    	}
	}
}



void AnalyticsProtocol::logEvent(const char* eventId, const EventParamMap* pParams/* = NULL */)
{
	callJavaFunctionWithName_string_map("logEvent", eventId, pParams);
}

void AnalyticsProtocol::logTimedEventBegin(const char* eventId, const EventParamMap* pParams/* = NULL */)
{
	callJavaFunctionWithName_string_map("logTimedEventBegin", eventId, pParams);
}

void AnalyticsProtocol::logTimedEventEnd(const char* eventId)
{
	callJavaFunctionWithName_string_map("logTimedEventEnd", eventId, NULL);
}

}} //namespace cocos2d { namespace plugin {
