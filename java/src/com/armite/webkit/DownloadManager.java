/*
 * Copyright (C) 2012 armite@126.com
 *
 */
package com.armite.webkit;

import android.util.Log;
import java.net.URL;
import java.io.IOException;
import java.io.File;
import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.ByteArrayInputStream;

public class DownloadManager {
    private final String TAG = "DownloadManager";

    private boolean isStore() {
        Log.i(TAG, "isStore");
        return false;
    }

    private boolean isHook() {
        Log.i(TAG, "isHook");
        return false;
    }

    private String hookHtmlString(String url, byte[] html) {
        //Log.i(TAG, "hookHtmlString:"+html);
        return null;
    }

    private void startHtmlDown() {
        Log.i(TAG, "startHtmlDown ");
    }

    private void errorMsg(String msg, String url, int line) {
        Log.i(TAG, "errorMsgToConsole:"+msg);
        Log.i(TAG, "errorMsgToConsole at:"+url+","+line);
    }

    private boolean startResourceDown(String url) {
        Log.i(TAG, "startResourceDown:"+url);
        return false;
    }

    private void endResourceDown(String url, int code) {
        Log.i(TAG,code+" endResourceDown:"+url);
    }

    private void endHtmlDown(int statusCode) {
        Log.i(TAG, "endHtmlDown " + statusCode);
    }

    private String inputMethod() {
        Log.i(TAG, "inputMethod");
        return "";
    }

    private final String ResourceHome = "/data/media/Armite";
    private void storeResource(String url, byte[] content) {
        Log.i(TAG, "storeResource");
        try {
            URL fileUrl = new URL(url);
            String filePath = ResourceHome + fileUrl.getPath();
            Log.i(TAG, "storeResource file:"+filePath);

            String fileDir = filePath.substring(0, filePath.lastIndexOf("/"));
            File fileDirFile = new File(fileDir);
            if (!fileDirFile.exists()) {
                Log.i(TAG, "storeResource create dir:"+fileDir);
                fileDirFile.mkdirs();
            }

            File file = new File(filePath);
            if (!file.exists()) {
                file.createNewFile();
                BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(file), 8192);
                ByteArrayInputStream bi = new ByteArrayInputStream(content);

                byte[] readContent = new byte[1024];
                int readCount = bi.read(readContent);
                while (readCount != -1) {
                    bos.write(readContent, 0, readCount);
                    readCount = bi.read(readContent);
                }

                bos.flush();
                bi.close();
                bos.close();
            }
        } catch (IOException e) {
            Log.i(TAG, "storeResource exception:"+e.getMessage());
            e.printStackTrace();
        }
    }
}




