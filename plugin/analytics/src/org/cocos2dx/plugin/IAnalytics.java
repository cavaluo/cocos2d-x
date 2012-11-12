package org.cocos2dx.plugin;

import java.util.Hashtable;

public interface IAnalytics {

	public void beginSession(String appKey);
	public void endSession();
	public void setSessionContinueMillis(int millis);
	public void setCaptureUncaughtException(boolean isEnabled);
	public void setDebugMode(boolean isDebugMode);
	public void logError(String errorId, String message, Hashtable<String, String> paramMap);
	public void logEvent(String eventId);
	public void logEvent(String eventId, Hashtable<String, String> paramMap);
	public void logTimedEventBegin(String eventId);
	public void logTimedEventEnd(String eventId);
}
