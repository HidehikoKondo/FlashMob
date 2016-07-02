#include <string.h>
#include <jni.h>

#include "BasicsApplication.h"
#include "Listener.h"

extern "C"
{
	JNIEXPORT void JNICALL Java_demo_android_basics_BasicsActivity_startDemo(JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL Java_demo_android_basics_BasicsActivity_stopDemo(JNIEnv * env, jobject obj);
};

Listener* gListener = NULL;

JNIEXPORT void JNICALL Java_demo_android_basics_BasicsActivity_startDemo(JNIEnv* env, jobject obj)
{
	jclass clazz = env->FindClass("demo/android/basics/BasicsActivity");
	jmethodID setTextMethod = env->GetMethodID(clazz, "setText", "(Ljava/lang/String;)V");
	jmethodID onStopMethod = env->GetMethodID(clazz, "onDemoStopped", "()V");

	BasicsApplication::run(gListener = new Listener(env, obj, setTextMethod, onStopMethod));
}


JNIEXPORT void JNICALL Java_demo_android_basics_BasicsActivity_stopDemo(JNIEnv * env, jobject obj)
{
	gListener->StopDemo();
}
