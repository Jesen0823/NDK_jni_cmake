package com.jesen.jnimirrorbitmap

import android.graphics.BitmapFactory
import android.os.Bundle
import android.widget.ImageView
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val imageV = findViewById<ImageView>(R.id.imageV)

        var bitmap = BitmapFactory.decodeResource(resources, R.mipmap.mirrortest)
        imageV.setImageBitmap(bitmap)
        val jniMirrorHelper = JNIMirrorHelper()
        imageV.setOnClickListener {
            val newBitmap = jniMirrorHelper.mirrorBitmap(bitmap)
            imageV.setImageBitmap(newBitmap)
            // 重新赋值
            bitmap = newBitmap
        }
    }
}