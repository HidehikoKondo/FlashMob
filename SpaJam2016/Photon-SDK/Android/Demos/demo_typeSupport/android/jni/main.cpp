#include <string.h>
#include <jni.h>

#include "TypeSupportApplication.h"
#include "AndroidUIListener.h"

extern "C"
{
	JNIEXPORT void JNICALL Java_demo_android_typeSupport_DemoActivity_startDemo(JNIEnv * env, jobject obj);
	JNIEXPORT void JNICALL Java_demo_android_typeSupport_DemoActivity_stopDemo(JNIEnv * env, jobject obj);
};

AndroidUIListener* gListener = NULL;

JNIEXPORT void JNICALL Java_demo_android_typeSupport_DemoActivity_startDemo(JNIEnv* env, jobject obj)
{
	jclass clazz = env->FindClass("demo/android/typeSupport/DemoActivity");
	jmethodID addTextMethod = env->GetMethodID(clazz, "addText", "(Ljava/lang/String;)V");
	jmethodID onStopMethod = env->GetMethodID(clazz, "onDemoStopped", "()V");

	TypeSupportApplication::run(gListener = new AndroidUIListener(env, obj, addTextMethod, onStopMethod));
}

JNIEXPORT void JNICALL Java_demo_android_typeSupport_DemoActivity_stopDemo(JNIEnv * env, jobject obj)
{
	gListener->StopDemo();
}