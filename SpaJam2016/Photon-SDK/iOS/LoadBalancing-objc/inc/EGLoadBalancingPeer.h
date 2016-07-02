/* Exit Games Photon LoadBalancing - objC Client Lib
 * Copyright (C) 2004-2016 by Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#import "Photon-objc/inc/EGPhotonPeer.h"
#import "LoadBalancing-objc/inc/EGAuthenticationValues.h"
#import "LoadBalancing-objc/inc/EGLobbyStatsRequest.h"
#import "LoadBalancing-objc/inc/EGRaiseEventOptions.h"
#import "LoadBalancing-objc/inc/EGRoomOptions.h"

@interface EGLoadBalancingPeer : EGPhotonPeer

- (bool) opJoinLobby;
- (bool) opJoinLobby:(NSString*)lobbyName;
- (bool) opJoinLobby:(NSString*)lobbyName :(nByte)lobbyType;
- (bool) opLeaveLobby;
- (bool) opCreateRoom:(NSString*)gameID;
- (bool) opCreateRoom:(NSString*)gameID :(EGRoomOptions*)options;
- (bool) opCreateRoom:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customLocalPlayerProperties;
- (bool) opJoinRoom:(NSString*)gameID;
- (bool) opJoinRoom:(NSString*)gameID :(EGRoomOptions*)options;
- (bool) opJoinRoom:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customLocalPlayerProperties;
- (bool) opJoinRoom:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customLocalPlayerProperties :(bool)createIfNotExists;
- (bool) opJoinRoom:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customLocalPlayerProperties :(bool)createIfNotExists :(int)playerNumber;
- (bool) opJoinRoom:(NSString*)gameID :(EGRoomOptions*)options :(NSDictionary*)customLocalPlayerProperties :(bool)createIfNotExists :(int)playerNumber :(int)cacheSliceIndex;
- (bool) opJoinRandomRoom;
- (bool) opJoinRandomRoom:(NSDictionary*)customRoomProperties;
- (bool) opJoinRandomRoom:(NSDictionary*)customRoomProperties :(nByte)maxPlayers; // = MatchmakingMode::FILL_ROOM;
- (bool) opJoinRandomRoom:(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode;
- (bool) opJoinRandomRoom:(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode :(NSString*)lobbyName; // = LobbyType::DEFAULT
- (bool) opJoinRandomRoom:(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode :(NSString*)lobbyName :(nByte)lobbyType;
- (bool) opJoinRandomRoom:(NSDictionary*)customRoomProperties :(nByte)maxPlayers :(nByte)matchmakingMode :(NSString*)lobbyName :(nByte)lobbyType :(NSString*)sqlLobbyFilter;
- (bool) opLeaveRoom; // = false
- (bool) opLeaveRoom:(bool)willComeBack;
- (bool) opRaiseEvent:(bool)reliable :(id<NSObject>)parameters :(nByte)eventCode;
- (bool) opRaiseEvent:(bool)reliable :(id<NSObject>)parameters :(nByte)eventCode :(EGRaiseEventOptions*)options;
- (bool) opAuthenticate:(NSString*)appID :(NSString*)appVersion :(bool)encrypted;
- (bool) opAuthenticate:(NSString*)appID :(NSString*)appVersion :(bool)encrypted :(EGAuthenticationValues*)authenticationValues;
- (bool) opAuthenticate:(NSString*)appID :(NSString*)appVersion :(bool)encrypted :(EGAuthenticationValues*)authenticationValues :(bool)lobbyStats;
- (bool) opAuthenticate:(NSString*)appID :(NSString*)appVersion :(bool)encrypted :(EGAuthenticationValues*)authenticationValues :(bool)lobbyStats :(NSString*)regionCode;
- (bool) opFindFriends:(EGArray*)friendsToFind;
- (bool) opLobbyStats; // = nil
- (bool) opLobbyStats:(EGArray*)lobbiesToQuery; // array of EGLobbyStatsRequest
- (bool) opChangeGroups:(EGArray*)groupsToRemove :(EGArray*)groupsToAdd; // arrays of nByte
- (bool) opWebRpc:(NSString*)uriPath; // = nil
- (bool) opWebRpc:(NSString*)uriPath :(id<NSObject>)parameters;
- (bool) opGetRegions:(bool)encrypted :(NSString*)appID;
- (bool) opSetPropertiesOfPlayer:(int)playerNr :(NSDictionary*)properties;
- (bool) opSetPropertiesOfRoom:(NSDictionary*)properties; // = false
- (bool) opSetPropertiesOfRoom:(NSDictionary*)properties :(bool)webForward;

@end