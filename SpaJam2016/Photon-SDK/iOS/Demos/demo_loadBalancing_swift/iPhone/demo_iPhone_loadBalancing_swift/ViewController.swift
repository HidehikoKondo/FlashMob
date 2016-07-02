import Foundation
import UIKit
var networkLogic: NetworkLogic!;

class ViewController: UIViewController, DemoView
{
	
	override func viewDidLoad()
	{
		super.viewDidLoad()
		networkLogic = NetworkLogic(demoView : self)
		NSTimer.scheduledTimerWithTimeInterval(0.1, target: self, selector: Selector("service"), userInfo: nil, repeats: true)
		// Do any additional setup after loading the view, typically from a nib.
		statusLabel.text = "Loaded..."
		networkLogic.updateState()
	}

	override func didReceiveMemoryWarning()
	{
		super.didReceiveMemoryWarning()
		// Dispose of any resources that can be recreated.
	}

	func service()
	{
		networkLogic.service()
	}
	
	@IBOutlet var statusLabel:UILabel!
	@IBOutlet var button:UIButton!
	@IBOutlet var button2:UIButton!
	@IBOutlet var logText:UITextView!
		
	@IBAction func onButton(sender: AnyObject)
	{
		networkLogic.onButton();
	}
	
	@IBAction func onButton2(sender: AnyObject)
	{
		networkLogic.onButton2()
	}

	func write(s : String)
	{
		self.out(s)
	}
	
	func log(s : String)
	{
		//self.out(s + "\n")
		print(s)
	}

	private func out(s: String)
	{
		self.logText.text = String(self.logText.text).stringByAppendingString(s)
		//self.logText.layoutIfNeeded()
		self.logText.setContentOffset(CGPoint(x : 0, y : self.logText.contentSize.height - self.logText.bounds.size.height), animated: false)
	
		//	logText.scrollRectToVisible(CGRect(x:0, y:logText.contentSize.height - 30, width:logText.contentSize.width, height:30), animated: false)
	}
	
	func showState(state : Int, stateStr : String, roomName : String, playerNr : Int32, inLobby : Bool, inRoom : Bool)
	{
		if (inRoom)
		{
			self.statusLabel.text = String(format:"%@ %@ / %d", stateStr, roomName, playerNr)
		}
		else
		{
			self.statusLabel.text = stateStr;
		}
		if (inLobby) {
			button.setTitle("Join or Create", forState: .Normal)
		} else if (inRoom) {
			button.setTitle("Leave", forState: .Normal)
		} else {
			button.setTitle("Connect", forState: .Normal)
		}
		
		button2.setTitle("Disonnect", forState: .Normal)
	}
}