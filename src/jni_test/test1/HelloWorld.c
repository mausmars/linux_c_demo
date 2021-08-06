#include <jni.h>
#include <stdio.h>
#include "../HelloWorld.h"

char* JstringTostr2(JNIEnv* env, jstring jstr) {
	char* pStr = NULL;
	jclass jstrObj = (*env)->FindClass(env, "java/lang/String");
	jstring encode = (*env)->NewStringUTF(env, "utf-8");
	jmethodID methodId = (*env)->GetMethodID(env, jstrObj, "getBytes", "(Ljava/lang/String;)[B");
	jbyteArray byteArray = (jbyteArray)(*env)->CallObjectMethod(env, jstr,
			methodId, encode);
	jsize strLen = (*env)->GetArrayLength(env, byteArray);
	jbyte *jBuf = (*env)->GetByteArrayElements(env, byteArray, JNI_FALSE);

	if (jBuf > 0) {
		pStr = (char*) malloc(strLen + 1);
		if (!pStr) {
			return NULL;
		}
		memcpy(pStr, jBuf, strLen);
		pStr[strLen] = 0;
	}
	(*env)->ReleaseByteArrayElements(env, byteArray, jBuf, 0);
	return pStr;
}

//C字符串转java字符串
jstring StrToJstring(JNIEnv* env, const char* pStr) {
	int strLen = strlen(pStr);
	jclass jstrObj = (*env)->FindClass(env, "java/lang/String");
	jmethodID methodId = (*env)->GetMethodID(env, jstrObj, "<init>",
			"([BLjava/lang/String;)V");
	jbyteArray byteArray = (*env)->NewByteArray(env, strLen);
	jstring encode = (*env)->NewStringUTF(env, "utf-8");
	(*env)->SetByteArrayRegion(env, byteArray, 0, strLen, (jbyte*) pStr);
	return (jstring)(*env)->NewObject(env, jstrObj, methodId, byteArray, encode);
}

JNIEXPORT void JNICALL
Java_HelloWorld_test1(JNIEnv *env, jobject thiz) {
	printf("test1! \r\n");
	return;
}

JNIEXPORT jobject JNICALL
Java_HelloWorld_test2(JNIEnv *env, jobject thiz, jobject obj_obj1) {
	printf("test2! \r\n");

	jclass testcls1 = (*env)->GetObjectClass(env, obj_obj1);
	if (testcls1 == NULL) {
		printf("GetObjectClass failed \n");
	}
	jfieldID ageFieldID = (*env)->GetFieldID(env, testcls1, "age", "I");
	jfieldID nameFieldID = (*env)->GetFieldID(env, testcls1, "name",
			"Ljava/lang/String;");
	jint age1 = (*env)->GetIntField(env, obj_obj1, ageFieldID);  //获得属性值
	jstring name1 = (jstring)(*env)->GetObjectField(env, obj_obj1, nameFieldID); //获得属性值

	printf("HelloWorld_test2 age=%d \r\n", age1);
	printf("HelloWorld_test2 name1=%s \r\n", JstringTostr2(env, name1));

	//c语言需要(*env)，每个方法第一个参数为env
	jclass testcls2 = (*env)->FindClass(env, "TestBean");
	jmethodID constrocMID = (*env)->GetMethodID(env, testcls2, "<init>",
			"(ILjava/lang/String;)V");
	jstring name2 = (*env)->NewStringUTF(env, "come from native!!!");
	jint age2 = 22;
	jobject test_ojb = (*env)->NewObject(env, testcls2, constrocMID, age2,
			name2);
	return test_ojb;

//	return obj_obj1;
}
