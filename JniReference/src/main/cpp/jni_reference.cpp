#include "base.h"

//
// Created by X1 Carbon on 2022/4/18.
//


extern "C"
JNIEXPORT jstring JNICALL
Java_com_jesen_jnireference_JNIReference_callNativeStringArry(JNIEnv *env, jobject thiz,
                                                              jobjectArray str_arry) {
    int len = env->GetArrayLength(str_arry);
    LOGD("native: arry length is %d",len);
    jstring first_ele = static_cast<jstring>(env->GetObjectArrayElement(str_arry, 0));
    // jstring类型转换为c风格的字符串
    const char *str = env->GetStringUTFChars(first_ele,0);
    LOGI("first element is :%s",str);
    env->ReleaseStringUTFChars(first_ele,str);
    return env->NewStringUTF(str);
}