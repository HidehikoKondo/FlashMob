#include "Common-cpp/inc/Common.h"
#include "Chat-cpp/inc/Client.h"
#import "NetworkLogic.h"
#import "DemoConstants.h"

namespace EGDbgLvl = ExitGames::Common::DebugLevel;

@interface NetworkLogic ()

@property (readonly) EGLogger* Logger;
@property int SubscribeState;
@property int SetFriendsState;

@end

@implementation NetworkLogic

// properties

@synthesize LastInput = mLastInput;
@synthesize MessageToSend = mMessageToSend;
@synthesize Logger = mLogger;

- (void) setSubscribeState:(int)s
{
	mSubscribeState = s;
	[mView onSubscribeStateSet:s];
}
- (int) SubscribeState
{
	return mSubscribeState;
}

- (void) setSetFriendsState:(int)s
{
	mSetFriendsState = s;
	[mView onSetFriendsStateSet:s];
}

- (int) SetFriendsState
{
	return mSetFriendsState;
}
// methods

- (NetworkLogic*) initWithOutputListener:(id<OutputListener>)listener :(id<ChatDemoView>)view
{
	self = [super init];
	(mLogger=[[EGLogger alloc] initWithDebugOutputLevel:EGDbgLvl::INFO]).Listener = EGBase.Listener = self;
	mOutputListener = listener;
	mView = view;
	
	mChatClient=[[EGChatClient alloc] initClient:self :appId :appVersion];
	mChatClient.DebugOutputLevel = EGDbgLvl::INFO;
	
	// to print welcome message
	[self onStateChange:mChatClient.State];
	self.LastInput = INPUT_NON;
	return self;
}

+ (NetworkLogic*) networkLogicWithOutputListener:(id<OutputListener>)listener :(id<ChatDemoView>)view
{
	return [[[NetworkLogic alloc] initWithOutputListener:listener :view] autorelease];
}

- (void) connect
{
	[mOutputListener writeLine:@"[i]: Connecting..."];
	EGMutableAuthenticationValues* authenticationValues = [EGMutableAuthenticationValues authenticationValues];
	authenticationValues.UserID = mView.UserID;
	[mChatClient connect:authenticationValues];
}

- (void) disconnect
{
	[mChatClient disconnect];
}

- (void) subscribe
{
	if(mSubscribeState)
	{
		if([mChatClient opUnsubscribe:[EGArray arrayWithArray:subscribeChannels]])
			[mOutputListener writeLine:@"[i]: Unsubscribing from %@...", [subscribeChannels toString]];
		else
			[mOutputListener writeLine:@"[i]: Connect first"];
	}
	else
	{
		if([mChatClient opSubscribe:[EGArray arrayWithArray:subscribeChannels]])
			[mOutputListener writeLine:@"[i]: Subscribing to %@...", [subscribeChannels toString]];
		else
			[mOutputListener writeLine:@"[i]: Connect first"];
	}
}

- (void) setFriends
{
	EGMutableArray* f = [EGMutableArray arrayWithCapacity:userCount :NSStringFromClass([NSString class])];
	for(int i = 0;i < userCount;i++)
		[f addObject:[userPrefix stringByAppendingFormat:@"%d", i]];
	if(self.SetFriendsState)
	{
		if([mChatClient opRemoveFriends:f])
			[mOutputListener writeLine:@"[i]: Removing friends: %@ ...\n", [f toString]];
		else 
			[mOutputListener writeLine:@"[i]: Connect first"];
		self.SetFriendsState = 0;
	}
	else{
		if([mChatClient opAddFriends:f])
		{
			[mOutputListener writeLine:@"[i]: Setting friends: %@ ...\n", [f toString]];
			self.SetFriendsState = 1;
		}
		else 
			[mOutputListener writeLine:@"[i]: Connect first"];
	}
}


