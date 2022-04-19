//
// Created by X1 Carbon on 2022/4/19.
//

#include "jvm.h"
#include "base.h"

static JavaVM* gVM = nullptr;

#ifdef __cplusplus
extern "C"{
#endif

void setJvm(JavaVM *jvm){
    gVM = jvm;
}

JavaVM *getJvm(){
    return gVM;
}

#ifdef __cplusplus
}
#endif