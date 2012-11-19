#include "AnalyticsUtils.h"
#include <android/log.h>

namespace cocos2d { namespace plugin {

#define JAVAVM    cocos2d::JniHelper::getJavaVM()

#if 1
#define  LOG_TAG    "AnalyticsUtils"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)
#else
#define  LOGD(...) 
#endif

jobject AnalyticsUtils::createJavaMapObject(JniMethodInfo&t, const LogEventParamMap* paramMap)
{
	jclass class_Hashtable = t.env->FindClass("java/util/Hashtable"); 
	jmethodID construct_method = t.env->GetMethodID( class_Hashtable, "<init>","()V"); 
	jobject obj_Map = t.env->NewObject( class_Hashtable, construct_method, "");
	if (paramMap != NULL)
	{
		jmethodID add_method= t.env->GetMethodID( class_Hashtable,"put","(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;"); 
		for (LogEventParamMap::const_iterator it = paramMap->begin(); it != paramMap->end(); ++it)
		{
			t.env->CallObjectMethod(obj_Map, add_method, t.env->NewStringUTF(it->first.c_str()), t.env->NewStringUTF(it->second.c_str()));  
		}
	}
    t.env->DeleteLocalRef(class_Hashtable);
    return obj_Map;
}

bool AnalyticsUtils::initJavaAnalytics(const char* className)
{
	return_val_if_fails(className != NULL && strlen(className) > 0, false);
	bool bRet = false;
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t
		, "org/cocos2dx/plugin/AnalyticsWrapper"
		, "java_initAnalytics"
		, "(Ljava/lang/String;)Z"))
	{
		jstring jclassName = t.env->NewStringUTF(className);
		bRet = (bool)t.env->CallStaticBooleanMethod(t.classID, t.methodID, jclassName);
		t.env->DeleteLocalRef(jclassName);
		t.env->DeleteLocalRef(t.classID);
	}
	return bRet;
}

JNIEnv* AnalyticsUtils::getEnv()
{
    bool bRet = false;
    JNIEnv* env = NULL;
    do 
    {
        if (JAVAVM->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK)
        {
            LOGD("Failed to get the environment using GetEnv()");
            break;
        }

        if (JAVAVM->AttachCurrentThread(&env, 0) < 0)
        {
            LOGD("Failed to get the environment using AttachCurrentThread()");
            break;
        }

        bRet = true;
    } while (0);        

    if (!bRet) {
    	env = NULL; 
    }

    return env;
}

}}// namespace cocos2d { namespace plugin {
