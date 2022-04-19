package com.jesen.jnithreadinvoke

import com.jesen.jnithreadinvoke.base.IThreadCallback
import com.jesen.jnithreadinvoke.base.ICallbackMethod

class JNIInvokeMethod {
    init {
        System.loadLibrary("invoke-lib")
    }

    // java层将Callback接口传递给native
    external fun nativeCallback(callback: ICallbackMethod)
    external fun nativeThreadCallback(callback: IThreadCallback)
}