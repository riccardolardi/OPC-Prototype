//
//  LiveViewController.m
//  ImageCaptureSample
//
//  Copyright (c) 2014 Olympus Imaging Corporation. All rights reserved.
//

#import <AudioToolbox/AudioToolbox.h>
#import "AppDelegate.h"
#import "CameraLiveImageView.h"
#import "LiveViewController.h"
#import "ParameterViewController.h"
#import "RecViewController.h"
#import "MIKMIDI.h"

@interface LiveViewController () <OLYCameraLiveViewDelegate, OLYCameraPropertyDelegate, OLYCameraRecordingSupportsDelegate>

@property (weak, nonatomic) IBOutlet UIView *imageContainerView;
@property (weak, nonatomic) IBOutlet CameraLiveImageView *imageView;
@property (weak, nonatomic) IBOutlet UILabel *remainingRecordableImagesLabel;
@property (weak, nonatomic) IBOutlet UIImageView *batteryLevelImageView;
@property (weak, nonatomic) IBOutlet UIButton *drivemodeButton;
@property (weak, nonatomic) IBOutlet UIButton *takemodeButton;
@property (weak, nonatomic) IBOutlet UIButton *shutterSpeedButton;
@property (weak, nonatomic) IBOutlet UIButton *apertureValueButton;
@property (weak, nonatomic) IBOutlet UIButton *exposureCompensationButton;
@property (weak, nonatomic) IBOutlet UIButton *isoSensitivityButton;
@property (weak, nonatomic) IBOutlet UIButton *whiteBalanceButton;
@property (weak, nonatomic) IBOutlet UIButton *shutterButton;
@property (weak, nonatomic) IBOutlet UIButton *secondaryButton;
@property (weak, nonatomic) IBOutlet UIView *parameterContainerView;
@property (weak, nonatomic) UIView *parameterBackgroundView;
@property (weak, nonatomic) ParameterViewController *parameterViewController;
@property (strong, nonatomic) NSDictionary *drivemodeIconList;
@property (strong, nonatomic) NSDictionary *whiteBalanceIconList;
@property (strong, nonatomic) NSDictionary *batteryIconList;
@property (assign, nonatomic) SystemSoundID focusedSound;
@property (assign, nonatomic) SystemSoundID shutterSound;
@property (strong, nonatomic) UIImage *capturedImage;

@end

@implementation LiveViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    [[self.isoSensitivityButton titleLabel] setNumberOfLines:2];
	self.parameterContainerView.hidden = YES;
	self.parameterBackgroundView = nil;
    
    self.drivemodeIconList = @{
        @"<TAKE_DRIVE/DRIVE_NORMAL>": @"RM_icn_drive_setting_single",
        @"<TAKE_DRIVE/DRIVE_CONTINUE>":	@"RM_icn_drive_setting_seq",
    };
    self.whiteBalanceIconList = @{
        @"<WB/WB_AUTO>": @"RM_icn_WB_setting_WBAUTO",
        @"<WB/MWB_SHADE>": @"RM_icn_WB_setting_16",
        @"<WB/MWB_CLOUD>": @"RM_icn_WB_setting_17",
        @"<WB/MWB_FINE>": @"RM_icn_WB_setting_18",
        @"<WB/MWB_LAMP>": @"RM_icn_WB_setting_20",
        @"<WB/MWB_FLUORESCENCE1>": @"RM_icn_WB_setting_35",
        @"<WB/MWB_WATER_1>": @"RM_icn_WB_setting_64",
        @"<WB/WB_CUSTOM1>": @"RM_icn_WB_setting_512",
    };
	self.batteryIconList = @{
		@"<BATTERY_LEVEL/UNKNOWN>": @"TT_icn_battery_unknown",
		@"<BATTERY_LEVEL/CHARGE>": @"TT_icn_battery_charge",
		@"<BATTERY_LEVEL/EMPTY>": @"TT_icn_battery_empty",
		@"<BATTERY_LEVEL/WARNING>": @"TT_icn_battery_half",
		@"<BATTERY_LEVEL/LOW>": @"TT_icn_battery_middle",
		@"<BATTERY_LEVEL/FULL>": @"TT_icn_battery_full",
		@"<BATTERY_LEVEL/EMPTY_AC>": @"TT_icn_battery_supply_empty",
		@"<BATTERY_LEVEL/SUPPLY_WARNING>": @"TT_icn_battery_supply_half",
		@"<BATTERY_LEVEL/SUPPLY_LOW>": @"TT_icn_battery_supply_middle",
		@"<BATTERY_LEVEL/SUPPLY_FULL>": @"TT_icn_battery_supply_full",
	};

	NSURL *focusedSoundURL = [[NSBundle mainBundle] URLForResource:@"FocusedSound" withExtension:@"caf"];
	SystemSoundID focusedSoundID;
	AudioServicesCreateSystemSoundID((__bridge CFURLRef)focusedSoundURL, &focusedSoundID);
	self.focusedSound = focusedSoundID;
    
	NSURL *shutterSoundURL = [[NSBundle mainBundle] URLForResource:@"ShutterSound" withExtension:@"caf"];
	SystemSoundID shutterSoundID;
	AudioServicesCreateSystemSoundID((__bridge CFURLRef)shutterSoundURL, &shutterSoundID);
	self.shutterSound = shutterSoundID;
    
    OLYCamera *camera = AppDelegateCamera();
    __block NSError *error = nil;
    NSString *value = @"<TAKEMODE/P>";
    if (![camera setCameraPropertyValue:ICSCameraPropertyTakemode value:value error:&error]) {
        NSLog(@"ERROR SETTING TAKEMODE TO P");
        return;
    }
    
    [self connectMidi];
}

- (void)didReceiveMemoryWarning
{
     [super didReceiveMemoryWarning];
}

- (void)dealloc
{
	self.drivemodeIconList = nil;
	self.whiteBalanceIconList = nil;
	self.batteryIconList = nil;
	
	AudioServicesDisposeSystemSoundID(self.focusedSound);
	AudioServicesDisposeSystemSoundID(self.shutterSound);
	
	[[NSNotificationCenter defaultCenter] removeObserver:self];
}

- (BOOL)prefersStatusBarHidden
{
	return YES;
}

