/*
 * add by armite@126.com
 */

#include "log.h"
#include "object.h"
#include "plugin.h"

#include <string.h>
#include <stdio.h>

const char *CPlugin::getMIMEDescription()
{
    return "application/MediaPlayer::MediaPlayer";
}

const char *CPlugin::getPluginName()
{
    return "MediaPlayer";
}

CPlugin* CPlugin::getPluginInstance(NPP instance, int16_t argc, char* argn[], char* argv[])
{
    return (CPlugin*)new CMediaPlayerPlugin(instance);
}

void CPlugin::delPluginInstance(NPP instance)
{
    CMediaPlayerPlugin* pPlugin = (CMediaPlayerPlugin*)instance->pdata;
    delete pPlugin;
}

//one name, one params array
static const char *MEDIAPLAYERMETHODS_NAME[MEDIAPLAYERPLUGIN_METHODNUM*2]={
    "addBatchMedia","(Ljava/lang/String;)V",
    "addSingleMedia","(ILjava/lang/String;)V",
    "bindNativePlayerInstance","(I)I",
    "clearAllMedia","()V",
    "fastForward","(I)V",
    "fastRewind","(I)V",
    "getAllowTrickmodeFlag","()I",
    "getAudioPID","()I",
    "getAudioPIDs","()Ljava/lang/String;",
    "getAudioTrack","()Ljava/lang/String;",
    "getAudioTrackUIFlag","()I",
    "getAudioVolumeUIFlag","()I",
    "getChannelNoUIFlag","()I",
    "getChannelNum","()I",
    "getCurrentAudioChannel","()Ljava/lang/String;",
    "getCurrentIndex","()I",
    "getCurrentPlayTime","()Ljava/lang/String;",
    "getEntryID","()Ljava/lang/String;",
    "getMediaCode","()Ljava/lang/String;",
    "getMediaCount","()I",
    "getMediaDuration","()I",
    "getMuteFlag","()I",
    "getMuteUIFlag","()I",
    "getNativePlayerInstance","()I",
    "getNativePlayerInstanceID","()I",
    "getNativePlayerinstanceID","()I",
    "getNativeUIFlag","()I",
    "getPlaybackMode","()Ljava/lang/String;",
    "getPlaylist","()Ljava/lang/String;",
    "getProgressBarUIFlag","()I",
    "getSingleOrPlaylistMode","()I",
    "getSubtitileFlag","()I",
    "getSubtitle","()Ljava/lang/String;",
    "getSubtitlePID","()I",
    "getSubtitlePIDs","()Ljava/lang/String;",
    "getVendorSpecificAttr","()Ljava/lang/String;",
    "getVideoAlpha","()I",
    "getVideoDisplayHeight","()I",
    "getVideoDisplayLeft","()I",
    "getVideoDisplayMode","()I",
    "getVideoDisplayTop","()I",
    "getVideoDisplayWidth","()I",
    "getVolume","()I",
    "gotoEnd","()V",
    "gotoStart","()V",
    "initMediaPlayer","(IIIIIIIIIIIIII)V",
    "joinChannel","(I)I",
    "leaveChannel","()V",
    "moveMediaByIndex","(Ljava/lang/String;I)V",
    "moveMediaByIndex1","(II)V",
    "moveMediaByOffset","(Ljava/lang/String;I)V",
    "moveMediaToFirst","(Ljava/lang/String;)V",
    "moveMediaByOffset1","(II)V",
    "moveMediaToFirst1","(I)V",
    "moveMediaToLast","(Ljava/lang/String;)V",
    "moveMediaToLast1","(I)V",
    "moveMediaToNext","(Ljava/lang/String;)V",
    "moveMediaToNext1","(I)V",
    "moveMediaToPrevious","(Ljava/lang/String;)V",
    "moveMediaToPrevious1","(I)V",
    "pause","()V",
    "play","()V",
    "playFromStart","()V",
    "refreshVideoDisplay","()V",
    "releaseMediaPlayer","(I)I",
    "removeMediaByEntryID","(Ljava/lang/String;)V",
    "removeMediaByIndex","(I)V",
    "resume","()V",
    "selectFirst","()V",
    "selectLast","()V",
    "selectMediaByIndex","(I)V",
    "selectMediaByOffset","(I)V",
    "selectNext","()V",
    "selectPrevious","()V",
    "sendVendorSpecificCommand","(Ljava/lang/String;)V",
    "set","(Ljava/lang/String;Ljava/lang/String;)V",
    "setAllowTrickmodeFlag","(I)V",
    "setAudioPID","(I)V",
    "setAudioTrackUIFlag","(I)V",
    "setAudioVolumeUIFlag","(I)V",
    "setChannelNoUIFlag","(I)V",
    "setCycleFlag","(I)V",
    "setMuteFlag","(I)V",
    "setMuteUIFlag","(I)V",
    "setNativeUIFlag","(I)V",
    "setProgressBarUIFlag","(I)V",
    "setRandomFlag","(I)V",
    "setSingleMedia","(Ljava/lang/String;)V",
    "setSingleOrPlaylistMode","(I)V",
    "setSubtitileFlag","(I)V",
    "setSubtitlePID","(I)V",
    "setVendorSpecificAttr","(Ljava/lang/String;)V",
    "setVideoAlpha","(I)V",
    "setVideoDisplayArea","(IIII)V",
    "setVideoDisplayMode","(I)V",
    "setVolume","(I)V",
    "stop","()V",
    "switchAudioChannel","()V",
    "switchAudioTrack","()V",
    "switchSubtitle","()V"
};

