/* Exit Games Photon Chat - C++ Client Lib
 * Copyright (C) 2004-2016 by Exit Games GmbH. All rights reserved.
 * http://www.photonengine.com
 * mailto:developer@photonengine.com
 */

#pragma once

#include "Photon-cpp/inc/PhotonPeer.h"
#include "Chat-cpp/inc/AuthenticationValues.h"

namespace ExitGames
{
	namespace Chat
	{
		class Peer : public Photon::PhotonPeer
		{
		public:
			Peer(Photon::PhotonListener& listener, nByte connectionProtocol=Photon::ConnectionProtocol::DEFAULT);
			virtual ~Peer(void);

			virtual bool opAuthenticateOnNameServer(const Common::JString& appID, const Common::JString& appVersion, const Common::JString& region, const AuthenticationValues& authenticationValues=AuthenticationValues());
			virtual bool opAuthenticateOnFrontEnd(const Common::JString& secret);

			virtual bool opSubscribe(const Common::JVector<Common::JString>& channels, int messagesFromHistory);
			virtual bool opUnsubscribe(const Common::JVector<Common::JString>& channels);
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
			virtual bool opAddFriends(const Common::JVector<Common::JString>& userIDs);
			virtual bool opRemoveFriends(const Common::JVector<Common::JString>& userIDs);
		private:
			bool opPublishMessage(const Common::JString& channelName, const Common::Object& message);
			virtual bool opSendPrivateMessage(const Common::JString& userName, const Common::Object& message, bool encrypt=false);
			virtual bool opSetOnlineStatus(int status, const Common::Object& message=ExitGames::Common::Object(), bool skipMessage=false);
			bool sendChannelOperation(const Common::JVector<Common::JString>& channels, nByte operation, int messagesFromHistory=0);

			typedef PhotonPeer super;

			friend class Client;
		};
	}
}