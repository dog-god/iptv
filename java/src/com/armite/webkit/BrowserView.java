/*
 * Copyright (C) 2012 armite@126.com
 *
 */
package com.armite.webkit;

import android.app.Activity;
import android.os.Bundle;
import android.content.Context;
import android.view.View;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.PixelFormat;
import android.content.pm.ApplicationInfo;
import android.util.Log;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.opengl.GLSurfaceView;
import android.view.KeyEvent;
import android.graphics.Paint;
import android.graphics.PorterDuff;
import android.graphics.PorterDuff.Mode;
import android.graphics.PorterDuffXfermode;
import android.widget.FrameLayout;
import android.widget.VideoView;
import android.widget.MediaController;
import android.net.Uri;
import android.graphics.Rect;
import android.os.Handler;
import android.os.Message;
import android.view.Surface;
import android.graphics.BitmapFactory;
import java.io.IOException;
import java.io.InputStream;

import com.armite.webkit.plug.IBrowserInterface;
import com.armite.webkit.plug.MyPlayerCenter;
import com.armite.webkit.plug.Utility;

import android.os.SystemClock;

public class BrowserView extends FrameLayout implements SurfaceHolder.Callback, WebView.WindowExpose,IBrowserInterface {
    private final String TAG = "BrowserView";
    private WebView mWebView = null;
    private Bitmap mBitmap = null;
    private Paint mPaint = null;

    private SurfaceView mWebSurface = null;
    private SurfaceHolder mHolder = null;
    
    private SurfaceView mPlayerSurface = null;
    private SurfaceHolder mPlayerHolder = null;

    private final int BROWSERWIDTH = 1280;
    private final int BROWSERHEIGHT = 720;
    //private final int BROWSERWIDTH = 640;
    //private final int BROWSERHEIGHT = 530;
    private Rect mViewSrc = new Rect(0, 0, BROWSERWIDTH, BROWSERHEIGHT);
    private Rect mViewDst = new Rect(0, 0, BROWSERWIDTH, BROWSERHEIGHT);
    public final int MSG_HIDEVIDEOVIEW = 1;
    public final int MSG_SHOWVIDEOVIEW = 2;
    private boolean mCanSetBrowser = false;
    
    public BrowserView(Armite armite) {
        super(armite);
        
        mPlayerSurface = new SurfaceView(armite);
        mPlayerHolder = mPlayerSurface.getHolder();
        mPlayerHolder.addCallback(this);
        addView(mPlayerSurface);
        MyPlayerCenter.init(this.getContext(),this); 
        
        

        mWebSurface = new SurfaceView(armite);
        mWebSurface.setZOrderMediaOverlay(true);
        mHolder = mWebSurface.getHolder();
        mHolder.setFormat(PixelFormat.TRANSLUCENT);
        mHolder.addCallback(this);
        addView(mWebSurface);

        mWebView = WebView.getInstance();

        mBitmap = Bitmap.createBitmap(BROWSERWIDTH, BROWSERHEIGHT, Bitmap.Config.ARGB_8888);
        mPaint = new Paint();
        mPaint.setXfermode(new PorterDuffXfermode(PorterDuff.Mode.SRC));
        
        mBrowserView = this;
    }

    public void updateWindow(int x, int y, int w, int h) {
        mCanSetBrowser = true;
    	try{
        Canvas cv = mHolder.lockCanvas();
        try{
        if (cv != null) {
            mViewSrc.right = w;
            mViewSrc.bottom = h;
            cv.drawBitmap(mBitmap, mViewSrc, mViewDst, mPaint);
            
        }
        }catch(Exception ex2){
        	Log.e(TAG, ex2.getMessage());
        }
        mHolder.unlockCanvasAndPost(cv);
    	}catch(Exception ex){
    		Log.e(TAG, ex.getMessage());
    	}
    }

    public static BrowserView mBrowserView = null;
    public void updateCdcView(Bitmap bm) {
        try{
            Canvas cv = mHolder.lockCanvas();
            try{
                if (cv != null) {
                    mViewSrc.right = bm.getWidth();
                    mViewSrc.bottom = bm.getHeight();
                    cv.drawBitmap(bm, mViewSrc, mViewDst, mPaint);
                }
            }catch(Exception ex2){
               Log.e(TAG, ex2.getMessage());
            }
            mHolder.unlockCanvasAndPost(cv);
        }catch(Exception ex){
            Log.e(TAG, ex.getMessage());
        }
    }

    public void onPause() {
    }

    public void onResume() {
    }

