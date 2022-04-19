package com.jesen.jniexception

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.TextView
import java.lang.IllegalArgumentException

/**
 * JNI异常的捕获：
 * native发生异常可以抛送给Java端，在Java端捕获
 * */
class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val clickBtn = findViewById<TextView>(R.id.clickBtn)
        val jniExceptionTest = JNIExceptionTest()
        clickBtn.setOnClickListener {
            try {
                jniExceptionTest.nativeThrowException()
            }catch (e: IllegalArgumentException){
                Log.d("MainActivity","click exception: ${e.message}")
            }

            jniExceptionTest.nativeInvokeJavaException()
        }
    }
}