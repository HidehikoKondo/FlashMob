/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2016 by Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#include "Photon-cpp/inc/Enums/ConnectionProtocol.h"
#include "LoadBalancing-cpp/inc/FriendInfo.h"
#include "LoadBalancing-cpp/inc/Listener.h"
#include "LoadBalancing-cpp/inc/LobbyStatsRequest.h"
#include "LoadBalancing-cpp/inc/LobbyStatsResponse.h"
#include "LoadBalancing-cpp/inc/MutablePlayer.h"
#include "LoadBalancing-cpp/inc/MutableRoom.h"
#include "LoadBalancing-cpp/inc/Enums/LobbyType.h"
#include "LoadBalancing-cpp/inc/Enums/MatchmakingMode.h"
#include "LoadBalancing-cpp/inc/Enums/RegionSelectionMode.h"
#include "LoadBalancing-cpp/inc/Enums/ServerType.h"

namespace ExitGames
{
	namespace LoadBalancing
	{
		class Client : protected Photon::PhotonListener
		{
		public:
			Client(LoadBalancing::Listener& listener, const Common::JString& applicationID, const Common::JString& appVersion, nByte connectionProtocol=Photon::ConnectionProtocol::DEFAULT, bool autoLobbyStats=false, nByte regionSelectionMode=RegionSelectionMode::DEFAULT);
			virtual ~Client(void);

			virtual bool connect(AuthenticationValues authenticationValues=AuthenticationValues(), const Common::JString& username=L"", const Common::JString& serverAddress=M_NAMESERVER, nByte serverType=ServerType::NAME_SERVER);
			virtual void disconnect(void);

			virtual void service(bool dispatchIncomingCommands=true);
			virtual void serviceBasic(void);
			virtual bool opCustom(const Photon::OperationRequest& operationRequest, bool sendReliable, nByte channelID=0, bool encrypt=false);
			virtual bool sendOutgoingCommands(void);
			virtual bool sendAcksOnly(void);
			virtual bool dispatchIncomingCommands(void);
			virtual bool establishEncryption(void);
			virtual void fetchServerTimestamp(void);
			virtual void resetTrafficStats(void);
			virtual void resetTrafficStatsMaximumCounters(void);
			virtual Common::JString vitalStatsToString(bool all) const;

