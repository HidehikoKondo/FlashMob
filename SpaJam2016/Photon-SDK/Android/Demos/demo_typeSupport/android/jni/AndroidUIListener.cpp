
#include <string.h>
#include <jni.h>
#include <wchar.h>
#include <android/log.h>

#include "AndroidUIListener.h"
#include "Common-cpp/inc/JString.h"
#include "Common-cpp/inc/UTF8String.h"


#define APP_TAG "demo-typeSupport"

AndroidUIListener::AndroidUIListener(JNIEnv* env, jobject obj, jmethodID writeMethod, jmethodID onStopMethod)
	: mEnv(env)
	, mObj(env->NewGlobalRef(obj))
	, mMethod(writeMethod)
	, mOnStopMethod(onStopMethod)
	, mShouldStop(false)
{}

AndroidUIListener::~AndroidUIListener(void)
{
	mEnv->DeleteGlobalRef(mObj);
}

void AndroidUIListener::StopDemo(void)
{
	mShouldStop = true;
}

void AndroidUIListener::writeString(const ExitGames::Common::JString& str)
{
	write(str.UTF8Representation().cstr());
}

void AndroidUIListener::write(const char* str)
{
	__android_log_print(ANDROID_LOG_INFO, APP_TAG, "%s", str);
	jstring jstr = mEnv->NewStringUTF(str);
	mEnv->CallVoidMethod(mObj, mMethod, jstr);
	mEnv->DeleteLocalRef(jstr);
}

bool AndroidUIListener::anyKeyPressed(void) const
{
	return mShouldStop;
}

void AndroidUIListener::onLibClosed(void)
{
	__android_log_print(ANDROID_LOG_INFO, APP_TAG, "OnLibClosed");
	mEnv->CallVoidMethod(mObj, mOnStopMethod);
}