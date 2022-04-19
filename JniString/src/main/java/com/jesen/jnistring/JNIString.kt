package com.jesen.jnistring

class JNIString {

    init {
        System.loadLibrary("stringtl-lib")
    }

    external fun callNativeString(str:String):String

    external fun stringMethod(str:String)
}