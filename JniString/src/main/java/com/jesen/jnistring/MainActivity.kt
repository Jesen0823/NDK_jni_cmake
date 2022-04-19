package com.jesen.jnistring

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val jniString = JNIString()
        val textHello = findViewById<TextView>(R.id.textHell)
        val helloText = findViewById<TextView>(R.id.hellText)

        textHello.setOnClickListener {
            jniString.stringMethod("from java")
        }

        helloText.setOnClickListener {
            jniString.callNativeString("from and return")
        }
    }
}