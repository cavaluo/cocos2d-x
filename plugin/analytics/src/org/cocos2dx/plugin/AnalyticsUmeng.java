package org.cocos2dx.plugin;

import java.util.Hashtable;
import android.content.Context;
import android.util.Log;

import com.umeng.analytics.MobclickAgent;

public class AnalyticsUmeng implements IAnalytics{
	
	private static boolean sIsInitialized = false;
	private Context mContext = null;
	
	protected static String TAG = "AnalyticsUmeng";
	
	protected static void LogE(String msg, Exception e) {
		Log.e(TAG, msg, e);
	}
	
	public AnalyticsUmeng(Context context) {
		mContext = context;
	}
	
	public boolean isValid() {
		return mContext != null;
	}
	@Override
	public void startSession(String appKey) {
		// TODO Auto-generated method stub
		MobclickAgent.onResume(mContext);
	}

	@Override
	public void stopSession() {
		// TODO Auto-generated method stub
		MobclickAgent.onPause(mContext);
	}

	@Override
	public void setSessionContinueMillis(int millis) {
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
	public void logTimedEventEnd(String eventId) {
		// TODO Auto-generated method stub
		MobclickAgent.onEventEnd(mContext, eventId);
	}

	protected String getConfigParams(String key) {
		if (!isValid()) return null;
		String ret = "";
		try{
			ret = MobclickAgent.getConfigParams(mContext, key);
		} catch(Exception e){
			LogE("Exception in logTimedEventBegin", e);
		}
		return ret;
	}
	
	protected void updateOnlineConfig() {
		if (!isValid()) return;
		try{
			MobclickAgent.updateOnlineConfig(mContext);
		} catch(Exception e){
			LogE("Exception in updateOnlineConfig", e);
		}
	}
	
	protected void setDefaultReportPolicy(int policy) {
		if (!isValid()) return;
		try{
			MobclickAgent.setDefaultReportPolicy(mContext, policy);
		} catch(Exception e){
			LogE("Exception in setDefaultReportPolicy", e);
		}
	}
	
	protected void logEventWithLabel(String eventId, String label) {
		if (!isValid()) return;
		try{
			MobclickAgent.onEvent(mContext, eventId, label);
		} catch(Exception e){
			LogE("Exception in logEventWithLabel", e);
		}
	}
	
	protected void logEventWithDuration(String eventId, int duration) {
		if (!isValid()) return;
		try{
			MobclickAgent.onEventDuration(mContext, eventId, duration);
		} catch(Exception e){
			LogE("Exception in logEventWithDuration, eventId, duration", e);
		}
	}
	
	protected void logEventWithDuration(String eventId, int duration, String label) {
		if (!isValid()) return;
		try{
			MobclickAgent.onEventDuration(mContext, eventId, label, duration);
		} catch(Exception e){
			LogE("Exception in logEventWithDuration, eventId, label, duration", e);
		}
	}
	
	protected void logEventWithDuration(String eventId, int duration, Hashtable<String, String> paramMap) {
		if (!isValid()) return;
		try{
			MobclickAgent.onEventDuration(mContext, eventId, paramMap, duration);
		} catch(Exception e){
			LogE("Exception in logEventWithDuration,eventId,duration,paramMap", e);
		}
	}
	
	protected void logTimedEventWithLabelBegin(String eventId, String label) {
		if (!isValid()) return;
		try{
			MobclickAgent.onEventBegin(mContext, eventId, label);
		} catch(Exception e){
			LogE("Exception in logTimedEventWithLabelBegin", e);
		}
	}
	
	protected void logTimedEventWithLabelEnd(String eventId, String label) {
		if (!isValid()) return;
		try{
			MobclickAgent.onEventEnd(mContext, eventId, label);
		} catch(Exception e){
			LogE("Exception in logTimedEventWithLabelEnd", e);
		}
	}
	
	protected void logTimedKVEventBegin(String eventId, String label, Hashtable<String, String> paramMap) {
		if (!isValid()) return;
		try{
			MobclickAgent.onKVEventBegin(mContext, eventId, paramMap, label);
		} catch(Exception e){
			LogE("Exception in logTimedKVEventBegin", e);
		}
	}
	
	protected void logTimedKVEventEnd(String eventId, String label) {
		if (!isValid()) return;
		try{
			MobclickAgent.onKVEventEnd(mContext, eventId, label);
		} catch(Exception e){
			LogE("Exception in logTimedKVEventEnd", e);
		}
	}
	
	protected static void init() {
		if (!sIsInitialized) {
			sIsInitialized = true;
			Context ctx = AnalyticsWrapper.getContext();
			if (ctx != null) {
				AnalyticsWrapper.nativeInitAnalytics(new AnalyticsUmeng(ctx), AnalyticsUmeng.class.getName().replace('.', '/'));
			} else {
				Log.e("AnalyticsUmeng", "AnalyticsWrapper wasn't initialized.");
			}
		}
	}
}
