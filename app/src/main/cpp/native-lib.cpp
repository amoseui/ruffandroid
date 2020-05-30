#include <jni.h>
#include <string>

#include "main.h"

extern "C" JNIEXPORT jstring JNICALL
Java_com_amoseui_ruffjni_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++ " + std::to_string(test());
    return env->NewStringUTF(hello.c_str());
}
