package com.jesen.jnireference

class JNIReference {

    init {
        System.loadLibrary("referencel-lib")
    }

    external fun callNativeStringArry(strArry:Array<String>):String
}