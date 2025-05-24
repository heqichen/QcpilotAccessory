#include <jni.h>
#include "qcpilot/jni_adaptor.h"
#include <raymob.h>
#include <string.h>
#include <stdint.h>
#include <android/log.h>
#include <stdint.h>

#define MIN(a, b) (((a)<(b))?(a):(b))
#define MAX(a, b) (((a)>(b))?(a):(b))

// give me buffer length at least 10240
void fetchPacket(char *buffer, size_t size, size_t *outSize) {
    jobject context = GetNativeLoaderInstance();
    if (context != NULL) {
        JNIEnv *env = AttachCurrentThread();
        jclass nativeLoaderClass = (*env)->GetObjectClass(env, context);
        jfieldID qcFacadeField = (*env)->GetFieldID(env, nativeLoaderClass, "facade",
                                                    "Lcom/cooboc/qcpilot/Facade;");
        jobject qcFacade = (*env)->GetObjectField(env, context, qcFacadeField);

        if (qcFacade != NULL) {
            jclass qcFacadeClass = (*env)->GetObjectClass(env, qcFacade);

            jmethodID method = (*env)->GetMethodID(env, qcFacadeClass, "fetchPacket", "()[B");
            jbyteArray keyBytes = (jbyteArray) (*env)->CallObjectMethod(env, qcFacade, method);
            const size_t bufferSize = MIN((*env)->GetArrayLength(env, keyBytes), size);

            // obtain the array elements
            jbyte *elements = (*env)->GetByteArrayElements(env, keyBytes, NULL);
            if (!elements) {
                // handle JNI error ...
                *outSize = 0;
            } else {
                *outSize = bufferSize;
                for (int i = 0; i < bufferSize; i++) {
                    buffer[i] = elements[i];
                }
                // Do not forget to release the element array provided by JNI:
                (*env)->ReleaseByteArrayElements(env, keyBytes, elements, JNI_ABORT);
            }
        }
        DetachCurrentThread();
    }
}


// give me buffer length at least 10240
void fetchKeyboardEventList(int *buffer, size_t size, size_t *outSize) {
    jobject context = GetNativeLoaderInstance();
    if (context != NULL) {
        JNIEnv *env = AttachCurrentThread();
        jclass nativeLoaderClass = (*env)->GetObjectClass(env, context);
        jfieldID qcFacadeField = (*env)->GetFieldID(env, nativeLoaderClass, "facade",
                                                    "Lcom/cooboc/qcpilot/Facade;");
        jobject qcFacade = (*env)->GetObjectField(env, context, qcFacadeField);

        if (qcFacade != NULL) {
            jclass qcFacadeClass = (*env)->GetObjectClass(env, qcFacade);

            jmethodID method = (*env)->GetMethodID(env, qcFacadeClass, "fetchKeyboardEvents",
                                                   "()[I");
            jintArray keyList = (jintArray) (*env)->CallObjectMethod(env, qcFacade, method);
            const size_t bufferSize = MIN((*env)->GetArrayLength(env, keyList), size);

            // obtain the array elements
            jint *elements = (*env)->GetIntArrayElements(env, keyList, NULL);
            if (!elements) {
                // handle JNI error ...
                *outSize = 0;
            } else {
                *outSize = bufferSize;
                for (int i = 0; i < bufferSize; i++) {
                    buffer[i] = elements[i];
                }
                // Do not forget to release the element array provided by JNI:
                (*env)->ReleaseIntArrayElements(env, keyList, elements, JNI_ABORT);
            }
        }
        DetachCurrentThread();
    }
}



// static char buffer[10240];
// static size_t bufferSize = 0U;
// static uint64_t lastReceivedElapsedTime = 0U;

// void readPacket() {
//     jobject context = GetNativeLoaderInstance();
//     if (context != NULL) {
//         JNIEnv *env = AttachCurrentThread();
//         jclass nativeLoaderClass = (*env)->GetObjectClass(env, context);

//         jfieldID qcFacadeField = (*env)->GetFieldID(env, nativeLoaderClass, "facade",
//                                                     "Lcom/cooboc/qcpilot/Facade;");
//         jobject qcFacade = (*env)->GetObjectField(env, context, qcFacadeField);

//         if (qcFacade != NULL) {
//             jclass qcFacadeClass = (*env)->GetObjectClass(env, qcFacade);
//             {
//                 jmethodID method = (*env)->GetMethodID(env, qcFacadeClass, "fun", "()[B");
//                 jbyteArray keyBytes = (jbyteArray) (*env)->CallObjectMethod(env, qcFacade, method);
//                 bufferSize = (*env)->GetArrayLength(env, keyBytes);

//                 // obtain the array elements
//                 jbyte *elements = (*env)->GetByteArrayElements(env, keyBytes, NULL);
//                 if (!elements) {
//                     // handle JNI error ...
//                 }
//                 for (int i = 0; i < bufferSize; i++) {
//                     buffer[i] = elements[i];
//                 }
//                 // Do not forget to release the element array provided by JNI:
//                 (*env)->ReleaseByteArrayElements(env, keyBytes, elements, JNI_ABORT);
//             }
//             {
//                 jmethodID timeMethod = (*env)->GetMethodID(env, qcFacadeClass,
//                                                            "getLastReceivedElapsedMillis", "()J");
//                 jlong ret = (jlong) (*env)->CallLongMethod(env, qcFacade, timeMethod);
//                 lastReceivedElapsedTime = ret;
//             }


//         }

//         DetachCurrentThread();
//     }
// }

// uint8_t *getBuffer() {
//     return (uint8_t *) buffer;
// }

// size_t getBufferSize() {
//     return bufferSize;
// }

// uint64_t a_getLastReceivedElapsedMillis() {
//     return lastReceivedElapsedTime;
// }