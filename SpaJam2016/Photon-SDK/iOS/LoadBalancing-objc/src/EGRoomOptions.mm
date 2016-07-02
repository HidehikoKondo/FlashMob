/* Exit Games Photon LoadBalancing - objC Client Lib
* Copyright (C) 2004-2016 by Exit Games GmbH. All rights reserved.
* http://www.photonengine.com
* mailto:developer@photonengine.com
*/

#include "LoadBalancing-cpp/inc/Enums/LobbyType.h"
#import "Common-objc/inc/NSObject+CopyDeep.h"
#import "LoadBalancing-objc/inc/EGRoomOptions.h"

/** @file EGRoomOptions.h */

@implementation EGRoomOptions
{
@protected
	bool mIsVisible;
	bool mIsOpen;
	nByte mMaxPlayers;
	NSDictionary* mCustomRoomProperties;
	EGArray* mPropsListedInLobby;
	NSString* mLobbyName;
	nByte mLobbyType;
	int mPlayerTtl;
	int mEmptyRoomTtl;
}

@synthesize IsVisible = mIsVisible;
@synthesize IsOpen = mIsOpen;
@synthesize MaxPlayers = mMaxPlayers;

- (NSDictionary*) CustomRoomProperties
{
	return [[mCustomRoomProperties copyDeep] autorelease];
}
- (EGArray*) PropsListedInLobby
{
	return [[mPropsListedInLobby copy] autorelease];
}

- (NSString*) LobbyName
{
	return [[mLobbyName copy] autorelease];
}

@synthesize LobbyType = mLobbyType;
@synthesize PlayerTtl = mPlayerTtl;
@synthesize EmptyRoomTtl = mEmptyRoomTtl;

- (instancetype) init
{
	return [self initRoomOptions:true];
}

- (instancetype) initRoomOptions:(bool)isVisible
{
	return [self initRoomOptions:isVisible :true];
}

- (instancetype) initRoomOptions:(bool)isVisible :(bool)isOpen
{
	return [self initRoomOptions:isVisible : isOpen :0];
}

- (instancetype) initRoomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers
{
	return [self initRoomOptions:isVisible :isOpen :maxPlayers :nil];
}

- (instancetype) initRoomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties
{
	return [self initRoomOptions:isVisible :isOpen :maxPlayers :customRoomProperties :nil];
}

- (instancetype) initRoomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby
{
	return [self initRoomOptions:isVisible :isOpen :maxPlayers :customRoomProperties :propsListedInLobby :nil];
}

- (instancetype) initRoomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby :(NSString*)lobbyName
{
	return [self initRoomOptions:isVisible :isOpen :maxPlayers :customRoomProperties :propsListedInLobby :lobbyName :ExitGames::LoadBalancing::LobbyType::DEFAULT];
}

- (instancetype) initRoomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby :(NSString*)lobbyName :(nByte)lobbyType
{
	return [self initRoomOptions:isVisible :isOpen :maxPlayers :customRoomProperties :propsListedInLobby :lobbyName :lobbyType :0];
}

- (instancetype) initRoomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby :(NSString*)lobbyName :(nByte)lobbyType :(int)playerTtl
{
	return [self initRoomOptions:isVisible :isOpen :maxPlayers :customRoomProperties :propsListedInLobby :lobbyName :lobbyType :playerTtl :0];
}

- (instancetype) initRoomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby :(NSString*)lobbyName :(nByte)lobbyType :(int)playerTtl :(int)emptyRoomTtl
{
	self = [super init];
	mIsVisible = isVisible;
	mIsOpen = isOpen;
	mMaxPlayers = maxPlayers;
	mCustomRoomProperties = [customRoomProperties copyDeep];
	mPropsListedInLobby = [propsListedInLobby copyDeep];
	mLobbyName = [lobbyName copy];
	mLobbyType = lobbyType;
	mPlayerTtl = playerTtl;
	mEmptyRoomTtl = emptyRoomTtl;
	return self;
}

+ (instancetype) roomOptions
{
	return [[self new] autorelease];
}

+ (instancetype) roomOptions:(bool)isVisible
{
	return [[[self alloc] initRoomOptions:isVisible] autorelease];
}

+ (instancetype) roomOptions:(bool)isVisible :(bool)isOpen
{
	return [[[self alloc] initRoomOptions:isVisible :isOpen] autorelease];
}

+ (instancetype) roomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers
{
	return [[[self alloc] initRoomOptions:isVisible :isOpen :maxPlayers] autorelease];
}

+ (instancetype) roomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties
{
	return [[[self alloc] initRoomOptions:isVisible :isOpen :maxPlayers :customRoomProperties] autorelease];
}

