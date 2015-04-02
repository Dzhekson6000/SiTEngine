package org.SiT.lib;

import android.app.Activity;
import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;

public abstract class SiTActivity extends Activity {
    //private final static String TAG = SiTActivity.class.getSimpleName();
    
    SiTGLSurfaceView _glSurfaceView;
    private static Context _context = null;
    
    public static Context getContext() {
		return _context;
	}
    
    @Override
    protected void onCreate(Bundle icicle) {
        super.onCreate(icicle);
        loadLib();
        _context = this;
        _glSurfaceView = new SiTGLSurfaceView(_context);
        setContentView(_glSurfaceView);
    }

    private void loadLib() {
    	try {
			ApplicationInfo ai = getPackageManager().getApplicationInfo(getPackageName(), PackageManager.GET_META_DATA);
			Bundle bundle = ai.metaData;
			try {
        		String libName = bundle.getString("android.app.lib_name");
        		System.loadLibrary(libName);
			} catch (Exception e) {
		 		// ERROR
			}
		} catch (PackageManager.NameNotFoundException e) {
		 	// ERROR
		}
		
	}

	@Override protected void onPause() {
        super.onPause();
        _glSurfaceView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        _glSurfaceView.onResume();
    }
}