- (void) sendMessage:(NSString*)m
{
	NSUInteger sep = [m rangeOfString:@":"].location;
	if(sep != NSNotFound) // publish
		[mChatClient opPublishMessage:[m substringToIndex:sep] :[m substringFromIndex:sep + 1]];
	else 
	{
		NSUInteger sep = [m rangeOfString:@"@"].location;
		if(sep != NSNotFound) // private
			[mChatClient opSendPrivateMessage:[m substringToIndex:sep] :[m substringFromIndex:sep + 1]];
		else
		{ // publish to random channel
			static int cnt = 0;
			if(mChatClient.PublicChannels.count)
			{
				EGChatChannel* ch = mChatClient.PublicChannels[cnt++ % mChatClient.PublicChannels.count];
				[mChatClient opPublishMessage:ch.Name :m];
			}
			else
				[mOutputListener writeLine:@"[i]: Not subscribed to any channels"];
		}
	}
}

- (void) setOnlineStatus:(int)status
{
	if([mChatClient opSetOnlineStatus:status :@"My status changed"]) // update message
//		if([mChatClient opSetOnlineStatus:status :nil :true]) // skip message
//		if([mChatClient opSetOnlineStatus:status]) // clear message
		[mOutputListener writeLine:@"[i] my status sent: %d", status];
}

- (void) run
{
	switch(self.LastInput)
	{
		case INPUT_CONNECT:
			[self connect];
			break;
		case INPUT_DISCONNECT:
			[self disconnect];
			break;
		case INPUT_SUBSCRIBE:
			[self subscribe];
			break;
		case INPUT_SET_FRIENDS:
			[self setFriends];
			break;
		default:
			if(self.LastInput >= INPUT_SET_ONLINE_STATUS)
				[self setOnlineStatus:(self.LastInput - INPUT_SET_ONLINE_STATUS)];
			break;
	}
	self.LastInput = INPUT_NON;
	
	if(self.MessageToSend)
	{
		[self sendMessage:self.MessageToSend];
		self.MessageToSend = nil;
	}
	[mChatClient service];
}

- (void) dealloc
{
	[mChatClient release];
	[super dealloc];
}

// protocol implementations

- (void) debugReturn:(int)debugLevel :(NSString*)string
{
	fwprintf(stderr, L"%ls\n", string.UTF32String);
/*
	switch(debugLevel)
	{
	case ExitGames::Common::DebugLevel::ERRORS: 
		[mOutputListener writeLine:@"[e]: %@", string];
	case ExitGames::Common::DebugLevel::WARNINGS: 
		[mOutputListener writeLine:@"[w]: %@", string];
	default: 
		[mOutputListener writeLine:@"[i]: %@", string];
		break;
	}
*/
}

// index = const in ExitGames::Chat::ClientState::ClientState
static NSArray* ClientStateStr =
@[
	@"Uninitialized",
	@"ConnectingToNameServer",
	@"ConnectedToNameServer",
	@"Authenticating",
	@"Authenticated",
	@"DisconnectingFromNameServer",
	@"ConnectingToFrontEnd",
	@"ConnectedToFrontEnd",
	@"Disconnecting",
	@"Disconnected"
];

- (void) onStateChange:(int)state
{
	NSString* s = state < ClientStateStr.count?ClientStateStr[state]:@"Unknown";
	EGLOG(EGDbgLvl::INFO, L"Client State: %ls / %d", s.UTF32String, state);
	[mView onClientStateChange:state :s];
	if(state == ExitGames::Chat::ClientState::ConnectedToFrontEnd)
	{
		[mOutputListener writeLine:@"[i]: [Subscribe] for public channels"];
		[mOutputListener writeLine:@"[i]:    or type in 'userid@message'"];
		[mOutputListener writeLine:@"[i]:    and press 'OK' for private"];
		self.SubscribeState = 0;
	}
	else if(state == ExitGames::Chat::ClientState::Uninitialized || state == ExitGames::Chat::ClientState::Disconnected)
	{
		if(mChatClient.DisconnectedCause == ExitGames::Chat::DisconnectCause::INVALID_AUTHENTICATION)
		{
			[mOutputListener writeLine:@"[i]: Disconnected due to invalid authentication"];
			[mOutputListener writeLine:@"[i]: Is app id correct?"];
		}
		else
			[mOutputListener writeLine:@"[i]: Disconnected"];
		[mOutputListener writeLine:@"-------------------------------------------------"];
		[mOutputListener writeLine:@"[i]: type in user id and press [Connect]"];
		self.SubscribeState = 0;
		self.SetFriendsState = 0;
	}
}

