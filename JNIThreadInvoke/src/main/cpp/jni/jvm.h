//
// Created by X1 Carbon on 2022/4/19.
//

#ifndef NDK_JNI_CMAKE_JVM_H
#define NDK_JNI_CMAKE_JVM_H

#include "base.h"

#ifdef __cplusplus
extern "C"{
#endif

void setJvm(JavaVM *jvm);

JavaVM *getJvm();

#ifdef __cplusplus
}
#endif

#endif //NDK_JNI_CMAKE_JVM_H
