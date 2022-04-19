//
// Created by X1 Carbon on 2022/4/18.
//

#ifndef NDK_JNI_CMAKE_BASE_H
#define NDK_JNI_CMAKE_BASE_H

#include <android/log.h>
#include <jni.h>

#define LOG_TAG "JESEN_JNI"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


#endif //NDK_JNI_CMAKE_BASE_H