			virtual bool opJoinLobby(const Common::JString& lobbyName=Common::JString(), nByte lobbyType=LobbyType::DEFAULT);
			virtual bool opLeaveLobby(void);
			virtual bool opCreateRoom(const Common::JString& gameID, const RoomOptions& options=RoomOptions());
			virtual bool opJoinOrCreateRoom(const Common::JString& gameID, const RoomOptions& options=RoomOptions(), int cacheSliceIndex=0);
			virtual bool opJoinRoom(const Common::JString& gameID, int playerNumber=0, int cacheSliceIndex=0);
			virtual bool opJoinRandomRoom(const Common::Hashtable& customRoomProperties=Common::Hashtable(), nByte maxPlayers=0, nByte matchmakingMode=MatchmakingMode::FILL_ROOM, const Common::JString& lobbyName=Common::JString(), nByte lobbyType=LobbyType::DEFAULT, const Common::JString& sqlLobbyFilter=Common::JString());
			virtual bool opLeaveRoom(bool willComeBack=false);
			template<typename Ftype> typename Common::Helpers::EnableIf<!Common::Helpers::ConfirmAllowed<Ftype>::dimensions, bool>::type opRaiseEvent(bool reliable, Ftype parameters, nByte eventCode, RaiseEventOptions options=RaiseEventOptions())
			{
				return mPeer.opRaiseEvent(reliable, parameters, eventCode, options);
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<Common::Helpers::ConfirmAllowed<Ftype>::dimensions==1, bool>::type opRaiseEvent(bool reliable, Ftype pParameterArray, typename Common::Helpers::ArrayLengthType<Ftype>::type arrSize, nByte eventCode, RaiseEventOptions options=RaiseEventOptions())
			{
				return mPeer.opRaiseEvent(reliable, pParameterArray, arrSize, eventCode, options);
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<(Common::Helpers::ConfirmAllowed<Ftype>::dimensions>1), bool>::type opRaiseEvent(bool reliable, Ftype pParameterArray, const short* pArrSizes, nByte eventCode, RaiseEventOptions options=RaiseEventOptions())
			{
				return mPeer.opRaiseEvent(reliable, pParameterArray, pArrSizes, eventCode, options);
			}
			virtual bool opFindFriends(const Common::JString* friendsToFind, short numFriendsToFind);
			virtual bool opLobbyStats(const Common::JVector<LoadBalancing::LobbyStatsRequest>& lobbiesToQuery=Common::JVector<LoadBalancing::LobbyStatsRequest>());
			virtual bool opChangeGroups(const Common::JVector<nByte>* pGroupsToRemove, const Common::JVector<nByte>* pGroupsToAdd);
			virtual bool opCustomAuthenticationSendNextStepData(const AuthenticationValues& authenticationValues);
			virtual bool opWebRpc(const Common::JString& uriPath);
			template<typename Ftype> typename Common::Helpers::EnableIf<!Common::Helpers::ConfirmAllowed<Ftype>::dimensions, bool>::type opWebRpc(const Common::JString& uriPath, Ftype parameters)
			{
				return mPeer.opWebRpc(uriPath, parameters);
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<Common::Helpers::ConfirmAllowed<Ftype>::dimensions==1, bool>::type opWebRpc(const Common::JString& uriPath, Ftype pParameterArray, typename Common::Helpers::ArrayLengthType<Ftype>::type arrSize)
			{
				return mPeer.opWebRpc(uriPath, pParameterArray, arrSize);
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<(Common::Helpers::ConfirmAllowed<Ftype>::dimensions>1), bool>::type opWebRpc(const Common::JString& uriPath, Ftype pParameterArray, const short* pArrSizes)
			{
				return mPeer.opWebRpc(uriPath, pParameterArray, pArrSizes);
			}

			virtual bool selectRegion(const Common::JString& selectedRegion);

			int getServerTimeOffset(void) const;
			int getServerTime(void) const;
			int getBytesOut(void) const;
			int getBytesIn(void) const;
			int getByteCountCurrentDispatch(void) const;
			int getByteCountLastOperation(void) const;
			int getSentCountAllowance(void) const;
			void setSentCountAllowance(int setSentCountAllowance);
			int getTimePingInterval(void) const;
			void setTimePingInterval(int setTimePingInterval);
			int getRoundTripTime(void) const;
			int getRoundTripTimeVariance(void) const;
			int getTimestampOfLastSocketReceive(void) const;
			int getDebugOutputLevel(void) const;
			bool setDebugOutputLevel(int debugLevel);
			int getIncomingReliableCommandsCount(void) const;
			short getPeerId(void) const;
			int getDisconnectTimeout(void) const;
			void setDisconnectTimeout(int disconnectTimeout);
			int getQueuedIncomingCommands(void) const;
			int getQueuedOutgoingCommands(void) const;
			bool getIsEncryptionAvailable(void) const;
			int getResentReliableCommands(void) const;
			int getLimitOfUnreliableCommands(void) const;
			void setLimitOfUnreliableCommands(int value);
			bool getCrcEnabled(void) const;
			void setCrcEnabled(bool crcEnabled);
			int getPacketLossByCrc(void) const;
			bool getTrafficStatsEnabled(void) const;
			void setTrafficStatsEnabled(bool trafficStatsEnabled);
			int getTrafficStatsElapsedMs(void) const;
			const Photon::TrafficStats& getTrafficStatsIncoming(void) const;
			const Photon::TrafficStats& getTrafficStatsOutgoing(void) const;
			const Photon::TrafficStatsGameLevel& getTrafficStatsGameLevel(void) const;
			nByte getQuickResendAttempts(void);
			void setQuickResendAttempts(nByte quickResendAttempts);

			static short getPeerCount(void);

			int getState(void) const;
			const Common::JString& getMasterserverAddress(void) const;
			int getCountPlayersIngame(void) const;
			int getCountGamesRunning(void) const;
			int getCountPlayersOnline(void) const;
			MutableRoom& getCurrentlyJoinedRoom(void);
			const Common::JVector<Room*>& getRoomList(void) const;
			const Common::JVector<Common::JString>& getRoomNameList(void) const;
			bool getIsInRoom(void) const;
			bool getIsInGameRoom(void) const;
			bool getIsInLobby(void) const;
			bool getAutoJoinLobby(void) const;
			void setAutoJoinLobby(bool onConnect);
			MutablePlayer& getLocalPlayer(void);
			const Common::JVector<FriendInfo>& getFriendList(void) const;
			int getFriendListAge(void) const;
			int getDisconnectedCause(void) const;
			const Common::JString& getUserID(void) const;
#ifdef EG_PLATFORM_SUPPORTS_CPP11
			const Common::JString& getRegionWithBestPing(void) const;
#endif
		private:
			virtual bool opGetRegions(bool encrypted, const Common::JString& appID);
			virtual bool opSetPropertiesOfPlayer(int playerNr, const Common::Hashtable& properties);
			virtual bool opSetPropertiesOfRoom(const Common::Hashtable& properties, bool webForward=false);

			virtual Room* createRoom(const Common::JString& name, const Common::Hashtable& properties);
			virtual void destroyRoom(const Room* pRoom) const;
			virtual MutablePlayerFactory* getMutablePlayerFactory(void) const;
			virtual MutableRoomFactory* getMutableRoomFactory(void) const;

			// From Photon::PhotonListener
			virtual void onOperationResponse(const Photon::OperationResponse& operationResponse);
			virtual void onStatusChanged(int statusCode);
			virtual void onEvent(const Photon::EventData& eventData);
			virtual void onPingResponse(const Common::JString& address, unsigned int result);
			virtual void debugReturn(int debugLevel, const Common::JString& string);

			void readoutProperties(Common::Hashtable& roomProperties, Common::Hashtable& playerProperties, bool multiplePlayers, int targetPlayerNr);
			void handleConnectionFlowError(int oldState, int errorCode, const Common::JString& errorString);
			void onConnectToMasterFinished(bool comingFromGameserver);
			MutablePlayer* createMutablePlayer(int number, const Common::Hashtable& properties);
			void destroyMutablePlayer(const MutablePlayer* pPlayer) const;
			MutableRoom* createMutableRoom(const Common::JString& name, const Common::Hashtable& properties, const Common::JVector<Common::JString>& propsListedInLobby, int playerTtl, int emptyRoomTtl);
			void destroyMutableRoom(const MutableRoom* pRoom) const;
#ifdef EG_PLATFORM_SUPPORTS_CPP11
			virtual void pingBestRegion(unsigned int pingsPerRegion);
#endif

			bool getIsOnGameServer(void) const;

			Peer mPeer;
			Listener& mListener;
			Common::Logger mLogger;
			Common::JString mGameserver;
			Common::JString mAppVersion;
			Common::JString mRoomName;
			Common::JString mAppID;
			Common::JString mAppIDPeerInit; // appID adapted to the size supported by PhotonPeer
			int mPeerCount;
			int mRoomCount;
			int mMasterPeerCount;
			nByte mLastJoinType;
			nByte mLastLobbyJoinType;
			int mLastJoinPlayerNumber;
			int mLastCacheSliceIndex;
			MutableRoom* mpCurrentlyJoinedRoom;
			Common::JVector<Room*> mRoomList;
			Common::JVector<Common::JString> mRoomNameList;
			int mCachedErrorCodeFromGameServer;
			Common::JString mCachedErrorStringFromGameServer;
			bool mAutoJoinLobby;
			MutablePlayer* mpLocalPlayer;
			Common::JVector<FriendInfo> mFriendList;
			Common::JVector<Common::JString> mLastFindFriendsRequest;
			int mFriendListTimestamp;
			bool mIsFetchingFriendList;
			Common::JVector<LobbyStatsRequest> mLobbyStatsRequestList;
			int mState;
			AuthenticationValues mAuthenticationValues;
			bool mAutoLobbyStats;
			MutablePlayerFactory* mpMutablePlayerFactory;
			MutableRoomFactory* mpMutableRoomFactory;
			int mDisconnectedCause;
			Common::JVector<Common::JString> mAvailableRegions;
			Common::JVector<Common::JString> mAvailableRegionServers;
			Common::JString mSelectedRegion;
			const nByte M_REGION_SELECTION_MODE;
			Common::JString mMasterserver;
			const nByte M_CONNECTION_PROTOCOL;
			unsigned int mPingsPerRegion;
			ExitGames::Common::JVector<ExitGames::Common::JVector<unsigned int> > mPingResponses;
			Common::JString mRegionWithBestPing;

			static const Common::JString M_NAMESERVER;
			static const unsigned int M_PINGS_PER_REGION = 5;

			friend class MutablePlayer;
			friend class MutableRoom;
		};
	}
}