package com.armite.webkit.plug;

import java.util.ArrayList;

import org.json.JSONArray;

import android.util.Log;

public class MediaPlayer {
		public String TAG="MediaPlayer";
	  public String mInstanceID="";
	  
	  public MediaPlayer(){
		  mInstanceID =MyPlayerCenter.getNextInstanceID(); 
	  }
	  public int GetLastError()
	  {
	    return MyPlayerCenter.GetLastError(mInstanceID);
	  }
	  public boolean IsLive()
	  {
	    return MyPlayerCenter.IsLive(mInstanceID);	    		
	  }


	  public boolean IsPause()
	  {
		  return MyPlayerCenter.IsPause(mInstanceID);
	  }
	  public void addBatchMedia(String jsonString)
	  {
		  MyPlayerCenter.addBatchMedia(mInstanceID, jsonString);
	  }
	  public void addSingleMedia(int index, String jsonString)
	  {
		  MyPlayerCenter.addSingleMedia(mInstanceID, index, jsonString);
	  }
	  public int bindNativePlayerInstance(int nativeInstanceID)
	  {
		  return MyPlayerCenter.bindNativePlayerInstance(mInstanceID,nativeInstanceID);
	  }
	  public void clearAllMedia()
	  {
		  MyPlayerCenter.clearAllMedia(mInstanceID);
	  }
	  public void fastForward(int speed)
	  {
		  MyPlayerCenter.fastForward(mInstanceID, speed);
	  }

	  public void fastRewind(int speed)
	  {
		  MyPlayerCenter.fastRewind(mInstanceID, speed);  
	  }
	  public int getAllowTrickmodeFlag()
	  {
		  return MyPlayerCenter.getAllowTrickmodeFlag(mInstanceID);			 	
	  }
	  public int getAudioPID()
	  {
		  return MyPlayerCenter.getAudioPID(mInstanceID);
	  }

	  public String getAudioPIDs()
	  {
		  return MyPlayerCenter.getAudioPIDs(mInstanceID);
	  }

	  public String getAudioTrack()
	  {
		  return MyPlayerCenter.getAudioTrack(mInstanceID);
	  }
	  

	  
	  public int getAudioTrackUIFlag()
	  {
		  return MyPlayerCenter.getAudioTrackUIFlag(mInstanceID);	  
	  }

	  public int getAudioVolumeUIFlag()
	  {
		  return MyPlayerCenter.getAudioVolumeUIFlag(mInstanceID);
	  }

	  public int getChannelNoUIFlag()
	  {
		  return MyPlayerCenter.getChannelNoUIFlag(mInstanceID);	    
	  }


	  public int getChannelNum()
	  {
		  return MyPlayerCenter.getChannelNum(mInstanceID);	
	  }
	  

	
	  public String getCurrentAudioChannel()
	  {
		  return MyPlayerCenter.getCurrentAudioChannel(mInstanceID);
	  }
	  public int getCurrentIndex()
	  {
		  return MyPlayerCenter.getCurrentIndex(mInstanceID);
	  }
	  public String getCurrentPlayTime()
	  {
		  return MyPlayerCenter.getCurrentPlayTime(mInstanceID);
	 
	  }


	  public String getEntryID()
	  {
		  return MyPlayerCenter.getEntryID(mInstanceID);
	  }
	  public String getMediaCode()
	  {
		  return MyPlayerCenter.getMediaCode(mInstanceID);
	  }
	  
	  public int getMediaCount()
	  {
		  return MyPlayerCenter.getMediaCount(mInstanceID);
	  }
	  public int getMediaDuration()
	  {
		  return MyPlayerCenter.getMediaDuration(mInstanceID);
	  }
	  
	
	  public int getMuteFlag(){
		  return MyPlayerCenter.getMuteFlag(mInstanceID);	
	  }

	  public int getMuteUIFlag()
	  {
		  return MyPlayerCenter.getMuteUIFlag(mInstanceID);
	  }
	  public int getNativePlayerInstance()
	  {
		  return getNativePlayerInstanceID();
	  }
	  
