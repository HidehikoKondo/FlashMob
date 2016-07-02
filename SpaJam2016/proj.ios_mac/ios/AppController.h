#import <UIKit/UIKit.h>
#import <WatchConnectivity/WatchConnectivity.h>


@class RootViewController;


@interface AppController : NSObject <UIApplicationDelegate, WCSessionDelegate>
{
    UIWindow *window;
}


@property(nonatomic, readonly) RootViewController* viewController;

- (void)speech:(NSString *)message;

@end

