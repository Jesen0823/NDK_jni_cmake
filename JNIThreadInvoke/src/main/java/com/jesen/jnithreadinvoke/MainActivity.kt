package com.jesen.jnithreadinvoke

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.jesen.jnithreadinvoke.base.ICallbackMethod
import com.jesen.jnithreadinvoke.base.IThreadCallback

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val jniInvokeMethod = JNIInvokeMethod()
        // native会在当前线程执行
        jniInvokeMethod.nativeCallback(object : ICallbackMethod {
            override fun callbackMethod() {
                Log.d("MainActivity", "callbackMethod  thread is :${Thread.currentThread().name}")
            }
        })

        // native会创建新线程执行此方法
        jniInvokeMethod.nativeThreadCallback(object : IThreadCallback {
            override fun callbackThread() {
                Log.d("MainActivity", "callbackThread  thread is :${Thread.currentThread().name}")
            }
        })

        // 测试native调用java类构造方法，创建java对象
        val jniContructor = JNIContructor()
        val question1 = jniContructor.allocObjectConstructor()
        val question2 = jniContructor.invokeConstructors()
        Log.d("MainActivity", "question1: ${question1.title}, question2: ${question2.title}")
    }
}