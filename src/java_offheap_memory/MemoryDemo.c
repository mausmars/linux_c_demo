#include <jni.h>
#include <stdio.h>
#include "MemoryDemo.h"

JNIEXPORT jlong JNICALL Java_MemoryDemo_jmalloc
(JNIEnv *env, jobject thiz, jint size){
    char* p = (char*) malloc(size);
    memset(p, 0, size);
    printf("c malloc size=(%zu) %p ! \n",size,p);
    return p;
}


JNIEXPORT void JNICALL Java_MemoryDemo_jfree
(JNIEnv *env, jobject thiz, jlong p){
    free(p);
    printf("c free %p ! \n",p);
}