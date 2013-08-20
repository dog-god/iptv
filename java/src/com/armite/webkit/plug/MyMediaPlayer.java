package com.armite.webkit.plug;

import java.util.ArrayList;

import org.json.JSONArray;
import org.json.JSONObject;

import android.content.Context;
import android.content.Intent;
import android.media.AudioManager;
import android.media.MediaPlayer;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Message;
import android.util.Log;
import android.view.SurfaceHolder;

/***
 * 实现物理的播放器实现
 * @author x220
 *
 */
public class MyMediaPlayer implements Handler.Callback,
		MediaPlayer.OnCompletionListener, MediaPlayer.OnErrorListener,
		MediaPlayer.OnInfoListener, MediaPlayer.OnPreparedListener,
		MediaPlayer.OnSeekCompleteListener,
		MediaPlayer.OnBufferingUpdateListener {
	public static final String TAG = "MyMediaPlayer";
	private SurfaceHolder mSurfaceHolder=null;
	public static final int MSG_PLAYER_JOINCHANNEL = 1;
	public static final int MSG_PLAYER_SETMEDIA = 2;
	public static final int MSG_PLAYER_DISPLAY = 3;
	public static final int MSG_PLAYER_STARTPLAY = 4;
	public static final int MSG_PLAYER_PAUSE = 5;
	public static final int MSG_PLAYER_PLAY = 6;
	public static final int MSG_PLAYER_STOP = 7;
	public static final int MSG_PLAYER_FASTFORWARD = 8;
	public static final int MSG_PLAYER_FASTREWIND = 9;
	public static final int MSG_PLAYER_SETALPHA = 10;
	public static final int MSG_PLAYER_EVNET = 11;
	public static final int MSG_PLAYER_LEAVECHANNEL = 12;
	public static final int MSG_PLAYER_SEEK = 13;
	public static final int MSG_PLAYER_GOTOEND = 14;
	public static final int MSG_PLAYER_GOTOSTART = 15;
	public static final int MSG_PLAYER_RESUME = 16;
	public static final int MSG_PLAYER_REFRESHVIDEO = 17;
	public static final int MSG_PLAYER_RELEASE = 18;

	private int mSpeed = 1;
	private String mStartTime="0";
	private int mStatus = STATUS_IDLE;
	/*这张状态转换图清晰的描述了MediaPlayer的各个状态，也列举了主要的方法的调用时序，每种方法只能在一些特定的状态下使用，如果使用时MediaPlayer的状态不正确则会引发IllegalStateException异常。
Idle 状态：当使用new()方法创建一个MediaPlayer对象或者调用了其reset()方法时，该MediaPlayer对象处于idle状态。这两种方法的一个重要差别就是：如果在这个状态下调用了getDuration()等方法（相当于调用时机不正确），通过reset()方法进入idle状态的话会触发OnErrorListener.onError()，并且MediaPlayer会进入Error状态；如果是新创建的MediaPlayer对象，则并不会触发onError(),也不会进入Error状态。
End 状态：通过release()方法可以进入End状态，只要MediaPlayer对象不再被使用，就应当尽快将其通过release()方法释放掉，以释放相关的软硬件组件资源，这其中有些资源是只有一份的（相当于临界资源）。如果MediaPlayer对象进入了End状态，则不会在进入任何其他状态了。
Initialized 状态：这个状态比较简单，MediaPlayer调用setDataSource()方法就进入Initialized状态，表示此时要播放的文件已经设置好了。
Prepared 状态：初始化完成之后还需要通过调用prepare()或prepareAsync()方法，这两个方法一个是同步的一个是异步的，只有进入Prepared状态，才表明MediaPlayer到目前为止都没有错误，可以进行文件播放。
Preparing 状态：这个状态比较好理解，主要是和prepareAsync()配合，如果异步准备完成，会触发OnPreparedListener.onPrepared()，进而进入Prepared状态。
Started 状态：显然，MediaPlayer一旦准备好，就可以调用start()方法，这样MediaPlayer就处于Started状态，这表明MediaPlayer正在播放文件过程中。可以使用isPlaying()测试MediaPlayer是否处于了Started状态。如果播放完毕，而又设置了循环播放，则MediaPlayer仍然会处于Started状态，类似的，如果在该状态下MediaPlayer调用了f()或者start()方法均可以让MediaPlayer停留在Started状态。
Paused 状态：Started状态下MediaPlayer调用pause()方法可以暂停MediaPlayer，从而进入Paused状态，MediaPlayer暂停后再次调用start()则可以继续MediaPlayer的播放，转到Started状态，暂停状态时可以调用seekTo()方法，这是不会改变状态的。
Stop 状态：Started或者Paused状态下均可调用stop()停止MediaPlayer，而处于Stop状态的MediaPlayer要想重新播放，需要通过prepareAsync()和prepare()回到先前的Prepared状态重新开始才可以。
PlaybackCompleted状态：文件正常播放完毕，而又没有设置循环播放的话就进入该状态，并会触发OnCompletionListener的onCompletion()方法。此时可以调用start()方法重新从头播放文件，也可以stop()停止MediaPlayer，或者也可以seekTo()来重新定位播放位置。
Error状态：如果由于某种原因MediaPlayer出现了错误，会触发OnErrorListener.onError()事件，此时MediaPlayer即进入Error状态，及时捕捉并妥善处理这些错误是很重要的，可以帮助我们及时释放相关的软硬件资源，也可以改善用户体验。通过setOnErrorListener(android.media.MediaPlayer.OnErrorListener)可以设置该监听器。如果MediaPlayer进入了Error状态，可以通过调用reset()来恢复，使得MediaPlayer重新返回到Idle状态。
*/
	private static final int STATUS_IDLE = 0;
	private static final int STATUS_END = 1;
	private static final int STATUS_PREPARED = 2;
	private static final int STATUS_PREPARING = 3;
	private static final int STATUS_STARTED = 4;
	private static final int STATUS_STOP = 5;
	private static final int STATUS_PAUSED = 6;
	private static final int STATUS_PLAYBACKCOMPLETED = 7;
	private static final int STATUS_ERROR = 8;
	
	private static final int STATUS_RELEASED = 10;

	public Context mContext=null;
	public IBrowserInterface mBrowserInterface=null;
	private int mLastError = 0;

	private ArrayList mPlayList = new ArrayList();

	public boolean mLive = true;
	
	public int mAllowTrickmodeFlag = 0;
	public int mAudioTrackUIFlag = 0;
	public int mAudioVolumeUIFlag = 0;
	public int mChannelNoUIFlag = 0;
	public int mCurrentIndex = 0;
	public int mCurrentUserChannelID = -1;
	public int mMuteFlag = 0;
	public int mMuteUIFlag = 0;
	public int mNativePlayerInstanceID = 1;
	public int mNativeUIFlag = 0;
	public int mProgressBarUIFlag = 0;
	public int mSingleOrPlaylistMode = 0;
	public int mSubtitileFlag = 0;
	public String mVendorSpecific = "";
	public int mCycleFlag = 0;
	public int mRandomFlag = 0;
	public int mAutoDelFlag = 0;
	public int mVideoAlpha = 0;
	public int mVideoDisplayLeft = 0;
	public int mVideoDisplayTop = 0;
	public int mVideoDisplayWidth = 1920;
	public int mVideoDisplayHeight = 1080;
	public int mVideoDisplayMode = 0;
	public int mVolume = 50;
	
	public int mLeft=0;
	public int mTop =0;
	public int mWidth=1080;
	public int mHeight=720;

	private static final String KEY_URI = "key-uri";
	private HandlerThread mThread = null;
	private Handler mHandler = null;
	MediaPlayer mPlayer = null;
	public static int PLAYER_INNER = 1;
	public static int mPlayerType = PLAYER_INNER;
	AudioManager mAudioManager=null;
	public void printLog(String msg) {
		Log.e(TAG, msg);
	}

	public MyMediaPlayer() {

		printLog("current thread id: " + Thread.currentThread().getId());		
		// another thread to handle msg to avoid blocking UI thread
		//注册信息，并将信息发给主播放器
		mThread = new HandlerThread("armite-mediaplayer");
		mThread.start();
		mHandler = new Handler(mThread.getLooper(), this);

		mStatus = STATUS_IDLE;
		initInnerPlayer();
		  
	}
	public void initInnerPlayer(){
		if (mPlayerType == PLAYER_INNER) {
			if(mPlayer==null){
				mPlayer = new MediaPlayer();
				mPlayer.setOnCompletionListener(this);
				mPlayer.setOnInfoListener(this);
				mPlayer.setOnErrorListener(this);
				mPlayer.setOnPreparedListener(this);
				mPlayer.setOnSeekCompleteListener(this);
				mPlayer.setOnBufferingUpdateListener(this);
				if(this.mSurfaceHolder!=null){
					mPlayer.setDisplay(this.mSurfaceHolder);
				}
			}
		}

	}
	public void setContext(Context context){
		this.mContext = context;
		mAudioManager=(AudioManager)this.mContext.getSystemService(Context.AUDIO_SERVICE);
	}
	public void setBrowserInterface(IBrowserInterface intf){
		this.mBrowserInterface = intf;
	}
	
	public void setSurfaceHolder(SurfaceHolder sh){
		mSurfaceHolder = sh;
		if (mPlayerType == PLAYER_INNER) {
			if(mPlayer!=null){
				mPlayer.setDisplay(sh);
			}
		}
	}
	public int GetLastError() {
		return mLastError;
	}

	public boolean IsLive() {
		return this.mLive;
	}

	public boolean IsPause() {
		return this.mStatus == STATUS_PAUSED;
	}

	public void addBatchMedia(String jsonString) {
		try {
			JSONArray tmpJSONArray = new JSONArray(jsonString);
			for (int i = 0; i < tmpJSONArray.length(); i++) {
				this.mPlayList.add(tmpJSONArray.get(i));
			}
		} catch (Exception ex) {
			printLog(ex.getMessage());
		}
	}

	public void addSingleMedia(int index, String jsonString) {
		if (jsonString == null)
			return;
		if ((jsonString.startsWith("[")) && (jsonString.endsWith("]")))
			jsonString = jsonString.substring(1, jsonString.length() - 2);
		try {
			JSONObject tmpobj = new JSONObject(jsonString);
			this.mPlayList.add(index, tmpobj);
		} catch (Exception ex) {
			printLog(ex.getMessage());
		}
	}

	/*public int bindNativePlayerInstance(int nativeInstanceID) {

		return 0;
	}*/

	public void clearAllMedia() {
		this.mPlayList.clear();
	}

	public void fastForward(int speed) {
		if(mPlayer==null)return;
		/*
		Message msg = Message.obtain(mHandler);
		msg.what = MSG_PLAYER_FASTFORWARD;
		msg.arg1 = mNativePlayerInstanceID;
		mHandler.sendMessage(msg);
		*/
		mSpeed = speed;
		if(this.mStatus==STATUS_STARTED||this.mStatus==STATUS_PAUSED||this.mStatus==STATUS_PREPARING||this.mStatus==STATUS_PLAYBACKCOMPLETED){
			try{
				this.mPlayer.seekTo(this.mPlayer.getCurrentPosition()+1000*this.mSpeed);
			}catch(Exception ex){
				Log.e(TAG,ex.getMessage());
			}
		}
	}

	public void fastRewind(int speed) {
		if(mPlayer==null)return;
		/*
		Message msg = Message.obtain(mHandler);
		msg.what = MSG_PLAYER_FASTREWIND;
		msg.arg1 = mNativePlayerInstanceID;
		mHandler.sendMessage(msg);*/
		mSpeed = speed; 
		if(this.mStatus==STATUS_STARTED||this.mStatus==STATUS_PAUSED||this.mStatus==STATUS_PREPARING||this.mStatus==STATUS_PLAYBACKCOMPLETED){
			try{
				this.mPlayer.seekTo(this.mPlayer.getCurrentPosition()-1000*this.mSpeed);
			}catch(Exception ex){
				Log.e(TAG,ex.getMessage());
			}
		}
	}

	public int getAllowTrickmodeFlag() {
		return this.mAllowTrickmodeFlag;

	}

	public int getAudioPID() {
		return 0;
	}

	public String getAudioPIDs() {
		return "";
	}

	public String getAudioTrack() {
		return "";
	}

	public int getAudioTrackUIFlag() {
		return this.mAudioTrackUIFlag;
	}

	public int getAudioVolumeUIFlag() {
		return this.mAudioVolumeUIFlag;
	}

	public int getChannelNoUIFlag() {
		return this.mChannelNoUIFlag;
	}

	public int getChannelNum() {

		return 0;
	}

	public String getCurrentAudioChannel() {
		/*
		 * int i1 = this.f.f(); String str; if (i1 == 1) str = "Left"; while
		 * (true) { return str; if (i1 == 2) { str = "Right"; continue; } if
		 * (Config.PLATTYPE.equals("SC")) { str = "JointStereo"; continue; } str
		 * = "Stereo"; }
		 */
		return "Stereo";

	}

	public int getCurrentIndex() {
		return this.mCurrentIndex;
	}

	public String getCurrentPlayTime() {
		if(mPlayer==null)return "0";
		/*
		 * 获取媒体播放到的当前时间点
		 * 对VoD为从该媒体起始点开始计算的相对时间，以秒为单位；对TVoD为当前播放点的绝对时间；对Channel而言无意义
		 * 参见RFC2326中的Normal Play Time (NPT)和Absolute Time (Clock Time)两种时间类型的格式
		 */
		int tmppos = 0;
		try{
		if (mPlayer != null ) {//mPlayer.isPlaying()
			tmppos = mPlayer.getCurrentPosition();
			tmppos = tmppos/1000;
		}
		}catch(Exception ex){
			Log.e(TAG, ex.getMessage());
		}
		// 直播返回的utc时间
		return "" + tmppos;

	}
//the current position in milliseconds 
	public String getCurrentPlayTimeInMS() {
		if(mPlayer==null)return "0";
		/*
		 * 获取媒体播放到的当前时间点
		 * 对VoD为从该媒体起始点开始计算的相对时间，以秒为单位；对TVoD为当前播放点的绝对时间；对Channel而言无意义
		 * 参见RFC2326中的Normal Play Time (NPT)和Absolute Time (Clock Time)两种时间类型的格式
		 */
		int tmppos = 0;
		try{
		if (mPlayer != null) {//&& mPlayer.isPlaying()
			tmppos = mPlayer.getCurrentPosition();
		}
		// 直播返回的utc时间
		}catch(Exception ex){
			Log.e(TAG, ex.getMessage());
		}
		return "" + tmppos;

	}
	
	public String getEntryID() {
		String tmpstr = "";
		if ((this.mCurrentIndex >= 0)
				&& (this.mCurrentIndex < this.mPlayList.size())) {
			try {
				tmpstr = ((JSONObject) this.mPlayList.get(this.mCurrentIndex))
						.getString("entryID");
				Log.e(TAG, "EntryID"+tmpstr);
			} catch (Exception ex) {
				printLog(ex.getMessage());
			}
		}
		return tmpstr;
	}

	public String getMediaCode() {
		String tmpstr = "";
		if ((this.mCurrentIndex >= 0)
				&& (this.mCurrentIndex < this.mPlayList.size())) {
			try {
				tmpstr = ((JSONObject) this.mPlayList.get(this.mCurrentIndex))
						.getString("mediaCode");
			} catch (Exception ex) {
				printLog(ex.getMessage());
			}
		}
		return tmpstr;
	}

	public int getMediaCount() {
		return this.mPlayList.size();
	}
	/**
	 * 整数，以秒为单位	获取当前播放的媒体的总时长
	 * @return
	 */
	public int getMediaDuration() {
		int tmpduration=0;
		if(mPlayer==null)return 0;
		try{
			tmpduration = this.mPlayer.getDuration();
			//duration in milliseconds 
			tmpduration = tmpduration/1000;
		}catch(Exception ex){
			Log.e(TAG, ex.getMessage());
		}
		return tmpduration;
	}
	public int getMediaDurationInMS() {
		
		int tmpduration=0;
		if(mPlayer==null)return 0;
		try{
			tmpduration = this.mPlayer.getDuration();
			//duration in milliseconds 
		}catch(Exception ex){
			Log.e(TAG, ex.getMessage());
		}
		return tmpduration;
	}

	public int getMuteFlag() {
		return this.mMuteFlag;
	}

	public int getMuteUIFlag() {
		return this.mMuteUIFlag;
	}
	public int getNativeUIFlag() {
		return this.mNativeUIFlag;
	}

	public String getPlaybackMode() {
		/*分：Normal Play，Pause，Trickmode；当模式为Trickmode时必须带2x/-2x, 4x/-4x, 8x/-8x, 16x/-16x, 32x/-32x参数来表示快进/快退的速度参数，如：
		{PlayMode: “Normal Play”,
		Speed:1x}*/
		StringBuilder tmpsb = new StringBuilder();
		if(this.mStatus==STATUS_PAUSED){
			tmpsb.append("{PlayMode:\"Pause\",Speed:\"").append(this.mSpeed).append("x\"}");
		}
		else if(this.mStatus==STATUS_STARTED){
			if(this.mSpeed==1){
				tmpsb.append("{PlayMode:\"Normal Play\",Speed:\"").append(this.mSpeed).append("x\"}");
			}else{
				tmpsb.append("{PlayMode:\"Trickmode\",Speed:\"").append(this.mSpeed).append("x\"}");
			}
				
		}else{			
		}
		return tmpsb.toString();
	}

	public String getPlaylist() {
		StringBuilder tmpsb = new StringBuilder();
		tmpsb.append("[");
		for (int i = 0; i < this.mPlayList.size(); i++) {
			tmpsb.append(this.mPlayList.get(i).toString());
			if (i < (this.mPlayList.size() - 1))
				tmpsb.append(",");
		}
		tmpsb.append("]");
		return tmpsb.toString();
	}

	public int getProgressBarUIFlag() {
		return this.mProgressBarUIFlag;
	}

	public int getSingleOrPlaylistMode() {
		return this.mSingleOrPlaylistMode;
	}

	public int getSubtitileFlag() {
		return this.mSubtitileFlag;
	}

	public String getSubtitle() {
		return "";
	}

	public int getSubtitlePID() {
		return 0;
	}

	public String getSubtitlePIDs() {
		return "";
	}

	public String getVendorSpecificAttr() {
		return this.mVendorSpecific;
	}

	public int getVideoAlpha() {
		return this.mVideoAlpha;
	}

	public int getVideoDisplayHeight() {
		return this.mVideoDisplayHeight;
	}

	public int getVideoDisplayLeft() {
		return this.mVideoDisplayLeft;
	}

	public int getVideoDisplayMode() {
		return this.mVideoDisplayMode;
	}

	public int getVideoDisplayTop() {
		return this.mVideoDisplayTop;
	}

	public int getVideoDisplayWidth() {
		return this.mVideoDisplayWidth;
	}

	public int getVolume() {
		int tmpvolume=0;
		if(mPlayer==null)return 0;
		if(mAudioManager!=null){
			tmpvolume = mAudioManager.getStreamVolume(AudioManager.STREAM_MUSIC);			
		}
		return tmpvolume;

	}

	public void gotoEnd() {
		/*
		Message msg = Message.obtain(mHandler);
		msg.what = MSG_PLAYER_GOTOEND;
		msg.arg1 = mNativePlayerInstanceID;
		mHandler.sendMessage(msg);
*/
		if(mPlayer==null)return;
		try{
			if(this.mStatus==STATUS_STARTED||this.mStatus==STATUS_PAUSED||this.mStatus==STATUS_PREPARING||this.mStatus==STATUS_PLAYBACKCOMPLETED)
				mPlayer.seekTo(this.mPlayer.getDuration()-5000);//提前5s
		}catch(Exception ex){
			Log.e(TAG,ex.getMessage());
		}
	}

	
	public void gotoStart() {
		if(mPlayer==null)return;
		/*
		Message msg = Message.obtain(mHandler);
		msg.what = MSG_PLAYER_GOTOSTART;
		msg.arg1 = mNativePlayerInstanceID;
		mHandler.sendMessage(msg);*/
		try{
			if(this.mStatus==STATUS_STARTED||this.mStatus==STATUS_PAUSED||this.mStatus==STATUS_PREPARING||this.mStatus==STATUS_PLAYBACKCOMPLETED)
					mPlayer.seekTo(0);
		}catch(Exception ex){
			Log.e(TAG, ex.getMessage());
		}
	}

	
	public void initMediaPlayer(int nativePlayerinstanceID, int playlistMode,
			int videoDisplayMode, int height, int width, int left, int top,
			int muteFlag, int nativeUIFlag, int subtitleFlag,
			int videoAlpha, int cycleFlag, int randomFlag, int autoDelFlag) {
				
		this.mSingleOrPlaylistMode = playlistMode;//// 0: 单播 1: 播放列表
		this.mVideoDisplayMode = videoDisplayMode;
		this.mHeight = height;
		this.mWidth = width;
		this.mLeft = left;
		this.mTop = top;
		this.mMuteFlag = muteFlag;
		this.mNativeUIFlag = nativeUIFlag;
		this.mSubtitileFlag = subtitleFlag;
		this.mVideoAlpha = videoAlpha;
		this.mCycleFlag = cycleFlag;
		this.mRandomFlag = randomFlag;
		this.mAutoDelFlag = autoDelFlag;
		//this.mPlayer.setDisplay(this.mSurfaceHolder);
	}

	public int joinChannel(int userChannelID) {
		/*
		 * Userchannelid，整数，表示用户频道号。 返回值：0，表示成功； -1：表示频道号无效。
		 */
		// 这个需要获取系统的频道列表，在Authentication中
		// 获取Authentication
		if (Authentication.mChannelList != null) {
			for (int i = 0; i < Authentication.mChannelList.size(); i++) {
				if (((LiveChannel) Authentication.mChannelList.get(i)).UserChannelID == userChannelID) {
					// 发送消息JOIN CHANNEL
					this.mLive = true;
					LiveChannel tmpchannel = (LiveChannel) Authentication.mChannelList
							.get(i);
					Message msg = Message.obtain(mHandler);
					msg.what = MSG_PLAYER_JOINCHANNEL;
					msg.arg1 = mNativePlayerInstanceID;
					msg.arg2 = userChannelID;
					this.mCurrentUserChannelID = userChannelID;
					mHandler.sendMessage(msg);
					//对于IGMP我们需要修改为udp://的方式
					
					return 0;
				}
			}
		}
		return -1;
	}

	public void leaveChannel() {
		this.mCurrentUserChannelID = -1;
		Message msg = Message.obtain(mHandler);
		msg.what = MSG_PLAYER_LEAVECHANNEL;
		msg.arg1 = mNativePlayerInstanceID;
		mHandler.sendMessage(msg);

	}

	public int getArrayIndexByEntryID(String entryID) {
		int tmpret = -1;
		for (int i = 0; i < this.mPlayList.size(); i++) {
			try {
				if (((JSONObject) this.mPlayList.get(i)).get("entryID") != null) {
					String tmpentryid = ((JSONObject) this.mPlayList.get(i))
							.get("entryID").toString();
					if (tmpentryid.equals(entryID)) {
						tmpret = i;
						break;
					}
				}
			} catch (Exception ex) {
				printLog(ex.getMessage());
			}
		}
		return tmpret;
	}

	public void moveMediaByIndex(String entryID, int toIndex) {
		int tmpOrgIndex = getArrayIndexByEntryID(entryID);
		if (tmpOrgIndex != -1) {
			moveMediaByIndex1(tmpOrgIndex, toIndex);
		}

	}

	public void moveMediaByIndex1(int fromIndex, int toIndex) {
		if((fromIndex!=toIndex)&&(fromIndex>=0)&&(fromIndex<this.mPlayList.size())&&(toIndex>=0)&&(toIndex<this.mPlayList.size())){
			
			JSONObject tmpfromobj = (JSONObject)this.mPlayList.get(fromIndex);
		
			 if (fromIndex > toIndex)
		        {
		          this.mPlayList.remove(fromIndex);
		          this.mPlayList.add(toIndex, tmpfromobj);		          
		        }
			 else{
		        this.mPlayList.add(toIndex + 1, tmpfromobj);
		        this.mPlayList.remove(fromIndex);
			 }
		}		
	}

	public void moveMediaByOffset(String entryID, int offset) {
		int tmpOrgIndex = getArrayIndexByEntryID(entryID);
		if (tmpOrgIndex != -1) {
			moveMediaByOffset1(tmpOrgIndex, offset);
		}

	}

	public void moveMediaToFirst(String entryID) {
		int tmpOrgIndex = getArrayIndexByEntryID(entryID);
		if (tmpOrgIndex != -1) {
		    moveMediaByIndex1(tmpOrgIndex, 0);
		}
	}

	public void moveMediaByOffset1(int fromIndex, int offset) {
		moveMediaByIndex1(fromIndex, fromIndex + offset);
	}

	public void moveMediaToFirst1(int fromIndex) {
		 moveMediaByIndex1(fromIndex, 0);
	}

	public void moveMediaToLast(String entryID) {
		int tmpOrgIndex = getArrayIndexByEntryID(entryID);
		if (tmpOrgIndex != -1) {
		    moveMediaByIndex1(tmpOrgIndex, this.mPlayList.size()-1);
		}
	}

	public void moveMediaToLast1(int fromIndex) {
		   moveMediaByIndex1(fromIndex, this.mPlayList.size()-1);
	}

	public void moveMediaToNext(String entryID) {
		int tmpOrgIndex = getArrayIndexByEntryID(entryID);
		if (tmpOrgIndex != -1) {
			moveMediaByIndex1(tmpOrgIndex, tmpOrgIndex+1);
		}
	}

	public void moveMediaToNext1(int fromIndex) {
		  moveMediaByIndex1(fromIndex, fromIndex + 1);
	}

	public void moveMediaToPrevious(String entryID) {
		int tmpOrgIndex = getArrayIndexByEntryID(entryID);
		if (tmpOrgIndex != -1) {
			moveMediaByIndex1(tmpOrgIndex, tmpOrgIndex-1);
		}
	}

	public void moveMediaToPrevious1(int fromIndex) {
		moveMediaByIndex1(fromIndex, fromIndex-1);
	}

	public void pause() {
		if(mPlayer==null)return;
		/*
		Message msg = Message.obtain(mHandler);
		msg.what = MSG_PLAYER_PAUSE;
		msg.arg1 = this.mNativePlayerInstanceID;
		mHandler.sendMessage(msg);*/
		this.mStatus = STATUS_PAUSED;
		try{
			mPlayer.pause();
		}catch(Exception ex){
			Log.e(TAG, ex.getMessage());
		}
	}

	public String getCurrentPlayUrl() {
		String tmpret = "";
		if ((this.mCurrentIndex >= 0)
				&& (this.mCurrentIndex < this.mPlayList.size())) {
			try {
				tmpret = ((JSONObject) this.mPlayList.get(this.mCurrentIndex))
						.getString("mediaUrl");
			} catch (Exception ex) {
				printLog(ex.getMessage());
			}
		}
		//tmpret="http://58.215.173.59:8080/1.mp4";//测试的时候使用这个地址
		tmpret="http://192.168.0.100:9191/1.mp4";
		return tmpret;
	}

	public void playByUrl(String uri, int time, int x, int y, int w, int h) {
		//设置窗口和进行播放 
		  //mBrowserView.videoShow(this.mNativePlayerInstanceID, uri, x, y, w, h);
	 	    Message msg = Message.obtain(mHandler);
	        msg.what = MSG_PLAYER_STARTPLAY;
	        msg.arg1 = this.mNativePlayerInstanceID;
	        msg.arg2 = time;
	        Bundle data = new Bundle();
	        data.putString(KEY_URI, uri);
	        msg.setData(data);
	        mHandler.sendMessage(msg);
	}
	 
	public void play() {
		String uri = getCurrentPlayUrl();
		if (!uri.equals("")) {
			try {
				initInnerPlayer();
				this.mPlayer.setDataSource(this.mContext,Uri.parse(uri));
			} catch (Exception e) {
				Log.e(TAG, e.getMessage());
				return;
			}
			this.mStartTime  ="0";
			notifyPlayModeChange(STATUS_IDLE,1,STATUS_PREPARING,this.mSpeed);
			this.mPlayer.prepareAsync();
			this.mPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
			this.mStatus = STATUS_PREPARING;

			/*
			Message msg = Message.obtain(mHandler);
			msg.what = MSG_PLAYER_PLAY;
			msg.arg1 = this.mNativePlayerInstanceID;
			Bundle bundle = new Bundle();
			bundle.putString("timestamp", "");
			bundle.putString("speed", "1");
			bundle.putString("url", "" + uri);
			msg.setData(bundle);
			mHandler.sendMessage(msg);
			*/
		}
	}

	public void playByTime(int type, String timestamp, int speed) {
		/*
		 * -type: 1：参见RFC2326中的Normal Play Time (NPT) 2：参见RFC2326中的Absolute Time
		 * (Clock Time) -timestamp: 参见RFC2326中的Normal Play Time (NPT)和Absolute
		 * Time (Clock Time)两种时间类型的格式
		 */
	/*	Message msg = Message.obtain(mHandler);
		msg.what = MSG_PLAYER_PLAY;
		msg.arg1 = this.mNativePlayerInstanceID;
		Bundle bundle = new Bundle();
		bundle.putString("timestamp", timestamp);
		bundle.putString("speed", "" + speed);
		msg.setData(bundle);
		mHandler.sendMessage(msg);*/
		if(this.mStatus==STATUS_STARTED||this.mStatus==STATUS_PAUSED||this.mStatus==STATUS_PREPARING||this.mStatus==STATUS_PLAYBACKCOMPLETED){
			if(mPlayer==null)return;
			try{				
				mPlayer.seekTo(Integer.parseInt(timestamp)*1000);//提前5s
			}catch(Exception ex){
				Log.e(TAG,ex.getMessage());
			}
		}else{
		String uri = getCurrentPlayUrl();
		if (!uri.equals("")) {
			try {
				initInnerPlayer();
				this.mPlayer.setDataSource(this.mContext,Uri.parse(uri));
			} catch (Exception e) {
				Log.e(TAG, e.getMessage());
				return;
			}
		}
		this.mStartTime  = timestamp;
		notifyPlayModeChange(STATUS_IDLE,1,STATUS_PREPARING,this.mSpeed);
		this.mPlayer.prepareAsync();
		this.mPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
		this.mStatus = STATUS_PREPARING;
		}
		
	}

	public void playFromStart() {
		/*
		Message msg = Message.obtain(mHandler);
		msg.what = MSG_PLAYER_PLAY;
		msg.arg1 = this.mNativePlayerInstanceID;
		Bundle bundle = new Bundle();
		bundle.putString("timestamp", "");
		bundle.putString("speed", "1");
		msg.setData(bundle);
		mHandler.sendMessage(msg);
		 */
		String uri = getCurrentPlayUrl();
		if (!uri.equals("")) {
			try {
				initInnerPlayer();
				this.mPlayer.setDataSource(this.mContext,Uri.parse(uri));
			} catch (Exception e) {
				Log.e(TAG, e.getMessage());
				return;
			}
		}
		this.mStartTime  = "0";
		notifyPlayModeChange(STATUS_IDLE,1,STATUS_PREPARING,this.mSpeed);
		this.mPlayer.prepareAsync();
		this.mPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);			
		//哪个时间发送到开始时间，这边设置开始位置
		this.mStatus = STATUS_PREPARING;
		
	}

	public void refreshVideoDisplay() {
		/*Message msg = Message.obtain(mHandler);
		msg.what = MSG_PLAYER_REFRESHVIDEO;
		msg.arg1 = this.mNativePlayerInstanceID;	
		mHandler.sendMessage(msg);*/
		
	}
	public int releaseMediaPlayer(int instanceID) {
			
		if(mPlayer==null)return -1;
		try{
			if(mPlayer.isPlaying()){
				stop();
			}
			if(this.mStatus!=STATUS_RELEASED){
				mPlayer.reset();
				mPlayer.release();
			}
			
		}catch(Exception ex){
			Log.e(TAG, ex.getMessage());
		}
		mPlayer = null;
		mStatus = STATUS_RELEASED;
		return 0;
	}
	

	public void removeMediaByEntryID(String entryID) {
		int tmpIndex = this.getArrayIndexByEntryID(entryID);
		removeMediaByIndex(tmpIndex);
	}

	public void removeMediaByIndex(int index) {
		if(index!=-1){
				if((index>=0)&&(index<this.mPlayList.size())){
				this.mPlayList.remove(index);
				if(this.mPlayList.size()==0){
					this.mCurrentIndex = -1;
				}
				else if(this.mCurrentIndex==index){
				//需要调整下位置
					this.mCurrentIndex = index+1;
					if(this.mCurrentIndex>=this.mPlayList.size())
						this.mCurrentIndex = this.mPlayList.size()-1;
				}
			}
		}
	}

	public void resume() {
		if(mPlayer==null)return;
		/*
		Message msg = Message.obtain(mHandler);
		msg.what = MSG_PLAYER_RESUME;
		msg.arg1 = mNativePlayerInstanceID;
		mHandler.sendMessage(msg);*/
		try{
			mPlayer.start();
		}catch(Exception ex){
			Log.e(TAG, ex.getMessage());
		}
		mSpeed = 1;//重新恢复正常速度
		this.mStatus=STATUS_STARTED;
	}

	public void selectFirst() {
		if (this.mPlayList.size() > 0)
			this.mCurrentIndex = 0;
		else
			this.mCurrentIndex = -1;
	}

	public void selectLast() {
		if (this.mPlayList.size() > 0)
			this.mCurrentIndex = this.mPlayList.size() - 1;
		else
			this.mCurrentIndex = -1;

	}

	public void selectMediaByIndex(int index) {
		if ((index >= 0) && (index < this.mPlayList.size()))
			this.mCurrentIndex = index;
	}

	public void selectMediaByOffset(int offset) {
		int tmpnextindex = this.mCurrentIndex + offset;
		if (tmpnextindex >= this.mPlayList.size())
			this.mCurrentIndex = this.mPlayList.size() - 1;
		if (tmpnextindex < 0)
			tmpnextindex = 0;
		this.mCurrentIndex = tmpnextindex;
	}

	public void selectNext() {
		selectMediaByOffset(1);
	}

	public void selectPrevious() {
		selectMediaByOffset(-1);
	}

	public void sendVendorSpecificCommand(String paramString) {
	}

	public void set(String paramString1, String paramString2) {

	}

	public void setAllowTrickmodeFlag(int bAllowTrickmodeFlag) {
		this.mAllowTrickmodeFlag = bAllowTrickmodeFlag;

	}

	public void setAudioPID(int paramInt) {
	}

	public void setAudioTrackUIFlag(int flag) {
		this.mAudioTrackUIFlag = flag;
	}

	public void setAudioVolumeUIFlag(int flag) {
		this.mAudioVolumeUIFlag = flag;
	}

	public void setChannelNoUIFlag(int flag) {
		this.mChannelNoUIFlag = flag;
	}

	public void setCycleFlag(int flag) {
		this.mCycleFlag = flag;	
	}

	public void setMuteFlag(int flag) {
		this.mMuteFlag = flag;		
		if(mAudioManager!=null){
			mAudioManager.setStreamMute(AudioManager.STREAM_MUSIC, flag==1); //设置是否静音
		}
	}

	public void setMuteUIFlag(int flag) {
		this.mMuteUIFlag = flag;
	}

	public void setNativeUIFlag(int flag) {
		this.mNativeUIFlag = flag;
	}

	public void setProgressBarUIFlag(int flag) {
		this.mProgressBarUIFlag = flag;
	}

	public void setRandomFlag(int flag) {
		this.mRandomFlag = flag;
	}

	public void setSingleMedia(String jsonString) {
		
		if ((jsonString.startsWith("[")) && (jsonString.endsWith("]")))
			jsonString = jsonString.substring(1, jsonString.length() - 1);
		
		try {
			Log.e("", jsonString);
			JSONObject tmpjson = new JSONObject(jsonString);	
			this.mPlayList.clear();
			this.mPlayList.add(tmpjson);
			this.mSingleOrPlaylistMode = 1;
		} catch (Exception ex) {
			printLog(ex.getMessage());
		}
	}

	public void setSingleOrPlaylistMode(int mode) {
		this.mSingleOrPlaylistMode = mode;

	}

	public void setSubtitileFlag(int flag) {
		this.mSubtitileFlag = flag;
	}

	public void setSubtitlePID(int param) {
	}

	public void setVendorSpecificAttr(String paramString) {
		this.mVendorSpecific = paramString;
	}

	public void setVideoAlpha(int alpha) {
		this.mVideoAlpha = alpha;
	}

	public void setVideoDisplayArea(int left, int top,
			int width, int height) {

	}

	public void setVideoDisplayMode(int mode) {
		// 0：指尺寸 1:全屏 2:宽度 3:高度 255：音频
		this.mVideoDisplayMode = mode;
	}

	public void setVolume(int vol) {
		if(mPlayer==null)return;
		this.mVolume = vol;
		if(mPlayer==null)return;
		//mPlayer.setVolume(vol, vol);//左右声道
		if(mAudioManager!=null){
			//Volume：0-100，表示音量，0为静音，100为最大音量。
			int tmpmax = mAudioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);			
			//int currentVolume = mAudioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
			int tmpvolume = vol*tmpmax/100;
			if(vol==0){
					mAudioManager.setStreamVolume(AudioManager.STREAM_MUSIC, 0, 0);
			}else{
					mAudioManager.setStreamVolume(AudioManager.STREAM_MUSIC, tmpvolume, 0); //tempVolume:音量绝对值
				}
		}
	}

	public void stop() {
		if(mPlayer==null)return;
		try{
			//if(mPlayer.isPlaying())			
				mPlayer.stop();
		}catch(Exception ex){
			Log.e(TAG, ex.getMessage());
		}
		this.mStatus=STATUS_STOP;
	}

	public void switchAudioChannel() {

	}

	public void switchAudioTrack() {
	}

	public void switchSubtitle() {

	}

	public boolean handleMessage(Message msg) {
		synchronized (this) {
			printLog("MediaPlayer handleMessage:" + msg.what);
			/*
			Intent tmpintent = new Intent();
			tmpintent.putExtra("instanceid","");
			tmpintent.putExtra("action","");
			tmpintent.putExtra("params","");
			sendBroadcast(tmpintent);
			*/
			switch (msg.what) {
			case MSG_PLAYER_PLAY:
				// handleStart(msg.arg1, msg.arg2,
				// msg.getData().getString(KEY_URI));
				break;
			case MSG_PLAYER_STOP:
				// handleStop(msg.arg1);
				break;
			case MSG_PLAYER_PAUSE:
				// handlePause(msg.arg1);
				break;
			case MSG_PLAYER_RESUME:
				// handleResume(msg.arg1);
				break;
			case MSG_PLAYER_SEEK:
				// handleSeekTo(msg.arg1, msg.arg2);
				break;
			}
			return true;
		}
	}

	//扩展函数,可选
		//设置快收模式 
		public int setXBurstMode(boolean xburst){   //设置是否快收模式，针对rtsp
			return 0;
		}
		//设置重发模式  
		public int setARQ(boolean arq){ //设置是否ARQ
			return 0;
		}
		//获取单项统计
		public String getStaticsItem(String item){
			return "";
		}
		//获取播放统计信息 
		public String getStatics(){
			return "";
		}


		public void onSeekComplete(MediaPlayer mp) {
			printLog("enter onSeekComplete");
			try{
			//this.mPlayer.start();
			}catch(Exception ex){
				Log.e(TAG, ex.getMessage());
			}
			printLog("exit onSeekComplete");
		}

		public void onBufferingUpdate(MediaPlayer mp, int percent) {

			
		}
				
		// callback
		// mediaplayer callback
		public void onCompletion(MediaPlayer mp) {
			mStatus = STATUS_PLAYBACKCOMPLETED;
			if(this.mBrowserInterface!=null){				
				this.mBrowserInterface.notifyMediaEvent("EVENT_MEDIA_END", this.mNativePlayerInstanceID, this.getMediaCode(), this.getEntryID());
			}
		}

		public boolean onError(MediaPlayer mp, int what, int extra) {
			printLog("onError " + extra);			
			mp.reset();
			mStatus = STATUS_IDLE;
			if(this.mBrowserInterface!=null){				
				int tmperrorcode=what;
				String tmperrordesc="";			
				/*if (what==MediaPlayer.MEDIA_ERROR_NOT_VALID_FOR_PROGRESSIVE_PLAYBACK) {  

            System.out.println("第一种错误");  

        }  
        if (what==MediaPlayer.MEDIA_ERROR_SERVER_DIED) {  

            System.out.println("第二种错误");  
        }  

        if (what==MediaPlayer.MEDIA_ERROR_UNKNOWN) {  

            System.out.println("第三种错误");  
        }  */
				this.mBrowserInterface.notifyMediaError("EVENT_MEDIA_ERROR", this.mNativePlayerInstanceID,tmperrorcode,tmperrordesc, this.getMediaCode());
			}
			return false;
		}

		public void onPrepared(MediaPlayer mp) {		
			if(mp!=null){
				int tmporgstatus = this.mStatus;
				int tmporgspeed = this.mSpeed;
				int old_play_mode=0;
				int new_play_mode=0;
				this.mStatus = STATUS_STARTED;
				try{
				mp.start();
				if(this.mStartTime!=null){
					int tmpstarttime=0;
					try{
						tmpstarttime = Integer.parseInt(this.mStartTime)*1000;
					}catch(Exception ex){
						
					}
					if(tmpstarttime>0){
						mp.seekTo(tmpstarttime*1000);
					}
				}
				}catch(Exception ex2){
					Log.e(TAG, ex2.getMessage());
				}
				if(this.mBrowserInterface!=null){								
					this.mBrowserInterface.notifyMediaEvent("EVENT_MEDIA_BEGINING", this.mNativePlayerInstanceID, this.getMediaCode(), this.getEntryID());
				}
			}
		}
		public void notifyPlayModeChange(int orgstatus,int orgspeed,int newstatus,int newspeed){
			
			/*0	STOP	停止状态
1	PAUSE	暂停状态
2	NORMAL_PLAY	正常播放状态
3	TRICK_MODE	正常播放之外，以指定播放速率快进，快退，慢进，慢退
其他		待定
*/
			int old_play_mode=0;
			int new_play_mode=0;
			
			if(orgstatus==STATUS_STOP||orgstatus==STATUS_PLAYBACKCOMPLETED)old_play_mode=0;
			else if(orgstatus==STATUS_PAUSED)old_play_mode = 1;
			else if(orgstatus==STATUS_STARTED)old_play_mode = 2;
			if(this.mSpeed!=1){
				if(orgstatus!=STATUS_PAUSED)old_play_mode = 3;
			}
			
			if(newstatus==STATUS_STOP||orgstatus==STATUS_PLAYBACKCOMPLETED)new_play_mode=0;
			else if(newstatus==STATUS_PAUSED)new_play_mode = 1;
			else if(newstatus==STATUS_STARTED)new_play_mode = 2;
			if(newspeed!=1){
				if(newstatus!=STATUS_PAUSED)new_play_mode = 3;
			}			
			this.mBrowserInterface.notifyMediaPlayModeChange("EVENT_PLAYMODE_CHANGE", this.mNativePlayerInstanceID, new_play_mode, newspeed, old_play_mode, orgspeed);
		}
		
		public boolean onInfo(MediaPlayer mp, int what, int extra) {		
			/*
  public static final int MEDIA_ERROR_UNKNOWN = 1;
  public static final int MEDIA_ERROR_SERVER_DIED = 100;
  public static final int MEDIA_ERROR_NOT_VALID_FOR_PROGRESSIVE_PLAYBACK = 200;
  public static final int MEDIA_INFO_UNKNOWN = 1;
  public static final int MEDIA_INFO_VIDEO_TRACK_LAGGING = 700;
  public static final int MEDIA_INFO_BUFFERING_START = 701;
  public static final int MEDIA_INFO_BUFFERING_END = 702;
  public static final int MEDIA_INFO_BAD_INTERLEAVING = 800;
  public static final int MEDIA_INFO_NOT_SEEKABLE = 801;
  public static final int MEDIA_INFO_METADATA_UPDATE = 802;*/
			  if (what==MediaPlayer.MEDIA_INFO_BAD_INTERLEAVING) {  

		            //音频和视频数据不正确地交错时将出现该提示信息.在一个  

		            //正确交错的媒体文件中,音频和视频样本将依序排列,从而  

		            //使得播放可以有效和平稳地进行  

		        }  

		        if (what==MediaPlayer.MEDIA_INFO_NOT_SEEKABLE) {  

		            //当媒体不能正确定位时将出现该提示信息.  

		            //此时意味着它可能是一个在线流  

		        }  

		        if (what==MediaPlayer.MEDIA_INFO_VIDEO_TRACK_LAGGING) {  

		            //当设备无法播放视频时将出现该提示信息  

		            //比如视频太复杂或者码率过高  

		        }  

		        if (what==MediaPlayer.MEDIA_INFO_METADATA_UPDATE) {  

		            //当新的元数据可用时将出现该提示信息  

		        }  

		        if (what==MediaPlayer.MEDIA_INFO_UNKNOWN) {  

		            //其余不可知提示信息  

		        }  
			 
			return true;
		}

		// callback for external caller
		// for err callback
		public static interface OnErrorListener {
			public static final int ERRCODE_ID = 0;
			public static final int ERRCODE_INVALID_STOP = 1;
			public static final int ERRCODE_INVALID_PAUSE = 2;
			public static final int ERRCODE_INVALID_RESUME = 3;
			public static final int ERRCODE_INVALID_SEEK = 4;

			public void onError(int id, int errCode, String errStr);
		}

		private OnErrorListener errListener;

		public void setOnErrorListener(OnErrorListener listener) {
			errListener = listener;
		}

	      
	         

}