	  public int getNativePlayerinstanceID()
	  {
		  return getNativePlayerInstanceID();
	  }
	  public int getNativePlayerInstanceID()
	  {
		  return MyPlayerCenter.getNativePlayerInstanceID();		  
	  }

	  public int getNativeUIFlag()
	  {
		  return MyPlayerCenter.getNativeUIFlag(mInstanceID);		
	  }

	  public String getPlaybackMode()
	  {
		  return MyPlayerCenter.getPlaybackMode(mInstanceID);
	  }

	  public String getPlaylist()
	  {
		  return MyPlayerCenter.getPlaylist(mInstanceID);
	  }
	  
	  public int getProgressBarUIFlag()
	  {
		  return MyPlayerCenter.getProgressBarUIFlag(mInstanceID); 
	  }

	  public int getSingleOrPlaylistMode()
	  {
		  return MyPlayerCenter.getSingleOrPlaylistMode(mInstanceID);
	  }

	  public int getSubtitileFlag()
	  {
		  return MyPlayerCenter.getSubtitileFlag(mInstanceID);
	  }

	  public String getSubtitle()
	  {
		  return MyPlayerCenter.getSubtitle(mInstanceID);
	  }

	  public int getSubtitlePID()
	  {
		  return MyPlayerCenter.getSubtitlePID(mInstanceID);
	  }

	  public String getSubtitlePIDs()
	  {
		  return MyPlayerCenter.getSubtitlePIDs(mInstanceID);
	  }

	  
	  public String getVendorSpecificAttr()
	  {
		  return MyPlayerCenter.getVendorSpecificAttr(mInstanceID);
	  }
	  
	  

	  
	  public int getVideoAlpha()
	  {
		  return MyPlayerCenter.getVideoAlpha(mInstanceID);
	  }

	  public int getVideoDisplayHeight()
	  {
		  return MyPlayerCenter.getVideoDisplayHeight(mInstanceID);
	  }

	  public int getVideoDisplayLeft()
	  {
		  return MyPlayerCenter.getVideoDisplayLeft(mInstanceID);
	  }

	  public int getVideoDisplayMode()
	  {
		  return MyPlayerCenter.getVideoDisplayMode(mInstanceID);
	  }

	  public int getVideoDisplayTop()
	  {
		  return MyPlayerCenter.getVideoDisplayTop(mInstanceID);
	  }

	  public int getVideoDisplayWidth()
	  {
		  return MyPlayerCenter.getVideoDisplayWidth(mInstanceID);
	  }
	  
	  public int getVolume()
	  {
		  return MyPlayerCenter.getVolume(mInstanceID);
	  }
	  public void gotoEnd()
	  {
		  MyPlayerCenter.gotoEnd(mInstanceID);
	  }

	  public void gotoStart()
	  {
		  MyPlayerCenter.gotoStart(mInstanceID);
	  }

	  public void initMediaPlayer(int nativePlayerinstanceID, int playlistFlag, int videoDisplayMode, int height, int width, int left, int top, int muteFlag,  int useNativeUIFlag, int subtitleFlag,int videoAlpha,int cycleFlag,int randomFlag,int autoDelFlag)
	  {
		  //创建一个内部id
		  MyPlayerCenter.initMediaPlayer(mInstanceID,nativePlayerinstanceID, playlistFlag, videoDisplayMode, height, width, left, top, muteFlag, useNativeUIFlag, subtitleFlag, videoAlpha, cycleFlag, randomFlag, autoDelFlag);
	
	  }

	  public int  joinChannel(int userChannelID)
	  {
		  return MyPlayerCenter.joinChannel(mInstanceID,userChannelID);
			
		  
	  }

	  public void leaveChannel()
	  {
		  MyPlayerCenter.leaveChannel(mInstanceID);
	  }

	  public void moveMediaByIndex(String jsonString, int index)
	  {
		  MyPlayerCenter.moveMediaByIndex(mInstanceID,jsonString,index);
	  }

	  public void moveMediaByIndex1(int fromIndex, int toIndex)
	  {
		  MyPlayerCenter.moveMediaByIndex1(mInstanceID,fromIndex,toIndex);
	  }

