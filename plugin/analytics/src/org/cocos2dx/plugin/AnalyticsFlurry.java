package org.cocos2dx.plugin;

import java.util.Hashtable;

import android.content.Context;
import android.provider.SyncStateContract.Constants;
import android.util.Log;

import com.flurry.android.FlurryAgent;

public class AnalyticsFlurry implements IAnalytics {


	private static boolean sIsInitialized = false;
	private Context mContext = null;
	protected static String TAG = "AnalyticsFlurry";
	
	protected static void LogE(String msg, Exception e) {
		Log.e(TAG, msg, e);
	}
	
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

	protected void logTimedEventBegin(String eventId, Hashtable<String, String> paramMap) {
		try{
			FlurryAgent.logEvent(eventId, paramMap, true);
		} catch(Exception e){
			LogE("Exception in logTimedEventBegin", e);
		}
	}
	
	protected void setReportLocation(boolean enabled) {
		try{
			FlurryAgent.setReportLocation(enabled);
		} catch(Exception e){
			LogE("Exception in setReportLocation", e);
		}
	}
	
	protected void  logPageView() {
		try{
			FlurryAgent.onPageView();
		} catch(Exception e){
			LogE("Exception in logPageView", e);
		}
	}
	
	protected int getAgentVersion() {
		int ret = 0;
		try {
			ret = FlurryAgent.getAgentVersion();
		} catch(Exception e){
			LogE("Exception in getAgentVersion", e);
		}
		return ret;
	}
	
	protected void setVersionName(String versionName) {
		try {
			FlurryAgent.setVersionName(versionName);
		} catch(Exception e){
			LogE("Exception in setVersionName", e);
		}
	}
	
	protected void setAge(int age) {
		try {
			FlurryAgent.setAge(age);
		} catch(Exception e){
			LogE("Exception in setAge", e);
		}
	}
	
	protected void setGender(byte gender) {
		try {
			FlurryAgent.setGender(gender);
		} catch(Exception e){
			LogE("Exception in setGender", e);
		}
	}
	
	protected void setUserId(String userId) {
		try {
			FlurryAgent.setUserId(userId);
		} catch(Exception e){
			LogE("Exception in setUserId", e);
		}
	}
	
	protected void setUseHttps(boolean useHttps) {
		try {
			FlurryAgent.setUseHttps(useHttps);
		} catch(Exception e){
			LogE("Exception in setUseHttps", e);
		}
	}
	
	protected static void init() {
		if (!sIsInitialized) {
			sIsInitialized = true;
			Context ctx = AnalyticsWrapper.getContext();
			if (ctx != null) {
				AnalyticsWrapper.nativeInitAnalytics(new AnalyticsFlurry(ctx), AnalyticsFlurry.class.getName().replace('.', '/'));
			} else {
				Log.e("AnalyticsFlurry", "AnalyticsWrapper wasn't initialized.");
			}
		}
	}
}