- (void)viewWillAppear:(BOOL)animated
{
	[super viewWillAppear:animated];
	[self.navigationController setNavigationBarHidden:YES animated:animated];
    
	_imageView.image = nil;
	[_imageView hideFocusFrame];
	
	[self updateDrivemodeButton];
	[self updateTakemodeButton];
	[self updateShutterSpeedButton];
	[self updateApertureValueButton];
	[self updateExposureCompensationButton];
	[self updateIsoSensitivityButton];
	[self updateWhiteBalanceButton];
	[self updateBatteryLevelLabel];
	[self updateRemainingRecordableImagesLabel];
	
	OLYCamera *camera = AppDelegateCamera();
    camera.liveViewDelegate = self;
	camera.cameraPropertyDelegate = self;
	camera.recordingSupportsDelegate = self;
    [camera addObserver:self forKeyPath:@"actualApertureValue" options:0 context:@selector(apertureValueValueDidChange:)];
    [camera addObserver:self forKeyPath:@"actualShutterSpeed" options:0 context:@selector(shutterSpeedValueDidChange:)];
    [camera addObserver:self forKeyPath:@"actualExposureCompensation" options:0 context:@selector(exposureCompensationValueDidChange:)];
    [camera addObserver:self forKeyPath:@"actualIsoSensitivity" options:0 context:@selector(isoSensitivityValueDidChange:)];
    [camera addObserver:self forKeyPath:@"remainingImageCapacity" options:0 context:@selector(remainingRecordableImagesValueDidChange:)];
    [camera addObserver:self forKeyPath:@"mediaBusy" options:0 context:@selector(mediaBusyValueDidChange:)];
}

- (void)viewDidAppear:(BOOL)animated
{
	[super viewDidAppear:animated];
    [UIApplication sharedApplication].idleTimerDisabled = YES;
}

- (void)viewWillDisappear:(BOOL)animated
{
	[super viewWillDisappear:animated];
	[UIApplication sharedApplication].idleTimerDisabled = NO;
	
	OLYCamera *camera = AppDelegateCamera();
	camera.liveViewDelegate = nil;
	camera.cameraPropertyDelegate = nil;
	camera.recordingSupportsDelegate = nil;
	@try {
		[camera removeObserver:self forKeyPath:@"actualApertureValue"];
		[camera removeObserver:self forKeyPath:@"actualShutterSpeed"];
		[camera removeObserver:self forKeyPath:@"actualExposureCompensation"];
		[camera removeObserver:self forKeyPath:@"actualIsoSensitivity"];
		[camera removeObserver:self forKeyPath:@"remainingImageCapacity"];
		[camera removeObserver:self forKeyPath:@"mediaBusy"];
	}
	@catch (NSException *exception) {
		// Ignore all exceptions.
	}
}

- (IBAction)backToLiveView:(UIStoryboardSegue *)segue
{
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
	if ([segue.identifier isEqualToString:@"EmbedParameterScene"]) {
		ParameterViewController *controller = (ParameterViewController *)segue.destinationViewController;
		self.parameterViewController = controller;
        
	} else if ([segue.identifier isEqualToString:@"GoToRecView"]) {
        RecViewController *controller = (RecViewController *)segue.destinationViewController;
		controller.image = self.capturedImage;
		self.capturedImage = nil;
        
	} else if ([segue.identifier isEqualToString:@"GoToSettingView"]) {
		// No operations.
	}
}

- (IBAction)settingButtonDidTap:(UIButton *)sender
{
	[self performSegueWithIdentifier:@"GoToSettingView" sender:self];
}

#pragma mark - Camera actions -

- (IBAction)shutterButtonDidPan:(UIPanGestureRecognizer *)recognizer
{    
    CGPoint translation = [recognizer translationInView:self.view];
    recognizer.view.center = CGPointMake(recognizer.view.center.x + translation.x,
                                         recognizer.view.center.y + translation.y);
    [recognizer setTranslation:CGPointMake(0, 0) inView:self.view];
}

- (IBAction)secondaryButtonDidPan:(UIPanGestureRecognizer *)recognizer
{
    CGPoint translation = [recognizer translationInView:self.view];
    recognizer.view.center = CGPointMake(recognizer.view.center.x + translation.x,
                                         recognizer.view.center.y + translation.y);
    [recognizer setTranslation:CGPointMake(0, 0) inView:self.view];
}

- (IBAction)imageViewDidPan:(UIPanGestureRecognizer *)recognizer
{
    CGPoint viewPoint = [recognizer locationInView:_imageView];
    CGPoint imagePoint = [_imageView convertPointFromViewArea:viewPoint];
 	CGPoint focusPoint = OLYCameraConvertPointOnLiveImageIntoViewfinder(imagePoint, _imageView.image);
    
    // If the focus point is out of area, ignore the touch.
    if (!CGRectContainsPoint(CGRectMake(0, 0, 1, 1), focusPoint)) {
        [_imageView hideFocusFrame];
        return;
    }
    
    CGPoint translation = [recognizer translationInView:self.view];
    recognizer.view.center = CGPointMake(recognizer.view.center.x + translation.x,
                                         recognizer.view.center.y + translation.y);
    [recognizer setTranslation:CGPointMake(0, 0) inView:self.view];
}

