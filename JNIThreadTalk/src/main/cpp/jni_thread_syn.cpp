//
// Created by X1 Carbon on 2022/4/20.
// 线程同步

#include <base.h>
#include <stdio.h>
#include <pthread.h>
#include <jvm.h>
#include <unistd.h>
#include <queue>

pthread_mutex_t mutex; //互斥变量
pthread_cond_t cond; //条件变量

pthread_t waitThread;
pthread_t notifyThread;

int flag = 0;

void *waitThreadMothed(void *) {
    // 加锁
    pthread_mutex_lock(&mutex);
    LOGI("I has been locked.");
    while (flag == 0) {
        LOGI("I am waiting.");
        pthread_cond_wait(&cond, &mutex);
    }
    LOGI("I am weakUp.");
    // 解锁
    pthread_mutex_unlock(&mutex);
    pthread_exit(0);
}

void *notifyThreadMothed(void *) {
    LOGI("notify lock.");
    // 加锁
    pthread_mutex_lock(&mutex);
    flag = 1;
    // 解锁
    pthread_mutex_unlock(&mutex);

    // 唤醒等待的线程
    pthread_cond_signal(&cond);
    LOGI("notify unlock.");
    pthread_exit(0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jesen_jnithreadtalk_JNIThreadSyn_waitNativeThread(JNIEnv *env, jobject thiz) {
    // 创建线程并wait
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond, nullptr);

    pthread_create(&waitThread, nullptr, waitThreadMothed, nullptr);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_jesen_jnithreadtalk_JNIThreadSyn_notifyNativeThread(JNIEnv *env, jobject thiz) {
    // notify阻塞的线程
    pthread_create(&notifyThread, nullptr, notifyThreadMothed, nullptr);

}