    private int mDisplayWidth = BROWSERWIDTH;
    private int mDisplayHeight = BROWSERHEIGHT;
    private String mMainURL;
    public void initBrowser(String url, int w, int h) {
        if (mWebView == null)
            return;

        mMainURL = url;
        mDisplayWidth = w;
        mDisplayHeight = h;
        mViewDst.right = mDisplayWidth;
        mViewDst.bottom = mDisplayHeight;

        mWebView.setWindowExpose(this);
    }

    private Thread mBrowserThread = null;
    private void startBrowser() {
        if (mBrowserThread != null)
            return;

        mBrowserThread = new Thread(new Runnable() {
           public void run() {
                Thread.currentThread().setPriority(Thread.MAX_PRIORITY);
                android.os.Process.setThreadPriority(android.os.Process.THREAD_PRIORITY_URGENT_DISPLAY);
                mWebView.StartBrowser(mBitmap, mMainURL);
            }
        });

        mBrowserThread.setName("browser");
        mBrowserThread.setPriority(Thread.MAX_PRIORITY);
        mBrowserThread.start();
    }

    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        Log.i(TAG, "surfaceChanged");
        if(holder==mHolder){
        	startBrowser();
        }
    }

    public void surfaceCreated(SurfaceHolder holder) {
        Log.i(TAG, "surfaceCreated");
        if(holder==mPlayerHolder){
        	MyPlayerCenter.setSurfaceHolder(mPlayerHolder);
        }
    }

    public void surfaceDestroyed(SurfaceHolder holder) {
        Log.i(TAG, "surfaceDestroyed");
        if(holder==mPlayerHolder){
        	//MyPlayerCenter.setSurfaceHolder(null);
        }
    }

    public void exitBrowser() {
        if (mWebView == null)
            return;
        try {
            mWebView.ExitBrowser();
            mBrowserThread.join(1000);
        } catch (InterruptedException e) {
            Log.i(TAG, "exitBrowser error:" + e.getMessage());
            e.printStackTrace();
        }
    }
    
    private boolean sendKey2cvm(int key) {
        int vKey = 0;
        switch(key) {
            case KeyEvent.KEYCODE_A:
            case KeyEvent.KEYCODE_DPAD_LEFT:        vKey = 75; break;
            case KeyEvent.KEYCODE_W:
            case KeyEvent.KEYCODE_DPAD_UP:          vKey = 72; break;
            case KeyEvent.KEYCODE_D:
            case KeyEvent.KEYCODE_DPAD_RIGHT:       vKey = 77; break;
            case KeyEvent.KEYCODE_S:
            case KeyEvent.KEYCODE_DPAD_DOWN:        vKey = 80; break;
            case KeyEvent.KEYCODE_ENTER:
            case KeyEvent.KEYCODE_DPAD_CENTER:      vKey = 28; break;
            case KeyEvent.KEYCODE_DEL:              vKey = 16; break; //end
            case KeyEvent.KEYCODE_POUND:
            case KeyEvent.KEYCODE_BACK:             vKey = 14; break; //clear
            case KeyEvent.KEYCODE_PAGE_UP:          vKey = 59; break; //soft1
            case KeyEvent.KEYCODE_PAGE_DOWN:        vKey = 20; break; //soft2
            case KeyEvent.KEYCODE_0:                vKey = 11; break;
            case KeyEvent.KEYCODE_1:                vKey = 2; break;
            case KeyEvent.KEYCODE_2:                vKey = 3; break;
            case KeyEvent.KEYCODE_3:                vKey = 4; break;
            case KeyEvent.KEYCODE_4:                vKey = 5; break;
            case KeyEvent.KEYCODE_5:                vKey = 6; break;
            case KeyEvent.KEYCODE_6:                vKey = 7; break;
            case KeyEvent.KEYCODE_7:                vKey = 8; break;
            case KeyEvent.KEYCODE_8:                vKey = 9; break;
            case KeyEvent.KEYCODE_9:                vKey = 10; break;
        }
        if (vKey == 0)
            return false;
        Log.i(TAG, "sendEvent2cvm:"+vKey);
        mWebView.sendEvent2cvm(vKey);
        return true;
    }

    public boolean cvm_running = false;
    public boolean sendKeyEvent(int KeyCode, int unicode) {
        if (cvm_running)
            return sendKey2cvm(KeyCode);
        if (mWebView != null)
            return mWebView.sendKeyEvent(KeyCode, unicode);
        return false;
    }

    private int m_actionDownX = 0;
    private int m_actionDownY = 0;
    public boolean onTouchEvent(MotionEvent event) {
        if (mWebView != null) {
            int x = (int) event.getX() * BROWSERWIDTH / mDisplayWidth;
            int y = (int) event.getY() * BROWSERHEIGHT / mDisplayHeight;
            if (event.getAction() == MotionEvent.ACTION_DOWN) {
                m_actionDownX = x;
                m_actionDownY = y;
                mWebView.SendMouseEvent("mouse-down", x, y);
                return true;
            } else if (event.getAction() == MotionEvent.ACTION_UP) {
                if (x > m_actionDownX + 9 || x < m_actionDownX - 9 || y > m_actionDownY + 9 || y < m_actionDownY - 9)
                    mWebView.SendMouseEvent("mouse-up", x, y);
                else
                    mWebView.SendMouseEvent("mouse-up", m_actionDownX, m_actionDownY);
                return true;
            } else if (event.getAction() == MotionEvent.ACTION_MOVE) {
                if (x > m_actionDownX + 9 || x < m_actionDownX - 9 || y > m_actionDownY + 9 || y < m_actionDownY - 9)
                    mWebView.SendMouseEvent("mouse-move", x, y);
                return true;
            }
        }
        return super.onTouchEvent(event);
    }

	@Override
	public void sendKeyEvent(int KeyCode) {
		// TODO Auto-generated method stub
		sendKeyEvent(KeyCode, 0);
	}

	@Override
	public void hideWebView() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void showWebView() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void hideVideoView() {
		// TODO Auto-generated method stub
		  Message msg = Message.obtain(mHandler);
	      msg.what = MSG_HIDEVIDEOVIEW;
	      mHandler.sendMessage(msg);
	}

	@Override
	public void showVideoView() {
		// TODO Auto-generated method stub
		Message msg = Message.obtain(mHandler);
	      msg.what = MSG_SHOWVIDEOVIEW;
	      mHandler.sendMessage(msg);
	}

	@Override
	public void setVideoArea(int left, int top, int width, int height) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void setVideoMode(int mode) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void setVideoAlpha(int alpha) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void quit() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void startConfig() {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void notifyChannelEvent(String type, int instance_id,
			String channel_code, int userChannelID) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void notifyMediaEvent(String type, int instance_id,
			String mediaCode, String entryID) {
		// TODO Auto-generated method stub
		StringBuilder tmpsb = new StringBuilder();
		tmpsb.append("{\"type\":\"").append(type).append("\",\"instance_id\":").append(instance_id)
		.append(",\"media_code\":\"").append(mediaCode).append("\",\"entry_id\":\"").append(entryID).append("\"}");
		Utility.setEvent(tmpsb.toString());
		this.sendKeyEvent(0x0300, 0x0300);
	}

	@Override
	public void notifyMediaError(String type, int instance_id, int errorcode,
			String errordesc, String mediaCode) {
		// TODO Auto-generated method stub
		StringBuilder tmpsb = new StringBuilder();
		tmpsb.append("{\"type\":\"").append(type).append("\",\"instance_id\":").append(instance_id)
		.append("\",\"error_code\":").append(errorcode).append(",\"error_message\":\"").append(errordesc)
		.append("\",\"media_code\":\"").append(mediaCode).append("\"}");
		Utility.setEvent(tmpsb.toString());
		this.sendKeyEvent(0x0300, 0x0300);
		
	}

	@Override
	public void notifyMediaPlayModeChange(String type, int instance_id,
			int new_play_mode, int new_play_rate, int old_play_mode,
			int old_play_rate) {
		// TODO Auto-generated method stub
		/*Type
instance_id
new_play_mode
new_play_rate
old_play_mode
old_play_rate
*/
		StringBuilder tmpsb = new StringBuilder();
		tmpsb.append("{\"type\":\"").append(type).append("\",\"instance_id\":").append(instance_id)
		.append(",\"new_play_mode\":").append(new_play_mode).append(",\"new_play_rate\":").append(new_play_rate)
		.append(",\"old_play_mode\":").append(old_play_mode).append(",\"old_play_rate\":").append(old_play_rate).append("}");
		Utility.setEvent(tmpsb.toString());
		this.sendKeyEvent(0x0300, 0x0300);

		
		
	}

	@Override
	public void notifyJVMEvent(String type, int event_code, int event_result,
			String event_message) {
		// TODO Auto-generated method stub
		
	}
	private Handler mHandler = new MainHandler();

    private class MainHandler extends Handler {
        @Override
            public void handleMessage(Message msg) {
            switch (msg.what) {
            	case MSG_HIDEVIDEOVIEW:
            		//mPlayerSurface.setVisibility(View.GONE);
            		mWebSurface.bringToFront();

            		break;
            	case MSG_SHOWVIDEOVIEW:
            		mPlayerSurface.setVisibility(View.VISIBLE);
            		break;
                default:
                    break;
            }
        }
      }	
}

