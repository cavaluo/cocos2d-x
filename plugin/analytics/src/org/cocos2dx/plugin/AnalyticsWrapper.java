package org.cocos2dx.plugin;

import java.util.Hashtable;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Handler;
import android.util.Log;

public class AnalyticsWrapper {
	
	protected static boolean sIsDebug = false;
	protected static IAnalytics sAnalytics = null;
	protected static Context sContext = null;
	protected static GLSurfaceView mGLSurfaceView = null; 
	protected static Handler sMainThreadHander = null;
	
	public static void LogD(String tag, String msg) { if (sIsDebug) Log.d(tag, msg); }
	
	public static void init(IAnalytics analyticsInstance, Context context, GLSurfaceView view)
	{
		sAnalytics = analyticsInstance;
		sContext = context;
		mGLSurfaceView = view;
		if (null == sMainThreadHander) {
			sMainThreadHander = new Handler();
		}
	}
	
	public static boolean isValid() {
		
		boolean ret = sAnalytics != null;
		if (!ret) {
			LogD("AnalyticsWrapper", "invalid parameter");
		}
		return ret;
	}
	
	public static void beginSession(String appKey)
	{
		if (!isValid()) return;
		sAnalytics.beginSession(appKey);
	}
	
	public static void endSession()
	{
		if (!isValid()) return;
		sAnalytics.endSession();
	}
	
	public static void setSessionContinueMillis(long millis)
	{
		if (!isValid()) return;
		sAnalytics.setSessionContinueMillis(millis);
	}
	
	public static void setCaptureUncaughtException(boolean isEnabled)
	{
		if (!isValid()) return;
		sAnalytics.setCaptureUncaughtException(isEnabled);
	}
	
	public static void setDebugMode(boolean isDebugMode)
	{
		if (!isValid()) return;
		sAnalytics.setDebugMode(isDebugMode);
	}
	
	public static void logError(String errorId, String message, Hashtable<String, String> paramMap)
	{
		if (!isValid()) return;
		sAnalytics.logError(errorId, message, paramMap);
	}
	
	public static void logEvent(String eventId)
	{
		if (!isValid()) return;
		sAnalytics.logEvent(eventId);
	}
	
	public static void logEvent(String eventId, Hashtable<String, String> paramMap)
	{
		if (!isValid()) return;
		sAnalytics.logEvent(eventId, paramMap);
	}
	
	public static void logTimedEventBegin(String eventId)
	{
		if (!isValid()) return;
		sAnalytics.logTimedEventBegin(eventId);
	}
	
	public static void logTimedEventBegin(String eventId, Hashtable<String, String> paramMap)
	{
		if (!isValid()) return;
		sAnalytics.logTimedEventBegin(eventId, paramMap);
	}
	
	public static void logTimedEventEnd(String eventId)
	{
		if (!isValid()) return;
		sAnalytics.logTimedEventEnd(eventId);
	}
	
	
	public static void runOnGLThread(Runnable r) {
		if (null == mGLSurfaceView) LogD("runOnGLThread", "getCocos2dxGLSurfaceView null!!!");
		mGLSurfaceView.queueEvent(r);
	}

	public static void runOnMainThread(Runnable r) {
		if (null == sMainThreadHander) LogD("runOnMainThread", "getUIHandler null !!!");
		sMainThreadHander.post(r);
	}
}
