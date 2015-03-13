//
//  SettingViewController.m
//  ImageCaptureSample
//
//  Copyright (c) 2014 Olympus Imaging Corporation. All rights reserved.
//

#import "AppDelegate.h"
#import "SettingViewController.h"

@interface SettingViewController ()

@property (weak, nonatomic) IBOutlet UITableViewCell *qualityCellQVGA;
@property (weak, nonatomic) IBOutlet UITableViewCell *qualityCellVGA;
@property (weak, nonatomic) IBOutlet UITableViewCell *qualityCellSVGA;
@property (weak, nonatomic) IBOutlet UITableViewCell *qualityCellXGA;
@property (weak, nonatomic) IBOutlet UITableViewCell *previewCell;
@property (weak, nonatomic) IBOutlet UITableViewCell *poweroffCell;
@property (weak, nonatomic) IBOutlet UITableViewCell *cameraVersionCell;
@property (weak, nonatomic) IBOutlet UITableViewCell *cameraKitVersionCell;
@property (strong, nonatomic) NSArray *qualityCellList;
@property (strong, nonatomic) NSArray *qualityValueList;

@end

@implementation SettingViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	
	self.qualityCellList = @[self.qualityCellQVGA, self.qualityCellVGA, self.qualityCellSVGA, self.qualityCellXGA];
	self.qualityValueList = @[NSStringFromCGSize(OLYCameraLiveViewSizeQVGA), NSStringFromCGSize(OLYCameraLiveViewSizeVGA), NSStringFromCGSize(OLYCameraLiveViewSizeSVGA), NSStringFromCGSize(OLYCameraLiveViewSizeXGA)];
	
	// Apply the current configuration to UI widgets.
	// Live view quality section:
	NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
	NSString *quality = [userDefaults objectForKey:@"live_preview_quality"];
	for (NSInteger index = 0; index < self.qualityValueList.count; index++) {
		UITableViewCell *qualityCell = self.qualityCellList[index];
		if ([quality isEqualToString:self.qualityValueList[index]]) {
			qualityCell.accessoryType = UITableViewCellAccessoryCheckmark;
		} else {
			qualityCell.accessoryType = UITableViewCellAccessoryNone;
		}
	}
	// Capture action section:
	NSString *recview = [userDefaults stringForKey:ICSCameraPropertyRecview];
	if ([recview isEqualToString:@"<RECVIEW/ON>"]) {
		self.previewCell.accessoryType = UITableViewCellAccessoryCheckmark;
	} else {
		self.previewCell.accessoryType = UITableViewCellAccessoryNone;
	}
	// Camera control section:
	self.poweroffCell.textLabel.textColor = [self.view tintColor];
	// Camera version section:
	OLYCamera *camera = AppDelegateCamera();
	NSDictionary *hardwareInformation = [camera inquireHardwareInformation:nil];
	if (hardwareInformation) {
		self.cameraVersionCell.textLabel.text = hardwareInformation[OLYCameraHardwareInformationCameraFirmwareVersionKey];
	} else {
		self.cameraVersionCell.textLabel.text = @"Unknown";
	}
	// SDK version section:
	self.cameraKitVersionCell.textLabel.text = OLYCameraKitVersion;
    
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)dealloc
{
	self.qualityCellList = nil;
}

- (BOOL)prefersStatusBarHidden
{
	return YES;
}

- (void)viewWillAppear:(BOOL)animated
{
	[super viewWillAppear:animated];
	[self.navigationController setNavigationBarHidden:NO animated:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
	if ([self.navigationController.viewControllers indexOfObject:self] == NSNotFound) {
		// Commit the new configuration when going back to the previous scene.
		NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
		for (NSInteger index = 0; index < self.qualityCellList.count; index++) {
			UITableViewCell *qualityCell = self.qualityCellList[index];
			if (qualityCell.accessoryType == UITableViewCellAccessoryCheckmark) {
				NSString *quality = self.qualityValueList[index];
				[userDefaults setObject:quality forKey:@"live_preview_quality"];
				[self applyLivePreviewQualityToCamera];
				break;
			}
		}
		NSString *preview = @"<RECVIEW/OFF>";
		if (self.previewCell.accessoryType == UITableViewCellAccessoryCheckmark) {
			preview = @"<RECVIEW/ON>";
		}
		[userDefaults setValue:preview forKey:ICSCameraPropertyRecview];
		[self applyShutterCapturedPreview];
	}
	[super viewWillDisappear:animated];
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
	[tableView deselectRowAtIndexPath:indexPath animated:YES];
	
	UITableViewCell *cell = [tableView cellForRowAtIndexPath:indexPath];
	if ([self.qualityCellList containsObject:cell]) {
		// Live view quality section:
		// Update the position of check mark.
		for (UITableViewCell *qualityCell in self.qualityCellList) {
			if ([cell isEqual:qualityCell]) {
				[qualityCell setAccessoryType:UITableViewCellAccessoryCheckmark];
			} else {
				[qualityCell setAccessoryType:UITableViewCellAccessoryNone];
			}
		}
	} else if ([cell isEqual:self.previewCell]) {
		// Capture action section:
		// Update the position of check mark.
		if (cell.accessoryType == UITableViewCellAccessoryCheckmark) {
			cell.accessoryType = UITableViewCellAccessoryNone;
		} else {
			cell.accessoryType = UITableViewCellAccessoryCheckmark;
		}
	} else if ([cell isEqual:self.poweroffCell]) {
		// Camera control section:
		AppDelegateCameraDisconnectWithPowerOff(YES);
	} else {
		// Ignore others.
	}
}

- (void)applyLivePreviewQualityToCamera
{
	OLYCamera *camera = AppDelegateCamera();
	NSError *error = nil;
	NSString *userLivePreviewQuality = [[NSUserDefaults standardUserDefaults] stringForKey:@"live_preview_quality"];
	if (userLivePreviewQuality) {
		if (![camera changeLiveViewSize:CGSizeFromString(userLivePreviewQuality) error:&error]) {
			NSLog(@"To change the live view size is failed: %@", error ? error : @"Unknown error");
		}
	}
}

- (void)applyShutterCapturedPreview
{
	NSString *recviewValue;
	NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
	recviewValue = [userDefaults stringForKey:ICSCameraPropertyRecview];
	if (!recviewValue) {
		recviewValue = @"<RECVIEW/OFF>";
	}

	OLYCamera *camera = AppDelegateCamera();
	NSError *error = nil;
	if (![camera setCameraPropertyValue:ICSCameraPropertyRecview value:recviewValue error:&error]) {
		NSLog(@"To change the rec-view mode is failed: %@", error ? error : @"Unknown error");
	}
}

@end