CMediaPlayerPlugin::CMediaPlayerPlugin(NPP pNPInstance) 
: CPlugin(pNPInstance)
{
    m_jniEnv = (JNIEnv*)NPN_GetJavaEnv();
    jclass clazz = m_jniEnv->FindClass("com/armite/webkit/plug/MediaPlayer");
    m_class = (jclass)m_jniEnv->NewGlobalRef(clazz);

    jobject object = m_jniEnv->AllocObject(m_class);
    m_object = m_jniEnv->NewGlobalRef(object);

    NP_TRACE("CMediaPlayerPlugin begin\n");
    for(int i=0;i<MEDIAPLAYERPLUGIN_METHODNUM;i++){
        m_myNames[i]=NPN_GetStringIdentifier(MEDIAPLAYERMETHODS_NAME[2*i]);
        m_myMethods[i]=m_jniEnv->GetMethodID(m_class,MEDIAPLAYERMETHODS_NAME[2*i],MEDIAPLAYERMETHODS_NAME[2*i+1]);
    }
/*
    "playByTime","(ILjava/lang/String;I)V",
    "playByTime","(ILjava/lang/String;)V",
    "playByTime","(III)V",
    "playByTime","(II)V",
*/
    m_playByTimeNames = NPN_GetStringIdentifier("playByTime");
    //NP_TRACE("CMediaPlayerPlugin 1\n");
    m_playByTimeMethods = m_jniEnv->GetMethodID(m_class, "playByTime", "(ILjava/lang/String;I)V");
    //NP_TRACE("CMediaPlayerPlugin 2\n");
    m_playByTime2Methods = m_jniEnv->GetMethodID(m_class, "playByTime2", "(ILjava/lang/String;)V");
//    NP_TRACE("CMediaPlayerPlugin 3\n");
    m_playByTime3Methods = m_jniEnv->GetMethodID(m_class, "playByTime3", "(III)V");
  //  NP_TRACE("CMediaPlayerPlugin 4\n");
    m_playByTime4Methods = m_jniEnv->GetMethodID(m_class, "playByTime4", "(II)V");

    NP_TRACE("CMediaPlayerPlugin end\n");
}

CMediaPlayerPlugin::~CMediaPlayerPlugin()
{
    if (m_class)
        m_jniEnv->DeleteGlobalRef(m_class);
    if (m_object)
        m_jniEnv->DeleteGlobalRef(m_object);
}

bool CMediaPlayerPlugin::setProperty(NPIdentifier name, const NPVariant *value)
{
    UNIMPLEMENTED();
    return false;
}

