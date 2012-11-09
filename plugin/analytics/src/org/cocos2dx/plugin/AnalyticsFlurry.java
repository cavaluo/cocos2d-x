package org.cocos2dx.plugin;

import java.util.Hashtable;

import android.content.Context;

import com.flurry.android.FlurryAgent;

public class AnalyticsFlurry implements IAnalytics {

	private Context mContext = null;
	
	public AnalyticsFlurry(Context context) {
		mContext = context;
	}
	
	@Override
	public void beginSession(String appKey) {
		// TODO Auto-generated method stub
		FlurryAgent.onStartSession(mContext, appKey);
	}

	@Override
	public void endSession() {
		// TODO Auto-generated method stub
		FlurryAgent.onEndSession(mContext);
	}

	@Override
	public void setSessionContinueMillis(long millis) {
		// TODO Auto-generated method stub
		FlurryAgent.setContinueSessionMillis(millis);
	}

	@Override
	public void setCaptureUncaughtException(boolean isEnabled) {
		// TODO Auto-generated method stub
		FlurryAgent.setCaptureUncaughtExceptions(isEnabled);
	}

	@Override
	public void setDebugMode(boolean isDebugMode) {
		// TODO Auto-generated method stub
		FlurryAgent.setLogEnabled(isDebugMode);
	}

	@Override
	public void logError(String errorId, String message,
			Hashtable<String, String> paramMap) {
		// TODO Auto-generated method stub
		FlurryAgent.onError(errorId, message, "");
	}

	@Override
	public void logEvent(String eventId) {
		// TODO Auto-generated method stub
		FlurryAgent.logEvent(eventId);
	}

	@Override
	public void logEvent(String eventId, Hashtable<String, String> paramMap) {
		// TODO Auto-generated method stub
		FlurryAgent.logEvent(eventId, paramMap);
	}

	@Override
	public void logTimedEventBegin(String eventId) {
		// TODO Auto-generated method stub
		FlurryAgent.logEvent(eventId, true);
	}

	@Override
	public void logTimedEventBegin(String eventId,
			Hashtable<String, String> paramMap) {
		// TODO Auto-generated method stub
		FlurryAgent.logEvent(eventId, paramMap, true);
	}

	@Override
	public void logTimedEventEnd(String eventId) {
		// TODO Auto-generated method stub
		FlurryAgent.endTimedEvent(eventId);
	}

	public static int getAgentVersion() {
		return FlurryAgent.getAgentVersion();
	}
	
	public static void setVersionName(String versionName) {
		FlurryAgent.setVersionName(versionName);
	}
	
	public static void setAge(int age) {
		FlurryAgent.setAge(age);
	}
	
	public static void setGender(byte gender) {
		FlurryAgent.setGender(gender);
	}
	
	public static void setUserId(String userId) {
		FlurryAgent.setUserId(userId);
	}
	
	public static void setUseHttps(boolean isUseHttps) {
		FlurryAgent.setUseHttps(isUseHttps);
	}
}
