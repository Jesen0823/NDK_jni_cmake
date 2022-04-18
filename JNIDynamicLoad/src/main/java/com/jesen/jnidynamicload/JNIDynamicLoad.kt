package com.jesen.jnidynamicload

class JNIDynamicLoad {

    init {
        System.loadLibrary("dynamic-lib")
    }

    external fun sum(x:Int,y:Int):Int

    external fun getNativeString():String
}