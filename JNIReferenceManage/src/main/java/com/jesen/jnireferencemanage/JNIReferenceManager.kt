package com.jesen.jnireferencemanage

class JNIReferenceManager {

    init {
        System.loadLibrary("references-lib")
    }

    external  fun errorCacheLocalReference():String

    external fun useWeakGlobalReference()

    external fun cacheWithGlobalReference():String
}