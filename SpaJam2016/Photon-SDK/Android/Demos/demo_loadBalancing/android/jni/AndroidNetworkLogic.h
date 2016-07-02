#ifndef __ANDROID_NETWORK_LOGIC_H
#define __ANDROID_NETWORK_LOGIC_H

#include <jni.h>

#include "NetworkLogic.h"

class AndroidNetworkLogic: public NetworkLogic, OutputListener, NetworkLogicListener
{
public:
	AndroidNetworkLogic(JNIEnv* env, jobject obj, jmethodID writeMethod, jmethodID stateUpdateMethod);
	~AndroidNetworkLogic(void);

	virtual void write(const ExitGames::Common::JString& str);
	virtual void writeLine(const ExitGames::Common::JString& str);
	virtual void debugReturn(int debugLevel, const ExitGames::Common::JString& str);
	virtual void stateUpdate(State newState);
private:
	JNIEnv* mEnv;
	jobject mObj;
	jmethodID mWriteMethod;
	jmethodID mStateUpdateMethod;
};

#endif