- (IBAction)imageViewDidTap:(UITapGestureRecognizer *)sender
{
	OLYCamera *camera = AppDelegateCamera();
	NSError *error;
	
	// The application is not supported lock auto focus on movie mode.
	if (camera.actionType == OLYCameraActionTypeMovie) {
		return;
	}
	
    CGPoint viewPoint = [sender locationInView:_imageView];
    CGPoint imagePoint = [_imageView convertPointFromViewArea:viewPoint];
	CGPoint focusPoint = OLYCameraConvertPointOnLiveImageIntoViewfinder(imagePoint, _imageView.image);
	
	// If the focus point is out of area, ignore the touch.
	if (!CGRectContainsPoint(CGRectMake(0, 0, 1, 1), focusPoint)) {
		[_imageView hideFocusFrame];
		return;
	}
	
    // Display a provisional focus frame at the touched point.
	CGRect preFocusFrameRect = CGRectMake(viewPoint.x - 22, viewPoint.y - 22, 44, 44);
	[_imageView showFocusFrame:preFocusFrameRect status:CameraFocusFrameStatusRunning animated:NO];

	// Set auto-focus point.
    [[UIApplication sharedApplication] beginIgnoringInteractionEvents];
    if (![camera setAutoFocusPoint:focusPoint error:&error]) {
		[[UIApplication sharedApplication] endIgnoringInteractionEvents];
		[_imageView showFocusFrame:preFocusFrameRect status:CameraFocusFrameStatusFailed animated:YES];
		return;
	}
	// Lock auto-focus.
	__weak LiveViewController *weakSelf = self;
	[camera lockAutoFocus:^(NSDictionary *info) {
		[[UIApplication sharedApplication] endIgnoringInteractionEvents];
		
		NSString *focusResult = info[OLYCameraTakingPictureProgressInfoFocusResultKey];
		NSValue *focusRectValue = info[OLYCameraTakingPictureProgressInfoFocusRectKey];
		if ([focusResult isEqualToString:@"ok"] && focusRectValue) {
			AudioServicesPlaySystemSound(weakSelf.focusedSound);
			
			CGRect focusRect = [focusRectValue CGRectValue];
			CGRect imageRect = OLYCameraConvertRectOnViewfinderIntoLiveImage(focusRect, weakSelf.imageView.image);
			CGRect postFocusFrameRect = [weakSelf.imageView convertRectFromImageArea:imageRect];
			[weakSelf.imageView showFocusFrame:postFocusFrameRect status:CameraFocusFrameStatusFocused animated:YES];
			
		} else if ([focusResult isEqualToString:@"none"]) {
			[weakSelf.imageView hideFocusFrame];
			
		} else {
			[weakSelf.imageView showFocusFrame:preFocusFrameRect status:CameraFocusFrameStatusFailed animated:YES];
			
		}
		
	} errorHandler:^(NSError *error) {
		[[UIApplication sharedApplication] endIgnoringInteractionEvents];
		
		[weakSelf.imageView hideFocusFrame];
		
		NSString *title = NSLocalizedString(@"AF failed", nil);
		NSString *message = error.localizedDescription;
		NSString *ok = NSLocalizedString(@"OK", nil);
		UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:title message:message delegate:nil cancelButtonTitle:ok otherButtonTitles:nil];
		[alertView show];
		
	}];
	
}

- (IBAction)imageViewDidPinch:(UIPinchGestureRecognizer *)recognizer
{
    recognizer.view.transform = CGAffineTransformScale(recognizer.view.transform, recognizer.scale, recognizer.scale);
    recognizer.scale = 1;
}

- (IBAction)imageViewDidRotate:(UIRotationGestureRecognizer *)recognizer
{
    recognizer.view.transform = CGAffineTransformRotate(recognizer.view.transform, recognizer.rotation);
    recognizer.rotation = 0;
}

- (IBAction)shutterButtonDidTap:(UITapGestureRecognizer *)sender
{
	OLYCamera *camera = AppDelegateCamera();
	OLYCameraActionType actionType = [camera actionType];
    
    if (actionType != OLYCameraActionTypeSingle) {
        
        __block NSError *error = nil;
        NSString *value = @"<TAKEMODE/P>";
        if (![camera setCameraPropertyValue:ICSCameraPropertyTakemode value:value error:&error]) {
            NSLog(@"ERROR SETTING TAKEMODE TO P");
            return;
        }
        
    }
    
	if (camera.takingPicture || camera.recordingVideo) {
        NSLog(@"STILL TAKING PICTURE/FILMING");
		return;
    } else {
        [self takePicture];
    }
    
}

- (IBAction)shutterButtonDidLongPress:(UILongPressGestureRecognizer *)sender
{
    /*
    OLYCamera *camera = AppDelegateCamera();
    OLYCameraActionType actionType = [camera actionType];
    
    if (sender.state == UIGestureRecognizerStateBegan) {
		if (camera.takingPicture) {
			return;
		}
		if (actionType == OLYCameraActionTypeSingle) {
			[self takePicture];
		} else if (actionType == OLYCameraActionTypeSequential) {
			[self beginTakingPicture];
        } else if (actionType == OLYCameraActionTypeMovie) {
            [self beginRecordingVideo];
		}
		
	} else if (sender.state == UIGestureRecognizerStateEnded ||
			   sender.state == UIGestureRecognizerStateCancelled) {
        if (actionType == OLYCameraActionTypeSequential) {
			[self endTakingPicture];
        } else if (actionType == OLYCameraActionTypeMovie) {
            [self endRecordingVideo];
		}
	}
    */
    
}

- (IBAction)secondaryButtonDidTap:(UITapGestureRecognizer *)sender
{
    OLYCamera *camera = AppDelegateCamera();
    OLYCameraActionType actionType = [camera actionType];
    
    if (actionType != OLYCameraActionTypeMovie) {
        
        __block NSError *error = nil;
        NSString *value = @"<TAKEMODE/movie>";
        if (![camera setCameraPropertyValue:ICSCameraPropertyTakemode value:value error:&error]) {
            NSLog(@"ERROR SETTING TAKEMODE TO MOVIE");
            return;
        }
        
    }
        
    if (camera.recordingVideo) {
        [self endRecordingVideo];
        
        __block NSError *error = nil;
        NSString *value = @"<TAKEMODE/P>";
        if (![camera setCameraPropertyValue:ICSCameraPropertyTakemode value:value error:&error]) {
            NSLog(@"ERROR SETTING TAKEMODE TO P");
            return;
        }
        
    } else {
        [self beginRecordingVideo];
    }

}

- (IBAction)secondaryButtonDidLongPress:(UILongPressGestureRecognizer *)sender
{
    // OLYCamera *camera = AppDelegateCamera();
    // OLYCameraActionType actionType = [camera actionType];
    
    /*
    if (camera.takingPicture) {
        return;
    }
    
    if (camera.recordingVideo) {
        [self endRecordingVideo];
    } else {
        [self beginRecordingVideo];
    }
    */
}

