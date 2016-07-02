//
//  NativeInterface.cpp
//  Ocha
//
//  Created by UdonkoApps on 2016/07/02.
//
//

#include "NativeInterface.h"
#include "NativeInterface_Jni.h"

#include "cocos2d.h"
#include "PrivateConfig.h"


namespace cocos2dExt
{
    //Watchから文字を受け取る
    void NativeInterface::getTextFromWatch(const std::string &text)
    {
        //イベントでわたしてみる (必要なとこで受け取る)
        auto event = cocos2d::EventCustom(EVENT_NAME__TEXTFROMWATCH);

        auto data = cocos2d::Value(text);
        event.setUserData(&data);

        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
    }

    void NativeInterface::putTextToWatch(const std::string &text)
    {
        putTextToWatchJni(text.c_str());
    }

    //コンパス
    float NativeInterface::getCompass()
    {
        auto pos = getCompassJni();
        return pos;
    }

    //読み上げてるメソッド
    void NativeInterface::speech(const std::string &message)
    {
        speechJni(message.c_str());
    }
};