bool CMediaPlayerPlugin::hasProperty(NPIdentifier name)
{
    return false;
}

bool CMediaPlayerPlugin::getProperty(NPIdentifier name, const NPVariant *result)
{
    UNIMPLEMENTED();
    return false;
}

bool CMediaPlayerPlugin::hasMethod(NPIdentifier name)
{
    NP_TRACE("CMediaPlayerPlugin hasMethod:%s\n",NPN_UTF8FromIdentifier(name));
    if(name==m_playByTimeNames)return true;
    for(int i=0;i<MEDIAPLAYERPLUGIN_METHODNUM;i++){
        if(m_myNames[i]==name)return true;
    }
    return false;
}

bool CMediaPlayerPlugin::invoke(NPIdentifier name, const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    NP_TRACE("CMediaPlayerPlugin invoke:%s\n",NPN_UTF8FromIdentifier(name));
    if(name==m_playByTimeNames){
/*
    "playByTime","(ILjava/lang/String;I)V",
    "playByTime","(ILjava/lang/String;)V",
    "playByTime","(III)V",
    "playByTime","(II)V",
*/
        if (argCount ==2){
		if(NPVARIANT_IS_DOUBLE(args[0]) && NPVARIANT_IS_STRING(args[1])){
                  int tmpval1 = NPVARIANT_TO_DOUBLE(args[0]);
                  NPString msg2 = NPVARIANT_TO_STRING(args[1]);
                  jstring tmpval2 = m_jniEnv->NewStringUTF(msg2.UTF8Characters);
                  m_jniEnv->CallVoidMethod(m_object, m_playByTime2Methods, tmpval1,tmpval2);
                  m_jniEnv->DeleteLocalRef(tmpval2);
                return true;
               }
	       else if(NPVARIANT_IS_DOUBLE(args[0]) && NPVARIANT_IS_DOUBLE(args[1])){
                  int tmpval1 = NPVARIANT_TO_DOUBLE(args[0]);
                  int tmpval2 = NPVARIANT_TO_DOUBLE(args[1]);
                  m_jniEnv->CallVoidMethod(m_object, m_playByTime4Methods, tmpval1,tmpval2);
                return true;
               }
      
       }else if(argCount==3){

	if(NPVARIANT_IS_DOUBLE(args[0]) && NPVARIANT_IS_STRING(args[1])&&NPVARIANT_IS_DOUBLE(args[2]) ){
                  int tmpval1 = NPVARIANT_TO_DOUBLE(args[0]);
                  NPString msg2 = NPVARIANT_TO_STRING(args[1]);
                  jstring tmpval2 = m_jniEnv->NewStringUTF(msg2.UTF8Characters);
                  int tmpval3 = NPVARIANT_TO_DOUBLE(args[2]);
                  m_jniEnv->CallVoidMethod(m_object, m_playByTimeMethods, tmpval1,tmpval2,tmpval3);
                  m_jniEnv->DeleteLocalRef(tmpval2);
                return true;
               }
	       else if(NPVARIANT_IS_DOUBLE(args[0]) && NPVARIANT_IS_DOUBLE(args[1])&&NPVARIANT_IS_DOUBLE(args[2])){
                  int tmpval1 = NPVARIANT_TO_DOUBLE(args[0]);
                  int tmpval2 = NPVARIANT_TO_DOUBLE(args[1]);
                  int tmpval3 = NPVARIANT_TO_DOUBLE(args[2]);
                  m_jniEnv->CallVoidMethod(m_object, m_playByTime3Methods, tmpval1,tmpval2);
                return true;
               }    

      }

    }else{
    for(int i=0;i<MEDIAPLAYERPLUGIN_METHODNUM;i++){
        if(m_myNames[i]==name){
            //call back
            char *tmpmethodname = (char*)MEDIAPLAYERMETHODS_NAME[2*i];
            char * tmpmethodparamdef = (char*)MEDIAPLAYERMETHODS_NAME[2*i+1];
            /*NP_TRACE("CMediaPlayerPlugin invoke:%s %s\n",tmpmethodname, tmpmethodparamdef );*/

            if(strcmp(tmpmethodparamdef,"()V")==0){
                /*
                   "clearAllMedia","()V",
                   "gotoEnd","()V",
                   "gotoStart","()V",
                   "leaveChannel","()V",
                   "pause","()V",
                   "play","()V",
                   "playFromStart","()V",
                   "refreshVideoDisplay","()V",
                   "resume","()V",
                   "selectFirst","()V",
                   "selectLast","()V",
                   "selectNext","()V",
                   "selectPrevious","()V",
                   "stop","()V",
                   "switchAudioChannel","()V",
                   "switchAudioTrack","()V",
                   "switchSubtitle","()V"
                 */
                m_jniEnv->CallVoidMethod(m_object, m_myMethods[i]);
                VOID_TO_NPVARIANT(*result);	
                return true;
            } else if(strcmp(tmpmethodparamdef,"(I)V")==0){
                /*"fastForward","(I)V",
                  "fastRewind","(I)V",
                  "moveMediaToFirst1","(I)V",
                  "moveMediaToLast1","(I)V",
                  "moveMediaToNext1","(I)V",
                  "moveMediaToPrevious1","(I)V",
                  "removeMediaByIndex","(I)V",
                  "selectMediaByIndex","(I)V",
                  "selectMediaByOffset","(I)V",
                  "setAllowTrickmodeFlag","(I)V",
                  "setAudioPID","(I)V",
                  "setAudioTrackUIFlag","(I)V",
                  "setAudioVolumeUIFlag","(I)V",
                  "setChannelNoUIFlag","(I)V",
                  "setCycleFlag","(I)V",
                  "setMuteFlag","(I)V",
                  "setMuteUIFlag","(I)V",
                  "setNativeUIFlag","(I)V",
                  "setProgressBarUIFlag","(I)V",
                  "setRandomFlag","(I)V",
                  "setSingleOrPlaylistMode","(I)V",
                 */
                if (argCount != 1 || !NPVARIANT_IS_DOUBLE(args[0]))
                    return false;
                int tmpval = NPVARIANT_TO_DOUBLE(args[0]);
                m_jniEnv->CallVoidMethod(m_object, m_myMethods[i], tmpval);
                VOID_TO_NPVARIANT(*result);
                return true;
            } else if(strcmp(tmpmethodparamdef,"(I)I")==0){
                /*
                   "bindNativePlayerInstance","(I)I",
                   "joinChannel","(I)I",
                   "releaseMediaPlayer","(I)I",
                   "setSubtitileFlag","(I)V",
                   "setSubtitlePID","(I)V",
                   "setVideoAlpha","(I)V",
                   "setVideoDisplayMode","(I)V",
                   "setVolume","(I)V",

                 */
                if (argCount != 1 || !NPVARIANT_IS_DOUBLE(args[0]))
                    return false;
                int tmpval = NPVARIANT_TO_DOUBLE(args[0]);
                int tmpresult = m_jniEnv->CallIntMethod(m_object, m_myMethods[i], tmpval);
                INT32_TO_NPVARIANT(tmpresult,*result);
                return true;
            } else if(strcmp(tmpmethodparamdef,"(II)V")==0){
                /*
                   "moveMediaByIndex1","(II)V",
                   "moveMediaByOffset1","(II)V",
	           "playByTime2Int","(II)V",
                 */
                if (argCount != 2 || !NPVARIANT_IS_DOUBLE(args[0])|| !NPVARIANT_IS_DOUBLE(args[1]))
                    return false;
                int tmpval1 = NPVARIANT_TO_DOUBLE(args[0]);
                int tmpval2 = NPVARIANT_TO_DOUBLE(args[1]);
                m_jniEnv->CallVoidMethod(m_object, m_myMethods[i], tmpval1,tmpval2);
                VOID_TO_NPVARIANT(*result);
                return true;
            } 
            else if(strcmp(tmpmethodparamdef,"(III)V")==0){
            /* "playByTimeInt","(III)V",*/

    if (argCount != 3 || !NPVARIANT_IS_DOUBLE(args[0])|| !NPVARIANT_IS_DOUBLE(args[1]) || !NPVARIANT_IS_DOUBLE(args[2]))
                    return false;
                int tmpval1 = NPVARIANT_TO_DOUBLE(args[0]);
                int tmpval2 = NPVARIANT_TO_DOUBLE(args[1]);
                int tmpval3 = NPVARIANT_TO_DOUBLE(args[2]);
                m_jniEnv->CallVoidMethod(m_object, m_myMethods[i], tmpval1,tmpval2,tmpval3);
                VOID_TO_NPVARIANT(*result);
                return true;


            }
		else if(strcmp(tmpmethodparamdef,"(IIII)V")==0){
                /*
                   "setVideoDisplayArea","(IIII)V",
                 */
                if (argCount != 4 || !NPVARIANT_IS_DOUBLE(args[0])|| !NPVARIANT_IS_DOUBLE(args[1]) || !NPVARIANT_IS_DOUBLE(args[2]) || !NPVARIANT_IS_DOUBLE(args[3]))
                    return false;
                int tmpval1 = NPVARIANT_TO_DOUBLE(args[0]);
                int tmpval2 = NPVARIANT_TO_DOUBLE(args[1]);
                int tmpval3 = NPVARIANT_TO_DOUBLE(args[2]);
                int tmpval4 = NPVARIANT_TO_DOUBLE(args[3]);
                m_jniEnv->CallVoidMethod(m_object, m_myMethods[i], tmpval1,tmpval2,tmpval3,tmpval4);

                VOID_TO_NPVARIANT(*result);
                return true;

            } else if(strcmp(tmpmethodparamdef,"(IIIIIIIIIIIIII)V")==0){
                /*
                   "initMediaPlayer","(IIIIIIIIIIIIII)V",
                 */
                if (argCount != 14 || !NPVARIANT_IS_DOUBLE(args[0]) || !NPVARIANT_IS_DOUBLE(args[1]) || 
                    !NPVARIANT_IS_DOUBLE(args[2]) || !NPVARIANT_IS_DOUBLE(args[3]) || !NPVARIANT_IS_DOUBLE(args[4]) ||
                    !NPVARIANT_IS_DOUBLE(args[5])|| !NPVARIANT_IS_DOUBLE(args[6]) || !NPVARIANT_IS_DOUBLE(args[7]) ||
                    !NPVARIANT_IS_DOUBLE(args[8])|| !NPVARIANT_IS_DOUBLE(args[9]) || !NPVARIANT_IS_DOUBLE(args[10]) ||
                    !NPVARIANT_IS_DOUBLE(args[11])|| !NPVARIANT_IS_DOUBLE(args[12]) || !NPVARIANT_IS_DOUBLE(args[13]))
                    return false;
                int tmpval1 = NPVARIANT_TO_DOUBLE(args[0]);
                int tmpval2 = NPVARIANT_TO_DOUBLE(args[1]);
                int tmpval3 = NPVARIANT_TO_DOUBLE(args[2]);
                int tmpval4 = NPVARIANT_TO_DOUBLE(args[3]);
                int tmpval5 = NPVARIANT_TO_DOUBLE(args[4]);
                int tmpval6 = NPVARIANT_TO_DOUBLE(args[5]);
                int tmpval7 = NPVARIANT_TO_DOUBLE(args[6]);
                int tmpval8 = NPVARIANT_TO_DOUBLE(args[7]);
                int tmpval9 = NPVARIANT_TO_DOUBLE(args[8]);
                int tmpval10 = NPVARIANT_TO_DOUBLE(args[9]);
                int tmpval11 = NPVARIANT_TO_DOUBLE(args[10]);
                int tmpval12 = NPVARIANT_TO_DOUBLE(args[11]);
                int tmpval13 = NPVARIANT_TO_DOUBLE(args[12]);
                int tmpval14 = NPVARIANT_TO_DOUBLE(args[13]);

                m_jniEnv->CallVoidMethod(m_object, m_myMethods[i], tmpval1,tmpval2,tmpval3,tmpval4,tmpval5,tmpval6,tmpval7,tmpval8,tmpval9,tmpval10,
                        tmpval11,tmpval12,tmpval13,tmpval14);

                VOID_TO_NPVARIANT(*result);
                return true;

            } else if(strcmp(tmpmethodparamdef,"()I")==0){
                /*
                   "getAllowTrickmodeFlag","()I",
                   "getAudioPID","()I",
                   "getAudioTrackUIFlag","()I",
                   "getAudioVolumeUIFlag","()I",
                   "getChannelNoUIFlag","()I",
                   "getChannelNum","()I",
                   "getCurrentIndex","()I",
                   "getMediaCount","()I",
                   "getMediaDuration","()I",
                   "getMuteFlag","()I",
                   "getMuteUIFlag","()I",
                   "getNativePlayerInstance","()I",
                   "getNativePlayerInstanceID","()I",
                   "getNativePlayerinstanceID","()I",
                   "getNativeUIFlag","()I",
                   "getProgressBarUIFlag","()I",
                   "getSingleOrPlaylistMode","()I",
                   "getSubtitileFlag","()I",
                   "getSubtitlePID","()I",
                   "getVideoAlpha","()I",
                   "getVideoDisplayHeight","()I",
                   "getVideoDisplayLeft","()I",
                   "getVideoDisplayMode","()I",
                   "getVideoDisplayTop","()I",
                   "getVideoDisplayWidth","()I",
                   "getVolume","()I",
                 */

                int tmpresult = m_jniEnv->CallIntMethod(m_object, m_myMethods[i]);
                INT32_TO_NPVARIANT(tmpresult,*result);
                return true;

            } else if(strcmp(tmpmethodparamdef,"(Ljava/lang/String;)V")==0){
                /*"addBatchMedia","(Ljava/lang/String;)V",
                  "moveMediaToFirst","(Ljava/lang/String;)V",
                  "moveMediaToLast","(Ljava/lang/String;)V",
                  "moveMediaToNext","(Ljava/lang/String;)V",
                  "moveMediaToPrevious","(L/java/lang/String;)V",
                  "removeMediaByEntryID","(Ljava/lang/String;)V",
                  "sendVendorSpecificCommand","(Ljava/lang/String;)V",
                  "setVendorSpecificAttr","(Ljava/lang/String;)V",

                 */
                if (argCount != 1 || !NPVARIANT_IS_STRING(args[0]))
                    return false;
                NPString msg = NPVARIANT_TO_STRING(args[0]);
                jstring jmsg = m_jniEnv->NewStringUTF(msg.UTF8Characters);
                m_jniEnv->CallVoidMethod(m_object, m_myMethods[i], jmsg);
                m_jniEnv->DeleteLocalRef(jmsg);
                return true;
            } else if(strcmp(tmpmethodparamdef,"()Ljava/lang/String;")==0){
                /*"getAudioPIDs","()Ljava/lang/String;",
                  "getAudioTrack","()Ljava/lang/String;",
                  "getCurrentAudioChannel","()Ljava/lang/String;",
                  "getCurrentPlayTime","()Ljava/lang/String;",
                  "getEntryID","()Ljava/lang/String;",
                  "getMediaCode","()Ljava/lang/String;",
                  "getPlaybackMode","()Ljava/lang/String;",
                  "getPlaylist","()Ljava/lang/String;",
                  "getSubtitle","()Ljava/lang/String;",
                  "getSubtitlePIDs","()Ljava/lang/String;",
                  "getVendorSpecificAttr","()Ljava/lang/String;",

                 */		

                jstring ret = (jstring)m_jniEnv->CallObjectMethod(m_object, m_myMethods[i]);
                const char* v = (char*)m_jniEnv->GetStringUTFChars(ret, JNI_FALSE);
                const char* s = strdup(v);
                m_jniEnv->ReleaseStringUTFChars(ret, v);
                STRINGZ_TO_NPVARIANT(s, *result);
                return true;

            } else if(strcmp(tmpmethodparamdef,"(Ljava/lang/String;I)V")==0){
                /*
                   "moveMediaByOffset","(Ljava/lang/String;I)V",
                   "moveMediaByIndex","(Ljava/lang/String;I)V",
                   "setSingleMedia","(Ljava/lang/String;)V",
                 */
                if (argCount != 2 || !NPVARIANT_IS_STRING(args[0])|| !NPVARIANT_IS_DOUBLE(args[1]))
                    return false;
                NPString msg1 = NPVARIANT_TO_STRING(args[0]);
                jstring tmpval1 = m_jniEnv->NewStringUTF(msg1.UTF8Characters);
                int tmpval2 = NPVARIANT_TO_DOUBLE(args[1]);
                m_jniEnv->CallVoidMethod(m_object, m_myMethods[i], tmpval1,tmpval2);
                m_jniEnv->DeleteLocalRef(tmpval1);
                return true;
            } else if(strcmp(tmpmethodparamdef,"(Ljava/lang/String;Ljava/lang/String;)V")==0){
                /*"set","(Ljava/lang/String;Ljava/lang/String;)V",

                 */
                if (argCount != 2 || !NPVARIANT_IS_STRING(args[0])|| !NPVARIANT_IS_STRING(args[1]))
                    return false;
                NPString msg1 = NPVARIANT_TO_STRING(args[0]);
                jstring tmpval1 = m_jniEnv->NewStringUTF(msg1.UTF8Characters);

                NPString msg2 = NPVARIANT_TO_STRING(args[1]);
                jstring tmpval2 = m_jniEnv->NewStringUTF(msg2.UTF8Characters);

                m_jniEnv->CallVoidMethod(m_object, m_myMethods[i], tmpval1,tmpval2);
                m_jniEnv->DeleteLocalRef(tmpval1);
                m_jniEnv->DeleteLocalRef(tmpval2);
                return true;

            } else if(strcmp(tmpmethodparamdef,"(ILjava/lang/String;I)V")==0){
                /*"playByTime","(ILjava/lang/String;I)V",
                 */
                if (argCount !=3  || !NPVARIANT_IS_DOUBLE(args[0])|| !NPVARIANT_IS_STRING(args[1])||!NPVARIANT_IS_DOUBLE(args[2]))
                    return false;
                int tmpval1 = NPVARIANT_TO_DOUBLE(args[0]);

                NPString msg2 = NPVARIANT_TO_STRING(args[1]);
                jstring tmpval2 = m_jniEnv->NewStringUTF(msg2.UTF8Characters);

                int tmpval3 = NPVARIANT_TO_DOUBLE(args[3]);
                m_jniEnv->CallVoidMethod(m_object, m_myMethods[i], tmpval1,tmpval2,tmpval3);
                m_jniEnv->DeleteLocalRef(tmpval2);
                return true;
            } else if(strcmp(tmpmethodparamdef,"(ILjava/lang/String;)V")==0){
                /* "addSingleMedia","(ILjava/lang/String;)V",
		"playByTime2","(ILjava/lang/String;)V",
                 */
                if (argCount !=2  || !NPVARIANT_IS_DOUBLE(args[0])|| !NPVARIANT_IS_STRING(args[1]))
                    return false;
                int tmpval1 = NPVARIANT_TO_DOUBLE(args[0]);
                NPString msg2 = NPVARIANT_TO_STRING(args[1]);
                jstring tmpval2 = m_jniEnv->NewStringUTF(msg2.UTF8Characters);
                m_jniEnv->CallVoidMethod(m_object, m_myMethods[i], tmpval1,tmpval2);
                m_jniEnv->DeleteLocalRef(tmpval2);
                return true;
            } else {
                return false;
            }
            break;
        }
    }
   }

    return false;
}

bool CMediaPlayerPlugin::invokeDefault(const NPVariant *args, uint32_t argCount, NPVariant *result)
{
    NP_TRACE("CMediaPlayerPlugin invokeDefault\n");
    return true;
}