- (void)takePicture
{
	[[UIApplication sharedApplication] beginIgnoringInteractionEvents];
    
	__weak LiveViewController *weakSelf = self;
	OLYCamera *camera = AppDelegateCamera();
	[camera takePicture:nil progressHandler:^(OLYCameraTakingProgress progress, NSDictionary *info) {
		
		if (progress == OLYCameraTakingProgressEndFocusing) {
			NSString *focusResult   = info[OLYCameraTakingPictureProgressInfoFocusResultKey];
			NSValue *focusRectValue = info[OLYCameraTakingPictureProgressInfoFocusRectKey];
            
			if ([focusResult isEqualToString:@"ok"] && focusRectValue) {
				CGRect focusRect = [focusRectValue CGRectValue];
				CGRect imageRect = OLYCameraConvertRectOnViewfinderIntoLiveImage(focusRect, weakSelf.imageView.image);
				CGRect postFocusFrameRect = [weakSelf.imageView convertRectFromImageArea:imageRect];
				[weakSelf.imageView showFocusFrame:postFocusFrameRect status:CameraFocusFrameStatusFocused animated:YES];
				
			} else if ([focusResult isEqualToString:@"none"]) {
				[weakSelf.imageView hideFocusFrame];
			} else {
				[weakSelf.imageView hideFocusFrame];
			}
			
		} else if (progress == OLYCameraTakingProgressBeginCapturing) {
			AudioServicesPlaySystemSound(weakSelf.shutterSound);
		}
		
	} completionHandler:^(NSDictionary *info) {
		[[UIApplication sharedApplication] endIgnoringInteractionEvents];
        
		[weakSelf.imageView hideFocusFrame];
		
	} errorHandler:^(NSError *error) {
		[[UIApplication sharedApplication] endIgnoringInteractionEvents];
		
		[weakSelf.imageView hideFocusFrame];
		
		if (error.domain != OLYCameraErrorDomain || error.code != OLYCameraErrorFocusFailed) {
			NSString *title = NSLocalizedString(@"Take failed", nil);
			NSString *message = error.localizedDescription;
			NSString *ok = NSLocalizedString(@"OK", nil);
			UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:title message:message delegate:nil cancelButtonTitle:ok otherButtonTitles:nil];
			[alertView show];
		}
		
	}];
}

- (void)beginTakingPicture
{
	[[UIApplication sharedApplication] beginIgnoringInteractionEvents];
    
	__weak LiveViewController *weakSelf = self;
	OLYCamera *camera = AppDelegateCamera();
	[camera startTakingPicture:nil progressHandler:^(OLYCameraTakingProgress progress, NSDictionary *info) {
        
		if (progress == OLYCameraTakingProgressEndFocusing) {
			NSString *focusResult = info[OLYCameraTakingPictureProgressInfoFocusResultKey];
			NSValue *focusRectValue = info[OLYCameraTakingPictureProgressInfoFocusRectKey];
			if ([focusResult isEqualToString:@"ok"] && focusRectValue) {
				CGRect focusRect = [focusRectValue CGRectValue];
				CGRect imageRect = OLYCameraConvertRectOnViewfinderIntoLiveImage(focusRect, weakSelf.imageView.image);
				CGRect postFocusFrameRect = [weakSelf.imageView convertRectFromImageArea:imageRect];
				[weakSelf.imageView showFocusFrame:postFocusFrameRect status:CameraFocusFrameStatusFocused animated:YES];
				
			} else if ([focusResult isEqualToString:@"none"]) {
				[weakSelf.imageView hideFocusFrame];
				
			} else {
				[weakSelf.imageView hideFocusFrame];
				
			}
            
		} else if (progress == OLYCameraTakingProgressBeginCapturing) {
			AudioServicesPlaySystemSound(weakSelf.shutterSound);
		}
		
	} completionHandler:^{
		[[UIApplication sharedApplication] endIgnoringInteractionEvents];
        
	} errorHandler:^(NSError *error) {
		[[UIApplication sharedApplication] endIgnoringInteractionEvents];
		
		[weakSelf.imageView hideFocusFrame];
		
		if (error.domain != OLYCameraErrorDomain || error.code != OLYCameraErrorFocusFailed) {
			NSString *title = NSLocalizedString(@"Take failed", nil);
			NSString *message = error.localizedDescription;
			NSString *ok = NSLocalizedString(@"OK", nil);
			UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:title message:message delegate:nil cancelButtonTitle:ok otherButtonTitles:nil];
			[alertView show];
		}
		
	}];
}

- (void)endTakingPicture
{
	[[UIApplication sharedApplication] beginIgnoringInteractionEvents];
    
	__weak LiveViewController *weakSelf = self;
    OLYCamera *camera = AppDelegateCamera();
	[camera stopTakingPicture:^(OLYCameraTakingProgress progress, NSDictionary *info) {
		// No operation.
	} completionHandler:^(NSDictionary *info) {
		[[UIApplication sharedApplication] endIgnoringInteractionEvents];
		
		[weakSelf.imageView hideFocusFrame];

	} errorHandler:^(NSError *error) {
		[[UIApplication sharedApplication] endIgnoringInteractionEvents];
		
		[weakSelf.imageView hideFocusFrame];
		
		if (error.domain != OLYCameraErrorDomain || error.code != OLYCameraErrorFocusFailed) {
			NSString *title = NSLocalizedString(@"Take failed", nil);
			NSString *message = error.localizedDescription;
			NSString *ok = NSLocalizedString(@"OK", nil);
			UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:title message:message delegate:nil cancelButtonTitle:ok otherButtonTitles:nil];
			[alertView show];
		}
		
	}];
}

- (void)beginRecordingVideo
{
	[[UIApplication sharedApplication] beginIgnoringInteractionEvents];
    
	OLYCamera *camera = AppDelegateCamera();
    self.secondaryButton.selected = YES;
    [camera startRecordingVideo:nil completionHandler:^{
		[[UIApplication sharedApplication] endIgnoringInteractionEvents];
    } errorHandler:^(NSError *error) {
		[[UIApplication sharedApplication] endIgnoringInteractionEvents];
        
		NSString *title = NSLocalizedString(@"Record failed", nil);
		NSString *message = error.localizedDescription;
		NSString *ok = NSLocalizedString(@"OK", nil);
		UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:title message:message delegate:nil cancelButtonTitle:ok otherButtonTitles:nil];
		[alertView show];
	}];
}

- (void)endRecordingVideo
{
	[[UIApplication sharedApplication] beginIgnoringInteractionEvents];
    
    OLYCamera *camera = AppDelegateCamera();
    self.secondaryButton.selected = NO;
	[camera stopRecordingVideo:^(NSDictionary *info) {
		[[UIApplication sharedApplication] endIgnoringInteractionEvents];
	} errorHandler:^(NSError *error) {
		[[UIApplication sharedApplication] endIgnoringInteractionEvents];
        
		NSString *title = NSLocalizedString(@"Record failed", nil);
		NSString *message = error.localizedDescription;
		NSString *ok = NSLocalizedString(@"OK", nil);
		UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:title message:message delegate:nil cancelButtonTitle:ok otherButtonTitles:nil];
		[alertView show];
    }];
}

