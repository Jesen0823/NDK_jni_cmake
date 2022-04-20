#include <jni.h>

//
// Created by X1 Carbon on 2022/4/20.
// 生产者消费者
#include "base.h"
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <queue>

using namespace std;

queue<int> data;
pthread_mutex_t dataMutex;
pthread_cond_t dataCond;

void *productMethod(void *) {
    while (data.size() < 10) {
        pthread_mutex_lock(&dataMutex);
        LOGI("生产者生产");
        data.push(1);
        if (data.size() > 0) {
            LOGI("等待消费...");
            pthread_cond_signal(&dataCond);
        }
        pthread_mutex_unlock(&dataMutex);
        sleep(2);
    }
    pthread_exit(0);
}


[[noreturn]] void *consumerMethod(void *) {
    while (1) {
        pthread_mutex_lock(&dataMutex);
        if (data.size() > 0) {
            LOGI("消费物品");
            data.pop();
        } else {
            LOGI("没有产品了，等待生产");
            pthread_cond_wait(&dataCond, &dataMutex);
        }
        pthread_mutex_unlock(&dataMutex);
        sleep(1);
    }
    pthread_exit(0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_jesen_jnithreadtalk_JNIProductConsumer_startProductConsumer(JNIEnv *env, jobject thiz) {
    // 生产者消费者
    pthread_mutex_init(&dataMutex, nullptr);
    pthread_cond_init(&dataCond, nullptr);

    pthread_t productThread;
    pthread_t consumerThread;

    pthread_create(&productThread, nullptr, productMethod, nullptr);
    pthread_create(&consumerThread, nullptr, consumerMethod, nullptr);
}