/*
 * Copyright (C) 2012 armite@126.com
 *
 */
package com.armite.webkit;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.content.Intent;
import android.content.Context;
import android.view.View;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.content.pm.ApplicationInfo;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.KeyEvent;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.PorterDuff.Mode;
import android.graphics.PorterDuffXfermode;
import android.graphics.Rect;
import android.view.Window;
import android.view.WindowManager;
import android.widget.FrameLayout;
import android.graphics.PixelFormat;
import android.util.DisplayMetrics;
import android.widget.VideoView;
import android.widget.MediaController;
import android.net.Uri;
import android.graphics.Point;
import android.view.Display;
import android.content.res.AssetManager;
import java.io.IOException;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.zip.ZipEntry;
import java.util.Enumeration;
import java.util.zip.ZipFile;
import java.util.zip.ZipException;
import android.view.inputmethod.InputMethodManager;
import android.os.ResultReceiver;
import android.graphics.Color;
import android.view.inputmethod.EditorInfo;

public class Armite extends Activity {
    private BrowserView mBrowserView = null;

    //private final String mWebViewHome = "http://www.baidu.com";
    private final String mWebViewHome = "http://10.0.2.2:8080/index.html";
    //private final String mWebViewHome = "http://58.215.173.59:8080/testepg/page/index/index.do";
    //private final String mWebViewHome = "http://182.138.31.29:8080/cnrHdEpg/page/index/index.do";
    //private final String mWebViewHome = "http://182.138.31.29:8080/cnrHdEpg/page/search/index.do";
    //private final String mWebViewHome = "http://192.168.0.100:9191/test2.html";//index.html";
    //private final String mWebViewHome = "http://192.168.252.244/TestSuite/index.html";
    //private final String mWebViewHome = "http://iptvauth.online.sh.cn:7001/iptv3a/UserAuthenticationAction.do?UserID=19101389&Action=login";
    private final String TAG = "Armite Activity";

    @Override
    public void onCreate(Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);
        //getWindow().addFlags(WindowManager.LayoutParams.FLAG_SHOW_WALLPAPER);
        android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_URGENT_DISPLAY);

        String dataDir = getApplicationInfo().dataDir;
        Point size = new Point(1280, 720);
        //getWindowManager().getDefaultDisplay().getSize(size);
        //DisplayMetrics displaysMetrics = new DisplayMetrics();
        //getWindowManager().getDefaultDisplay().getMetrics(displaysMetrics);
        //size.set(displaysMetrics.widthPixels, displaysMetrics.heightPixels);
        Log.i(TAG, "w="+size.x+",y="+size.y);

        mBrowserView = new BrowserView(this);
        mBrowserView.initBrowser(mWebViewHome, size.x, size.y);
        setContentView(mBrowserView);
        initCvmData();
    }

    @Override
    public boolean onKeyDown(int KeyCode, KeyEvent event) {
        if (mBrowserView != null) {
            Log.i(TAG, event.getRepeatCount() + "onKeyDown:"+KeyCode);
            switch(KeyCode) {
            	case 0:
            	return super.onKeyDown(KeyCode, event);
                case KeyEvent.KEYCODE_DPAD_UP:
                case KeyEvent.KEYCODE_DPAD_DOWN:
                case KeyEvent.KEYCODE_DPAD_LEFT:
                case KeyEvent.KEYCODE_DPAD_RIGHT:
                case KeyEvent.KEYCODE_DPAD_CENTER:
                case KeyEvent.KEYCODE_ENTER:
                case KeyEvent.KEYCODE_DEL:
                case KeyEvent.KEYCODE_BACK:
                return mBrowserView.sendKeyEvent(KeyCode, 0);
                default:
                	return mBrowserView.sendKeyEvent(KeyCode, 0);
            }
        }
        return  super.onKeyDown(KeyCode, event);
    }
    
    private void writeToFile(AssetManager am, String name, String dir) {
        File file = new File(dir + "/" + name);
        if (file.exists())
            return;
        try {
            file.createNewFile();
            BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(file), 8192);
            InputStream ins = am.open(name);
            BufferedInputStream bi = new BufferedInputStream(ins);

            byte[] readContent = new byte[1024];
            int readCount = bi.read(readContent);
            while (readCount != -1) {
                bos.write(readContent, 0, readCount);
                readCount = bi.read(readContent);
            }

            bos.flush();
            bi.close();
            bos.close();
        } catch (IOException e) {
            Log.i(TAG, "writeToFile exception:"+e.getMessage());
            e.printStackTrace();
        }
    }

    public void initCvmData() {
        final String configName = "MIDPFilterConfig.txt";
        final String midpClassName = "MIDPPermittedClasses.txt";
        final String skinName = "skin.bin";
        final String homeDir = "/cvm/lib";

        try {
            String dataDir = getApplicationInfo().dataDir;
            AssetManager am = getAssets();
            String fileDir = dataDir + homeDir;
            File fileDirFile = new File(fileDir);
            if (!fileDirFile.exists()) {
                Log.i(TAG, "cvm home create:"+fileDir);
                fileDirFile.mkdirs();
            }

            writeToFile(am, configName, fileDir);
            writeToFile(am, midpClassName, fileDir);
            writeToFile(am, skinName, fileDir);
        } catch (Exception e) {
            Log.i(TAG, "initCvmData exception:"+e.getMessage());
            e.printStackTrace();
        }
    }

    @Override
    protected void onStart() {
        super.onStart();
        Log.i(TAG, "activity lifecycle onStart pid:"  + android.os.Process.myPid());
    }

    @Override
    protected void onResume() {
        super.onResume();
        mBrowserView.onResume();
        Log.i(TAG, "activity lifecycle onResume");
    }

    @Override
    protected void onPause() {
        super.onPause();
        mBrowserView.onPause();
        Log.i(TAG, "activity lifecycle onPause");
    }

    @Override
    protected void onStop() {
        try {
            mBrowserView.exitBrowser();
        } catch (Exception e) {
            e.printStackTrace();
        }
        super.onStop();
        Log.i(TAG, "activity lifecycle onStop");
        android.os.Process.killProcess(android.os.Process.myPid());
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.i(TAG, "activity lifecycle onDestroy");
    }
}



