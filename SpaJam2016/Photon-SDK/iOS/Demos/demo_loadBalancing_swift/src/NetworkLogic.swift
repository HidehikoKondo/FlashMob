import Foundation

let DemoEventCode0 : nByte = 0

let PeerStatesStr : [String] =
[
	"Uninitialized",
	"PeerCreated",
	"ConnectingToNameserver",
	"ConnectedToNameserver",
	"DisconnectingFromNameserver",
	"Connecting",
	"Connected",
	"WaitingForCustomAuthenticationNextStepCall",
	"Authenticated",
	"JoinedLobby",
	"DisconnectingFromMasterserver",
	"ConnectingToGameserver",
	"ConnectedToGameserver",
	"AuthenticatedOnGameServer",
	"Joining",
	"Joined",
	"Leaving",
	"Left",
	"DisconnectingFromGameserver",
	"ConnectingToMasterserver",
	"ConnectedComingFromGameserver",
	"AuthenticatedComingFromGameserver",
	"Disconnecting",
	"Disconnected",
];

protocol DemoView
{
	func showState(state : Int, stateStr : String, roomName : String, playerNr : Int32, inLobby : Bool, inRoom : Bool)
	func log(_: String) -> Void
	func write(_: String) -> Void
}

class PhotonListener : NSObject, EGLoadBalancingListener
{
	var networkLogic : NetworkLogic!
	let demoView : DemoView
	init(networkLogic : NetworkLogic, demoView : DemoView)
	{
		self.networkLogic = networkLogic
		self.demoView = demoView
		super.init()
	}
	
	func debugReturn(debugLevel : Int32, _ string : String!) -> Void
	{
		self.demoView.log(string)
	}
	
	func connectionErrorReturn(errorCode : Int32) -> Void
	{
		self.demoView.log(String(format: "- connectionErrorReturn: %d", errorCode))
		networkLogic.updateState()
	}
	
	func clientErrorReturn(errorCode : Int32) -> Void
	{
		self.demoView.log(String(format: "- clientErrorReturn: %d", errorCode))
		networkLogic.updateState()
	}
	
	func warningReturn(warningCode : Int32)-> Void
	{
		self.demoView.log(String(format: "- warningReturn: %d", warningCode))
		networkLogic.updateState()
	}
	
	func serverErrorReturn(errorCode : Int32) -> Void
	{
		self.demoView.log(String(format: "- serverErrorReturn: %d", errorCode))
		networkLogic.updateState()
	}

	// events, triggered by certain operations of all players in the same room
	func joinRoomEventAction(playerNr : Int32, _ playernrs : EGArray!, _ player : EGLoadBalancingPlayer!) -> Void
	{
		self.demoView.log(String(format: "- joinRoomEventAction: %d %@ %@", playerNr, playernrs, player ))
		networkLogic.updateState()
	}
	
	func leaveRoomEventAction(playerNr : Int32, _ isInactive : Bool) -> Void
	{
		self.demoView.log(String(format: "- leaveRoomEventAction: %d %s", playerNr, isInactive ? "true" : "false" ))
		networkLogic.updateState()
	}
	
	func disconnectEventAction(playerNr : Int32) -> Void
	{
		self.demoView.log(String(format: "- leaveRoomEventAction: %d", playerNr))
		networkLogic.updateState()
	}

	// callbacks for operations on server
	func connectReturn(errorCode : Int32, _ errorString : String!) -> Void
	{
		self.demoView.log(String(format: "- connectReturn: %d %@", errorCode, errorString ?? ""))
		networkLogic.updateState()
	}
	
	func disconnectReturn() -> Void
	{
		self.demoView.log(String(format: "- disconnectReturn"))
		networkLogic.updateState()
	}
	
	func createRoomReturn(localPlayerNr : Int32, _ roomProperties : [NSObject : AnyObject]!, _ playerProperties : [NSObject : AnyObject]!, _ errorCode : Int32, _ errorString : String!) -> Void
	{
		self.demoView.log(String(format: "- createRoomReturn: %d %@ %@ %d %@", localPlayerNr, roomProperties ?? "", playerProperties ?? "", errorCode, errorString ?? ""))
		networkLogic.updateState()
	}