#pragma mark - Camera property control -

#pragma mark drive mode

- (IBAction)drivemodeButtonDidTap:(UIButton *)sender
{
	__block NSError *error = nil;
    OLYCamera *camera = AppDelegateCamera();
	NSArray *valueList = [camera cameraPropertyValueList:ICSCameraPropertyDrivemode error:&error];
	if (!valueList) {
		return;
	}
    NSMutableArray *parameterList = [[NSMutableArray alloc] init];
    for (NSString *value in valueList) {
		NSString *title = NSLocalizedString([camera cameraPropertyValueTitle:value], nil);
        [parameterList addObject:@{ICSParameterListTitleKey:title, ICSParameterListValueKey:value}];
    }
	NSString *currentValue = [camera cameraPropertyValue:ICSCameraPropertyDrivemode error:&error];
	if (!currentValue) {
		return;
	}
    self.drivemodeButton.selected = YES;

    __weak LiveViewController *weakSelf = self;
	[self presentParameterList:parameterList initialValue:currentValue handler:^(NSString *value) {
		[weakSelf dismissParameterList];
        self.drivemodeButton.selected = NO;
		if (![camera setCameraPropertyValue:ICSCameraPropertyDrivemode value:value error:&error]) {
			return;
		}
        [self updateDrivemodeButton];
    }];
}

- (void)updateDrivemodeButton
{
	NSError *error = nil;
    OLYCamera *camera = AppDelegateCamera();
	NSString *value = [camera cameraPropertyValue:ICSCameraPropertyDrivemode error:&error];
	UIImage *iconImageNormal = nil;
	UIImage *iconImageSelected = nil;
	if (value) {
		NSString *iconImageName = self.drivemodeIconList[value];
		iconImageNormal = [UIImage imageNamed:[NSString stringWithFormat:@"%@", iconImageName]];
		iconImageSelected = [UIImage imageNamed:[NSString stringWithFormat:@"%@_pushed", iconImageName]];
	}
	[self.drivemodeButton setImage:iconImageNormal forState:UIControlStateNormal];
	[self.drivemodeButton setImage:iconImageSelected forState:UIControlStateSelected];
	self.drivemodeButton.enabled = [camera canSetCameraProperty:ICSCameraPropertyDrivemode];
}

#pragma mark take mode (aperture mode)

- (IBAction)takemodeButtonDidTap:(UIButton *)sender
{
	__block NSError *error = nil;
    OLYCamera *camera = AppDelegateCamera();
	NSArray *valueList = [camera cameraPropertyValueList:ICSCameraPropertyTakemode error:&error];
	if (!valueList) {
		return;
	}
    NSMutableArray *parameterList = [[NSMutableArray alloc] init];
    for (NSString *value in valueList) {
		NSString *title = NSLocalizedString([camera cameraPropertyValueTitle:value], nil);
        [parameterList addObject:@{ICSParameterListTitleKey:title, ICSParameterListValueKey:value}];
    }
	NSString *currentValue = [camera cameraPropertyValue:ICSCameraPropertyTakemode error:&error];
	if (!currentValue) {
		return;
	}
    self.takemodeButton.selected = YES;
	
    __weak LiveViewController *weakSelf = self;
	[self presentParameterList:parameterList initialValue:currentValue handler:^(NSString *value) {
		[weakSelf dismissParameterList];
        self.takemodeButton.selected = NO;
		if (![camera setCameraPropertyValue:ICSCameraPropertyTakemode value:value error:&error]) {
			return;
		}
        [self updateTakemodeButton];
    }];
}

- (void)updateTakemodeButton
{
	NSError *error = nil;
	OLYCamera *camera = AppDelegateCamera();
	NSString *value = [camera cameraPropertyValue:ICSCameraPropertyTakemode error:&error];
	NSString *title = @"";
	if (value) {
		title = NSLocalizedString([camera cameraPropertyValueTitle:value], nil);
	}
	[self updateButtonTitle:self.takemodeButton withTitle:title];
	self.takemodeButton.enabled = [camera canSetCameraProperty:ICSCameraPropertyTakemode];
	self.shutterSpeedButton.enabled = [camera canSetCameraProperty:ICSCameraPropertyShutterSpeed];
	self.apertureValueButton.enabled = [camera canSetCameraProperty:ICSCameraPropertyApertureValue];
	self.exposureCompensationButton.enabled = [camera canSetCameraProperty:ICSCameraPropertyExposureCompensation];
	self.isoSensitivityButton.enabled = [camera canSetCameraProperty:ICSCameraPropertyIsoSensitivity];
	self.whiteBalanceButton.enabled = [camera canSetCameraProperty:ICSCameraPropertyWhiteBalance];
}

#pragma mark shutter speed

- (IBAction)shutterSpeedButtonDidTap:(UIButton *)sender
{
	__block NSError *error = nil;
    OLYCamera *camera = AppDelegateCamera();
	NSArray *valueList = [camera cameraPropertyValueList:ICSCameraPropertyShutterSpeed error:&error];
	if (!valueList) {
		return;
	}
    NSMutableArray *parameterList = [[NSMutableArray alloc] init];
    for (NSString *value in valueList) {
		NSString *title = NSLocalizedString([camera cameraPropertyValueTitle:value], nil);
        [parameterList addObject:@{ICSParameterListTitleKey:title, ICSParameterListValueKey:value}];
    }
	NSString *currentValue = [camera cameraPropertyValue:ICSCameraPropertyShutterSpeed error:&error];
	if (!currentValue) {
		return;
	}
    self.shutterSpeedButton.selected = YES;
	
    __weak LiveViewController *weakSelf = self;
	[self presentParameterList:parameterList initialValue:currentValue handler:^(NSString *value) {
		[weakSelf dismissParameterList];
        self.shutterSpeedButton.selected = NO;
		if (![camera setCameraPropertyValue:ICSCameraPropertyShutterSpeed value:value error:&error]) {
			return;
		}
    }];
}

- (void)shutterSpeedValueDidChange:(NSDictionary *)change
{
	[self updateShutterSpeedButton];
}

