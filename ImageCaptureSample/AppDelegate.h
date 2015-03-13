//
//  AppDelegate.h
//  ImageCaptureSample
//
//  Copyright (c) 2014 Olympus Imaging Corporation. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OLYCameraKit/OLYCamera.h>
#import <OLYCameraKit/OLYCameraError.h>

extern NSString *const kAppDelegateCameraDidChangeConnectionStateNotification;
extern NSString *const kConnectionStateKey;
extern NSString *const kConnectionStateConnected;
extern NSString *const kConnectionStateDisconnected;

extern NSString *ICSCameraPropertyTakemode;
extern NSString *ICSCameraPropertyDrivemode;
extern NSString *ICSCameraPropertyApertureValue;
extern NSString *ICSCameraPropertyShutterSpeed;
extern NSString *ICSCameraPropertyExposureCompensation;
extern NSString *ICSCameraPropertyWhiteBalance;
extern NSString *ICSCameraPropertyIsoSensitivity;
extern NSString *ICSCameraPropertyBatteryLevel;
extern NSString *ICSCameraPropertyRecview;

@interface AppDelegate : UIResponder <UIApplicationDelegate>

@property (strong, nonatomic) UIWindow *window;

@end

extern OLYCamera *AppDelegateCamera();
extern void AppDelegateCameraDisconnectWithPowerOff(BOOL powerOff);