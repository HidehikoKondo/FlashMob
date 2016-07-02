/* Exit Games Photon Chat - C++ Client Lib
 * Copyright (C) 2004-2016 by Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#include "Chat-cpp/inc/Channel.h"
#include "Chat-cpp/inc/Listener.h"
#include "Chat-cpp/inc/Peer.h"
#include "Chat-cpp/inc/Enums/ClientState.h"
#include "Chat-cpp/inc/Enums/DisconnectCause.h"
#include "Chat-cpp/inc/Enums/ErrorCode.h"
#include "Chat-cpp/inc/Enums/UserStatus.h"

namespace ExitGames
{
	namespace Chat
	{
		class Client : protected Photon::PhotonListener
		{
		public:
			Client(Listener& listener, const Common::JString& applicationID, const Common::JString& appVersion, nByte connectionProtocol=Photon::ConnectionProtocol::DEFAULT);
			virtual ~Client(void);

			virtual bool connect(AuthenticationValues authenticationValues=AuthenticationValues(), const Common::JString& nameServerAddress=M_NAMESERVER);
			virtual void disconnect(void);

			virtual void service(bool dispatchIncomingCommands=true);
			virtual void serviceBasic(void);
			virtual bool sendOutgoingCommands(void);
			virtual bool sendAcksOnly(void);
			virtual bool dispatchIncomingCommands(void);
			virtual void fetchServerTimestamp(void);
			virtual void resetTrafficStats(void);
			virtual void resetTrafficStatsMaximumCounters(void);
			virtual Common::JString vitalStatsToString(bool all) const;

			bool opSubscribe(const Common::JVector<Common::JString>& channels, int messagesFromHistory=0);
			bool opUnsubscribe(const Common::JVector<Common::JString>& channels);
			template<typename Ftype> typename Common::Helpers::EnableIf<!Common::Helpers::ConfirmAllowed<Ftype>::dimensions, bool>::type opPublishMessage(const Common::JString& channelName, Ftype parameters)
			{
				return opPublishMessage(channelName, Common::Helpers::ValueToObject::get(parameters));
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<Common::Helpers::ConfirmAllowed<Ftype>::dimensions==1, bool>::type opPublishMessage(const Common::JString& channelName, Ftype pParameterArray, typename Common::Helpers::ArrayLengthType<Ftype>::type arrSize)
			{
				return opPublishMessage(channelName, Common::Helpers::ValueToObject::get(pParameterArray, arrSize));
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<(Common::Helpers::ConfirmAllowed<Ftype>::dimensions>1), bool>::type opPublishMessage(const Common::JString& channelName, Ftype pParameterArray, const short* pArrSizes)
			{
				return opPublishMessage(channelName, Common::Helpers::ValueToObject::get(pParameterArray, pArrSizes));
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<!Common::Helpers::ConfirmAllowed<Ftype>::dimensions, bool>::type opSendPrivateMessage(const Common::JString& userName, Ftype parameters, bool encrypt=false)
			{
				return opSendPrivateMessage(userName, Common::Helpers::ValueToObject::get(parameters), encrypt);
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<Common::Helpers::ConfirmAllowed<Ftype>::dimensions==1, bool>::type opSendPrivateMessage(const Common::JString& userName, Ftype pParameterArray, typename Common::Helpers::ArrayLengthType<Ftype>::type arrSize, bool encrypt=false)
			{
				return opSendPrivateMessage(userName, Common::Helpers::ValueToObject::get(pParameterArray, arrSize), encrypt);
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<(Common::Helpers::ConfirmAllowed<Ftype>::dimensions>1), bool>::type opSendPrivateMessage(const Common::JString& userName, Ftype pParameterArray, const short* pArrSizes, bool encrypt=false)
			{
				return opSendPrivateMessage(userName, Common::Helpers::ValueToObject::get(pParameterArray, pArrSizes), encrypt);
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<!Common::Helpers::ConfirmAllowed<Ftype>::dimensions, bool>::type opSetOnlineStatus(int status, Ftype parameters=Ftype(), bool skipMessage=false)
			{
				return opSetOnlineStatus(status, Common::Helpers::ValueToObject::get(parameters), skipMessage);
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<Common::Helpers::ConfirmAllowed<Ftype>::dimensions==1, bool>::type opSetOnlineStatus(int status, Ftype pParameterArray=NULL, typename Common::Helpers::ArrayLengthType<Ftype>::type arrSize=0, bool skipMessage=false)
			{
				return opSetOnlineStatus(status, Common::Helpers::ValueToObject::get(pParameterArray, arrSize), skipMessage);
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<(Common::Helpers::ConfirmAllowed<Ftype>::dimensions>1), bool>::type opSetOnlineStatus(int status, Ftype pParameterArray=NULL, const short* pArrSizes=NULL, bool skipMessage=false)
			{
				return opSetOnlineStatus(status, Common::Helpers::ValueToObject::get(pParameterArray, pArrSizes), skipMessage);
			}
			bool opAddFriends(const Common::JVector<Common::JString>& userIDs);
			bool opRemoveFriends(const Common::JVector<Common::JString>& userIDs);

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

			const Common::JString& getUserID(void) const;
			int getState(void) const;
			int getDisconnectedCause(void) const;
			const Common::JString& getRegion(void) const;
			void setRegion(const Common::JString& region);
			const Common::JVector<Channel*>& getPublicChannels(void) const;
			const Common::JVector<Channel*>& getPrivateChannels(void) const;
			const Channel* getPublicChannel(const Common::JString& channelName) const;
			const Channel* getPrivateChannel(const Common::JString& userName) const;
		protected:
			// From Photon::PhotonListener
			virtual void onOperationResponse(const Photon::OperationResponse& operationResponse);
			virtual void onStatusChanged(int statusCode);
			virtual void onEvent(const Photon::EventData& eventData);
			virtual void debugReturn(int debugLevel, const Common::JString& string);
		private:
			bool opPublishMessage(const Common::JString& channelName, const Common::Object& message);
			bool opSendPrivateMessage(const Common::JString& userName, const Common::Object& message, bool encrypt=false);
			bool opSetOnlineStatus(int status, const Common::Object& message=ExitGames::Common::Object(), bool skipMessage=false);

			void handleConnectionFlowError(int oldState, int errorCode, const Common::JString& errorString);
			void handleAuthResponse(const Photon::OperationResponse& operationResponse);
			void handleSubscribeResponse(const Photon::EventData& operationResponse);
			void handleUnsubscribeResponse(const Photon::EventData& operationResponse);

			Channel* getChannel(Common::JVector<Channel*>& channels, const Common::JString& name);
			Channel* getOrAddChannel(Common::JVector<Channel*>& channels, const Common::JString& name, bool isPrivate);
			void removeChannel(Common::JVector<Channel*>& channels, const Common::JString& name);

			Peer mPeer;
			Listener& mListener;
			Common::Logger mLogger;
			Common::JString mAppVersion;
			Common::JString mAppID;
			Common::JString mAppIDPeerInit; // appID adapted to the size suported by PhotonPeer
			Common::JString mFrontEndAddress;
			int mState;
			AuthenticationValues mAuthenticationValues;
			int mDisconnectedCause;
			bool mDidAuthenticate;
			Common::JString mRegion;

			Common::JVector<Channel*> mPublicChannels;
			Common::JVector<Channel*> mPrivateChannels;

			const nByte M_CONNECTION_PROTOCOL;

			static const Common::JString M_NAMESERVER;
		};
	}
}