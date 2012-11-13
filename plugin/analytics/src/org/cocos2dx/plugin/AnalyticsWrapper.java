package org.cocos2dx.plugin;

import java.util.Hashtable;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Handler;
import android.util.Log;

public class AnalyticsWrapper {
	
	protected static boolean sIsDebugged = false;
	protected static IAnalytics sAnalytics = null;
	protected static Context sContext = null;
	protected static GLSurfaceView sGLSurfaceView = null; 
	protected static Handler sMainThreadHander = null;
	
	protected static String TAG = "AnalyticsWrapper";
	public static void LogD(String tag, String msg){ 
		if (sIsDebugged) Log.d(tag, msg);
	}
	
	protected static void LogE(String msg, Exception e) {
		Log.e(TAG, msg, e);
	}
	
	public static void init(Context context)
	{
		sContext = context;
		//mGLSurfaceView = view;
		if (null == sMainThreadHander) {
			sMainThreadHander = new Handler();
		}
	}
	
	public static Context getContext() {
		return sContext;
	}

	public static void setAnalytics(IAnalytics analytics)
	{
		sAnalytics = analytics;
	}
	
	public static boolean isValid() {
		
		boolean ret = sAnalytics != null;
		if (!ret) {
			LogD("AnalyticsWrapper", "invalid parameter");
		}
		return ret;
	}
	
	public static void startSession(String appKey)
	{
		if (!isValid()) return;
		try{
			sAnalytics.startSession(appKey);
		} catch(Exception e){
			LogE("Exception in startSession", e);
		}
	}
	
	public static void stopSession()
	{
		if (!isValid()) return;
		try{
			sAnalytics.stopSession();
		} catch(Exception e){
			LogE("Exception in stopSession", e);
		}
	}
	
	public static void setSessionContinueMillis(int millis)
	{
		if (!isValid()) return;
		try{
			sAnalytics.setSessionContinueMillis(millis);
		} catch(Exception e){
			LogE("Exception in setSessionContinueMillis", e);
		}
	}
	
	public static void setCaptureUncaughtException(boolean isEnabled)
	{
		if (!isValid()) return;
		try{
			sAnalytics.setCaptureUncaughtException(isEnabled);
		} catch(Exception e){
			LogE("Exception in setCaptureUncaughtException", e);
		}
	}
	
	public static void setDebugMode(boolean isDebugMode)
	{
		if (!isValid()) return;
		try{
			sAnalytics.setDebugMode(isDebugMode);
		} catch(Exception e){
			LogE("Exception in setDebugMode", e);
		}
	}
	
	public static void logError(String errorId, String message, Hashtable<String, String> paramMap)
	{
		if (!isValid()) return;
		try{
			sAnalytics.logError(errorId, message, paramMap);
		} catch(Exception e){
			LogE("Exception in logError", e);
		}
	}
	
	public static void logEvent(String eventId)
	{
		if (!isValid()) return;
		try{
			sAnalytics.logEvent(eventId);
		} catch(Exception e){
			LogE("Exception in logEvent", e);
		}
	}
	
	public static void logEvent(String eventId, Hashtable<String, String> paramMap)
	{
		if (!isValid()) return;
		try{
			sAnalytics.logEvent(eventId, paramMap);
		} catch(Exception e){
			LogE("Exception in logEvent", e);
		}
	}
	
	public static void logTimedEventBegin(String eventId)
	{
		if (!isValid()) return;
		try{
			sAnalytics.logTimedEventBegin(eventId);
		} catch(Exception e){
			LogE("Exception in logTimedEventBegin", e);
		}
	}
	
	public static void logTimedEventEnd(String eventId)
	{
		if (!isValid()) return;
		try{
			sAnalytics.logTimedEventEnd(eventId);
		} catch(Exception e){
			LogE("Exception in logTimedEventEnd", e);
		}
	}
	
	
	public static void runOnGLThread(Runnable r) {
		if (null == sGLSurfaceView) LogD("runOnGLThread", "getCocos2dxGLSurfaceView null!!!");
		sGLSurfaceView.queueEvent(r);
	}

	public static void runOnMainThread(Runnable r) {
		if (null == sMainThreadHander) LogD("runOnMainThread", "getUIHandler null !!!");
		sMainThreadHander.post(r);
	}
}
