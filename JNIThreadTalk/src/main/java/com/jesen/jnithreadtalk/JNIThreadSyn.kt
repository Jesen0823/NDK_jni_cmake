package com.jesen.jnithreadtalk

/**
 * 线程的同步
 * */
class JNIThreadSyn {
    init {
        System.loadLibrary("thread-lib")
    }

    external fun waitNativeThread()

    external fun notifyNativeThread()
}