- (void) connectionErrorReturn:(int)errorCode
{
	EGLOG(EGDbgLvl::ERRORS, L" code: %d", errorCode);
	[mOutputListener writeLine:@"[i]: Connection Error %d", errorCode];
}

- (void) clientErrorReturn:(int)errorCode
{
	EGLOG(EGDbgLvl::ERRORS, L" code: %d", errorCode);
	[mOutputListener writeLine:@"[i]: Error %d", errorCode];
}

- (void) warningReturn:(int)warningCode
{
	EGLOG(EGDbgLvl::WARNINGS, L" code: %d", warningCode);
	[mOutputListener writeLine:@"[i]: Warning %d", warningCode];
}

- (void) serverErrorReturn:(int)errorCode
{
	EGLOG(EGDbgLvl::ERRORS, L" code: %d", errorCode);
	[mOutputListener writeLine:@"[i]: Server Error %d", errorCode];
}

- (void) connectReturn:(int)errorCode :(NSString*)errorString
{
	EGLOG(EGDbgLvl::INFO, L"");
	if(errorCode)
	{
		EGLOG(EGDbgLvl::ERRORS, L"%ls", errorString.UTF32String);
		return;
	}
	[mOutputListener writeLine:@"[i]: Connected to Front End"];
}

- (void) disconnectReturn
{
	EGLOG(EGDbgLvl::INFO, L"");
	[mOutputListener writeLine:@"disconnected"];
}

- (void) subscribeReturn:(const EGArray *const)channels :(const EGArray *const)results
{
	EGLOG(EGDbgLvl::INFO, L"subscribeReturn: %ls / %ls", [channels toString].UTF32String, [results toString].UTF32String);
	[mOutputListener writeLine:@"[i]: Subscribe to %@ = %@", [channels toString], [results toString]];    
	if(self.SubscribeState == 0)
	{
		[mOutputListener writeLine:@"[i]: type in 'channel:message'"];
		[mOutputListener writeLine:@"[i]:   and press [Send] to publish"];
	}
	self.SubscribeState = 1;
}

- (void) unsubscribeReturn:(const EGArray *const)channels
{
	EGLOG(EGDbgLvl::INFO, L"unsubscribeReturn: %ls", [channels toString].UTF32String);
	[mOutputListener writeLine:@"[i]: Unsubscribed from %@", [channels toString]];
	self.SubscribeState = 0;
}

- (void) onStatusUpdate:(NSString* const)user :(int)status :(bool)gotMessage :(id<NSObject>)message
{ 	
	NSString* statusStr = @"";
	if(status < UserStatusStr.count) 
	{
		statusStr = UserStatusStr[status];
	}
	[mOutputListener writeLine:@"[i]: %@: %@(%d) / %@", user, statusStr, status, gotMessage?message:@"[message skipped]"];
}

- (void) onGetMessages:(NSString* const)channelName :(EGArray* const)senders :(EGArray* const)messages
{
	for(int i = 0;i < senders.count;i++)
	{
		[mOutputListener writeLine:@"[%@:%@]: %@", channelName, senders[i], messages[i]];
	}
}

- (void) onPrivateMessage:(NSString* const)sender :(id<NSObject>)message :(NSString* const)channelName
{
	[mOutputListener writeLine:@"[%@@%@]: %@", channelName, sender, message];
}


@end