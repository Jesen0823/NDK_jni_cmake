package com.jesen.jnireference.bean

import android.util.Log

/**
 * java对象类
 * */
data class DecFile(var name: String = "default", var size: Int = 0){
    companion object{
        var path = "d:/user"
        @JvmStatic
        var times = 0

        @JvmStatic
        fun callStaticMethod(strs: Array<String>?, num: Int): String {
            if (strs != null) {
                for (str in strs) {
                    Log.i("DecFile", "str in array is: $str")
                }
            }
            return "OK"
        }
    }

    fun putMaxSize(size: Int){
        Log.i("DecFile", "putMaxSize is: $size")
    }

    fun getCurrentPath():String{
        return path
    }
}
