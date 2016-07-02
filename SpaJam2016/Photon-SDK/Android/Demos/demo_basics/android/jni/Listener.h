#pragma once

#include <jni.h>
#include "UIListener.h"

class Listener: public UIListener
{
public:
	Listener(JNIEnv* env, jobject obj, jmethodID writeMethod, jmethodID onStopMethod);
	~Listener(void);
	void StopDemo(void);

	virtual void writeString(const ExitGames::Common::JString& str);
	virtual bool anyKeyPressed(void) const;
	virtual void onLibClosed(void);
private:
	void write(const char* str);

	JNIEnv* mEnv;
	jobject mObj;
	jmethodID mMethod;
	jmethodID mOnStopMethod;
	bool mShouldStop;
};