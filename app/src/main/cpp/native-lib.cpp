#include <jni.h>
#include <string>
#include <fmod.hpp>
#include <android/log.h>

using namespace FMOD;

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_ndk_1jni_1cmake_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {

    System *system;
    System_Create(&system);
    unsigned int version;
    system->getVersion(&version);
    __android_log_print(ANDROID_LOG_ERROR,"TEST","FMOD Version:%08x",version);

    char *vs = (char *) malloc(sizeof(char) * 16);
    sprintf(vs,"%08x",version);
    std::string hello = "Hello from C++";
    hello = hello.append("\nFMOD Version:").append(vs);
    return env->NewStringUTF(hello.c_str());
}
