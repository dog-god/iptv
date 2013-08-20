package com.armite.webkit.plug;

import java.net.InetAddress;
import java.net.NetworkInterface;
import java.net.SocketException;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

import android.content.Context;
import android.util.Log;

public class Authentication {
	public static Map mSvcEntryList = new HashMap();
	public static Map mChannelList = new HashMap();
	public static Map mCfgList = new HashMap();
	public static String mMac;
	public static String mStbID = "01234567890123456789012345678901";
	public static String mUserID = "19101389";
	public static String mPassword = "123456";
	public static String mReserved;
	public static String mIP = "";

	public static String mNTPDomain = "";
	public static String mUpgradeDomain = "";
	public static String mUpgradeDomainBackup = "";
	public static String mEPGDomain = "";
	public static String mTvmsResService = "";
	public static String mTvmsVerifyCode = "";
	public static int mTvmsResInterval = 60;
	public static String mEpgGroupNMB = "";
	public static String mUserToken = "";
	public static String mMode = "";

	public Context mContext;

	// http://iptvauth.online.sh.cn:7001/iptv3a/UserAuthenticationAction.do
	// 设备号:01234567890123456789012345678901
	// 帐号19101389
	// 密码123456

	public String CTCGetAuthInfo(String encryptToken) {

		String tmpret = "";
		// 3DES(Random+“$”+EncryToken+”$”+UserID +”$”+STBID+”$”+IP+”$”+MAC+”$”+
		// Reserved+ ”$”+ “CTC”)
		Random localRandom = new Random();
		String tmpRandom = ""
				+ Long.valueOf(Math.abs(localRandom.nextLong()) % 10000000L);
		this.mIP = getLocalIpAddress();
		tmpret = CTCAuthHelper.GenerateAuthInfo(this.mPassword, encryptToken,
				tmpRandom, this.mUserID, this.mStbID, this.mIP, this.mMac);
		return tmpret;
	}

	public String CTCGetConfig(String paramName) {
		if (this.mCfgList.containsKey(paramName)) {
			return (String) this.mCfgList.get(paramName);
		}
		return "";
	}

	public void CTCSetConfig(String paramName, String paramValue) {
		if (paramName == null)
			paramName = "";
		if (paramName.equals("Channel")) {
			if (this.mChannelList == null)
				this.mChannelList = new HashMap();
			LiveChannel tmpchannel = new LiveChannel(paramValue);
			this.mChannelList.put(Integer.toString(tmpchannel.UserChannelID),
					tmpchannel);

		} else if (paramName.equals("ServiceEntry")) {

			int m = paramValue.indexOf("URL=\"");
			int n = paramValue.indexOf("\",", m + 6);
			String str1 = paramValue.substring(m + 5, n);
			int i1 = paramValue.indexOf("HotKey=\"");
			int i2 = paramValue.indexOf("\",", i1 + 9);
			String str2 = paramValue.substring(i1 + 8, i2);
			this.mCfgList.put(str2, str1);

		} else if (paramName.equals("NTPDomain")) {
			this.mNTPDomain = paramValue;
			// 发送消息给系统进行更新

		} else if (paramName.equals("UpgradeDomain")) {
			this.mUpgradeDomain = paramValue;
		} else if (paramName.equals("UpgradeDomainBackup")) {

			this.mUpgradeDomainBackup = paramValue;
		} else if (paramName.equals("EPGDomain")) {

			this.mEPGDomain = paramValue;
		} else if (paramName.equals("SetEpgMode")) {

		} else if (paramName.equals("Resignon")) {

		} else if (paramName.equals("TvmsResService")) {
			mTvmsResService = paramValue;
		} else if (paramName.equals("TvmsVerifyCode")) {
			mTvmsVerifyCode = paramValue;
		} else if (paramName.equals("TvmsResInterval")) {
			try {
				mTvmsResInterval = Integer.parseInt(paramValue);
			} catch (Exception ex) {

			}
		} else if (paramName.equals("EpgGroupNMB")) {
			mEpgGroupNMB = paramValue;
		} else if (paramName.equals("EpgGroupNMB")) {
			mEpgGroupNMB = paramValue;
		} else if (paramName.equals("UserToken")) {
			mUserToken = paramValue;
		} else if (paramName.equals("Mode")) {
			mMode = paramValue;
		}
		Log.i("Authentication", paramName + " : " + paramValue);
		this.mCfgList.put(paramName, paramValue);

	}

	public boolean CTCStartUpdate() {

		return true;
	}

	public void login() {

		if (this.mCfgList != null)
			this.mCfgList.clear();
		if (this.mSvcEntryList != null)
			this.mSvcEntryList.clear();
		if (this.mChannelList != null)
			this.mChannelList.clear();
		// Now Login
	}

	public void setAuthParam(String userID, String password, String stbID,
			String mac, String reserved) {
		this.mUserID = userID;
		this.mPassword = password;
		this.mStbID = stbID;
		this.mMac = mac;
		this.mReserved = reserved;
	}

	public String getUserToken() {
		return CTCGetConfig("UserToken");
	}

	public String getVersion() {

		String tmpver = "";
		try {
			tmpver = this.mContext.getPackageManager().getPackageInfo(
					this.mContext.getPackageName(), 0).versionName;
		} catch (Exception ex) {
			Log.e("Authentication", ex.getMessage());
		}
		return tmpver;
	}

	public String getLocalIpAddress()

	{
		try {
			for (Enumeration<NetworkInterface> en = NetworkInterface
					.getNetworkInterfaces(); en.hasMoreElements();) {
				NetworkInterface intf = en.nextElement();
				for (Enumeration<InetAddress> enumIpAddr = intf
						.getInetAddresses(); enumIpAddr.hasMoreElements();) {
					InetAddress inetAddress = enumIpAddr.nextElement();
					if (!inetAddress.isLoopbackAddress()) {
						return inetAddress.getHostAddress().toString();
					}
				}
			}
		} catch (SocketException ex) {
			Log.e("WifiPreference IpAddress", ex.toString());
		}
		return null;
	}

}