- (void)updateShutterSpeedButton
{
	OLYCamera *camera = AppDelegateCamera();
	NSString *value = camera.actualShutterSpeed;
	NSString *title = @"";
	if (value) {
		title = NSLocalizedString([camera cameraPropertyValueTitle:value], nil);
	}
	[self updateButtonTitle:self.shutterSpeedButton withTitle:title];
	self.shutterSpeedButton.enabled = [camera canSetCameraProperty:ICSCameraPropertyShutterSpeed];
}

#pragma mark aperture value

- (IBAction)apertureValueButtonDidTap:(UIButton *)sender
{
	__block NSError *error = nil;
    OLYCamera *camera = AppDelegateCamera();
	NSArray *valueList = [camera cameraPropertyValueList:ICSCameraPropertyApertureValue error:&error];
	if (!valueList) {
		return;
	}
    NSMutableArray *parameterList = [[NSMutableArray alloc] init];
    for (NSString *value in valueList) {
		NSString *title = NSLocalizedString([camera cameraPropertyValueTitle:value], nil);
        [parameterList addObject:@{ICSParameterListTitleKey:title, ICSParameterListValueKey:value}];
    }
	NSString *currentValue = [camera cameraPropertyValue:ICSCameraPropertyApertureValue error:&error];
	if (!currentValue) {
		return;
	}
    self.apertureValueButton.selected = YES;
	
    __weak LiveViewController *weakSelf = self;
	[self presentParameterList:parameterList initialValue:currentValue handler:^(NSString *value) {
		[weakSelf dismissParameterList];
        self.apertureValueButton.selected = NO;
		if (![camera setCameraPropertyValue:ICSCameraPropertyApertureValue value:value error:&error]) {
			return;
		}
    }];
}

- (void)apertureValueValueDidChange:(NSDictionary *)change
{
	[self updateApertureValueButton];
}

- (void)updateApertureValueButton
{
	OLYCamera *camera = AppDelegateCamera();
	NSString *value = camera.actualApertureValue;
	NSString *title = @"";
	if (value) {
		title = NSLocalizedString([camera cameraPropertyValueTitle:value], nil);
	}
	[self updateButtonTitle:self.apertureValueButton withTitle:title];
	self.apertureValueButton.enabled = [camera canSetCameraProperty:ICSCameraPropertyApertureValue];
}

#pragma mark exposure compensation

- (IBAction)exposureCompensationButtonDidTap:(UIButton *)sender
{
	__block NSError *error = nil;
    OLYCamera *camera = AppDelegateCamera();
	NSArray *valueList = [camera cameraPropertyValueList:ICSCameraPropertyExposureCompensation error:&error];
	if (!valueList) {
		return;
	}
    NSMutableArray *parameterList = [[NSMutableArray alloc] init];
    for (NSString *value in valueList) {
		NSString *title = NSLocalizedString([camera cameraPropertyValueTitle:value], nil);
        [parameterList addObject:@{ICSParameterListTitleKey:title, ICSParameterListValueKey:value}];
    }
	NSString *currentValue = [camera cameraPropertyValue:ICSCameraPropertyExposureCompensation error:&error];
	if (!currentValue) {
		return;
	}
    self.exposureCompensationButton.selected = YES;
	
    __weak LiveViewController *weakSelf = self;
	[self presentParameterList:parameterList initialValue:currentValue handler:^(NSString *value) {
		[weakSelf dismissParameterList];
        self.exposureCompensationButton.selected = NO;
		if (![camera setCameraPropertyValue:ICSCameraPropertyExposureCompensation value:value error:&error]) {
			return;
		}
    }];
}

- (void)exposureCompensationHigher
{
    __block NSError *error = nil;
    OLYCamera *camera = AppDelegateCamera();
    NSArray *valueList = [camera cameraPropertyValueList:ICSCameraPropertyExposureCompensation error:&error];
    if (!valueList) {
        return;
    }
    NSMutableArray *parameterList = [[NSMutableArray alloc] init];
    for (NSString *value in valueList) {
        NSString *title = NSLocalizedString([camera cameraPropertyValueTitle:value], nil);
        [parameterList addObject:@{ICSParameterListTitleKey:title, ICSParameterListValueKey:value}];
    }
    NSString *currentValue = [camera cameraPropertyValue:ICSCameraPropertyExposureCompensation error:&error];
    if (!currentValue) {
        return;
    }

    NSInteger indexOfCurrentValue = [valueList indexOfObject:currentValue];
    int newIndex = (int)indexOfCurrentValue;
    if (valueList.count > newIndex+1) {
        NSString *value = [valueList objectAtIndex:newIndex+1];
        if (![camera setCameraPropertyValue:ICSCameraPropertyExposureCompensation value:value error:&error]) {
            NSLog(@"ERROR SETTING EX HIGHER TO: %d", newIndex);
            return;
        }
    }
}

- (void)exposureCompensationLower
{
    __block NSError *error = nil;
    OLYCamera *camera = AppDelegateCamera();
    NSArray *valueList = [camera cameraPropertyValueList:ICSCameraPropertyExposureCompensation error:&error];
    if (!valueList) {
        return;
    }
    NSMutableArray *parameterList = [[NSMutableArray alloc] init];
    for (NSString *value in valueList) {
        NSString *title = NSLocalizedString([camera cameraPropertyValueTitle:value], nil);
        [parameterList addObject:@{ICSParameterListTitleKey:title, ICSParameterListValueKey:value}];
    }
    NSString *currentValue = [camera cameraPropertyValue:ICSCameraPropertyExposureCompensation error:&error];
    if (!currentValue) {
        return;
    }

    NSInteger indexOfCurrentValue = [valueList indexOfObject:currentValue];
    int newIndex = (int)indexOfCurrentValue;
    
    if (newIndex-1 > 0) {
        NSString *value = [valueList objectAtIndex:newIndex-1];
        if (![camera setCameraPropertyValue:ICSCameraPropertyExposureCompensation value:value error:&error]) {
            NSLog(@"ERROR SETTING EX LOWER TO: %d", newIndex);
            return;
        }
    }
}

- (void)exposureCompensationValueDidChange:(NSDictionary *)change
{
	[self updateExposureCompensationButton];
}

- (void)updateExposureCompensationButton
{
	OLYCamera *camera = AppDelegateCamera();
	NSString *value = camera.actualExposureCompensation;
	NSString *title = @"";
	if (value) {
		title = NSLocalizedString([camera cameraPropertyValueTitle:value], nil);
	}
	[self updateButtonTitle:self.exposureCompensationButton withTitle:title];
	self.exposureCompensationButton.enabled = [camera canSetCameraProperty:ICSCameraPropertyExposureCompensation];
}

