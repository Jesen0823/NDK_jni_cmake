package com.jesen.jnireferencemanage

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.TextView

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)


        val textTv = findViewById<TextView>(R.id.textV)
        val jniReferenceManager = JNIReferenceManager()

        textTv.setOnClickListener {
            val ret1 = jniReferenceManager.errorCacheLocalReference()
            jniReferenceManager.useWeakGlobalReference()
            jniReferenceManager.cacheWithGlobalReference()

            Log.d("MainActivity", "局部引用 ret1 : $ret1")
        }

    }
}