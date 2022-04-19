#include <jni.h>

//
// Created by X1 Carbon on 2022/4/19
// native调用java类的构造方法创建java对象
// 两种方法差异不大.
//


extern "C"
JNIEXPORT jobject JNICALL
Java_com_jesen_jnithreadinvoke_JNIContructor_allocObjectConstructor(JNIEnv *env, jobject thiz) {
    // 先alloc一个对象然后调用类的构造方法
    jclass  cls = env->FindClass("com/jesen/jnithreadinvoke/base/Question");
    // 构造方法的方法名:init
    jmethodID  methodId = env->GetMethodID(cls,"<init>","(Ljava/lang/String;)V");
    jstring title = env->NewStringUTF("How many years since the earth bord ?");

    jobject question = env->AllocObject(cls);
    env->CallNonvirtualVoidMethod(question,cls,methodId,title);
    return question;
}
extern "C"
JNIEXPORT jobject JNICALL
Java_com_jesen_jnithreadinvoke_JNIContructor_invokeConstructors(JNIEnv *env, jobject thiz) {
    // native通过java构造方法创建对象，返回给java
    jclass  cls = env->FindClass("com/jesen/jnithreadinvoke/base/Question");
    // 构造方法的方法名:init
    jmethodID  methodId = env->GetMethodID(cls,"<init>","(Ljava/lang/String;)V");
    // 参数
    jstring title = env->NewStringUTF("Whats the beautiful birds top 10 in the world?");
    jobject  question = env->NewObject(cls,methodId,title);
    return question;
}