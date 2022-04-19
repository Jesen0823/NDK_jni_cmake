package com.jesen.jnithreadinvoke;

import com.jesen.jnithreadinvoke.base.Question;

/**
 * 两种 native调用java构造方法的实现
 * */
public class JNIContructor {

    static {
        System.loadLibrary("invoke-lib");
    }

    public native Question allocObjectConstructor();

    public native Question invokeConstructors();
}
