package com.armite.webkit.plug;

public class PlayerConst {
	
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
	
	
	
	private static final int STATUS_IDLE = 0;
	private static final int STATUS_INITIALIZED = 1;
	private static final int STATUS_PREPARED = 2;
	private static final int STATUS_PREPARING = 3;
	private static final int STATUS_STARTED = 4;
	private static final int STATUS_STOPPED = 5;
	private static final int STATUS_PAUSED = 6;
	private static final int STATUS_PLAYBACKCOMPLETED = 7;
	private static final int STATUS_ERROR = 8;
	private static final int STATUS_END = 9;
}
