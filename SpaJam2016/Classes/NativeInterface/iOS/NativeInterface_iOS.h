//
//  NativeInterface_iOS.h
//  Ocha
//
//  Created by UdonkoApps on 2016/07/02.
//
//

#import <Foundation/Foundation.h>
#include "cocos2d.h"

#import <CoreLocation/CoreLocation.h>
@interface CompassViewController : UIViewController
<CLLocationManagerDelegate> {
    CLLocationManager *locationManager;
}
@end


@interface NativeInterface_iOS

//Watchから文字を受け取る
+ (void) getTextFromWatch:(NSString *) text;

//Watchへ文字を送る
+ (void) putTextToWatch:(std::string) text;

//コンパス
+ (float) getCompass;

//読み上げてるメソッド
+ (void)speech:(NSString *)message;

//Apple Watchにつないでいるかどうか
+ (Boolean) isWatchSession;

@end
