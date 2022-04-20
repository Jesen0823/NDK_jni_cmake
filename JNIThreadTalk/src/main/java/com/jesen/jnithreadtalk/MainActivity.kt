package com.jesen.jnithreadtalk

import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val threadTest = JNIThreadTest()

        val btn1 = findViewById<Button>(R.id.createThreadBtn)
        btn1.setOnClickListener {
            threadTest.createNativeThread()
        }

        val btn2 = findViewById<Button>(R.id.createThreadArgBtn)
        btn2.setOnClickListener {
            threadTest.createNativeThreadWithArgs()
        }

        val btn3 = findViewById<Button>(R.id.threadJoinBtn)
        btn3.setOnClickListener {
            threadTest.joinNativeThread()
        }

        val jniThreadSyn = JNIThreadSyn()
        val btn4 = findViewById<Button>(R.id.threadWaitBtn)
        btn4.setOnClickListener {
            jniThreadSyn.waitNativeThread()
        }
        val btn5 = findViewById<Button>(R.id.threadNotifyBtn)
        btn5.setOnClickListener {
            jniThreadSyn.notifyNativeThread()
        }

        val jniProductConsumer = JNIProductConsumer()
        val btn6 = findViewById<Button>(R.id.productConsumerBtn)
        btn6.setOnClickListener {
            jniProductConsumer.startProductConsumer()
        }
    }
}