package com.armite.webkit.plug;

import java.util.Hashtable;
import java.util.Iterator;
import java.util.UUID;

import android.content.Context;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

/**
 * 播放器统一控制管理,提供静态方法
 * @author x220
 *
 */
public class MyPlayerCenter {
	public static String TAG="MyPlayerCenter";
	public static IBrowserInterface mBrowserInterface = null;
	public static Context mContext = null;
		
	public static MyMediaPlayer mNativePlayer =  new MyMediaPlayer();
	public static int mNativeInstanceID =1;
	
	public static SurfaceHolder mSurfaceHolder = null;
	
	//InstanceID为逻辑的，由统一管理
	public static Hashtable<String, Integer> mInstanceMap = new Hashtable();
	public MyPlayerCenter() {
		/*
		 * mNativePlayer.setOnCompletionListener(this);
		 * mNativePlayer.setOnInfoListener(this); mNativePlayer.setOnErrorListener(this);
		 * mNativePlayer.setOnPreparedListener(this);
		 * mNativePlayer.setOnSeekCompleteListener(this);
		 * mNativePlayer.setOnBufferingUpdateListener(this);
		 */		
	}

	public static void init(Context context,IBrowserInterface bsinterface) {
		// 设置主浏览器，发送事件是通过这个
		mBrowserInterface = bsinterface;
		mContext = context;
		mNativePlayer.setContext(context);
		mNativePlayer.setBrowserInterface(bsinterface);		
	}

	public static Context getContext(){
		return mContext;
	}
	public static IBrowserInterface getBrowser(){
		return mBrowserInterface;
	}
	public static int getNativePlayerInstanceID() {
		return mNativeInstanceID;// 现在只有一个播放器，固定
	}

	public static void setSurfaceHolder(SurfaceHolder sh) {
		mNativePlayer.setSurfaceHolder(sh);
	}
	public static String getNextInstanceID(){			
		//循环如果超过，那么需要循环回去，或者就产生GUID
		UUID uuid  =  UUID.randomUUID(); 
		String s = UUID.randomUUID().toString();//
		return s;
	}

	
	// 播放器控制
	public static int GetLastError(String instID) {
		
		return mNativePlayer.GetLastError();
	}

	public static boolean IsLive(String instID) {
		return mNativePlayer.IsLive();
	}

	public static boolean IsPause(String instID) {
		return mNativePlayer.IsPause();
	}

	public static void addBatchMedia(String instID, String jsonString) {
		mNativePlayer.addBatchMedia(jsonString);
	}

	public static void addSingleMedia(String instID, int index,
			String jsonString) {
		mNativePlayer.addSingleMedia(index, jsonString);
	}

	public static int bindNativePlayerInstance(String instID,int nativeInstanceID) {
		//将逻辑的绑定到物理的
		mInstanceMap.put(instID, nativeInstanceID);
		return 0;
		//return mNativePlayer.bindNativePlayerInstance(nativeInstanceID);
	}

	public static void clearAllMedia(String instID) {
		mNativePlayer.clearAllMedia();
	}

	public static void fastForward(String instID, int speed) {
		mNativePlayer.fastForward(speed);
	}

	public static void fastRewind(String instID, int speed) {
		mNativePlayer.fastRewind(speed);
	}

	public static int getAllowTrickmodeFlag(String instID) {
		return mNativePlayer.getAllowTrickmodeFlag();

	}

	public static int getAudioPID(String instID) {
		return mNativePlayer.getAudioPID();
	}

	public static String getAudioPIDs(String instID) {
		return mNativePlayer.getAudioPIDs();
	}

	public static String getAudioTrack(String instID) {
		return mNativePlayer.getAudioTrack();
	}

	public static int getAudioTrackUIFlag(String instID) {
		return mNativePlayer.getAudioTrackUIFlag();
	}

	public static int getAudioVolumeUIFlag(String instID) {
		return mNativePlayer.getAudioVolumeUIFlag();
	}

	public static int getChannelNoUIFlag(String instID) {
		return mNativePlayer.getChannelNoUIFlag();
	}

