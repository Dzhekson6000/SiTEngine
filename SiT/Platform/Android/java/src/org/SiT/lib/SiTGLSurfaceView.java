package org.SiT.lib;


import android.content.Context;
import android.opengl.GLSurfaceView;

public class SiTGLSurfaceView extends GLSurfaceView {
	//private static String TAG = SiTGLSurfaceView.class.getSimpleName();;
	
	public SiTGLSurfaceView(Context context) {
		super(context);
		initView();
	}

	private void initView() {
		this.setEGLContextClientVersion(2);
		this.setFocusableInTouchMode(true);
		
		this.setRenderer(new SiTRenderer());
	}

}
