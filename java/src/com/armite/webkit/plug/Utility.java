package com.armite.webkit.plug;

import android.util.Log;

public class Utility {

	public static String TAG="Utility";
	public static String mEvent="";
	public static void setEvent(String evt){
		  mEvent = evt;
	}
	 
	 
	 public  String getEvent(){
		 //Log.e(TAG,"Event:"+mEvent);
		 return mEvent;
	  }
	 
	  public  void setBrowserWindowAlpha(int paramByte){
	    float f = paramByte / 100.0F;
	    //   Iptv2EPG.web.loadUrl("javascript:document.body.style.opacity  = \"" + f + "\";");
	  }
	  public  void startLocalCfg(){
		  
	  }

	  
}
