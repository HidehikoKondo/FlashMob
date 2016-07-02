#import "EXViewController.h"

#include "BasicsApplication.h"
#include "UIListener.h"

class iPhoneUIListener: public UIListener
{
public:
	iPhoneUIListener(id logger):
	_logger(logger)
	{
	}
	
	void writeString(const ExitGames::Common::JString& str)
	{
		[_logger performSelectorOnMainThread:@selector(setString:) withObject:[NSString  stringWithUTF8String:str.UTF8Representation().cstr()] waitUntilDone:NO];
	}

	bool anyKeyPressed() const
	{
		return _logger.buttonCloseClicked;
	}

	void onLibClosed()
	{
		[_logger performSelectorOnMainThread:@selector(setString:) withObject:@"---CLOSED---" waitUntilDone:NO];
	}

	void sleep(int milliseconds)
	{
		usleep(milliseconds*1000);
	}
private:
	EXViewController* _logger;
};

@implementation EXViewController

@synthesize buttonCloseClicked;

- (void) startDemo
{
	BasicsApplication::run(new iPhoneUIListener(self));
}

- (void) setString:(NSString*)string
{
	textView.text = string;
}

- (IBAction) onStopButtonClicked:(id)sender
{
	self.buttonCloseClicked = YES;
	stopButton.hidden = YES;
}

#pragma mark - View lifecycle

- (void) didReceiveMemoryWarning
{
	[super didReceiveMemoryWarning];
}

- (void) viewDidLoad
{
	[super viewDidLoad];

	textView.text = @"";
	[self performSelectorInBackground:@selector(startDemo) withObject:nil];
}

@end