//
//  ConnectingViewController.m
//  ImageViewerSample
//
//  Copyright (c) 2014 Olympus Imaging Corporation. All rights reserved.
//

#import "ConnectingViewController.h"
#import "AppDelegate.h"

static NSString *const kNextViewControllerIdentifier = @"ImageCapture";

@interface ConnectingViewController ()

@property (weak, nonatomic) IBOutlet UILabel *cameraKitVersionLabel;

@end

@implementation ConnectingViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didChangeConnectionStateNotification:) name:kAppDelegateCameraDidChangeConnectionStateNotification object:nil];

	self.cameraKitVersionLabel.text = OLYCameraKitVersion;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark -

- (void)didChangeConnectionStateNotification:(NSNotification *)notification
{
	NSString *state = notification.userInfo[kConnectionStateKey];
	if (state == kConnectionStateConnected) {
		[self presentViewController:[self.storyboard instantiateViewControllerWithIdentifier:kNextViewControllerIdentifier] animated:NO completion:^{
			if (!AppDelegateCamera().connected) {
				[self.presentedViewController dismissViewControllerAnimated:NO completion:nil];
			}
		}];
	}
	else if (state == kConnectionStateDisconnected) {
		if (self.presentedViewController) {
			[self.presentedViewController dismissViewControllerAnimated:NO completion:nil];
		}
	}
}

@end