#pragma mark ISO sensitivity

- (IBAction)isoSensitivityButtonDidTap:(UIButton *)sender
{
	__block NSError *error = nil;
    OLYCamera *camera = AppDelegateCamera();
	NSArray *valueList = [camera cameraPropertyValueList:ICSCameraPropertyIsoSensitivity error:&error];
	if (!valueList) {
		return;
	}
    NSMutableArray *parameterList = [[NSMutableArray alloc] init];
    for (NSString *value in valueList) {
		NSString *title = NSLocalizedString([camera cameraPropertyValueTitle:value], nil);
        [parameterList addObject:@{ICSParameterListTitleKey:title, ICSParameterListValueKey:value}];
    }
	NSString *currentValue = [camera cameraPropertyValue:ICSCameraPropertyIsoSensitivity error:&error];
	if (!currentValue) {
		return;
	}
    self.isoSensitivityButton.selected = YES;

    __weak LiveViewController *weakSelf = self;
	[self presentParameterList:parameterList initialValue:currentValue handler:^(NSString *value) {
		[weakSelf dismissParameterList];
        self.isoSensitivityButton.selected = NO;
		if (![camera setCameraPropertyValue:ICSCameraPropertyIsoSensitivity value:value error:&error]) {
			return;
		}
    }];
}

- (void)isoSensitivityValueDidChange:(NSDictionary *)change
{
	[self updateIsoSensitivityButton];
}

- (void)updateIsoSensitivityButton
{
	NSError *error = nil;
	OLYCamera *camera = AppDelegateCamera();
	NSString *title = @"";
	NSString *preferred = [camera cameraPropertyValue:ICSCameraPropertyIsoSensitivity error:&error];
	if (preferred) {
		NSString *value = camera.actualIsoSensitivity;
		if ([preferred isEqualToString:@"<ISO/Auto>"]) {
			title = [NSString stringWithFormat:@"ISO-A\n%@", NSLocalizedString([camera cameraPropertyValueTitle:value], nil)];
		} else {
			title = [NSString stringWithFormat:@"ISO\n%@", NSLocalizedString([camera cameraPropertyValueTitle:value], nil)];
		}
	}
	[self updateButtonTitle:self.isoSensitivityButton withTitle:title];
	self.isoSensitivityButton.enabled = [camera canSetCameraProperty:ICSCameraPropertyIsoSensitivity];
}

#pragma mark white balance

- (IBAction)whiteBalanceButtonDidTap:(UIButton *)sender
{
	__block NSError *error = nil;
    OLYCamera *camera = AppDelegateCamera();
	NSArray *valueList = [camera cameraPropertyValueList:ICSCameraPropertyWhiteBalance error:&error];
	if (!valueList) {
		return;
	}
    NSMutableArray *parameterList = [[NSMutableArray alloc] init];
    for (NSString *value in valueList) {
		NSString *title = NSLocalizedString([camera cameraPropertyValueTitle:value], nil);
        [parameterList addObject:@{ICSParameterListTitleKey:title, ICSParameterListValueKey:value}];
    }
	NSString *currentValue = [camera cameraPropertyValue:ICSCameraPropertyWhiteBalance error:&error];
	if (!currentValue) {
		return;
	}
    self.whiteBalanceButton.selected = YES;
	
    __weak LiveViewController *weakSelf = self;
	[self presentParameterList:parameterList initialValue:currentValue handler:^(NSString *value) {
		[weakSelf dismissParameterList];
        self.whiteBalanceButton.selected = NO;
		if (![camera setCameraPropertyValue:ICSCameraPropertyWhiteBalance value:value error:&error]) {
			return;
		}
		[self updateWhiteBalanceButton];
    }];
}

- (void)whiteBalanceValueDidChange:(NSDictionary *)change
{
	[self updateWhiteBalanceButton];
}

- (void)updateWhiteBalanceButton
{
	NSError *error = nil;
    OLYCamera *camera = AppDelegateCamera();
	NSString *value = [camera cameraPropertyValue:ICSCameraPropertyWhiteBalance error:&error];
	UIImage *iconImageNormal = nil;
	UIImage *iconImageSelected = nil;
	if (value) {
		NSString *iconImageName = self.whiteBalanceIconList[value];
		iconImageNormal = [UIImage imageNamed:[NSString stringWithFormat:@"%@", iconImageName]];
		iconImageSelected = [UIImage imageNamed:[NSString stringWithFormat:@"%@_pushed", iconImageName]];
	}
	[self.whiteBalanceButton setImage:iconImageNormal forState:UIControlStateNormal];
	[self.whiteBalanceButton setImage:iconImageSelected forState:UIControlStateSelected];
	self.whiteBalanceButton.enabled = [camera canSetCameraProperty:ICSCameraPropertyWhiteBalance];
}

#pragma mark battery level

- (void)batteryLevelValueDidChange:(NSDictionary *)change
{
	[self updateBatteryLevelLabel];
}

- (void)updateBatteryLevelLabel
{
    NSError *error = nil;
	OLYCamera *camera = AppDelegateCamera();
    NSString *value = [camera cameraPropertyValue:ICSCameraPropertyBatteryLevel error:&error];
	UIImage *iconImage = nil;
	if (value) {
		NSString *iconImageName = self.batteryIconList[value];
		iconImage = [UIImage imageNamed:iconImageName];
	}
	self.batteryLevelImageView.image = iconImage;
}

#pragma mark remaining recordable images

- (void)remainingRecordableImagesValueDidChange:(NSDictionary *)change
{
	[self updateRemainingRecordableImagesLabel];
}

- (void)updateRemainingRecordableImagesLabel
{
	OLYCamera *camera = AppDelegateCamera();
	NSString *text = nil;
	if (camera.connected || camera.runMode == OLYCameraRunModeRecording) {
		if (camera.mediaBusy) {
			text = NSLocalizedString(@"BUSY", nil);
		} else {
			text = [NSString stringWithFormat:@"%lu", (unsigned long)camera.remainingImageCapacity];
		}
	} else {
		text = NSLocalizedString(@"???", nil);
	}
	self.remainingRecordableImagesLabel.text = text;
}

