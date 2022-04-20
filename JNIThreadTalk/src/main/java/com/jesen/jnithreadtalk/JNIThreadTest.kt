package com.jesen.jnithreadtalk

/**
 * 线程的创建
 * */
class JNIThreadTest {

    init {
        System.loadLibrary("thread-lib")
    }

    external fun createNativeThread()

    external fun createNativeThreadWithArgs()

    external fun joinNativeThread()
}