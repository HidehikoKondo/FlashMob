#import "AppDelegate.h"
#import "ViewController.h"
#import "DemoConstants.h"

@implementation AppDelegate

@synthesize window = _window;
@synthesize viewController = _viewController;

- (void) connect
{
	app.LastInput = INPUT_CONNECT;
}

- (void) disconnect
{
	app.LastInput = INPUT_DISCONNECT;
}

- (void) subscribe
{
	app.LastInput = INPUT_SUBSCRIBE;
}

- (void) setFriends
{
	app.LastInput = INPUT_SET_FRIENDS;
}

- (void) sendMessage:(NSString*)m
{
	[app.MessageToSend release];
	app.MessageToSend = m;
}

- (void) setOnlineStatus:(UIButton*)b
{
    app.LastInput = INPUT_SET_ONLINE_STATUS + static_cast<int>(b.tag);
}

- (void) run:(NSTimer*)timer
{
	[app run];
}

- (BOOL) application:(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)launchOptions
{
	self.window = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];

	self.viewController = [[[ViewController alloc] initWithNibName:[[UIDevice currentDevice] userInterfaceIdiom]==UIUserInterfaceIdiomPhone?@"ViewController_iPhone":@"ViewController_iPad" bundle:nil] autorelease];

	int w = self.window.frame.size.width;
	int h = self.window.frame.size.height;

	mViewChat=[[[UIView alloc] initWithFrame:CGRectMake(0, 0, w, h)] autorelease];
	mViewChat.backgroundColor = [UIColor darkGrayColor];
	
	[self.viewController.view addSubview:mViewChat];
	
	int y = 0;
	const int space = 10;
	const int font1 = 14;
	const int font2 = 18;
	const int font3 = 24;
	
	const unsigned short bw = w/2 - 2*space;
	const unsigned short bh = 44;

	mLabelState = [[UILabel alloc] initWithFrame:CGRectMake(space, y = y, w, 20)];
	mLabelState.text = @"Undef";
	mLabelState.font = [UIFont systemFontOfSize:font1];
	mLabelState.backgroundColor = [UIColor clearColor];
	
	UILabel* l = [[UILabel alloc] initWithFrame:CGRectMake(space, y += mLabelState.frame.size.height + space / 2, 0, 0)];
	l.text = @"User Id:";
	l.font = [UIFont systemFontOfSize:font3];
	l.backgroundColor = [UIColor clearColor];
	[l sizeToFit];
	
	mInputUserID = [[UITextField alloc] initWithFrame:CGRectMake(l.frame.size.width + 2 * space, y, w - l.frame.size.width - 2 * space, bh)];
	mInputUserID.delegate = self;
	mInputUserID.text = defaultUserID;
	mInputUserID.placeholder = @"<set user id>";
	mInputUserID.font = [UIFont boldSystemFontOfSize:font3];
	mInputUserID.backgroundColor = [UIColor clearColor];
	
	mButtConnect = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	[mButtConnect setTitle:@"Connect" forState:UIControlStateNormal];
	[mButtConnect addTarget:self action:@selector(connect) forControlEvents:UIControlEventTouchUpInside];
	mButtConnect.frame = CGRectMake(space, y += l.frame.size.height + space, bw, bh);
	mButtConnect.titleLabel.font = [UIFont boldSystemFontOfSize:font2];
	
	mButtDisconnect = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	[mButtDisconnect setTitle:@"Disconnect" forState:UIControlStateNormal];
	[mButtDisconnect addTarget:self action:@selector(disconnect) forControlEvents:UIControlEventTouchUpInside];
	mButtDisconnect.frame = CGRectMake(w - bw - space, y, bw, bh);
	mButtDisconnect.titleLabel.font = [UIFont boldSystemFontOfSize:font2];

	mButtSubscribe = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	[mButtSubscribe addTarget:self action:@selector(subscribe) forControlEvents:UIControlEventTouchUpInside];
	mButtSubscribe.frame = CGRectMake(space, y += bh + space, bw, bh);
	mButtSubscribe.titleLabel.font = [UIFont boldSystemFontOfSize:font2];
	[self onSubscribeStateSet:0];

	mButtSetFriends = [UIButton buttonWithType:UIButtonTypeRoundedRect];
	[mButtSetFriends addTarget:self action:@selector(setFriends) forControlEvents:UIControlEventTouchUpInside];
	mButtSetFriends.frame = CGRectMake(w - bw - space, y, bw, bh);
	mButtSetFriends.titleLabel.font = [UIFont boldSystemFontOfSize:font2];
	[self onSetFriendsStateSet:0];

	mInputMessage = [[UITextField alloc] initWithFrame:CGRectMake(space, y += bh + space, w - 2 * space, bh)];
	mInputMessage.font = [UIFont boldSystemFontOfSize:font3];
	mInputMessage.delegate = self;
	mInputMessage.placeholder = @"<message>";
	mInputMessage.tag = 1; // mark for 'return' key handler
	[mInputMessage sizeToFit];
	
	const int consoleH = h/3;
	
	console=[Console consoleWithFrame:CGRectMake(0, y += mInputMessage.frame.size.height + space, w, consoleH)];
	
	[mViewChat addSubview:mLabelState];
	[mViewChat addSubview:l];
	[mViewChat addSubview:mInputUserID];
	[mViewChat addSubview:mButtConnect];
	[mViewChat addSubview:mButtDisconnect];
	[mViewChat addSubview:mButtSubscribe];
	[mViewChat addSubview:mButtSetFriends];
	[mViewChat addSubview:mInputMessage];
	//	[self.viewController.view addSubview:console];
	[mViewChat addSubview:console];

	y += consoleH + space / 2;
	int x = space;
	const int smallButtH = bh/2;
	for(int i = 0;i < UserStatusStr.count;i++)
	{
		UIButton* b = [UIButton buttonWithType:UIButtonTypeRoundedRect];
		[b setTitle:UserStatusStr[i] forState:UIControlStateNormal];
		[b addTarget:self action:@selector(setOnlineStatus:) forControlEvents:UIControlEventTouchUpInside];
		[b sizeToFit];
		CGRect f = b.frame;
		f.size.height = smallButtH;
		if(x + f.size.width + space < w - space)
		{
			f.origin.x = x;
			f.origin.y = y;            
			x += f.size.width + space;
		}
		else
		{
			x = space + f.size.width + space;
			y += smallButtH + space / 2;
			f.origin.x = space;
			f.origin.y = y;
		}
		b.frame = f;
		b.tag = i;
		[mViewChat addSubview:b];
	}
	
	self.window.rootViewController = self.viewController;
	[self.window makeKeyAndVisible];

	[app=[NetworkLogic alloc] initWithOutputListener:console :self];

	[NSTimer scheduledTimerWithTimeInterval:0.1f target:self selector:@selector(run:) userInfo:nil repeats:true];

	return YES;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField              // called when 'return' key pressed. return NO to
{
	[textField resignFirstResponder];
	if(textField.tag == 1)
	{
		[self sendMessage:textField.text];
		textField.text = nil;
	}
	return YES;
}

