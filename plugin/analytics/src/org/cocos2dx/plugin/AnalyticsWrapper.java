package org.cocos2dx.plugin;


import java.lang.reflect.InvocationTargetException;
import java.util.List;

import android.app.Activity;
import android.app.ActivityManager;
import android.app.Application;
import android.content.Context;
import android.opengl.GLSurfaceView;
import android.os.Handler;
import android.util.Log;


public class AnalyticsWrapper {
	
	public static native void nativeInitAnalytics(Object instance, String className);
	
	protected static Context sContext = null;
	protected static GLSurfaceView sGLSurfaceView = null; 
	protected static Handler sMainThreadHander = null;
	private static final String TAG = "AnalyticsWrapper";
	
	public static void init(Context context)
	{
		sContext = context;
		//mGLSurfaceView = view;
		if (null == sMainThreadHander) {
			sMainThreadHander = new Handler();
		}
	}
	
	protected static boolean java_initAnalytics(String className)
	{
		// TODO Auto-generated method stub
		String classFullName = "org.cocos2dx.plugin."+className;
		Log.i(TAG, "class name : "+classFullName);
        Class<?> c = null;
        try {  
            c = Class.forName(classFullName);
        } catch (ClassNotFoundException e) {  
            Log.e(TAG, "Class not found.");
            return false;
        }  
          
        try {
        	Context ctx = getContext();
			if (ctx != null) {
	        	Object o = c.getDeclaredConstructor(Context.class).newInstance(ctx);
				AnalyticsWrapper.nativeInitAnalytics(o, classFullName.replace('.', '/'));
				return true;
			} else {
				Log.e(TAG, "AnalyticsWrapper wasn't initialized.");
			}
        } catch (InstantiationException e) {   
        	Log.e(TAG, "Class not accessible.");   
        } catch (IllegalAccessException e) {  
        	Log.e(TAG, "Class not instantiable.");  
        } catch (IllegalArgumentException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (SecurityException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (InvocationTargetException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (NoSuchMethodException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        return false;
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
