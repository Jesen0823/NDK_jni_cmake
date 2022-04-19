package com.jesen.jniexception

import java.io.ByteArrayInputStream
import java.io.InputStream
import java.lang.IllegalArgumentException

class JNIExceptionTest {
    init {
        System.loadLibrary("exception-lib")
    }


    external fun nativeInvokeJavaException()

    @Throws(IllegalArgumentException::class)
    external fun nativeThrowException()

    private fun operation():Int{
        return 2/0
    }
}