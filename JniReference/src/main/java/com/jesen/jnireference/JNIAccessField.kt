package com.jesen.jnireference

import com.jesen.jnireference.bean.DecFile

class JNIAccessField {
    init {
        System.loadLibrary("referencel-lib")
    }

    companion object {
        var num: Int = 10

        @JvmStatic
        external fun staticAccessInstanceField()
    }

    // 访问修改成员变量
    external fun accessInstanceField(decFile: DecFile)

    // 访问修改静态成员变量
    external fun accessStaticField(decFile: DecFile)

    external fun accessInstanceMethod(decFile: DecFile)

    external fun accessStaticMethod(decFile: DecFile)
}