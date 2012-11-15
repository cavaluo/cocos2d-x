#include "AnalyticsUmeng.h"
#include "jni/JniHelper.h"
#include <android/log.h>
#include "AnalyticsUtils.h"
#if 1
#define  LOG_TAG    "AnalyticsUmeng"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

namespace cocos2d { namespace plugin {

PLUGIN_REGISTER_IMPL(AnalyticsUmeng)

AnalyticsUmeng::AnalyticsUmeng()
{
	JniMethodInfo t; 
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsUmeng"
		, "init"
		, "()V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsUmeng::updateOnlineConfig()
{
	JniMethodInfo t;
    if (JniHelper::getStaticMethodInfo(t
        , "org/cocos2dx/plugin/AnalyticsUmeng"
        , "updateOnlineConfig"
        , "()V"))
    {
        t.env->CallStaticVoidMethod(t.classID, t.methodID);
        t.env->DeleteLocalRef(t.classID);
    }
}

const char* AnalyticsUmeng::getConfigParams(const char* key)
{
	static std::string ret = "";
	return_val_if_fails(key != NULL && strlen(key) > 0, "");

	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsUmeng"
		, "getConfigParams"
		, "(Ljava/lang/String;)Ljava/lang/String;"))
	{
		jstring jstrKey = t.env->NewStringUTF(key);
		jstring jstr = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID, jstrKey);
		ret = JniHelper::jstring2string(jstr);
		LOGD("ret = %s", ret.c_str());
		t.env->DeleteLocalRef(jstrKey);
		t.env->DeleteLocalRef(t.classID);
	}
	return ret.c_str();
}

void AnalyticsUmeng::setDefaultReportPolicy(ReportPolicy ePolicy)
{
	return_if_fails(ePolicy == REALTIME 
		         || ePolicy == BATCH_AT_LAUNCH
		         || ePolicy == DAILY
		         || ePolicy == WIFIONLY );

	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsUmeng"
		, "setDefaultReportPolicy"
		, "(I)V"))
	{
		t.env->CallStaticVoidMethod(t.classID, t.methodID, (jint)ePolicy);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsUmeng::logEventWithLabel(const char* eventId, const char* label)
{
	return_if_fails(eventId != NULL && strlen(eventId) > 0);
	return_if_fails(label != NULL && strlen(label) > 0);

	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsUmeng"
		, "logEventWithLabel"
		, "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		jstring jeventId = t.env->NewStringUTF(eventId);
		jstring jlabel = t.env->NewStringUTF(label);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jeventId, jlabel);
		t.env->DeleteLocalRef(jeventId);
		t.env->DeleteLocalRef(jlabel);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsUmeng::logEventWithDuration(const char* eventId, long duration, const char* label)
{
	return_if_fails(eventId != NULL && strlen(eventId) > 0);
	return_if_fails(label != NULL && strlen(label) > 0);

	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsUmeng"
		, "logEventWithDuration"
		, "(Ljava/lang/String;ILjava/lang/String;)V"))
	{
		jstring jeventId = t.env->NewStringUTF(eventId);
		jstring jlabel = t.env->NewStringUTF(label);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jeventId, duration, jlabel);
		t.env->DeleteLocalRef(jeventId);
		t.env->DeleteLocalRef(jlabel);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsUmeng::logEventWithDuration(const char* eventId, long duration, const LogEventParamMap* pParamMap /* = NULL */)
{
	return_if_fails(eventId != NULL && strlen(eventId) > 0);

	JniMethodInfo t;
	if (pParamMap == NULL)
	{
		if (JniHelper::getStaticMethodInfo(t
			, "org/cocos2dx/plugin/AnalyticsUmeng"
			, "logEventWithDuration"
			, "(Ljava/lang/String;I)V"))
		{
			jstring jeventId = t.env->NewStringUTF(eventId);
			t.env->CallStaticVoidMethod(t.classID, t.methodID, jeventId, duration);
			t.env->DeleteLocalRef(jeventId);
			t.env->DeleteLocalRef(t.classID);
		}
	}
	else
	{
		if (JniHelper::getStaticMethodInfo(t
			, "org/cocos2dx/plugin/AnalyticsUmeng"
			, "logEventWithDuration"
			, "(Ljava/lang/String;ILjava/util/Hashtable;)V"))
		{
			jstring jeventId = t.env->NewStringUTF(eventId);
			jobject jparamMap= createJavaMapObject(t, pParamMap);
			t.env->CallStaticVoidMethod(t.classID, t.methodID, jeventId, duration, jparamMap);
			t.env->DeleteLocalRef(jeventId);
			t.env->DeleteLocalRef(jparamMap);
			t.env->DeleteLocalRef(t.classID);
		}
	}

}

void AnalyticsUmeng::logTimedEventWithLabelBegin(const char* eventId, const char* label)
{
	return_if_fails(eventId != NULL && strlen(eventId) > 0);
	return_if_fails(label != NULL && strlen(label) > 0);

	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsUmeng"
		, "logTimedEventWithLabelBegin"
		, "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		jstring jeventId = t.env->NewStringUTF(eventId);
		jstring jlabel = t.env->NewStringUTF(label);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jeventId, jlabel);
		t.env->DeleteLocalRef(jeventId);
		t.env->DeleteLocalRef(jlabel);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsUmeng::logTimedEventWithLabelEnd(const char* eventId, const char* label)
{
	return_if_fails(eventId != NULL && strlen(eventId) > 0);
	return_if_fails(label != NULL && strlen(label) > 0);
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsUmeng"
		, "logTimedEventWithLabelEnd"
		, "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		jstring jeventId = t.env->NewStringUTF(eventId);
		jstring jlabel = t.env->NewStringUTF(label);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jeventId, jlabel);
		t.env->DeleteLocalRef(jeventId);
		t.env->DeleteLocalRef(jlabel);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsUmeng::logTimedKVEventBegin(const char* eventId, const char* label, const LogEventParamMap* pParamMap)
{
	return_if_fails(eventId != NULL && strlen(eventId) > 0);
	return_if_fails(label != NULL && strlen(label) > 0);

	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsUmeng"
		, "logTimedKVEventBegin"
		, "(Ljava/lang/String;Ljava/lang/String;Ljava/util/Hashtable;)V"))
	{
		jstring jeventId = t.env->NewStringUTF(eventId);
		jstring jlabel = t.env->NewStringUTF(label);
		jobject jparamMap= createJavaMapObject(t, pParamMap);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jeventId, jlabel, jparamMap);
		t.env->DeleteLocalRef(jeventId);
		t.env->DeleteLocalRef(jlabel);
		t.env->DeleteLocalRef(jparamMap);
		t.env->DeleteLocalRef(t.classID);
	}
}

void AnalyticsUmeng::logTimedKVEventEnd(const char* eventId, const char* label)
{
	return_if_fails(eventId != NULL && strlen(eventId) > 0);
	return_if_fails(label != NULL && strlen(label) > 0);
	
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsUmeng"
		, "logTimedKVEventEnd"
		, "(Ljava/lang/String;Ljava/lang/String;)V"))
	{
		jstring jeventId = t.env->NewStringUTF(eventId);
		jstring jlabel = t.env->NewStringUTF(label);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jeventId, jlabel);
		t.env->DeleteLocalRef(jeventId);
		t.env->DeleteLocalRef(jlabel);
		t.env->DeleteLocalRef(t.classID);
	}
}


}} // namespace cocos2d { namespace plugin {