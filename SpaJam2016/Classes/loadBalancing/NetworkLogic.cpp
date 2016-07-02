#include "NetworkLogic.h"

#ifdef _EG_EMSCRIPTEN_PLATFORM
	#include <emscripten.h>
#endif


static const ExitGames::Common::JString appId = L"601bc7ad-ac3a-4873-97b3-43a1306c5aa8"; // set your app id here
static const ExitGames::Common::JString appVersion = L"1.0";

static const bool autoLobbbyStats = true;
#ifdef EG_PLATFORM_SUPPORTS_CPP11
	// pinging takes a moment, so for a real game it makes sense to retrive the best region with getRegionWithBestPing(), store it in a file, use RegionSelectionMode::SELECT and pass that region to selectRegion() and to only use RegionSelectionMode::BEST, if no best region has been determined yet or if the player explicitly requests to repeat pinging
	static const nByte regionSelectionMode = ExitGames::LoadBalancing::RegionSelectionMode::BEST;
#else
	static const nByte regionSelectionMode = ExitGames::LoadBalancing::RegionSelectionMode::SELECT;
#endif


static const ExitGames::Common::JString PLAYER_NAME = 
#if defined _EG_WINDOWS_PLATFORM
	L"Windows";
#elif defined _EG_IPHONE_PLATFORM
	L"iOS";
#elif defined _EG_IMAC_PLATFORM
	L"OS X";
#elif defined _EG_MARMALADE_PLATFORM
	L"Marmalade";
#elif defined _EG_ANDROID_PLATFORM
	L"Android";
#elif defined _EG_PS3_PLATFORM
	L"PS3";
#elif defined _EG_LINUX_PLATFORM
	L"Linux";
#elif defined _EG_PS4_PLATFORM
	L"PS4";
#elif defined _EG_WINDOWSSTORE_PLATFORM
	L"Windows Store";
#elif defined _EG_EMSCRIPTEN_PLATFORM
	L"Emscripten";
#else
	L"unknown platform";
#endif


ExitGames::Common::JString& NetworkLogicListener::toString(ExitGames::Common::JString& retStr, bool /*withTypes*/) const
{
	return retStr;
}

State StateAccessor::getState(void) const
{
	return mState;
}

void StateAccessor::setState(State newState)
{
	mState = newState;
	for(unsigned int i=0; i<mStateUpdateListeners.getSize(); i++)
		mStateUpdateListeners[i]->stateUpdate(newState);
}

void StateAccessor::registerForStateUpdates(NetworkLogicListener* listener)
{
	mStateUpdateListeners.addElement(listener);
}

Input NetworkLogic::getLastInput(void) const
{
	return mLastInput;
}

void NetworkLogic::setLastInput(Input newInput)
{
	mLastInput = newInput;
}

State NetworkLogic::getState(void) const
{
	return mStateAccessor.getState();
}

// functions
//NetworkLogic::NetworkLogic(OutputListener* listener)
NetworkLogic::NetworkLogic()
#ifdef _EG_MS_COMPILER
#	pragma warning(push)
#	pragma warning(disable:4355)
#endif
	: mLoadBalancingClient(*this, appId, appVersion, ExitGames::Photon::ConnectionProtocol::DEFAULT, autoLobbbyStats, regionSelectionMode)
	, mLastPlayerNr(0)
	, mLastInput(INPUT_NON)
//	, mpOutputListener(listener)
#ifdef _EG_EMSCRIPTEN_PLATFORM
	, mAutoJoinRoom(true)
#else
	, mAutoJoinRoom(false)
#endif

#ifdef _EG_MS_COMPILER
#	pragma warning(pop)
#endif
{
	mStateAccessor.setState(STATE_INITIALIZED);
	mLoadBalancingClient.setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS)); // that instance of LoadBalancingClient and its implementation details
	mLogger.setListener(*this);
	mLogger.setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS)); // this class
	ExitGames::Common::Base::setListener(this);
	ExitGames::Common::Base::setDebugOutputLevel(DEBUG_RELEASE(ExitGames::Common::DebugLevel::INFO, ExitGames::Common::DebugLevel::WARNINGS)); // all classes that inherit from Base
}

void NetworkLogic::registerForStateUpdates(NetworkLogicListener* listener)
{
	mStateAccessor.registerForStateUpdates(listener);
}

