#include "base.h"
#include <string>
#include "jvm.h"
#include <pthread.h>

//
// Created by X1 Carbon on 2022/4/19.
//
#define JAVA_INVOKE_CLASS  "com/jesen/jnithreadinvoke/JNIInvokeMethod"

// 主要用在第二个方法nativeThreadCallback，即跨线程调用
static jclass threadClazz;
static jmethodID threadMethod;
static jobject threadObj;

// 新线程执行函数
void *threadCallback(void *) {
    // 这里需要env, 但是Env不能跨线程，拿不到
    // 解决方法： so加载的时候，会调用JNI_OnLoad()方法，其中有JavaVM变量，可以全局保存JavaVM
    JavaVM *gVM = getJvm();
    JNIEnv *env = nullptr;
    if (gVM->AttachCurrentThread(&env, nullptr) == 0) {
        LOGI("pre call| threadCallback AttachCurrentThread threadObject: %p", threadObj);
        env->CallVoidMethod(threadObj, threadMethod);
        LOGI("after call| threadCallback AttachCurrentThread, will detach.");
        gVM->DetachCurrentThread();
    }
    return 0;
}

void nativeCallback(JNIEnv *env, jobject thiz,
                    jobject callback) {
    // native 调用java层的接口
    LOGI("native nativeCallback.");

    jclass callbackClazz = env->GetObjectClass(callback);
    jmethodID callbackMethod = env->GetMethodID(callbackClazz, "callbackMethod", "()V");
    env->CallVoidMethod(callback, callbackMethod);
}

void nativeThreadCallback(JNIEnv *env, jobject thiz,
                          jobject callback) {
    // native在子线程中调用java层接口
    LOGI("native nativeThreadCallback.");
    threadObj = env->NewGlobalRef(callback); // 全局变量
    threadClazz = env->GetObjectClass(callback);
    threadMethod = env->GetMethodID(threadClazz, "callbackThread", "()V");

    // 创建新线程
    pthread_t handle;
    pthread_create(&handle, nullptr, threadCallback, nullptr);
}

static JNINativeMethod gMethods[] = {
        {"nativeCallback",       "(Lcom/jesen/jnithreadinvoke/base/ICallbackMethod;)V", (void *) nativeCallback},
        {"nativeThreadCallback", "(Lcom/jesen/jnithreadinvoke/base/IThreadCallback;)V", (void *) nativeThreadCallback}
};

int registerNativeMethods(JNIEnv *pEnv, const char *name, JNINativeMethod *methods, jint mMethods) {
    jclass jclas;
    jclas = pEnv->FindClass(name);
    if (jclas == nullptr) {
        return JNI_FALSE;
    }
    if (pEnv->RegisterNatives(jclas, methods, mMethods) < 0) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

// so加载的时候会调用，用来注册方法列表，保存JavaVM全局变量
int JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    if (vm->GetEnv(reinterpret_cast<void **>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return JNI_FALSE;
    }
    // 保存JavaVM
    setJvm(vm);
    jint int_arr_len = (sizeof gMethods) / sizeof(gMethods[0]);
    registerNativeMethods(env, JAVA_INVOKE_CLASS, gMethods, int_arr_len);
    LOGI("jni onLoad call");
    return JNI_VERSION_1_6;
}