	public static int getChannelNum(String instID) {
		return mNativePlayer.getChannelNum();
	}

	public static String getCurrentAudioChannel(String instID) {
		return mNativePlayer.getCurrentAudioChannel();
	}

	public static int getCurrentIndex(String instID) {
		return mNativePlayer.getCurrentIndex();
	}

	public static String getCurrentPlayTime(String instID) {
		return mNativePlayer.getCurrentPlayTime();
	}

	public static String getEntryID(String instID) {
		return mNativePlayer.getEntryID();
	}

	public static String getMediaCode(String instID) {
		return mNativePlayer.getMediaCode();
	}

	public static int getMediaCount(String instID) {
		return mNativePlayer.getMediaCount();
	}

	public static int getMediaDuration(String instID) {
		return mNativePlayer.getMediaDuration();
	}

	public static int getMuteFlag(String instID) {
		return mNativePlayer.getMuteFlag();
	}

	public static int getMuteUIFlag(String instID) {
		return mNativePlayer.getMuteFlag();
	}

	public static int getNativeUIFlag(String instID) {
		return mNativePlayer.getNativeUIFlag();
	}

	public static String getPlaybackMode(String instID) {
		return mNativePlayer.getPlaybackMode();
	}

	public static String getPlaylist(String instID) {
		return mNativePlayer.getPlaylist();
	}

	public static int getProgressBarUIFlag(String instID) {
		return mNativePlayer.getProgressBarUIFlag();
	}

	public static int getSingleOrPlaylistMode(String instID) {
		return mNativePlayer.getSingleOrPlaylistMode();
	}

	public static int getSubtitileFlag(String instID) {
		return mNativePlayer.getSubtitileFlag();
	}

	public static String getSubtitle(String instID) {
		return mNativePlayer.getSubtitle();
	}

	public static int getSubtitlePID(String instID) {
		return mNativePlayer.getSubtitlePID();
	}

	public static String getSubtitlePIDs(String instID) {
		return mNativePlayer.getSubtitlePIDs();
	}

	public static String getVendorSpecificAttr(String instID) {
		return mNativePlayer.getVendorSpecificAttr();
	}

	public static int getVideoAlpha(String instID) {
		return mNativePlayer.getVideoAlpha();
	}

	public static int getVideoDisplayHeight(String instID) {
		return mNativePlayer.getVideoDisplayHeight();
	}

	public static int getVideoDisplayLeft(String instID) {
		return mNativePlayer.getVideoDisplayLeft();
	}

	public static int getVideoDisplayMode(String instID) {
		return mNativePlayer.getVideoDisplayMode();
	}

	public static int getVideoDisplayTop(String instID) {
		return mNativePlayer.getVideoDisplayTop();
	}

	public static int getVideoDisplayWidth(String instID) {
		return mNativePlayer.getVideoDisplayWidth();
	}

	public static int getVolume(String instID) {
		return mNativePlayer.getVolume();
	}

	public static void gotoEnd(String instID) {
		mNativePlayer.gotoEnd();
	}

	public static void gotoStart(String instID) {
		mNativePlayer.gotoStart();
	}

	public static void initMediaPlayer(String instID,
			int nativePlayerinstanceID,
			int playlistFlag,
			int videoDisplayMode, int height, int width, int left, int top,
			int muteFlag, int useNativeUIFlag, int subtitleFlag,
			int videoAlpha, int cycleFlag, int randomFlag, int autoDelFlag) {
		//mBrowserInterface.showVideoView();
		mNativePlayer.initMediaPlayer(nativePlayerinstanceID, playlistFlag,
				videoDisplayMode, height, width, left, top, muteFlag,
				useNativeUIFlag, subtitleFlag, videoAlpha, cycleFlag,
				randomFlag, autoDelFlag);
	}

	public static int joinChannel(String instID, int userChannelID) {
		return mNativePlayer.joinChannel(userChannelID);
	}

	public static void leaveChannel(String instID) {
		mNativePlayer.leaveChannel();
	}

	public static int getArrayIndexByEntryID(String instID,
			String entryID) {
		return mNativePlayer.getArrayIndexByEntryID(entryID);
	}