void NetworkLogic::connect(const ExitGames::LoadBalancing::AuthenticationValues& authenticationValues)
{
//	mpOutputListener->writeLine(ExitGames::Common::JString(L"connecting to Photon"));
	mLoadBalancingClient.connect(authenticationValues, PLAYER_NAME);
	mStateAccessor.setState(STATE_CONNECTING);
}

void NetworkLogic::disconnect(void)
{
	mLoadBalancingClient.disconnect();
}

void NetworkLogic::opCreateRoom(void)
{
	ExitGames::Common::JString name;
	name += GETTIMEMS();
	mLoadBalancingClient.opCreateRoom(name, ExitGames::LoadBalancing::RoomOptions().setMaxPlayers(4).setPlayerTtl(INT_MAX/2).setEmptyRoomTtl(10000));	
	mStateAccessor.setState(STATE_JOINING);
//	mpOutputListener->writeLine(ExitGames::Common::JString(L"creating room ") + name + L"...");
}

void NetworkLogic::opJoinRandomRoom(void)
{
	mLoadBalancingClient.opJoinRandomRoom();
}

void NetworkLogic::opJoinOrCreateRoom(void)
{
	ExitGames::Common::JString name("DemoLoadBalancing");
	mLoadBalancingClient.opJoinOrCreateRoom(name);
	mStateAccessor.setState(STATE_JOINING);
//	mpOutputListener->writeLine(ExitGames::Common::JString(L"joining or creating room ") + name + L"...");
}

void NetworkLogic::run(void)
{
	State state = mStateAccessor.getState();
	if(mLastInput == INPUT_EXIT && state != STATE_DISCONNECTING && state != STATE_DISCONNECTED)
	{
		disconnect();
		mStateAccessor.setState(STATE_DISCONNECTING);
//		mpOutputListener->writeLine(L"terminating application");
	}
	else
	{
		switch(state)
		{
			case STATE_INITIALIZED:
				connect();
				break;
			case STATE_CONNECTING:
				break; // wait for callback
			case STATE_CONNECTED:
				switch(mLastInput)
				{
					case INPUT_1: // create Game
//						mpOutputListener->writeLine(L"\n=========================");
						opCreateRoom();
						break;
					case INPUT_2: // join Game
//						mpOutputListener->writeLine(L"\n=========================");
						// remove false to enable rejoin
						if(false && mLastJoinedRoom.length())
						{
//							mpOutputListener->writeLine(ExitGames::Common::JString(L"rejoining ") + mLastJoinedRoom + " with actorNr = " + mLastPlayerNr + "...");
							mLoadBalancingClient.opJoinRoom(mLastJoinedRoom, mLastPlayerNr);
						}
						else
						{
//							mpOutputListener->writeLine(ExitGames::Common::JString(L"joining random room..."));
							opJoinRandomRoom();
						}
						mStateAccessor.setState(STATE_JOINING);
						break;
					default: // no or illegal input -> stay waiting for legal input
						break;
				}
				break;
			case STATE_JOINING:
				break; // wait for callback
			case STATE_JOINED:
				sendEvent();
				switch(mLastInput)
				{
					case INPUT_1: // leave Game
						mLoadBalancingClient.opLeaveRoom();
//						mpOutputListener->writeLine(L"");
//						mpOutputListener->writeLine(L"leaving room");
						mStateAccessor.setState(STATE_LEAVING);
						break;
					case INPUT_2: // leave Game
						mLoadBalancingClient.opLeaveRoom(true);
//						mpOutputListener->writeLine(L"");
//						mpOutputListener->writeLine(L"leaving room (will come back)");
						mStateAccessor.setState(STATE_LEAVING);
						break;
					default: // no or illegal input -> stay waiting for legal input
						break;
				}
				break;
			case STATE_LEAVING:
				break; // wait for callback
			case STATE_LEFT:
				mStateAccessor.setState(STATE_CONNECTED);
				break;
			case STATE_DISCONNECTING:
				break; // wait for callback
			default:
				break;
		}
	}
	mLastInput = INPUT_NON;
	mLoadBalancingClient.service();
}

void NetworkLogic::sendEvent(void)
{
	static int64 count = 0;
	mLoadBalancingClient.opRaiseEvent(false, ++count, 0);
//	mpOutputListener->write(ExitGames::Common::JString(L"s") + count + L" ");
#if defined _EG_EMSCRIPTEN_PLATFORM
	mpOutputListener->writeLine(L"");
#endif
}

