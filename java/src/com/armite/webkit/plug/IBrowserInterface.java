package com.armite.webkit.plug;

public interface IBrowserInterface {
	public void sendKeyEvent(int keycode);
	/*EVENT_GO_CHANNEL	当按下CH+, CH-和数字键，机顶盒将打开下一个频道时触发
EVENT_MEDIA_END	当媒体播放器中的媒体播放到末端时触发
EVENT_MEDIA_BEGINING	当媒体播放器中的媒体播放到起始端时触发
EVENT_MEDIA_ERROR	当媒体播放器，发生异常时触发
EVENT_PLAYMODE_CHANGE	当媒体播放器的playback mode发生改变的时候触发
EVENT_REMINDER	当机顶盒定时提醒时触发，
EVENT_JVM_CLIENT	当增值业务客户端产生下载、启动、退出、出错等状态发生时触发
*/
	public void notifyChannelEvent(String type,int instance_id,String channel_code,int userChannelID);
	public void notifyMediaEvent(String type,int instance_id,String mediaCode,String entryID);
	public void notifyMediaError(String type,int instance_id,int errorcode,String errordesc,String mediaCode);	
	public void notifyMediaPlayModeChange(String type,int instance_id,int new_play_mode,int new_play_rate,int old_play_mode,int old_play_rate);

	public void notifyJVMEvent(String type,int event_code,int event_result,String event_message);

	
	public void hideWebView();
	public void showWebView();
	public void hideVideoView();
	public void showVideoView();
	public void setVideoArea(int left,int top,int width,int height);
	public void setVideoMode(int mode);//设置是全屏还是窗口
	public void setVideoAlpha(int alpha);//设置透明度
	public void quit();//退出应用程序
	public void startConfig();//进入设置界面
}
