#include <android/log.h>

#include "Listener.h"
#include "Common-cpp/inc/JString.h"
#include "Common-cpp/inc/UTF8String.h"

#define APP_TAG "demo-basics"

Listener::Listener(JNIEnv* env, jobject obj, jmethodID writeMethod, jmethodID onStopMethod)
	: mEnv(env)
	, mObj(env->NewGlobalRef(obj))
	, mMethod(writeMethod)
	, mOnStopMethod(onStopMethod)
	, mShouldStop(false)
{}

Listener::~Listener(void)
{
	mEnv->DeleteGlobalRef(mObj);
}

void Listener::StopDemo(void)
{
	mShouldStop = true;
}

void Listener::writeString(const ExitGames::Common::JString& str)
{
	write(str.UTF8Representation().cstr());
}

void Listener::write(const char* str)
{
	__android_log_print(ANDROID_LOG_INFO, APP_TAG, "%s", str);
	jstring jstr = mEnv->NewStringUTF(str);
	mEnv->CallVoidMethod(mObj, mMethod, jstr);
	mEnv->DeleteLocalRef(jstr);
}

bool Listener::anyKeyPressed(void) const
{
	return mShouldStop;
}

void Listener::onLibClosed(void)
{
	__android_log_print(ANDROID_LOG_INFO, APP_TAG, "OnLibClosed");
	mEnv->CallVoidMethod(mObj, mOnStopMethod);
}