	public static void moveMediaByIndex(String instID, String entryID,
			int toIndex) {
		mNativePlayer.moveMediaByIndex(entryID, toIndex);
	}

	public static void moveMediaByIndex1(String instID, int fromIndex,
			int toIndex) {
		mNativePlayer.moveMediaByIndex1(fromIndex, toIndex);
	}

	public static void moveMediaByOffset(String instID, String entryID,
			int offset) {
		mNativePlayer.moveMediaByOffset(entryID, offset);
	}

	public static void moveMediaToFirst(String instID, String entryID) {
		mNativePlayer.moveMediaToFirst(entryID);
	}

	public static void moveMediaByOffset1(String instID, int fromIndex,
			int offset) {
		mNativePlayer.moveMediaByOffset1(fromIndex, offset);
	}

	public static void moveMediaToFirst1(String instID, int fromIndex) {
		mNativePlayer.moveMediaToFirst1(fromIndex);
	}

	public static void moveMediaToLast(String instID, String entryID) {
		mNativePlayer.moveMediaToLast(entryID);
	}

	public static void moveMediaToLast1(String instID, int fromIndex) {
		mNativePlayer.moveMediaToLast1(fromIndex);
	}

	public static void moveMediaToNext(String instID, String entryID) {
		mNativePlayer.moveMediaToNext(entryID);
	}

	public static void moveMediaToNext1(String instID, int fromIndex) {
		mNativePlayer.moveMediaToNext1(fromIndex);
	}

	public static void moveMediaToPrevious(String instID, String entryID) {
		mNativePlayer.moveMediaToPrevious(entryID);
	}

	public static void moveMediaToPrevious1(String instID, int fromIndex) {
		mNativePlayer.moveMediaToPrevious1(fromIndex);
	}

	public static void pause(String instID) {
		mNativePlayer.pause();
	}

	public static String getCurrentPlayUrl(String instID) {
		return mNativePlayer.getCurrentPlayUrl();
	}

	public static void playByUrl(String instID, String uri, int time,
			int x, int y, int w, int h) {
		mNativePlayer.playByUrl(uri, time, x, y, w, h);
	}

	public static void play(String instID) {
		mNativePlayer.play();
	}

	public static void playByTime(String instID, int type,
			String timestamp, int speed) {
		mNativePlayer.playByTime(type, timestamp, speed);
	}

	public static void playFromStart(String instID) {
		mNativePlayer.playFromStart();

	}

	public static void refreshVideoDisplay(String instID) {
		mNativePlayer.refreshVideoDisplay();
	}

	//instID为逻辑的
	public static int releaseMediaPlayer(String instID,int nativeInstanceID) {
		Log.e(TAG, "releaseMediaPlayer:"+nativeInstanceID);
		//将映射停掉
		if(instID!=null)mInstanceMap.remove(instID);		
		//return mNativePlayer.releaseMediaPlayer(nativeInstanceID);
		//如果当前物理的没有任何逻辑的关联，那么就应该彻底停止播放
		if(!mInstanceMap.containsValue(nativeInstanceID)){
			mNativePlayer.releaseMediaPlayer(nativeInstanceID);
		}		
		return 0;
	}

	public static void removeMediaByEntryID(String instID, String entryID) {
		mNativePlayer.removeMediaByEntryID(entryID);
	}

	public static void removeMediaByIndex(String instID, int index) {
		mNativePlayer.removeMediaByIndex(index);
	}

	public static void resume(String instID) {
		mNativePlayer.resume();
	}

	public static void selectFirst(String instID) {
		mNativePlayer.selectFirst();
	}

	public static void selectLast(String instID) {
		mNativePlayer.selectLast();
	}

	public static void selectMediaByIndex(String instID, int index) {
		mNativePlayer.selectMediaByIndex(index);
	}

	public static void selectMediaByOffset(String instID, int offset) {
		mNativePlayer.selectMediaByOffset(offset);
	}

	public static void selectNext(String instID) {
		mNativePlayer.selectNext();
	}