-(void) touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
	[self->mViewChat endEditing:YES];
	[super touchesBegan:touches withEvent:event];
}

- (void) applicationWillResignActive:(UIApplication*)application
{
	/*
	Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
	Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
	*/
}

- (void) applicationDidEnterBackground:(UIApplication*)application
{
	/*
	Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
	If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
	*/
}

- (void) applicationWillEnterForeground:(UIApplication*)application
{
	/*
	Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
	*/
}

- (void) applicationDidBecomeActive:(UIApplication*)application
{
	/*
	Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
	*/
}

- (void) applicationWillTerminate:(UIApplication*)application
{
	app.LastInput = INPUT_EXIT;
}

// protocol implementations

- (NSString*) UserID
{
	return mInputUserID.text;
}

- (void) onClientStateChange:(int)state :(NSString* const)stateStr
{
	mLabelState.text = [stateStr stringByAppendingFormat:@" / %d", state];
}

- (void) onSubscribeStateSet:(int)state
{
	[mButtSubscribe setTitle:state?@"Unsubscribe":@"Subscribe" forState:UIControlStateNormal];
}
- (void) onSetFriendsStateSet:(int)state
{
	[mButtSetFriends setTitle:state?@"Clear friends":@"Set friends" forState:UIControlStateNormal];
}

- (void) dealloc
{
	[app release];
	[_window release];
	[_viewController release];
	[super dealloc];
}

@end