// protocol implementations

void NetworkLogic::debugReturn(int debugLevel, const ExitGames::Common::JString& string)
{
//	mpOutputListener->debugReturn(debugLevel, string);
}

void NetworkLogic::connectionErrorReturn(int errorCode)
{
	EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"code: %d", errorCode);
//	mpOutputListener->writeLine(ExitGames::Common::JString(L"received connection error ") + errorCode);
	mStateAccessor.setState(STATE_DISCONNECTED);
}

void NetworkLogic::clientErrorReturn(int errorCode)
{
	EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"code: %d", errorCode);
//	mpOutputListener->writeLine(ExitGames::Common::JString(L"received error ") + errorCode + L" from client");
}

void NetworkLogic::warningReturn(int warningCode)
{
	EGLOG(ExitGames::Common::DebugLevel::WARNINGS, L"code: %d", warningCode);
//	mpOutputListener->writeLine(ExitGames::Common::JString(L"received warning ") + warningCode + L" from client");
}

void NetworkLogic::serverErrorReturn(int errorCode)
{
	EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"code: %d", errorCode);
//	mpOutputListener->writeLine(ExitGames::Common::JString(L"received error ") + errorCode + " from server");
}

void NetworkLogic::joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& /*playernrs*/, const ExitGames::LoadBalancing::Player& player)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"%ls joined the game", player.getName().cstr());
//	mpOutputListener->writeLine(L"");
//	mpOutputListener->writeLine(ExitGames::Common::JString(L"player ") + playerNr + L" " + player.getName() + L" has joined the game");
}

void NetworkLogic::leaveRoomEventAction(int playerNr, bool isInactive)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
//	mpOutputListener->writeLine(L"");
//	mpOutputListener->writeLine(ExitGames::Common::JString(L"player ") + playerNr + L" has left the game");
}


void NetworkLogic::customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent)
{
//	// you do not receive your own events, unless you specify yourself as one of the receivers explicitly, so you must start 2 clients, to receive the events, which you have sent, as sendEvent() uses the default receivers of opRaiseEvent() (all players in same room like the sender, except the sender itself)
//	EGLOG(ExitGames::Common::DebugLevel::ALL, L"");
////	mpOutputListener->write(ExitGames::Common::JString(L"r") + ExitGames::Common::ValueObject<long long>(eventContent).getDataCopy() + L" ");
//#if defined _EG_EMSCRIPTEN_PLATFORM
//	mpOutputListener->writeLine(L"");
//#endif

    //MARK: *** 編集 ***

    ExitGames::Common::Hashtable * event;

    switch (eventCode)
    {
        case 2:
        {
            {
                event = ExitGames::Common::ValueObject<ExitGames::Common::Hashtable *>(eventContent).getDataCopy();
                int rep = ExitGames::Common::ValueObject<int>(event->getValue(1)).getDataCopy();

                std::array<int, 3> array = {playerNr, 2, rep};
                this->eventQueue.push(array);
            }
            break;
        }

        default:
            break;
    }
}

void NetworkLogic::connectReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if(errorCode)
	{
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
		mStateAccessor.setState(STATE_DISCONNECTING);
		return;
	}
//	mpOutputListener->writeLine(L"connected");
	mStateAccessor.setState(STATE_CONNECTED);
	if(mAutoJoinRoom)
		opJoinOrCreateRoom();
}

void NetworkLogic::disconnectReturn(void)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
//	mpOutputListener->writeLine(L"disconnected");
	mStateAccessor.setState(STATE_DISCONNECTED);
}

void NetworkLogic::createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if(errorCode)
	{
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
//		mpOutputListener->writeLine(L"opCreateRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_CONNECTED);
		return;
	}
	mLastJoinedRoom = mLoadBalancingClient.getCurrentlyJoinedRoom().getName();
	mLastPlayerNr = localPlayerNr;

	EGLOG(ExitGames::Common::DebugLevel::INFO, L"localPlayerNr: %d", localPlayerNr);
//	mpOutputListener->writeLine(L"... room " + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + " has been created");
//	mpOutputListener->writeLine(L"regularly sending dummy events now");
	mStateAccessor.setState(STATE_JOINED);


    //MARK: *** 編集 ***
    // ルーム内で割り当てられたプレイヤー番号を取得
    this->playerNr = localPlayerNr;

}

