/*
 * add by armite@126.com
 */

#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#include "jni.h"
#include "pluginbase.h"
#define MEDIAPLAYERPLUGIN_METHODNUM  100

class CMediaPlayerPlugin : CPlugin {
public:
    CMediaPlayerPlugin(NPP pNPInstance);
    ~CMediaPlayerPlugin();

    virtual bool hasProperty(NPIdentifier name);
    virtual bool setProperty(NPIdentifier name, const NPVariant *value);
    virtual bool getProperty(NPIdentifier name, const NPVariant *result);

    virtual bool hasMethod(NPIdentifier name);
    virtual bool invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result);
    virtual bool invokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result);

private:
    JNIEnv* m_jniEnv;
    jclass m_class;
    jobject m_object;

    NPIdentifier m_myNames[MEDIAPLAYERPLUGIN_METHODNUM];
    jmethodID    m_myMethods[MEDIAPLAYERPLUGIN_METHODNUM];

    NPIdentifier m_playByTimeNames;
    jmethodID    m_playByTimeMethods;
    jmethodID    m_playByTime2Methods;
    jmethodID    m_playByTime3Methods;
    jmethodID    m_playByTime4Methods;


//addBatchMedia
//addSingleMedia
//  
//clearAllMedia
//fastForward
//fastRewind
//getAllowTrickmodeFlag
//getAudioPID


//getAudioPIDs

//getAudioTrack


//getAudioTrackUIFlag


//getAudioVolumeUIFlag


//getChannelNoUIFlag

//getChannelNum

//getCurrentAudioChannel

//getCurrentIndex

//getCurrentPlayTime

//getEntryID

//getMediaCode

//getMediaCount

//getMediaDuration

//getMuteFlag

//getMuteUIFlag

//getNativePlayerInstance

//getNativePlayerInstanceID

//getNativePlayerinstanceID

//getNativeUIFlag

//getPlaybackMode

//getPlaylist

//getProgressBarUIFlag

//getSingleOrPlaylistMode


//getSubtitileFlag


//getSubtitle


//getSubtitlePID

//getSubtitlePIDs

//getVendorSpecificAttr

//getVideoAlpha

//getVideoDisplayHeight


//getVideoDisplayLeft


//getVideoDisplayMode

//getVideoDisplayTop


//getVideoDisplayWidth


//getVolume


//gotoEnd

//gotoStart

//initMediaPlayer

//joinChannel

//leaveChannel

//moveMediaByIndex

//moveMediaByIndex1

//moveMediaByOffset

//moveMediaToFirst

//moveMediaByOffset1

//moveMediaToFirst1

//moveMediaToLast

//moveMediaToLast1


//moveMediaToNext

//moveMediaToNext1

//moveMediaToPrevious

//moveMediaToPrevious1

//pause

//play

//playByTime


//playFromStart

//refreshVideoDisplay

//releaseMediaPlayer

//removeMediaByEntryID

//removeMediaByIndex

//resume

//selectFirst

//selectLast

//selectMediaByIndex

//selectMediaByOffset

//selectNext

//selectPrevious

//sendVendorSpecificCommand

//set

//setAllowTrickmodeFlag

//setAudioPID

//setAudioTrackUIFlag

//setAudioVolumeUIFlag

//setChannelNoUIFlag

//setCycleFlag

//setMuteFlag

//setMuteUIFlag

//setNativeUIFlag

//setProgressBarUIFlag

//setRandomFlag


//setSingleMedia

//setSingleOrPlaylistMode

//setSubtitileFlag

//setSubtitlePID

//setVendorSpecificAttr

//setVideoAlpha

//setVideoDisplayArea

//setVideoDisplayMode


//setVolume


//stop

//switchAudioChannel

//switchAudioTrack

//switchSubtitle














    
};

#endif // __PLUGIN_H__



