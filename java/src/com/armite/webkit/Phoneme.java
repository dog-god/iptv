/*
 * Copyright (C) 2012 armite@126.com
 *
 */
package com.armite.webkit;

import android.util.Log;
import org.apache.http.HttpEntity;
import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.client.methods.HttpGet;
import android.net.http.AndroidHttpClient;
import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.File;
import java.io.FileOutputStream;
import android.graphics.Bitmap;
import android.view.KeyEvent;

public class Phoneme {
    private static final String TAG = "Phoneme";
    private static final int IO_BUFFER_SIZE = 8 * 1024;
    public Phoneme() { }

    /* load cvm native library */
    static void loadCVMLib() {
        try {
            System.loadLibrary("cvm");
        } catch (Error e) {
            Log.i(TAG, "load native library error:libcvm.so");
        }
    }

    final String suitePath = "/data/data/com.armite.webkit/cvm/suite.jar";
    final String errorPath = "/data/local/tmp/suite.jar";
    public String getJarFile(String url) {
        Log.i(TAG, "getJarFile:"+url);
        if (url.startsWith("file:///"))
            return url.substring(7);
        if (!url.startsWith("http://"))
            return errorPath;

        final AndroidHttpClient client = AndroidHttpClient.newInstance("Android");
        final HttpGet getRequest = new HttpGet(url);

        try {
            File file = new File(suitePath);
            if (file.exists())
                file.delete();
            file.createNewFile();

            HttpResponse response = client.execute(getRequest);
            final int statusCode = response.getStatusLine().getStatusCode();
            if (statusCode != HttpStatus.SC_OK) {
                Log.i(TAG, "Error " + statusCode + " while retrieving jar from " + url);
                return errorPath;
            }
            final HttpEntity entity = response.getEntity();
            if (entity == null) {
                Log.i(TAG, "Error " + statusCode + " while retrieving jar from " + url);
                return errorPath;
            }

            InputStream inputStream = null;
            OutputStream outputStream = null;
            try {
                inputStream = entity.getContent();
                final FileOutputStream fileStream = new FileOutputStream(file);
                outputStream = new BufferedOutputStream(fileStream, IO_BUFFER_SIZE);

                byte[] b = new byte[IO_BUFFER_SIZE];
                int read;
                while ((read = inputStream.read(b)) != -1)
                    outputStream.write(b, 0, read);

                outputStream.flush();
            } finally {
                if (inputStream != null) {
                    inputStream.close();
                }
                if (outputStream != null) {
                    outputStream.close();
                }
                entity.consumeContent();
            }
        } catch (IOException e) {
            getRequest.abort();
            Log.w(TAG, "I/O error while retrieving jar from " + url, e);
        } catch (IllegalStateException e) {
            getRequest.abort();
            Log.w(TAG, "Incorrect URL: " + url);
        } catch (Exception e) {
            getRequest.abort();
            Log.w(TAG, "Error while retrieving jar from " + url, e);
        } finally {
            if (client != null) {
                client.close();
            }
        }

        return suitePath;
    }

    private static void refreshBitmap() {
        //Log.i(TAG, "refreshBitmap");
        BrowserView.mBrowserView.updateCdcView(mBitmap);
    }

    private static void releaseBitmap() {
        Log.i(TAG, "releaseBitmap");
        BrowserView.mBrowserView.cvm_running = false;
        BrowserView.mBrowserView.sendKeyEvent(KeyEvent.KEYCODE_BACK, 0);
    }

    private static Bitmap mBitmap = null;
    private static Bitmap getBitmap(int w, int h) {
        Log.i(TAG, "getBitmap");
        BrowserView.mBrowserView.cvm_running = true;
        if (mBitmap == null)
           mBitmap = Bitmap.createBitmap(w, h, Bitmap.Config.RGB_565);
        return mBitmap;
    }
}