	public static void selectPrevious(String instID) {
		mNativePlayer.selectPrevious();
	}

	public static void sendVendorSpecificCommand(String instID,
			String paramString) {
		mNativePlayer.sendVendorSpecificCommand(paramString);
	}

	public static void set(String instID, String name, String value) {
		mNativePlayer.set(name, value);
	}

	public static void setAllowTrickmodeFlag(String instID,
			int bAllowTrickmodeFlag) {
		mNativePlayer.setAllowTrickmodeFlag(bAllowTrickmodeFlag);

	}

	public static void setAudioPID(String instID, int pid) {
		mNativePlayer.setAudioPID(pid);
	}

	public static void setAudioTrackUIFlag(String instID, int flag) {
		mNativePlayer.setAudioTrackUIFlag(flag);
	}

	public static void setAudioVolumeUIFlag(String instID, int flag) {
		mNativePlayer.setAudioVolumeUIFlag(flag);
	}

	public static void setChannelNoUIFlag(String instID, int flag) {
		mNativePlayer.setChannelNoUIFlag(flag);
	}

	public static void setCycleFlag(String instID, int flag) {
		mNativePlayer.setCycleFlag(flag);
	}

	public static void setMuteFlag(String instID, int flag) {
		mNativePlayer.setMuteFlag(flag);
	}

	public static void setMuteUIFlag(String instID, int flag) {
		mNativePlayer.setMuteUIFlag(flag);
	}

	public static void setNativeUIFlag(String instID, int flag) {
		mNativePlayer.setNativeUIFlag(flag);
	}

	public static void setProgressBarUIFlag(String instID, int flag) {
		mNativePlayer.setProgressBarUIFlag(flag);
	}

	public static void setRandomFlag(String instID, int flag) {
		mNativePlayer.setRandomFlag(flag);
	}

	public static void setSingleMedia(String instID, String jsonStr) {
		mNativePlayer.setSingleMedia(jsonStr);
	}

	public static void setSingleOrPlaylistMode(String instID, int mode) {
		mNativePlayer.setSingleOrPlaylistMode(mode);
	}

	public static void setSubtitileFlag(String instID, int flag) {
		mNativePlayer.setSubtitileFlag(flag);
	}

	public static void setSubtitlePID(String instID, int pid) {
		mNativePlayer.setSubtitlePID(pid);
	}

	public static void setVendorSpecificAttr(String instID,
			String paramString) {
		mNativePlayer.setVendorSpecificAttr(paramString);
	}

	public static void setVideoAlpha(String instID, int alpha) {
		mNativePlayer.setVideoAlpha(alpha);
	}

	public static void setVideoDisplayArea(String instID, int left,
			int top, int width, int height) {

		mNativePlayer.setVideoDisplayArea(left, top, width, height);
	}

	public static void setVideoDisplayMode(String instID, int mode) {
		mNativePlayer.setVideoDisplayMode(mode);
	}

	public static void setVolume(String instID, int vol) {
		mNativePlayer.setVolume(vol);
	}

	public static void stop(String instID) {		
		mNativePlayer.stop();
		//调用最上层隐藏surface
		mBrowserInterface.hideVideoView();
	}

	public static void switchAudioChannel(String instID) {
		mNativePlayer.switchAudioChannel();
	}

	public static void switchAudioTrack(String instID) {
		mNativePlayer.switchAudioTrack();
	}

	public static void switchSubtitle(String instID) {
		mNativePlayer.switchSubtitle();
	}

	// 扩展函数,可选
	// 设置快收模式
	public static int setXBurstMode(String instID, boolean xburst) { // 设置是否快收模式，针对rtsp
		return mNativePlayer.setXBurstMode(xburst);
	}

	// 设置重发模式
	public static int setARQ(String instID, boolean arq) { // 设置是否ARQ
		return mNativePlayer.setARQ(arq);
	}

	// 获取单项统计
	public static String getStaticsItem(String instID, String item) {
		return mNativePlayer.getStaticsItem(item);
	}
	// 获取播放统计信息
	public static String getStatics(String instID) {
		return mNativePlayer.getStatics();
	}

}
