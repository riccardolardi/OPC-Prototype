//
//  RecViewController.m
//  ImageCaptureSample
//
//  Copyright (c) 2014 Olympus Imaging Corporation. All rights reserved.
//

#import "RecViewController.h"

@interface RecViewController ()

@property (weak, nonatomic) IBOutlet UIImageView *imageView;

@end

@implementation RecViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)dealloc
{
	self.image = nil;
}

- (BOOL)prefersStatusBarHidden
{
	return YES;
}

- (void)viewWillAppear:(BOOL)animated
{
	[super viewWillAppear:animated];
	[self.navigationController setNavigationBarHidden:YES animated:animated];
    self.imageView.image = self.image;
}

- (IBAction)viewDidTap:(id)sender
{
	[self performSegueWithIdentifier:@"backToLiveView" sender:self];
}

- (IBAction)camreaButtonDidTap:(id)sender {
	[self performSegueWithIdentifier:@"backToLiveView" sender:self];
}

@end
