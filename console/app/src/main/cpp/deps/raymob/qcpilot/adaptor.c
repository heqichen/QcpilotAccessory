#include <jni.h>
#include "qcpilot/adaptor.h"
#include <raymob.h>
#include <string.h>

static int count = 0;

static char buffer[10240];

char * foo() {
    buffer[0] = '\0';
    count += 10;
    jobject context = GetNativeLoaderInstance();
    if (context != NULL) {
        JNIEnv *env = AttachCurrentThread();
        jclass nativeLoaderClass = (*env)->GetObjectClass(env, context);

        jfieldID qcFacadeField = (*env)->GetFieldID(env, nativeLoaderClass, "facade",
                                                    "Lcom/cooboc/qcpilot/Facade;");
        jobject qcFacade = (*env)->GetObjectField(env, context, qcFacadeField);

        if (qcFacade != NULL) {
            jclass qcFacadeClass = (*env)->GetObjectClass(env, qcFacade);
            jmethodID method = (*env)->GetMethodID(env, qcFacadeClass, "fun", "()[B");
            jbyteArray keyBytes = (jbyteArray) (*env)->CallObjectMethod(env, qcFacade, method);
            count = (*env)->GetArrayLength(env, keyBytes);

            // obtain the array elements
            jbyte *elements = (*env)->GetByteArrayElements(env, keyBytes, NULL);
            if (!elements) {
                // handle JNI error ...
            }

            for (int i = 0; i < count; i++) {
                buffer[i] = elements[i];
            }

            // Do not forget to release the element array provided by JNI:
            (*env)->ReleaseByteArrayElements(env, keyBytes, elements, JNI_ABORT);

        }

        DetachCurrentThread();
    }
    return buffer;
}