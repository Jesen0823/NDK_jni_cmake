//
// Created by X1 Carbon on 2022/4/18.
//
#include "base.h"
#include <jni.h>
#include <string>

extern "C"
JNIEXPORT void JNICALL
Java_com_jesen_jnireference_JNIAccessField_accessInstanceField(JNIEnv *env, jobject thiz,
                                                               jobject dec_file) {
    // 修改常用变量
    jclass  cls = env->GetObjectClass(dec_file);
    jfieldID fieldId = env->GetFieldID(cls,"name","Ljava/lang/String;");
    jstring newStr = env->NewStringUTF("Download");
    env->SetObjectField(dec_file,fieldId, newStr);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jesen_jnireference_JNIAccessField_accessStaticField(JNIEnv *env, jobject thiz,
                                                             jobject dec_file) {
    // 修改静态成员变量
    jclass cls = env->GetObjectClass(dec_file);
    jfieldID jfieldId =  env->GetStaticFieldID(cls,"times","I");
    int times = env->GetStaticIntField(cls,jfieldId);
    LOGI("accessStaticField, pre itmes is: %d",times);
    env->SetStaticIntField(cls,jfieldId,++times);

}
extern "C"
JNIEXPORT void JNICALL
Java_com_jesen_jnireference_JNIAccessField_accessInstanceMethod(JNIEnv *env, jobject thiz,
                                                                jobject dec_file) {
    //  调用java方法
    /*jclass cls = env->GetObjectClass(dec_file);
    jmethodID methodId = env->GetMethodID(cls,"putMaxSize", "(I)V");
    env->CallVoidMethod(dec_file,methodId,2);*/

    jclass cls = env->GetObjectClass(dec_file);
    jmethodID methodId = env->GetMethodID(cls,"getCurrentPath", "()Ljava/lang/String;");
    jstring result = static_cast<jstring>(env->CallObjectMethod(dec_file, methodId));
    const char *path = env->GetStringUTFChars(result,0);
    LOGI("native call java, path: %s",path);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jesen_jnireference_JNIAccessField_accessStaticMethod(JNIEnv *env, jobject thiz,
                                                              jobject dec_file) {
    // 调用java的静态方法
    jclass cls = env->GetObjectClass(dec_file);
    jmethodID methodId = env->GetStaticMethodID(cls,"callStaticMethod", "([Ljava/lang/String;I)Ljava/lang/String;");

    jobjectArray strArray;
    int i;
    char *data[5]= {"A", "B", "C", "D", "E"};
    strArray= (jobjectArray)env->NewObjectArray(5,env->FindClass("java/lang/String"),env->NewStringUTF(""));
    for(i=0;i<5;i++) env->SetObjectArrayElement(strArray,i,env->NewStringUTF(data[i]));

    jobject funRet = env->CallStaticObjectMethod(cls,methodId,strArray,8);
    jstring res = static_cast<jstring>(funRet);
    const char *result = env->GetStringUTFChars(res,0);
    LOGI("native call java, static ret: %s",result);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jesen_jnireference_JNIAccessField_staticAccessInstanceField(JNIEnv *env, jclass clazz) {
    // 访问静态属性
    //jclass cls = env->GetObjectClass(dec_file);
    jfieldID jfieldId =  env->GetStaticFieldID(clazz,"num","I");
    int num = env->GetStaticIntField(clazz,jfieldId);
    LOGI("accessStaticField, pre num is: %d",num);
    env->SetStaticIntField(clazz,jfieldId,++num);
}