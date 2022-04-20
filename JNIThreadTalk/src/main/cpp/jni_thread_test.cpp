//
// Created by X1 Carbon on 2022/4/20.
// 线程的创建

#include <base.h>
#include <stdio.h>
#include <pthread.h>
#include <jvm.h>
#include <unistd.h>
#include <queue>

// 线程1执行的方法
void *thread1Method(void *) {
    // 耗时操作
    sleep(1);
    LOGI("I am the first thread.");
    return nullptr;
}

// 定义一个结构体
struct ThreadRunArgs {
    int id;
    int result;
};

// 线程2执行的方法
void *thread2ArgsMethod(void *arg) {
    ThreadRunArgs *args = static_cast<ThreadRunArgs *>(arg);
    LOGI("I am second thread, id is %d", args->id);
    LOGI("I am second thread, result is %d", args->result);
    // 手动退出线程
    pthread_exit(0);
    //return nullptr;
}

void *thread3MethodJoin(void *arg) {
    ThreadRunArgs *args = static_cast<ThreadRunArgs *>(arg);
    struct timeval begin;
    gettimeofday(&begin, nullptr);
    LOGI("thread3MethodJoin start time is :%lld", begin.tv_sec);

    sleep(1);
    struct timeval end;
    gettimeofday(&end, nullptr);
    LOGI("thread3MethodJoin end time is :%lld", end.tv_sec);
    LOGI("thread3MethodJoin ,time used is %d", end.tv_sec - begin.tv_sec);

    return reinterpret_cast<void *>(args->result);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jesen_jnithreadtalk_JNIThreadTest_createNativeThread(JNIEnv *env, jobject thiz) {
    // 1. 简单创建一个线程
    pthread_t handles;
    int result = pthread_create(&handles, nullptr, thread1Method, nullptr);
    if (result == 0) {
        LOGI(" createNativeThread, create thread success.");
    } else {
        LOGI(" createNativeThread, create thread failed.");
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jesen_jnithreadtalk_JNIThreadTest_createNativeThreadWithArgs(JNIEnv *env, jobject thiz) {
    // 2. 创建一个带参数线程
    pthread_t handles;
    ThreadRunArgs *args = new ThreadRunArgs;
    args->id = 2;
    args->result = 10;
    int result = pthread_create(&handles, nullptr, thread2ArgsMethod, args);
    if (result == 0) {
        LOGI(" createNativeThreadWithArgs, create thread success.");
    } else {
        LOGI(" createNativeThreadWithArgs, create thread failed.");
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jesen_jnithreadtalk_JNIThreadTest_joinNativeThread(JNIEnv *env, jobject thiz) {
    // join 挂起子线程 等待执行结果
    pthread_t handles;
    ThreadRunArgs *args = new ThreadRunArgs;
    args->id = 3;
    args->result = 11;
    int result = pthread_create(&handles, nullptr, thread3MethodJoin, args);

    if (result == 0) {
        LOGI(" joinNativeThread, create thread success.");
        void *ret = nullptr;
        pthread_join(handles, &ret);
        LOGI("joinNativeThread, result is %d", ret);
    } else {
        LOGI(" joinNativeThread, create thread failed.");
    }
}