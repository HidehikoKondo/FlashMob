/* Exit Games Photon LoadBalancing - objC Client Lib
 * Copyright (C) 2004-2016 by Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Common-objc/inc/EGArray.h"

@interface EGRoomOptions : EGBase <NSCopying, NSMutableCopying>

@property (readonly) bool IsVisible;
@property (readonly) bool IsOpen;
@property (readonly) nByte MaxPlayers;
@property (readonly, copy) NSDictionary* CustomRoomProperties;
@property (readonly, copy) EGArray* PropsListedInLobby;
@property (readonly, copy) NSString* LobbyName;
@property (readonly) nByte LobbyType;
@property (readonly) int PlayerTtl;
@property (readonly) int EmptyRoomTtl;

- (instancetype) initRoomOptions:(bool)isVisible;
- (instancetype) initRoomOptions:(bool)isVisible :(bool)isOpen;
- (instancetype) initRoomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers;
- (instancetype) initRoomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties;
- (instancetype) initRoomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby;
- (instancetype) initRoomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby :(NSString*)lobbyName;
- (instancetype) initRoomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby :(NSString*)lobbyName :(nByte)lobbyType;
- (instancetype) initRoomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby :(NSString*)lobbyName :(nByte)lobbyType :(int)playerTtl;
- (instancetype) initRoomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby :(NSString*)lobbyName :(nByte)lobbyType :(int)playerTtl :(int)emptyRoomTtl NS_DESIGNATED_INITIALIZER;
+ (instancetype) roomOptions;
+ (instancetype) roomOptions:(bool)isVisible;
+ (instancetype) roomOptions:(bool)isVisible :(bool)isOpen;
+ (instancetype) roomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers;
+ (instancetype) roomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties;
+ (instancetype) roomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby;
+ (instancetype) roomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby :(NSString*)lobbyName;
+ (instancetype) roomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby :(NSString*)lobbyName :(nByte)lobbyType;
+ (instancetype) roomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby :(NSString*)lobbyName :(nByte)lobbyType :(int)playerTtl;
+ (instancetype) roomOptions:(bool)isVisible :(bool)isOpen :(nByte)maxPlayers :(NSDictionary*)customRoomProperties :(EGArray*)propsListedInLobby :(NSString*)lobbyName :(nByte)lobbyType :(int)playerTtl :(int)emptyRoomTtl;

@end



@interface EGMutableRoomOptions : EGRoomOptions

@property (readwrite) bool IsVisible;
@property (readwrite) bool IsOpen;
@property (readwrite) nByte MaxPlayers;
@property (readwrite, copy) NSDictionary* CustomRoomProperties;
@property (readwrite, copy) EGArray* PropsListedInLobby;
@property (readwrite, copy) NSString* LobbyName;
@property (readwrite) nByte LobbyType;
@property (readwrite) int PlayerTtl;
@property (readwrite) int EmptyRoomTtl;

@end