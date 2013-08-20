package com.armite.webkit.plug;

public class CTCAuthHelper {
	public static  String GenerateAuthInfo(String password,String EncryToken,String Random,String UserID,String STBID,String IP,String MAC){
		String tmpret="";
		String Reserved="Reserved";
		String tmpdata=Random+"$"+EncryToken+"$"+UserID +"$"+STBID+"$"+IP+"$"+MAC+"$"+ Reserved+ "$"+ "CTC";
		String tmpkey = password;
		try{
			if(tmpkey.length()>24)tmpkey.substring(0,24);
			else{
				for (int i = tmpkey.length(); i < 24; i++){
   		 	    tmpkey = tmpkey + "0";
				}
			}
			
			byte[] tmpresuls = SecretKeyUtil.crypt(tmpkey.getBytes("ASCII"), tmpdata.getBytes("ASCII"), SecretKeyUtil.DES3);
			if(tmpresuls!=null)tmpret = SecretKeyUtil.byteToHexString(tmpresuls);
		}catch(Exception ex){
			
		}
		return tmpret;
	}
	public static String DecryptAuthInfo(String password,String data){	
		String tmpret="";
		String Reserved="Reserved";
		String tmpkey = password;
		try{
			byte[] tmpdata = SecretKeyUtil.hexToBytes(data);
			if(tmpkey.length()>24)tmpkey.substring(0,24);
			else{
				for (int i = tmpkey.length(); i < 24; i++){
   		 	    tmpkey = tmpkey + "0";
				}
			}
			byte[] tmpresuls = SecretKeyUtil.decrypt(tmpkey.getBytes("ASCII"), tmpdata, SecretKeyUtil.DES3);
			if(tmpresuls!=null)tmpret = new String(tmpresuls);
		}catch(Exception ex){
			
		}
		return tmpret;
	}
}
