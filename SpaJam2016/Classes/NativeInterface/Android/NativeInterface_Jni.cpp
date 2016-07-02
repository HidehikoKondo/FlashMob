//
//  NativeInterface_Jni.c
//  Ocha
//
//  Created by UdonkoApps on 2016/07/02.
//
//

#include "NativeInterface.h"
#include "NativeInterface_Jni.h"


//ClassPass ... 毎回メンドクサイのでやりとりする窓口は固定
#define CLASS_NAME  "com/udonkoapps/jni/NativeInterface"


#ifdef __cplusplus
extern "C" {
#endif


    //Watchから文字を受け取る(Android -> cocos2d-x)
    JNIEXPORT
    void JNICALL Java_com_udonkoapps_jni_NativeInterface_getTextFromWatch
    (JNIEnv * env, jobject obj)
    {
        cocos2dExt::NativeInterface::getTextFromWatch("");
    }


    //Watchへ文字を送る
    void putTextToWatchJni(const char * text)
    {
        cocos2d::JniMethodInfo methodInfo;

        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
                                                    CLASS_NAME,
                                                    "putTextToWatch",
                                                    "(Ljava/lang/String;)V") )
        {
            //生成(ローカル)
            jstring strArgText = methodInfo.env->NewStringUTF(text);

            //実行
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, strArgText);

            //解放
            methodInfo.env->DeleteLocalRef(methodInfo.classID);

            //解放(ローカル)
            methodInfo.env->DeleteLocalRef(strArgText);
        }
    }


    //コンパス(Android -> cocos2d-x)
    float getCompassJni()
    {
        auto result = 0.0f;

        cocos2d::JniMethodInfo methodInfo;

        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
                                                    CLASS_NAME,
                                                    "getCompass",
                                                    "()F") )
        {
            //実行
            result = methodInfo.env->CallStaticFloatMethod(methodInfo.classID, methodInfo.methodID);

            //解放
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }

        return result;
    }


    //読み上げてるメソッド
    void speechJni(const char * message)
    {
        cocos2d::JniMethodInfo methodInfo;

        if (cocos2d::JniHelper::getStaticMethodInfo(methodInfo,
                                                      CLASS_NAME,
                                                      "speech",
                                                      "(Ljava/lang/String;)V") )
        {
            //生成(ローカル)
            jstring strArgMessage = methodInfo.env->NewStringUTF(message);

            //実行
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, strArgMessage);

            //解放
            methodInfo.env->DeleteLocalRef(methodInfo.classID);

            //解放(ローカル)
            methodInfo.env->DeleteLocalRef(strArgMessage);
        }
    }


#ifdef __cplusplus
}
#endif