void NetworkLogic::joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if(errorCode)
	{
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
//		mpOutputListener->writeLine(L"opJoinOrCreateRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_CONNECTED);
		return;
	}
	mLastJoinedRoom = mLoadBalancingClient.getCurrentlyJoinedRoom().getName();
	mLastPlayerNr = localPlayerNr;

	EGLOG(ExitGames::Common::DebugLevel::INFO, L"localPlayerNr: %d", localPlayerNr);
//	mpOutputListener->writeLine(L"... room " + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + " has been entered");
//	mpOutputListener->writeLine(L"regularly sending dummy events now");
	mStateAccessor.setState(STATE_JOINED);
}

void NetworkLogic::joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if(errorCode)
	{		
		mLastJoinedRoom = "";
		mLastPlayerNr = 0;
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
//		mpOutputListener->writeLine(L"opJoinRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_CONNECTED);
		return;
	}
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"localPlayerNr: %d", localPlayerNr);
//	mpOutputListener->writeLine(L"... room " + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + " has been successfully joined");
//	mpOutputListener->writeLine(L"regularly sending dummy events now");
	mStateAccessor.setState(STATE_JOINED);

    //MARK: *** 編集 ***
    // ルーム内で割り当てられたプレイヤー番号を取得
    this->playerNr = localPlayerNr;
}

void NetworkLogic::joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if(errorCode)
	{
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
//		mpOutputListener->writeLine(L"opJoinRandomRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_CONNECTED);
		return;
	}

	mLastJoinedRoom = mLoadBalancingClient.getCurrentlyJoinedRoom().getName();
	mLastPlayerNr = localPlayerNr;
	
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"localPlayerNr: %d", localPlayerNr);	
//	mpOutputListener->writeLine(L"... room " + mLoadBalancingClient.getCurrentlyJoinedRoom().getName() + " has been successfully joined");
//	mpOutputListener->writeLine(L"regularly sending dummy events now");
	mStateAccessor.setState(STATE_JOINED);

    //MARK: *** 編集 ***
    // ルーム内で割り当てられたプレイヤー番号を取得
    this->playerNr = localPlayerNr;
}

void NetworkLogic::leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
	if(errorCode)
	{
		EGLOG(ExitGames::Common::DebugLevel::ERRORS, L"%ls", errorString.cstr());
//		mpOutputListener->writeLine(L"opLeaveRoom() failed: " + errorString);
		mStateAccessor.setState(STATE_DISCONNECTING);
		return;
	}
	mStateAccessor.setState(STATE_LEFT);
//	mpOutputListener->writeLine(L"room has been successfully left");
}

void NetworkLogic::joinLobbyReturn(void)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
//	mpOutputListener->writeLine(L"joined lobby");
}

void NetworkLogic::leaveLobbyReturn(void)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"");
//	mpOutputListener->writeLine(L"left lobby");
}

void NetworkLogic::onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"%ls", lobbyStats.toString().cstr());
//	mpOutputListener->writeLine(L"LobbyStats: " + lobbyStats.toString());
}

void NetworkLogic::onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"%ls", lobbyStats.toString().cstr());
//	mpOutputListener->writeLine(L"LobbyStats: " + lobbyStats.toString());
}

void NetworkLogic::onAvailableRegions(const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegions, const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegionServers)
{
	EGLOG(ExitGames::Common::DebugLevel::INFO, L"%ls / %ls", availableRegions.toString().cstr(), availableRegionServers.toString().cstr());
//	mpOutputListener->writeLine(L"onAvailableRegions: " + availableRegions.toString() + L" / " + availableRegionServers.toString());
	// select first region from list
//	mpOutputListener->writeLine(L"selecting region: " + availableRegions[0]);
	mLoadBalancingClient.selectRegion(availableRegions[0]);
}





#pragma mark - ### for cocos2d-x ###
// ルームが存在するか否かを返すメソッド
bool NetworkLogic::isRoomExists(void)
{
    auto result = true;

    if (this->mLoadBalancingClient.getRoomList().getIsEmpty())
    {
        result = false;
    }

    return result;
}


// イベントを送信するメソッド
void NetworkLogic::sendEvent(nByte code, ExitGames::Common::Hashtable* eventContent)
{
    this->mLoadBalancingClient.opRaiseEvent(true, eventContent, 1, code);
}
