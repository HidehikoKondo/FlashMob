#ifndef __ANDROID_UI_LISTENER_H
#define __ANDROID_UI_LISTENER_H

#include <jni.h>
#include "UIListener.h"

class AndroidUIListener: public UIListener
{
public:
	AndroidUIListener(JNIEnv* env, jobject obj, jmethodID writeMethod, jmethodID onStopMethod);
	~AndroidUIListener(void);
	void StopDemo(void);

public:
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

#endif