	func joinOrCreateRoomReturn(localPlayerNr : Int32, _ roomProperties : [NSObject: AnyObject]!,  _ playerProperties : [NSObject: AnyObject]!, _ errorCode : Int32, _ errorString : String!) -> Void
	{
		self.demoView.log(String(format: "- joinOrCreateRoomReturn: %d %@ %@ %d %@", localPlayerNr, roomProperties ?? "", playerProperties ?? "", errorCode, errorString ?? ""))
		networkLogic.updateState()
	}
	
	func joinRoomReturn(localPlayerNr : Int32, _ roomProperties : [NSObject : AnyObject]!, _ playerProperties : [NSObject : AnyObject]!, _ errorCode : Int32, _ errorString : String!) -> Void
	{
		self.demoView.log(String(format: "- joinRoomReturn: %d %@ %@ %d %@", localPlayerNr, roomProperties ?? "", playerProperties ?? "", errorCode, errorString ?? ""))
		networkLogic.updateState()
	}
	
	func leaveRoomReturn(errorCode : Int32, _ errorString : String!) -> Void
	{
		self.demoView.log(String(format: "- leaveRoomReturn: %d %@", errorCode, errorString ?? ""))
		networkLogic.updateState()
	}
	
	func joinLobbyReturn() -> Void
	{
		self.demoView.log(String(format: "- joinLobbyReturn"))
		networkLogic.updateState()
	}
	
	func leaveLobbyReturn() -> Void
	{
		self.demoView.log(String(format: "- leaveLobbyReturn"))
		networkLogic.updateState()
	}
		
	func joinRandomRoomReturn(localPlayerNr : Int32, _ roomProperties : [NSObject : AnyObject]!, _ playerProperties : [NSObject : AnyObject]!, _ errorCode : Int32, _ errorString : String!) -> Void
	{
		self.demoView.log(String(format: "- joinRandomRoomReturn: %d %@ %@ %d %@", localPlayerNr, roomProperties ?? "", playerProperties ?? "", errorCode, errorString ?? ""))
		if(errorCode != 0)
		{
			networkLogic.createRoom()
		}
		networkLogic.updateState()
	}
	
	func customEventAction(playerNr : Int32, _ eventCode : nByte,  _ eventContent : NSObject) -> Void
	{
		if(eventCode == DemoEventCode0)
		{
			if(eventContent is NSValue)
			{
				let v = eventContent as! NSValue;
				var count : int64 = 0
				v.getValue(&count)
				self.demoView.write(String(format: "p%d:%d ", playerNr, count))
			}
		}
	}
}

class NetworkLogic
{
	var client : EGLoadBalancingClient!
	let demoView : DemoView
	var listenerRef : PhotonListener! // store reference to prevent listener destroy
	
	init(demoView : DemoView)
	{
		self.demoView = demoView
		listenerRef = PhotonListener(networkLogic: self, demoView : demoView)
		self.client = EGLoadBalancingClient(client : listenerRef, appId, appVersion)
		self.client.DebugOutputLevel = EGDebugLevel_INFO
		client.connect();
	}
	
	var count : int64 = 0
	func sendEvent()
	{
		count++
		let d = NSValue(bytes: &count, objCType: (1 as NSNumber).objCType)
		client.opRaiseEvent(true, d, DemoEventCode0)
		demoView.write(String(format : "s:%d ", count))
	}
	
	func service()
	{
		autoreleasepool
		{
			if(client.IsInGameRoom)
			{
				sendEvent()
			}
			client.service()
		}
	}
	
	func createRoom()
	{
		demoView.log("creating...")
		client.opCreateRoom("Swift Demo")
	}
	
	func updateState()
	{
		var room = ""
		if(client.IsInGameRoom)
		{
			room = client.CurrentlyJoinedRoom.Name
		}
		var stateStr = ""
		if(Int(client.State) < PeerStatesStr.count)
		{
			stateStr = PeerStatesStr[Int(client.State)]
		}
		demoView.showState(Int(client.State), stateStr : String(format : "%@/%d", stateStr, client.State), roomName : room, playerNr : client.LocalPlayer.Number, inLobby : client.IsInLobby, inRoom : client.IsInGameRoom)
	}
	
	func onButton()
	{
		if(client.IsInLobby)
		{
			demoView.log("joining...")
			client.opJoinRandomRoom()
		}
		else if client.IsInGameRoom
		{
			demoView.log("leaving...")
			client.opLeaveRoom()
		}
		else
		{
			demoView.log("connecting...")
			client.connect()
		}
	}
	
	func onButton2()
	{
		demoView.log("disconnecting...")
		client.disconnect()
	}
}