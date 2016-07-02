#import "EXViewController.h"

#include "TypeSupportApplication.h"
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
	TypeSupportApplication::run(new iPhoneUIListener(self));
}

- (void) addString:(NSString*)string
{
	textView.text = [textView.text stringByAppendingFormat: @"\n%@", string];
	NSInteger len = [textView.text length];
	if(len > 10)
		[textView scrollRangeToVisible:NSMakeRange(len-10, 10)];
}

- (IBAction) onStopButtonClicked:(id)sender
{
	self.buttonCloseClicked = YES;
	stopButton.hidden = YES;
}

- (void) didReceiveMemoryWarning
{
	[super didReceiveMemoryWarning];
	// Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void) viewDidLoad
{
	[super viewDidLoad];

	textView.text = @"";
	[self performSelectorInBackground:@selector(startDemo)
						withObject:nil];
}

- (BOOL) shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
	return YES;
}

@end