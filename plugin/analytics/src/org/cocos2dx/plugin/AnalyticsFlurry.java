package org.cocos2dx.plugin;

import java.util.Hashtable;

import android.content.Context;
import android.provider.SyncStateContract.Constants;
import android.util.Log;

import com.flurry.android.FlurryAgent;

public class AnalyticsFlurry implements IAnalytics {

	private static boolean sIsInitialized = false;

	private Context mContext = null;
	
	public AnalyticsFlurry(Context context) {
		mContext = context;
	}
	
	@Override
	public void startSession(String appKey) {
		// TODO Auto-generated method stub
		FlurryAgent.onStartSession(mContext, appKey);
	}

	@Override
	public void stopSession() {
		// TODO Auto-generated method stub
		FlurryAgent.onEndSession(mContext);
	}

	@Override
	public void setSessionContinueMillis(int millis) {
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
		//FlurryAgent.setLogEnabled(isDebugMode);
		//FlurryAgent.setLogEvents(isDebugMode);
		if (isDebugMode) {
			FlurryAgent.setLogLevel(Log.DEBUG);
		}
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
	public void logTimedEventEnd(String eventId) {
		// TODO Auto-generated method stub
		FlurryAgent.endTimedEvent(eventId);
	}

	protected static void logTimedEventBegin(String eventId, Hashtable<String, String> paramMap) {
		FlurryAgent.logEvent(eventId, paramMap, true);
	}
	
	protected static void setReportLocation(boolean enabled) {
		FlurryAgent.setReportLocation(enabled);
	}
	
	protected static void  logPageView() {
		FlurryAgent.onPageView();
	}
	
	protected static int getAgentVersion() {
		return FlurryAgent.getAgentVersion();
	}
	
	protected static void setVersionName(String versionName) {
		FlurryAgent.setVersionName(versionName);
	}
	
	protected static void setAge(int age) {
		FlurryAgent.setAge(age);
	}
	
	protected static void setGender(byte gender) {
		FlurryAgent.setGender(gender);
	}
	
	protected static void setUserId(String userId) {
		FlurryAgent.setUserId(userId);
	}
	
	protected static void setUseHttps(boolean useHttps) {
		FlurryAgent.setUseHttps(useHttps);
	}
	
	protected static void init() {
		if (!sIsInitialized) {
			sIsInitialized = true;
			Context ctx = AnalyticsWrapper.getContext();
			if (ctx != null) {
				AnalyticsWrapper.setAnalytics(new AnalyticsFlurry(ctx));
			} else {
				Log.e("AnalyticsFlurry", "AnalyticsWrapper wasn't initialized.");
			}
		}
	}
}
