package org.SiT.lib;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;

public class SiTRenderer implements GLSurfaceView.Renderer{

	private final static long NANOSECONDSPERSECOND = 1000000000L;
	private final static long NANOSECONDSPERMICROSECOND = 1000000;

	private static long _interval = (long) (1.0 / 60 * SiTRenderer.NANOSECONDSPERSECOND);
	
	private long _lastTick;
	private int _screenWidth;
	private int _screenHeight;
	
	public void setScreenWidthAndHeight(final int screenWidth, final int screenHeight) {
		this._screenWidth = screenWidth;
		this._screenHeight = screenHeight;
	}
	
	@Override
	public void onDrawFrame(GL10 gl) {
		final long now = System.nanoTime();
		final long interval = now - this._lastTick;
		
		if (interval < SiTRenderer._interval) {
			try {
				Thread.sleep((SiTRenderer._interval - interval) / SiTRenderer.NANOSECONDSPERMICROSECOND);
			} catch (final Exception e) {
			}
		}
		this._lastTick = now;
		SiTLib.nativeDraw();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		SiTLib.nativeOnSurfaceChanged(width, height);
	}

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		SiTLib.nativeInit(_screenWidth, _screenHeight);
		
	}

}
