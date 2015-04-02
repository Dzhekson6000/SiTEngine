package org.SiT.lib;

public class SiTLib {
	public static native void nativeDraw();
	public static native void nativeInit(final int width, final int height);
	public static native void nativeOnSurfaceChanged(final int width, final int height);
}
