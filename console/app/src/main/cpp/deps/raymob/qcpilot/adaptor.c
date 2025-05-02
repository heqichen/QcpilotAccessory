#include <jni.h>
#include "qcpilot/adaptor.h"
#include <raymob.h>

static int count = 0;



int  foo() {
    count += 10;
    jobject context = GetNativeLoaderInstance();
    if (context != NULL) {
        JNIEnv* env = AttachCurrentThread();
        jclass nativeLoaderClass = (*env)->GetObjectClass(env, context);

        jfieldID qcFacadeField = (*env)->GetFieldID(env, nativeLoaderClass, "facade", "Lcom/cooboc/qcpilot/Facade;");
        jobject qcFacade = (*env)->GetObjectField(env, context, qcFacadeField);

        if (qcFacade != NULL) {
            jclass qcFacadeClass = (*env)->GetObjectClass(env, qcFacade);
            jmethodID method = (*env)->GetMethodID(env, qcFacadeClass, "fun", "()I");
            jint ret = (*env)->CallIntMethod(env, qcFacade, method);
            count = (int)ret;

        }

        DetachCurrentThread();
    }


    return count;



    }