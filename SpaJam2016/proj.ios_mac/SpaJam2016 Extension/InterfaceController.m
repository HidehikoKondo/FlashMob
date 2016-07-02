//
//  InterfaceController.m
//  SpaJam2016 Extension
//
//  Created by UdonkoApps on 2016/07/02.
//
//

#import "InterfaceController.h"
#import <CoreMotion/CoreMotion.h>

@interface InterfaceController()
@property (unsafe_unretained, nonatomic) IBOutlet WKInterfaceLabel *messageLabel;
@property (nonatomic) double xPos;

@end


@implementation InterfaceController{
    CMMotionManager *motionManager;
}

- (void)awakeWithContext:(id)context {
    
    
    self.xPos = 0;
    
    [super awakeWithContext:context];
    
    if ([WCSession isSupported]) {
        WCSession *session = [WCSession defaultSession];
        session.delegate = self;
        [session activateSession];
    }
    
    
    // Configure interface objects here.
}

- (void)willActivate {
    // This method is called when watch view controller is about to be visible to user
    
    //加速度センサー開始
    motionManager = [[CMMotionManager alloc] init];
    [motionManager startAccelerometerUpdates];
    [self setupAccelerometer];
    
    [super willActivate];
}


- (void)setupAccelerometer{
    if (motionManager.accelerometerAvailable){
        // センサーの更新間隔の指定、２Hz
        motionManager.accelerometerUpdateInterval = 0.2f;
        
        // ハンドラを設定
        CMAccelerometerHandler handler = ^(CMAccelerometerData *data, NSError *error)
        {
            // 加速度センサー
            double xac = data.acceleration.x;
            double yac = data.acceleration.y;
            double zac = data.acceleration.z;
            
            
            if((xac - _xPos) > 0.5f || (xac - _xPos) < -0.5f){
                NSLog(@"---SWING!!---");
                [self submit:@"SWING"];
            }
            
            
            self.xPos = xac;
            
            // 画面に表示
            NSLog([NSString stringWithFormat:@"x: %0.3f", _xPos]);
            
            //NSLog([NSString stringWithFormat:@"x: %0.3f", xac]);
            //NSLog([NSString stringWithFormat:@"y: %0.3f", yac]);
            //NSLog([NSString stringWithFormat:@"z: %0.3f", zac]);
            
        };
        
        // 加速度の取得開始
        [motionManager startAccelerometerUpdatesToQueue:[NSOperationQueue currentQueue] withHandler:handler];
    }
}


- (void)didDeactivate {
    // This method is called when watch view controller is no longer visible
    [super didDeactivate];
}


//ボタンをタップで通知
-(IBAction)submitNotification:(id)sender{
    NSLog(@"通知送る");
    [self submit:@"SWING"];
}


-(void)submit:(NSString *)message{
    NSDictionary *applicationDict = @{@"message" : message};
    [[WCSession defaultSession] updateApplicationContext:applicationDict error:nil];
    
    
    if ([[WCSession defaultSession] isReachable]) {
        [[WCSession defaultSession] sendMessage:applicationDict
                                   replyHandler:^(NSDictionary *replyHandler) {
                                       // do something
                                       NSLog(@"送った/ %@",message);
                                   }
                                   errorHandler:^(NSError *error) {
                                       // do something
                                       NSLog(@"送れなかった・・・orz");
                                   }
         ];
    }else{
        NSLog(@"つながってないよ");
    }
}

// Interactive Message
// 受信
- (void)session:(nonnull WCSession *)session didReceiveMessage:(nonnull NSDictionary<NSString *,id> *)message replyHandler:(nonnull void (^)(NSDictionary<NSString *,id> * __nonnull))replyHandler
{
    dispatch_async(dispatch_get_main_queue(), ^{
        NSLog(@"---");
        NSLog([message objectForKey:@"message"]);
        NSLog(@"---");
        NSLog([NSString stringWithFormat:@"----   app -> watch SUCCESS!!!!   ----%@", [message objectForKey:@"message"]]);
        
        [_messageLabel setText:[message objectForKey:@"message"]];
        
        
        // 4番だったら音声入力モードにする
        if([[message objectForKey:@"message"] isEqualToString:@"4"]){
            //音声入力モードにする
            NSArray* suggestions = @[@"こんにちは",@"ハロー",@"グーテンモルゲン"];
            [self presentTextInputControllerWithSuggestions:nil
                                           allowedInputMode:WKTextInputModePlain
                                                 completion:^(NSArray *results) {
                                                     //音声入力
                                                     if (results && results.count > 0) {
                                                         id aResult = [results objectAtIndex:0];
                                                         NSLog(@"音声入力：%@",(NSString*)aResult);
                                                         
                                                         if(![aResult isEqualToString:@""]){
                                                             //実演用になんか言えば良しとする　ほんとはどうぞって言うようにしたい
                                                             [_messageLabel setText:@"どうぞ"];
                                                             [self submit:@"DOUZO"];
                                                             
                                                         }else{
                                                             [_messageLabel setText:@"どうぞと言ってください"];
                                                         }
                                                     }
                                                     else {
                                                         // 文字が選択されていません。
                                                     }
                                                 }];
            
        }
        
        
    });
    
    replyHandler(@{@"reply" : @"OK"});
    
}


@end



