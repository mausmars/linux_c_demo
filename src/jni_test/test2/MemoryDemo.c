#include <jni.h>
#include <stdio.h>
#include "MemoryDemo.h"

JNIEXPORT jlong JNICALL Java_MemoryDemo_jmalloc
(JNIEnv *env, jobject thiz, jint size){
    printf("c malloc! \r\n");
    char* p = (char*) malloc(size);
    memset(p, 0, size);
    return p;
}


JNIEXPORT void JNICALL Java_MemoryDemo_jfree
(JNIEnv *env, jobject thiz, jlong p){
    printf("c free! \r\n");
    free(p);
}