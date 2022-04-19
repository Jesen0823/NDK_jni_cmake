#include <base.h>
#include <string>
//
// Created by X1 Carbon on 2022/4/18.
//


extern "C"
JNIEXPORT jstring JNICALL
Java_com_jesen_jnistring_JNIString_callNativeString(JNIEnv *env, jobject thiz, jstring jstr) {
    const char* str = env->GetStringUTFChars(jstr, 0);
    LOGI("native: java string is %s", str);
    env->ReleaseStringUTFChars(jstr, str);

    return env->NewStringUTF("this is C style string");
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jesen_jnistring_JNIString_stringMethod(JNIEnv *env, jobject thiz, jstring jstr) {
    const char* str = env->GetStringUTFChars(jstr,0);

    char buff[128];
    int len = env->GetStringLength(jstr);
    LOGI("native: java string length is %d",len);
    env->GetStringUTFRegion(jstr,0,len-1, buff);
    LOGI("native: buff str is %s",buff);

    env->ReleaseStringUTFChars(jstr,str);
}