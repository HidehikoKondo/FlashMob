//
//  NativeInterface_iOS.mm
//  Ocha
//
//  Created by UdonkoApps on 2016/07/02.
//
//

#include "NativeInterface_iOS.h"
#include "NativeInterface.h"

#import "AppController.h"
#import "RootViewController.h"


@interface NativeInterface_iOS()
@end


@implementation NativeInterface_iOS

//Watchから文字を受け取る
+ (void) getTextFromWatch:(NSString *) text
{
    cocos2dExt::NativeInterface::getTextFromWatch([text UTF8String]);
}


//Watchへ文字を送る
+ (void) putTextToWatch:(std::string) text
{
    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
    if (appController)
    {
        NSLog(@"--- cocos -> appcontroller ---");
        NSLog([NSString stringWithUTF8String:text.c_str()]);

        //TODO:
        [appController sendMessageForWatch:[NSString stringWithUTF8String:text.c_str()]];
    }
}


//コンパス
+ (float) getCompass
{
    auto direction = 0.0f;

    RootViewController * rootviewController = (RootViewController *)[UIApplication sharedApplication].keyWindow.rootViewController;
    if (rootviewController)
    {
        direction = rootviewController.direction;
    }

    return direction;
}

//読み上げてるメソッド
+ (void)speech:(NSString *)message
{
    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
    if (appController)
    {
        [appController speech:message];
    }
}

//Apple Watchにつないでいるかどうか
+ (Boolean) isWatchSession
{
    auto result = false;

    AppController *appController = (AppController *)[UIApplication sharedApplication].delegate;
    if (appController)
    {
        result = [appController isWatchSession];
    }

    return result;
}

@end
