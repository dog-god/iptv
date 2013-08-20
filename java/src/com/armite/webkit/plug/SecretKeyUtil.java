package com.armite.webkit.plug;
import java.security.spec.KeySpec;

import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.DESKeySpec;
import javax.crypto.spec.DESedeKeySpec; 
public class SecretKeyUtil {
	   private static final String ECB_PKCS5_PADDING = "/ECB/PKCS5Padding";
	    public static final String AES = "AES";
	    public static final String DES = "DES";
	    public static final String DES3 = "DESede";

	    /**
	     *  º”√‹
	     * 
	     * @param key
	     * @param data
	     * @return
	     */
	    public static byte[] crypt(byte key[], byte data[], String type) {

	        try {
	            KeySpec ks;
	            SecretKeyFactory kf;
	            SecretKey ky ;
	            if(type.equals(DES3))    
	            {        
	            	kf = SecretKeyFactory.getInstance(DES3);
	            	DESedeKeySpec dks = new DESedeKeySpec(key);
								ky = kf.generateSecret(dks);
	            }
	            else 
	            {
	            	kf = SecretKeyFactory.getInstance(type);
	            	ks = new DESKeySpec(key);     
	            	ky = kf.generateSecret(ks);      
	            }

	            Cipher c = Cipher.getInstance(type + ECB_PKCS5_PADDING);
	            c.init(Cipher.ENCRYPT_MODE, ky);
	            return c.doFinal(data);
	        } catch (Exception e) {
	            e.printStackTrace();
	            return null;
	        }
	    }

	    /**
	     *  Ω‚√‹
	     * 
	     * @param key
	     * @param data
	     * @return
	     */

	    public static byte[] decrypt(byte key[], byte data[], String type) {

	        try {         
	            KeySpec ks;
	            SecretKeyFactory kf;
	            SecretKey ky ;
	            if(type.equals(DES3))    
	            {        
	            	kf = SecretKeyFactory.getInstance(DES3);
	            	DESedeKeySpec dks = new DESedeKeySpec(key);
								ky = kf.generateSecret(dks);
	            }
	            else 
	            {
	            	kf = SecretKeyFactory.getInstance(type);
	            	ks = new DESKeySpec(key);     
	            	ky = kf.generateSecret(ks);      
	            }

	            Cipher c = Cipher.getInstance(type + ECB_PKCS5_PADDING);
	            c.init(Cipher.DECRYPT_MODE, ky);
	            return c.doFinal(data);
	        } catch (Exception e) {
	            e.printStackTrace();
	            return null;
	        }
	    }
	    

	    public static byte[] hexToBytes(String str) {
	        if (str == null) {
	            return null;
	        } else if (str.length() < 2) {
	            return null;
	        } else {
	            int len = str.length() / 2;
	            byte[] buffer = new byte[len];
	            for (int i = 0; i < len; i++) {
	                buffer[i] = (byte) Integer.parseInt(str.substring(i * 2,
	                        i * 2 + 2), 16);
	            }
	            return buffer;
	        }
	    }

	    public static String byteToHexString(byte[] bArray) {
	        StringBuffer sb = new StringBuffer();
	        String sTemp;
	        for (int i = 0; i < bArray.length; i++) {
	            sTemp = Integer.toHexString(0xFF & bArray[i]);
	            if (sTemp.length() < 2) {
	                sb.append(0);
	            }
	            sb.append(sTemp.toUpperCase());
	        }
	        return sb.toString();
	    }
	 

	    public static void main(String[] args) {

		      String tmpkey;
		      String data;
		      byte[] byteData= null;
		      byte[] r = null;
	        // String data =
	        // "Authenticator=AES(Random$UserAccount$TVID$IP$TVProfileString$BizField$TimeStamp$BesTV)";
	        /*String data = "722edfe7c854406ad00e9406973749b912624d7abb3cda73376fa48cf5795a9d11f97e3b04f7dde8";
	        String key = "12345678";

	        for (int i = key.length(); i < 24; i++) {
	            key = key + "0";
	        }

	        byte[] byteData = SecretKeyUtil.hexToBytes(data);

	        byte[] r = SecretKeyUtil.decrypt(key.getBytes(), byteData, DES);

	        System.out.println(new String(r));*/
	        if(args.length>2)
	        {
	        	try
	        	{
	        	 if(args[0].equals("encrypt")||args[0].equals("crypt"))
	        	 {
	        	 	   	tmpkey = args[1];
	        	 	   	data   = args[2];
	        				for (int i = tmpkey.length(); i < 24; i++){
	           		 	    tmpkey = tmpkey + "0";
	        				}
	        				System.out.println("key adjust:"+tmpkey);
	        				/*
								  char[] charArray = new char[]{0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08};
	        				int padLength = 8 - (data.length()%8);  
	  							for (int itmp=0; itmp<padLength; itmp++) {
	  									data += charArray[padLength-1];
	  							}*/
									System.out.println("data:"+data);
									System.out.println("datalen:"+data.length());
	        				byteData = data.getBytes();
	        				//pkcs5padding        					
	        				System.out.println("keybytes:"+tmpkey.getBytes("ASCII").length);
	        				System.out.println("byteData:"+byteData.length);
	        			
	        				r = SecretKeyUtil.crypt(tmpkey.getBytes(),byteData , DES3);
	        				
	        				System.out.println(byteToHexString(r));

	        	 }
	        	 else
	        	 {
	        	 	 	  	tmpkey = args[1];
	        	 	   	data   = args[2];
	        				for (int i = tmpkey.length(); i < 24; i++){
	           		 	    tmpkey = tmpkey + "0";
	        				}
	        				byteData = SecretKeyUtil.hexToBytes(data);
	        				r = SecretKeyUtil.decrypt(tmpkey.getBytes(), byteData, DES3);
	        				System.out.println(new String(r));
		
	        	 }
	       
	          }catch(Exception ex)
	          {
	          	System.out.println(ex);
	          }
	        }
	        else System.out.println("param type[encrypt decrypt] key[value] rawdata[need to encrypt or decrypt]");

	    }
}
