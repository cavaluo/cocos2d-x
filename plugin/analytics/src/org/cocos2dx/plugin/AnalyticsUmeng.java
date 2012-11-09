package org.cocos2dx.plugin;

import java.util.Hashtable;

import android.content.Context;

import com.umeng.analytics.MobclickAgent;

public class AnalyticsUmeng implements IAnalytics{

	private Context mContext = null;
	private static AnalyticsUmeng sThisObj = null;
	
	public AnalyticsUmeng(Context context) {
		mContext = context;
		sThisObj = this;
	}
	
	public static boolean isValid() {
		return (sThisObj != null) && (sThisObj.mContext != null);
	}
	@Override
	public void beginSession(String appKey) {
		// TODO Auto-generated method stub
		MobclickAgent.onResume(mContext);
	}

	@Override
	public void endSession() {
		// TODO Auto-generated method stub
		MobclickAgent.onPause(mContext);
	}

	@Override
	public void setSessionContinueMillis(long millis) {
		// TODO Auto-generated method stub
		MobclickAgent.setSessionContinueMillis(millis);
	}

	@Override
	public void setCaptureUncaughtException(boolean isEnabled) {
		// TODO Auto-generated method stub
		if (isEnabled) {
			MobclickAgent.onError(mContext);
		}
	}

	@Override
	public void setDebugMode(boolean isDebugMode) {
		// TODO Auto-generated method stub
		MobclickAgent.setDebugMode(isDebugMode);
	}

	@Override
	public void logError(String errorId, String message,
			Hashtable<String, String> paramsMap) {
		// TODO Auto-generated method stub
		MobclickAgent.reportError(mContext, message);
	}

	@Override
	public void logEvent(String eventId) {
		// TODO Auto-generated method stub
		MobclickAgent.onEvent(mContext, eventId);
	}

	@Override
	public void logEvent(String eventId, Hashtable<String, String> paramMap) {
		// TODO Auto-generated method stub
		MobclickAgent.onEvent(mContext, eventId, paramMap);
	}

	@Override
	public void logTimedEventBegin(String eventId) {
		// TODO Auto-generated method stub
		MobclickAgent.onEventBegin(mContext, eventId);
	}

	@Override
	public void logTimedEventBegin(String eventId,
			Hashtable<String, String> paramMap) {
		// TODO Auto-generated method stub
		MobclickAgent.onKVEventBegin(mContext, eventId, paramMap, eventId);
	}

	@Override
	public void logTimedEventEnd(String eventId) {
		// TODO Auto-generated method stub
		MobclickAgent.onKVEventEnd(mContext, eventId, eventId);
	}

	static String getConfigParams(String key) {
		if (!isValid()) return null;
		return MobclickAgent.getConfigParams(sThisObj.mContext, key);
	}
	
	static void setDefaultReportPolicy(int policy) {
		if (!isValid()) return;
		MobclickAgent.setDefaultReportPolicy(sThisObj.mContext, policy);
	}
	
	static void logEventWithLabel(String eventId, String label) {
		if (!isValid()) return;
		MobclickAgent.onEvent(sThisObj.mContext, eventId, label);
	}
	
	static void logEventWithDuration(String eventId, long duration) {
		if (!isValid()) return;
		MobclickAgent.onEventDuration(sThisObj.mContext, eventId, duration);
	}
	
	static void logEventWithDuration(String eventId, long duration, String label) {
		if (!isValid()) return;
	    MobclickAgent.onEventDuration(sThisObj.mContext, eventId, label, duration);
	}
	
	static void logEventWithDuration(String eventId, long duration, Hashtable<String, String> paramMap) {
		if (!isValid()) return;
		MobclickAgent.onEventDuration(sThisObj.mContext, eventId, paramMap, duration);
	}
	
}
