//
//  AppDelegate.m
//  ImageCaptureSample
//
//  Copyright (c) 2014 Olympus Imaging Corporation. All rights reserved.
//

#import "AppDelegate.h"
#import "Reachability.h"

NSString *const kAppDelegateCameraDidChangeConnectionStateNotification = @"kAppDelegateCameraDidChangeConnectionStateNotification";
NSString *const kConnectionStateKey = @"state";
NSString *const kConnectionStateConnected = @"connected";
NSString *const kConnectionStateDisconnected = @"disconnected";

NSString *ICSCameraPropertyTakemode = @"TAKEMODE";
NSString *ICSCameraPropertyDrivemode = @"TAKE_DRIVE";
NSString *ICSCameraPropertyApertureValue = @"APERTURE";
NSString *ICSCameraPropertyShutterSpeed = @"SHUTTER";
NSString *ICSCameraPropertyExposureCompensation = @"EXPREV";
NSString *ICSCameraPropertyWhiteBalance = @"WB";
NSString *ICSCameraPropertyIsoSensitivity = @"ISO";
NSString *ICSCameraPropertyBatteryLevel = @"BATTERY_LEVEL";
NSString *ICSCameraPropertyRecview = @"RECVIEW";

@interface AppDelegate () <OLYCameraConnectionDelegate>

@property (strong, nonatomic) dispatch_queue_t connectionQueue;
@property (strong, nonatomic) OLYCamera *camera;
@property (strong, nonatomic) Reachability *reachabilityForLocalWiFi;
@property (assign, getter = isConnecting, atomic) BOOL connecting;

@end

@implementation AppDelegate

+ (void)initialize
{
	if ([self class] != [AppDelegate class]) {
		return;
	}
	NSDictionary *userDefaults = @{@"live_preview_quality": NSStringFromCGSize(OLYCameraLiveViewSizeQVGA),
								   ICSCameraPropertyTakemode: @"<TAKEMODE/iAuto>",
								   ICSCameraPropertyDrivemode: @"<TAKE_DRIVE/DRIVE_NORMAL>",
								   ICSCameraPropertyRecview: @"<RECVIEW/ON>"};
	[[NSUserDefaults standardUserDefaults] registerDefaults:userDefaults];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	_camera = [[OLYCamera alloc] init];
	[_camera setConnectionDelegate:self];
	
	_connectionQueue = dispatch_queue_create([NSString stringWithFormat:@"%@.queue", [NSBundle mainBundle].bundleIdentifier].UTF8String, DISPATCH_QUEUE_SERIAL);
	
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didChangeNetworkReachability:) name:kReachabilityChangedNotification object:nil];
	_reachabilityForLocalWiFi = [Reachability reachabilityForLocalWiFi];
	
    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
	[self.reachabilityForLocalWiFi stopNotifier];
	[self disconnectWithPowerOff:NO];
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
	[self startScanningCamera];
}

- (void)applicationWillTerminate:(UIApplication *)application
{
}

#pragma mark -

- (void)startScanningCamera
{
	[self.reachabilityForLocalWiFi startNotifier];
	if (self.reachabilityForLocalWiFi.currentReachabilityStatus == ReachableViaWiFi) {
		[self startConnectingToCamera];
	}
}

