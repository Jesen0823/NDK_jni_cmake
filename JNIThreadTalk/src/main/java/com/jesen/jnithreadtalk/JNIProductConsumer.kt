package com.jesen.jnithreadtalk

class JNIProductConsumer {
    init {
        System.loadLibrary("thread-lib")
    }

    external fun startProductConsumer()
}