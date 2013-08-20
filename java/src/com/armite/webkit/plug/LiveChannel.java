package com.armite.webkit.plug;

public class LiveChannel {
	public int BeginTime;
	  public String Channel;
	  public String ChannelID;
	  public String ChannelLogURL;
	  public String ChannelName;
	  public String ChannelPurchased;
	  public String ChannelSDP;
	  public int ChannelType;
	  public String ChannelURL;
	  public int Interval;
	  public int Lasting;
	  public int PositionX;
	  public int PositionY;
	  public int TimeShift;
	  public int TimeShiftLength;
	  public String TimeShiftURL;
	  public int UserChannelID;

	  public LiveChannel(String paramString)
	  {
	    this.Channel = paramString;
	    this.ChannelID = GetItem("ChannelID");
	    this.ChannelName = GetItem("ChannelName");
	    this.UserChannelID = GetItemInt("UserChannelID");
	    this.ChannelURL = GetItem("ChannelURL");
	    this.TimeShift = GetItemInt("TimeShift");
	    this.ChannelSDP = GetItem("ChannelSDP");
	    this.TimeShiftURL = GetItem("TimeShiftURL");
	    this.ChannelLogURL = GetItem("ChannelLogURL");
	    this.PositionX = GetItemInt("PositionX");
	    this.PositionY = GetItemInt("PositionY");
	    this.BeginTime = GetItemInt("BeginTime");
	    this.Interval = GetItemInt("Interval");
	    this.Lasting = GetItemInt("Lasting");
	    this.ChannelType = GetItemInt("ChannelType");
	    this.ChannelPurchased = GetItem("ChannelPurchased");
	    this.TimeShiftLength = GetItemInt("TimeShiftLength");
	  }

	  public String GetItem(String paramString)
	  {
		  String str="";
	    int i = this.Channel.indexOf(paramString);
	    int j = this.Channel.indexOf("\"", i);
	    int k = this.Channel.indexOf("\"", j + 1);
	    if ((k > j) && (j > i))
	    {
	      str = this.Channel.substring(j + 1, k);
	      if (str.indexOf("null") != 0);
	    }	 
	      return str;
	  }

	  public int GetItemInt(String paramString)
	  {
	    int i = 0;
	    String str = GetItem(paramString);
	    if (str.compareTo("") == 0);
	      try
	      {
	        i = Integer.parseInt(str);
	      }
	      catch (Exception localException)
	      {
	      }
	      return i;	   
	  }
}