+ (instancetype) roomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby
{
	return [[[self alloc] initRoomOptions:isVisible :isOpen :maxPlayers :customRoomProperties :propsListedInLobby] autorelease];
}

+ (instancetype) roomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby :(NSString*)lobbyName
{
	return [[[self alloc] initRoomOptions:isVisible :isOpen :maxPlayers :customRoomProperties :propsListedInLobby :lobbyName] autorelease];
}

+ (instancetype) roomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby :(NSString*)lobbyName :(nByte)lobbyType
{
	return [[[self alloc] initRoomOptions:isVisible :isOpen :maxPlayers :customRoomProperties :propsListedInLobby :lobbyName :lobbyType] autorelease];
}

+ (instancetype) roomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby :(NSString*)lobbyName :(nByte)lobbyType :(int)playerTtl
{
	return [[[self alloc] initRoomOptions:isVisible :isOpen :maxPlayers :customRoomProperties :propsListedInLobby :lobbyName :lobbyType :playerTtl] autorelease];
}

+ (instancetype) roomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby :(NSString*)lobbyName :(nByte)lobbyType :(int)playerTtl :(int)emptyRoomTtl
{
	return [[[self alloc] initRoomOptions:isVisible :isOpen :maxPlayers :customRoomProperties :propsListedInLobby :lobbyName :lobbyType :playerTtl :emptyRoomTtl] autorelease];
}

- (NSString*) toString:(bool)withTypes
{
	return [NSString stringWithFormat:@"{isVisible=%@, isOpen=%@, maxPlayers=%hhu, customRoomProperties=%@, propsListedInLobby=%@, lobbyName=%@, lobbyType=%hhu, playerTtl=%d, emptyRoomTtl=%d}", self.IsVisible?@"true":@"false", self.IsOpen?@"true":@"false", self.MaxPlayers, [self.CustomRoomProperties toString:withTypes], [self.PropsListedInLobby toString], self.LobbyName, self.LobbyType, self.PlayerTtl, self.EmptyRoomTtl];
}

- (id) copyWithZone:(NSZone*)zone
{
	return [self retain];
}

- (id) mutableCopyWithZone:(NSZone*)zone
{
	return [[EGMutableRoomOptions alloc] initRoomOptions:self.IsVisible :self.IsOpen :self.MaxPlayers :self.CustomRoomProperties :self.PropsListedInLobby :self.LobbyName :self.LobbyType :self.PlayerTtl :self.EmptyRoomTtl];
}

- (void) dealloc
{
	[mLobbyName release];
	[mPropsListedInLobby release];
	[mCustomRoomProperties release];
	[super dealloc];
}

@end



@implementation EGMutableRoomOptions

@dynamic IsVisible;

- (void) setIsVisible:(bool)isVisible
{
	mIsVisible = isVisible;
}

@dynamic IsOpen;

- (void) setIsOpen:(bool)isOpen
{
	mIsOpen = isOpen;
}

@dynamic MaxPlayers;

- (void) setMaxPlayers:(nByte)maxPlayers
{
	mMaxPlayers = maxPlayers;
}

@dynamic CustomRoomProperties;

- (void) setCustomRoomProperties:(NSDictionary*)customRoomProperties
{
	[mCustomRoomProperties release];
	mCustomRoomProperties = [customRoomProperties copyDeep];
}

@dynamic PropsListedInLobby;

- (void) setPropsListedInLobby:(EGArray*)propsListedInLobby
{
	[mPropsListedInLobby release];
	mPropsListedInLobby = [propsListedInLobby copy];
}

@dynamic LobbyName;

- (void) setLobbyName:(NSString*)lobbyName
{
	[mLobbyName release];
	mLobbyName = [lobbyName copy];
}

@dynamic LobbyType;

- (void) setLobbyType:(nByte)lobbyType
{
	mLobbyType = lobbyType;
}

@dynamic PlayerTtl;

- (void) setPlayerTtl:(int)playerTtl
{
	mPlayerTtl = playerTtl;
}

@dynamic EmptyRoomTtl;

- (void) setEmptyRoomTtl:(int)emptyRoomTtl
{
	mEmptyRoomTtl = emptyRoomTtl;
}

- (id) copyWithZone:(NSZone*)zone
{
	return [[[self superclass] alloc] initRoomOptions:self.IsVisible :self.IsOpen :self.MaxPlayers :self.CustomRoomProperties :self.PropsListedInLobby :self.LobbyName :self.LobbyType :self.PlayerTtl :self.EmptyRoomTtl];
}

@end