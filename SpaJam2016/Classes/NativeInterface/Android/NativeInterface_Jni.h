//
//  NativeInterface_Jni.h
//  Ocha
//
//  Created by UdonkoApps on 2016/07/02.
//
//

#ifndef __NativeInterface_Jni__
#define __NativeInterface_Jni__

#include "cocos2d.h"

//#include <jni.h>
#include "platform/android/jni/JniHelper.h"


#ifdef __cplusplus
extern "C" {
#endif

    //Watchから文字を受け取る(Android -> cocos2d-x)
    JNIEXPORT
    void JNICALL Java_com_udonkoapps_jni_NativeInterface_getTextFromWatch(JNIEnv * env, jobject obj);

    //Watchへ文字を送る
    void putTextToWatchJni(const char * text);

    //コンパス(Android -> cocos2d-x)
    float getCompassJni();

    //読み上げてるメソッド
    void speechJni(const char * message);

#ifdef __cplusplus
}
#endif

#endif
