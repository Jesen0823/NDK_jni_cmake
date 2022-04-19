#include <jni.h>

//
// Created by X1 Carbon on 2022/4/19.
// JNI 中的三种引用类型
// 全局引用，局部引用，弱引用
#include <base.h>

// 局部引用手动释放: env->DeleteLocalRef(localRef)
//
extern "C"
JNIEXPORT jstring JNICALL
Java_com_jesen_jnireferencemanage_JNIReferenceManager_errorCacheLocalReference(JNIEnv *env,
                                                                               jobject thiz) {
    // 局部引用 localRefs, 会自动释放，不必手动释放
    // 局部引用不能太多，太多则需要手动释放，比如for循环中多次创建局部引用
    /*for(int i = 0; i < 100; ++i){
        jclass cls = env->FindClass("java/lang/String");
        LOGI("for 循环 局部引用手动释放 ");
        env->DeleteLocalRef(cls);
    }*/
    jclass  localRefs = env->FindClass("java/lang/String");
    jmethodID  methodId = env->GetMethodID(localRefs,"<init>","(Ljava/lang/String;)V");
    jstring  str = env->NewStringUTF("I am a String");
    return static_cast<jstring>(env->NewObject(localRefs, methodId, str));
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jesen_jnireferencemanage_JNIReferenceManager_useWeakGlobalReference(JNIEnv *env,
                                                                             jobject thiz) {
    // 弱引用 与全局引用不同的是：弱引用GC会被自动释放
    static jclass stringClass = nullptr;
    if(stringClass == nullptr){
        LOGI("No,There is no object,I will create it.");
        jclass cls = env->FindClass("java/lang/String");
        // 将局部引用cls赋值给全局引用stringClass
        stringClass = static_cast<jclass>(env->NewWeakGlobalRef(cls));
        // 释放局部变量
        env->DeleteLocalRef(cls);
    } else{
        LOGI("Yes,There is a cache object.");
    }
    jmethodID methodId = env->GetMethodID(stringClass,"<init>","(Ljava/lang/String;)V");

    // 引用对象是否已经被GC掉了
    jboolean isDied = env->IsSameObject(stringClass, nullptr);
    if (isDied){
        LOGI("weak reference , 已经GC回收了");
    } else{
        LOGI("weak reference , 没有自动GC回收");
    }
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_jesen_jnireferencemanage_JNIReferenceManager_cacheWithGlobalReference(JNIEnv *env,
                                                                               jobject thiz) {
    // 全局引用的缓存static
    static jclass stringClass = nullptr;
    if(stringClass == nullptr){
        LOGI("No,I will create it.");
        jclass cls = env->FindClass("java/lang/String");
        // 将局部引用cls赋值给全局引用stringClass
        stringClass = static_cast<jclass>(env->NewGlobalRef(cls));
        // 释放局部变量
        env->DeleteLocalRef(cls);
    } else{
        LOGI("Yes, cache object.");
    }
    jmethodID methodId = env->GetMethodID(stringClass,"<init>","(Ljava/lang/String;)V");
    jstring str = env->NewStringUTF("hello i am a string");
    jobject ret = env->NewObject(stringClass,methodId,str);
    // n全局引用不会自动释放，需要手动释放：
    env->DeleteGlobalRef(stringClass);

    return static_cast<jstring >(ret);
}