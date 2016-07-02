#import "OutputListener.h"
#import "Chat-objc/inc/EGChatClient.h"

typedef enum _Input
{
	INPUT_NON = 0,
	INPUT_CONNECT,
	INPUT_DISCONNECT,
	INPUT_SUBSCRIBE,
	INPUT_SET_FRIENDS,
	INPUT_EXIT,
    INPUT_SET_ONLINE_STATUS // base for several buttons, so keep it last in list
} Input;

@protocol ChatDemoView

@property (readonly) NSString* UserID;

- (void) onClientStateChange:(int)state :(NSString*)stateStr;
- (void) onSubscribeStateSet:(int)state;
- (void) onSetFriendsStateSet:(int)state;

@end


@interface NetworkLogic : NSObject <EGChatListener>
{
@private
	EGChatClient* mChatClient;
	EGLogger* mLogger;
    id<ChatDemoView> mView;
	id<OutputListener> mOutputListener;
    int mSubscribeState;
    int mSetFriendsState;
	int mLastInput;
	NSString* mMessageToSend;
}

@property (readwrite) int LastInput;
@property (readwrite, copy) NSString* MessageToSend;

- (NetworkLogic*) initWithOutputListener:(id<OutputListener>)listener :(id<ChatDemoView>)view;
+ (NetworkLogic*) networkLogicWithOutputListener:(id<OutputListener>)listener :(id<ChatDemoView>)view;
- (void) run;

@end