	  public void moveMediaByOffset(String jsonString, int index)
	  {
		  MyPlayerCenter.moveMediaByOffset(mInstanceID,jsonString,index);
	  }

	  public void moveMediaToFirst(String jsonString)
	  {
		  MyPlayerCenter.moveMediaToFirst(mInstanceID,jsonString);
	  }

	  public void moveMediaByOffset1(int fromIndex, int offset)
	  {
		  MyPlayerCenter.moveMediaByOffset1(mInstanceID,fromIndex,offset);  
	  }
	  public void moveMediaToFirst1(int index)
	  {
		  MyPlayerCenter.moveMediaToFirst1(mInstanceID,index);
	  }
	  public void moveMediaToLast(String jsonString)
	  {
		  MyPlayerCenter.moveMediaToLast(mInstanceID,jsonString);
	  }
	  
	  public void moveMediaToLast1(int index)
	  {
		  MyPlayerCenter.moveMediaToLast1(mInstanceID,index);
	  }
	  public void moveMediaToNext(String jsonString)
	  {
		  MyPlayerCenter.moveMediaToNext(mInstanceID,jsonString);
	  }
	  public void moveMediaToNext1(int index)
	  {
		  MyPlayerCenter.moveMediaToNext1(mInstanceID,index);
	  }
	  public void moveMediaToPrevious(String jsonString)
	  {
		  MyPlayerCenter.moveMediaToPrevious(mInstanceID,jsonString);
	  }
	  public void moveMediaToPrevious1(int index)
	  {
		  MyPlayerCenter.moveMediaToPrevious1(mInstanceID,index);
	  }
	  public void pause()
	  {
		  MyPlayerCenter.pause(mInstanceID);
	  }
	  public void play()
	  {
		  MyPlayerCenter.play(mInstanceID);
	  }
	  public void playByTime(int type, String timestamp, int speed)
	  {
		  MyPlayerCenter.playByTime(mInstanceID,type,timestamp,speed);
		  
	  }
	  public void playByTime2(int type, String timestamp)
	  {
		  MyPlayerCenter.playByTime(mInstanceID, type, timestamp, 1); //2-32  
	  }
	
	  /**
	   * 为了兼容有些人写的不好的代码，实际timestamp应该是字符串的
	   * @param type
	   * @param timestamp
	   * @param speed
	   */
	  public void playByTime3(int type, int timestamp, int speed)
	  {
		  MyPlayerCenter.playByTime(mInstanceID,type,""+timestamp,speed);		  
	  }
	  public void playByTime4(int type, int timestamp)
	  {
		  MyPlayerCenter.playByTime(mInstanceID,type,""+timestamp,1);		  
	  }

	  public void playFromStart()
	  {
		  MyPlayerCenter.playFromStart(mInstanceID); 
	  }

	  public void refreshVideoDisplay()
	  {
		  MyPlayerCenter.refreshVideoDisplay(mInstanceID);
	  }

	  public int releaseMediaPlayer(int nativeInstanceID)
	  {
		  return MyPlayerCenter.releaseMediaPlayer(mInstanceID,nativeInstanceID);
	  }
	  public void removeMediaByEntryID(String entryID)
	  {
		  MyPlayerCenter.removeMediaByEntryID(mInstanceID,entryID);
	  }

	  public void removeMediaByIndex(int index)
	  {
		  MyPlayerCenter.removeMediaByIndex(mInstanceID,index);
	  }

	  public void resume()
	  {
		  MyPlayerCenter.resume(mInstanceID);
	  }

	  public void selectFirst()
	  {
		  MyPlayerCenter.selectFirst(mInstanceID);  
	  }

	  public void selectLast()
	  {
		  MyPlayerCenter.selectLast(mInstanceID);
	  }

	  public void selectMediaByIndex(int index)
	  {
		  MyPlayerCenter.selectMediaByIndex(mInstanceID,index);
	  }

	  public void selectMediaByOffset(int index)
	  {
		  MyPlayerCenter.selectMediaByOffset(mInstanceID,index);
	  }
	  public void selectNext()
	  {
		  MyPlayerCenter.selectNext(mInstanceID);
	  }

