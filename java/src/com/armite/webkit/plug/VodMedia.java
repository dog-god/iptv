package com.armite.webkit.plug;

import org.json.JSONException;
import org.json.JSONObject;

public class VodMedia {
	public int allowTrickmode;
	  public int audioType;
	  public int copyProtection;
	  public int drmType;
	  public int endTime;
	  public String entryID;
	  public int fingerPrint;
	  public String mediaCode;
	  public int mediaType;
	  public String mediaUrl;
	  public int startTime;
	  public int streamType;
	  public int videoType;

	  public VodMedia(String paramString)
	  {
	   // i.b("strJSON:" + paramString);
	   // if (TextUtils.isEmpty(paramString));
	     String str = paramString.trim();
	      if ((str.startsWith("[")) && (str.endsWith("]")))
	        str = str.substring(1, -1 + str.length());
	      //i.b("strJSON-dowith:" + str);
	      try
	      {
	        JSONObject localJSONObject = new JSONObject(str);
	        this.mediaUrl = localJSONObject.getString("mediaUrl");
	        this.mediaCode = localJSONObject.getString("mediaCode");
	        this.mediaType = localJSONObject.getInt("mediaType");
	        this.audioType = localJSONObject.getInt("audioType");
	        this.videoType = localJSONObject.getInt("videoType");
	        this.streamType = localJSONObject.getInt("streamType");
	        this.drmType = localJSONObject.getInt("drmType");
	        this.fingerPrint = localJSONObject.getInt("fingerPrint");
	        this.copyProtection = localJSONObject.getInt("copyProtection");
	        this.allowTrickmode = localJSONObject.getInt("allowTrickmode");
	        this.startTime = localJSONObject.getInt("startTime");
	        this.endTime = localJSONObject.getInt("endTime");
	        this.entryID = localJSONObject.getString("entryID");
	      }
	      catch (JSONException localJSONException)
	      {
	        localJSONException.printStackTrace();
	      }
	    }
}
