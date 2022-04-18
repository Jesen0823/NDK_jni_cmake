//
// Created by X1 Carbon on 2022/4/18.
//
#include <base.h>

#define JAVA_CLASS "com/jesen/jnidynamicload/JNIDynamicLoad"

/// 1. 定义native层的方法
jstring getMessage(JNIEnv* env, jobject jobj){
    return env->NewStringUTF("this is a message.");
}

jint plus(JNIEnv* env, jobject jobj,int x, int y){
    return x+y;
}

/// 2. 建立方法对应表
static JNINativeMethod gMethods[] = {
   {"getNativeString","()Ljava/lang/String;",(void*) getMessage},
   {"sum","(II)I",(void*)plus}
};

/// 3. 定义注册对应方法
int registerNativeMethods(JNIEnv* env, const char* name, JNINativeMethod* methods,jint nMethods){
    jclass jclaz;
    jclaz = env->FindClass(name);
    if(jclaz == nullptr){
        return JNI_FALSE;
    }
    if(env->RegisterNatives(jclaz, methods,nMethods) <0){
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

/// 4. 预加载方法，其中会先注册方法对应表
JNIEXPORT int JNICALL JNI_OnLoad(JavaVM *vm, void* reserved){
    JNIEnv* env;
    if(vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK){
        return JNI_FALSE;
    }
    registerNativeMethods(env,JAVA_CLASS,gMethods,2);
    LOGI("jni onLoad call");
    return JNI_VERSION_1_6;
}