	  public void selectPrevious()
	  {
		  MyPlayerCenter.selectPrevious(mInstanceID);
	  }

	  public void sendVendorSpecificCommand(String command)
	  {
		  MyPlayerCenter.sendVendorSpecificCommand(mInstanceID,command);
	  }
	  public void set(String name, String value)
	  {
		  MyPlayerCenter.set(mInstanceID, name, value);  
	  }
	  public void setAllowTrickmodeFlag(int bAllowTrickmodeFlag)
	  {
		  MyPlayerCenter.setAllowTrickmodeFlag(mInstanceID, bAllowTrickmodeFlag);
		  
	  }
	  public void setAudioPID(int pid)
	  {
		  MyPlayerCenter.setAudioPID(mInstanceID, pid);
	  }

	  public void setAudioTrackUIFlag(int flag)
	  {
		  MyPlayerCenter.setAudioTrackUIFlag(mInstanceID, flag);
	  }

	  public void setAudioVolumeUIFlag(int flag)
	  {
		  MyPlayerCenter.setAudioVolumeUIFlag(mInstanceID, flag);
	  }

	  public void setChannelNoUIFlag(int flag)
	  {
		  MyPlayerCenter.setChannelNoUIFlag(mInstanceID, flag);
	  }

	  public void setCycleFlag(int flag)
	  {
		  MyPlayerCenter.setCycleFlag(mInstanceID, flag);
	  }

	  public void setMuteFlag(int flag)
	  {
		  MyPlayerCenter.setMuteFlag(mInstanceID, flag);

	  }
	  
	  public void setMuteUIFlag(int flag)
	  {
		  MyPlayerCenter.setMuteUIFlag(mInstanceID, flag);
	  }

	  public void setNativeUIFlag(int flag)
	  {
		  MyPlayerCenter.setNativeUIFlag(mInstanceID, flag);
	  }

	  public void setProgressBarUIFlag(int flag)
	  {
		  MyPlayerCenter.setProgressBarUIFlag(mInstanceID, flag);
	  }

	  public void setRandomFlag(int flag)
	  {
		  MyPlayerCenter.setRandomFlag(mInstanceID, flag);
	  }

	  public void setSingleMedia(String jsonString)
	  {
		  Log.e(TAG, jsonString);
		  MyPlayerCenter.setSingleMedia(mInstanceID, jsonString);
	  }
	  public void setSingleOrPlaylistMode(int mode)
	  {
		  MyPlayerCenter.setSingleOrPlaylistMode(mInstanceID, mode);
		  
	  }
	  public void setSubtitileFlag(int flag)
	  {
		  MyPlayerCenter.setSubtitileFlag(mInstanceID, flag);
	  }

	  public void setSubtitlePID(int pid)
	  {
		  MyPlayerCenter.setSubtitlePID(mInstanceID, pid);
	  }

	  public void setVendorSpecificAttr(String attr)
	  {
		  MyPlayerCenter.setVendorSpecificAttr(mInstanceID, attr);
	  }

	  public void setVideoAlpha(int alpha)
	  {
		  MyPlayerCenter.setVideoAlpha(mInstanceID, alpha);
	  }

	  public void setVideoDisplayArea(int left, int top, int width, int height)
	  {
		  MyPlayerCenter.setVideoDisplayArea(mInstanceID, left,top,width,height);
	  }
	  public void setVideoDisplayMode(int mode)
	  {
		  MyPlayerCenter.setVideoDisplayMode(mInstanceID, mode);
	  }

	  public void setVolume(int vol)
	  {
		  MyPlayerCenter.setVolume(mInstanceID, vol);
	  }
	  public void stop()
	  {
		  MyPlayerCenter.stop(mInstanceID); 
	  }

	  public void switchAudioChannel()
	  {
		  MyPlayerCenter.switchAudioChannel(mInstanceID);
	  }
	  public void switchAudioTrack()
	  {
		  MyPlayerCenter.switchAudioTrack(mInstanceID);
	  }

	  public void switchSubtitle()
	  {
		  MyPlayerCenter.switchSubtitle(mInstanceID);
	  }
}