- (void)mediaBusyValueDidChange:(NSDictionary *)change
{
	[self updateRemainingRecordableImagesLabel];
}

#pragma mark Helpers

- (void)updateButtonTitle:(UIButton *)button withTitle:(NSString *)title
{
	[button setTitle:title forState:UIControlStateNormal];
	[button setTitle:title forState:UIControlStateHighlighted];
	[button setTitle:title forState:UIControlStateSelected];
	[button setTitle:title forState:UIControlStateDisabled];
}

- (void)presentParameterList:(NSArray *)list initialValue:(NSString *)value handler:(void (^)(NSString *value))handler
{
	UIView *backgroundView = [[UIView alloc] initWithFrame:self.view.frame];
	backgroundView.backgroundColor = [UIColor clearColor];
    
	UITapGestureRecognizer *guesture = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(parameterBackgroundViewDidTap:)];
	backgroundView.gestureRecognizers = @[guesture];
    
	self.parameterBackgroundView = backgroundView;
	[self.view addSubview:backgroundView];
	[self.view bringSubviewToFront:self.parameterContainerView];
	[self.parameterViewController setList:list value:value handler:handler];
	self.parameterContainerView.hidden = NO;
}

- (void)parameterBackgroundViewDidTap:(UIView *)sender
{
	[self dismissParameterList];
    
    self.drivemodeButton.selected = NO;
    self.takemodeButton.selected = NO;
    self.shutterSpeedButton.selected = NO;
    self.apertureValueButton.selected = NO;
    self.exposureCompensationButton.selected = NO;
    self.isoSensitivityButton.selected = NO;
    self.whiteBalanceButton.selected = NO;
}

- (void)dismissParameterList
{
	self.parameterContainerView.hidden = YES;
	[self.parameterViewController removeList];
	[self.parameterBackgroundView removeFromSuperview];
	self.parameterBackgroundView.gestureRecognizers = nil;
	self.parameterBackgroundView = nil;
}

#pragma mark - Camera event handlings -

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
	if (![NSThread isMainThread]) {
		dispatch_async(dispatch_get_main_queue(), ^{
			 [self observeValueForKeyPath:keyPath ofObject:object change:change context:context];
		});
	} else {
		// The notification is received in main thread.
		SEL selector = (SEL)context;
		if (selector && [self respondsToSelector:selector]) {
			[self performSelector:selector withObject:change afterDelay:0];
		}
	}
}

- (void)camera:(OLYCamera *)camera didUpdateLiveView:(NSData *)data metadata:(NSDictionary *)metadata
{
	UIImage *image = OLYCameraConvertDataToImage(data, metadata);
    _imageView.image = nil; // HACK: Force to refresh UIImageView contents.
	_imageView.image = image;
}

- (void)camera:(OLYCamera *)camera didChangeCameraProperty:(NSString *)name
{
	if (![NSThread isMainThread]) {
		dispatch_async(dispatch_get_main_queue(), ^{
			[self camera:camera didChangeCameraProperty:name];
		});
	} else {
		// The notification is received in main thread.
        if ([name isEqualToString:ICSCameraPropertyTakemode]) {
            [self updateTakemodeButton];
        } else if ([name isEqualToString:ICSCameraPropertyDrivemode]) {
            [self updateDrivemodeButton];
        } else if ([name isEqualToString:ICSCameraPropertyWhiteBalance]) {
            [self updateWhiteBalanceButton];
        } else if ([name isEqualToString:ICSCameraPropertyBatteryLevel]) {
            [self updateBatteryLevelLabel];
        }
	}
}

- (void)camera:(OLYCamera *)camera didReceiveCapturedImagePreview:(NSData *)data metadata:(NSDictionary *)metadata
{
	if (![NSThread isMainThread]) {
		dispatch_async(dispatch_get_main_queue(), ^{
			[self camera:camera didReceiveCapturedImagePreview:data metadata:metadata];
		});
	} else {
		// If the controller is not show, ignore the notify.
		NSArray *controllers = self.navigationController.viewControllers;
		if ([controllers lastObject] != self) {
			return;
		}
		OLYCameraActionType actionType = [camera actionType];
		if (actionType == OLYCameraActionTypeSingle) {
			UIImage *image = OLYCameraConvertDataToImage(data, metadata);
			if (image) {
				self.capturedImage = image;
                // should show captured image?
				// [self performSegueWithIdentifier:@"GoToRecView" sender:self];
			}
		}
	}
}

// MIDI

- (void)connectMidi
{
    MIKMIDIDeviceManager *deviceManager = [MIKMIDIDeviceManager sharedDeviceManager];
    
    NSArray *availableDevices = [deviceManager availableDevices];
    
    MIKMIDIDevice *device;
    
    BOOL found = NO;
    
    int i = 0;
    for (id object in availableDevices) {
        // Ototo strangely responds with name following 3 space characters:
        if ([[object name] isEqual: @"Dentaku Ototo   "]) {
            device = availableDevices[i];
            NSLog(@"FOUND OTOTO");
            NSLog(@"Device name: %@", device.name);
            found = YES;
        }
        i++;
    }
    
    if (found == YES) {
        
        NSArray *sources = [device.entities valueForKeyPath:@"@unionOfArrays.sources"];
        if (![sources count]) return;
        MIKMIDISourceEndpoint *source = [sources objectAtIndex:0];
        NSError *error = nil;
        
        id connectionToken = [deviceManager connectInput:source error:&error eventHandler:^(MIKMIDISourceEndpoint *source, NSArray *commands) {
            
            for (MIKMIDIChannelVoiceCommand *command in commands) {
                
                if (command.commandType == MIKMIDICommandTypeNoteOn) {
                    
                    MIKMIDINoteOnCommand *note = command;
                    
                    [[UIApplication sharedApplication] handleMIDICommand:command];
                    
                    NSLog(@"Received from ototo: %@", command);
                    
                    if (note.note == 60) {
                        // shutter
                        [self shutterButtonDidTap:nil];
                    } else if (note.note == 62) {
                        // movie
                        [self secondaryButtonDidTap:nil];
                    } else if (note.note == 64) {
                        // EX-
                        [self exposureCompensationLower];
                    } else if (note.note == 65) {
                        // EX+
                        [self exposureCompensationHigher];
                    }
                    
                }
            }
            
        }];
        
        if (!connectionToken) NSLog(@"Unable to connect to input: %@", error);
    }
}

@end