package org.cocos2dx.plugin;


import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Handler;


public class AnalyticsWrapper {
	
	public static native void nativeInitAnalytics(IAnalytics instance, String className);
	
	protected static Context sContext = null;
	protected static GLSurfaceView sGLSurfaceView = null; 
	protected static Handler sMainThreadHander = null;
	
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
	
	public static void runOnGLThread(Runnable r) {
		if (null == sGLSurfaceView) return;
		sGLSurfaceView.queueEvent(r);
	}

	public static void runOnMainThread(Runnable r) {
		if (null == sMainThreadHander) return;
		sMainThreadHander.post(r);
	}
}
