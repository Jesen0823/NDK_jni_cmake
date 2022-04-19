package com.jesen.jnidynamicload

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val jniDynamicLoad = JNIDynamicLoad()
        val text = findViewById<TextView>(R.id.hell_text)
        text.setOnClickListener {
            (it as TextView).text = jniDynamicLoad.getNativeString()
        }

        val addText = findViewById<TextView>(R.id.addText)
        addText.setOnClickListener {
            addText.text = "2+3=${jniDynamicLoad.sum(2,3)}"
        }
    }
}