- (void)startConnectingToCamera
{
	if (self.isConnecting) {
		return;
	}
	self.connecting = YES;
	
	dispatch_async(self.connectionQueue, ^{
		// This process will take some time...
		NSError *error = nil;
		if (![_camera connect:&error]) {
			NSLog(@"To connect to the camera is failed: %@", error ? error : @"Unknown error");
			self.connecting = NO;
			return;
		}
		NSString *userLivePreviewQuality = [[NSUserDefaults standardUserDefaults] stringForKey:@"live_preview_quality"];
		if (userLivePreviewQuality) {
			if (![_camera changeLiveViewSize:CGSizeFromString(userLivePreviewQuality) error:&error]) {
				NSLog(@"To change the live view size is failed: %@", error ? error : @"Unknown error");
			}
		}
		if (![_camera changeRunMode:OLYCameraRunModeRecording error:&error]) {
			NSLog(@"To change the run-mode is failed: %@", error ? error : @"Unknown error");
			self.connecting = NO;
			return;
		}
		
		// Restores my settings.
		if (_camera.connected) {
			NSArray *names = @[ICSCameraPropertyTakemode,
							   ICSCameraPropertyDrivemode,
							   ICSCameraPropertyApertureValue,
							   ICSCameraPropertyShutterSpeed,
							   ICSCameraPropertyExposureCompensation,
							   ICSCameraPropertyWhiteBalance,
							   ICSCameraPropertyIsoSensitivity,
							   ICSCameraPropertyRecview];
			NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
			NSMutableDictionary *values = [[NSMutableDictionary alloc] initWithCapacity:names.count];
			[names enumerateObjectsUsingBlock:^(id name, NSUInteger idx, BOOL *stop) {
				id value = [userDefaults valueForKey:name];
				if (value) {
					[values setObject:value forKey:name];
				}
			}];
			if (values.count > 0) {
				if (![_camera setCameraPropertyValues:values error:&error]) {
					NSLog(@"To change the camera properties is failed: %@", error ? error : @"Unknown error");
				}
			}
		}
		self.connecting = NO;
		
		dispatch_async(dispatch_get_main_queue(), ^{
			if (!_camera.connected) {
				return;
			}
			
			[[NSNotificationCenter defaultCenter] postNotificationName:kAppDelegateCameraDidChangeConnectionStateNotification object:self userInfo:@{kConnectionStateKey: kConnectionStateConnected}];
		});
	});
}

- (void)disconnectWithPowerOff:(BOOL)powerOff
{
	[[NSNotificationCenter defaultCenter] postNotificationName:kAppDelegateCameraDidChangeConnectionStateNotification object:self userInfo:@{kConnectionStateKey: kConnectionStateDisconnected}];
	
	dispatch_sync(self.connectionQueue, ^{
		NSError *error = nil;
		
		// Stores current settings.
		if (_camera.connected) {
			NSArray *names = @[ICSCameraPropertyTakemode,
							   ICSCameraPropertyDrivemode,
							   ICSCameraPropertyApertureValue,
							   ICSCameraPropertyShutterSpeed,
							   ICSCameraPropertyExposureCompensation,
							   ICSCameraPropertyWhiteBalance,
							   ICSCameraPropertyIsoSensitivity,
							   ICSCameraPropertyRecview];
			NSDictionary *values = [_camera cameraPropertyValues:[NSSet setWithArray:names] error:&error];
			if (values) {
				NSUserDefaults *userDefaults = [NSUserDefaults standardUserDefaults];
				[values enumerateKeysAndObjectsUsingBlock:^(id key, id obj, BOOL *stop) {
					[userDefaults setObject:obj forKey:key];
				}];
			} else {
				NSLog(@"To get the camera properties is failed: %@", error ? error : @"Unknown error");
			}
		}
		
		if (![_camera disconnectWithPowerOff:powerOff error:&error]) {
			NSLog(@"To disconnect from the camera is failed: %@", error ? error : @"Unknown error");
		}
	});
}

#pragma mark - Reachabiliry

- (void)didChangeNetworkReachability:(Reachability *)noteObject
{
	NetworkStatus status = self.reachabilityForLocalWiFi.currentReachabilityStatus;
	dispatch_async(dispatch_get_main_queue(), ^{
		if (status == ReachableViaWiFi) {
			[self startConnectingToCamera];
		}
	});
}

#pragma mark - OLYCameraConnectionDelegate

- (void)camera:(OLYCamera *)camera disconnectedByError:(NSError *)error
{
	dispatch_async(dispatch_get_main_queue(), ^{
		[[NSNotificationCenter defaultCenter] postNotificationName:kAppDelegateCameraDidChangeConnectionStateNotification object:self userInfo:@{kConnectionStateKey: kConnectionStateDisconnected}];
	});
}

@end

OLYCamera *AppDelegateCamera()
{
	AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
	if (!delegate) {
		return nil;
	}
	return delegate.camera;
}

void AppDelegateCameraDisconnectWithPowerOff(BOOL powerOff)
{
	dispatch_async(dispatch_get_main_queue(), ^{
		AppDelegate *delegate = (AppDelegate *)[[UIApplication sharedApplication] delegate];
		[delegate disconnectWithPowerOff:powerOff];
	});
}
