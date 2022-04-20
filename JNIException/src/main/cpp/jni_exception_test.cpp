//
// Created by X1 Carbon on 2022/4/19.
//
#include <base.h>


extern "C"
JNIEXPORT void JNICALL
Java_com_jesen_jniexception_JNIExceptionTest_nativeInvokeJavaException(JNIEnv *env, jobject thiz) {
    // native调用jav层发生异常，检测异常
    jclass  cls = env->FindClass("com/jesen/jniexception/JNIExceptionTest");
    jmethodID methodId = env->GetMethodID(cls,"operation","()I");

    jmethodID constructorMethodId = env->GetMethodID(cls,"<init>","()V");

    jobject obj = env->NewObject(cls,constructorMethodId);
    // 调用java方法
    env->CallIntMethod(obj,methodId);

    // 异常捕获
    jthrowable  throwable = env->ExceptionOccurred();
    if(throwable){
        env->ExceptionDescribe();
        // 清除异常
        env->ExceptionClear();
    }

}
extern "C"
JNIEXPORT void JNICALL
Java_com_jesen_jniexception_JNIExceptionTest_nativeThrowException(JNIEnv *env, jobject thiz) {
    // native层将异常抛送给Java层
    jclass  cls = env->FindClass("java/lang/IllegalArgumentException");
    env->ThrowNew(cls,"native throw exception");
}