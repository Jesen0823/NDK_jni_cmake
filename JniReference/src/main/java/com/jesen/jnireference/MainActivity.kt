package com.jesen.jnireference

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.widget.Button
import android.widget.TextView
import com.jesen.jnireference.bean.DecFile

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val jniReference = JNIReference()
        val jniAccessField = JNIAccessField()

        // 向native传递一个数组对象，测试native对数组对象的接收
        val testArray = findViewById<TextView>(R.id.testArray)
        val arrs = arrayOf("Jude","Kaxi","Mole")
        testArray.setOnClickListener {
            testArray.text = "first is :${jniReference.callNativeStringArry(arrs)}"
        }

        val decFile = DecFile("download",1024)
        val beanBtn = findViewById<Button>(R.id.beanBtn)
        beanBtn.setOnClickListener {
            Log.d("MainActivity","--pre click, times:${DecFile.times}")

            jniAccessField.accessStaticField(decFile)
            jniAccessField.accessInstanceField(decFile)
            Log.d("MainActivity","--beanBtn click, decFile:$decFile")
            Log.d("MainActivity","--after click, times:${DecFile.times}")
            JNIAccessField.staticAccessInstanceField()
            Log.d("MainActivity","--after click, 2x times:${DecFile.times}")

            // 调用native 然后native调用DecFile的java方法
            jniAccessField.accessInstanceMethod(decFile)
            jniAccessField.accessStaticMethod(decFile)
        }




    }
}