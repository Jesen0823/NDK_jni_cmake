package com.jesen.jnimirrorbitmap

import android.graphics.Bitmap

class JNIMirrorHelper {
    init {
        System.loadLibrary("mirror-lib")
    }

    external fun mirrorBitmap(bitmap: Bitmap): Bitmap
}