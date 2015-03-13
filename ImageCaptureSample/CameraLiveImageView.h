//
//  CameraLiveImageView.h
//  ImageCaptureSample
//
//  Copyright (c) 2014 Olympus Imaging Corporation. All rights reserved.
//

#import <UIKit/UIKit.h>

enum CameraFocusFrameStatus
{
	CameraFocusFrameStatusRunning,
	CameraFocusFrameStatusFocused,
	CameraFocusFrameStatusFailed,
};

typedef enum CameraFocusFrameStatus CameraFocusFrameStatus;

@interface CameraLiveImageView : UIImageView

- (CGPoint)convertPointFromImageArea:(CGPoint)point;
- (CGPoint)convertPointFromViewArea:(CGPoint)point;
- (CGRect)convertRectFromImageArea:(CGRect)rect;
- (CGRect)convertRectFromViewArea:(CGRect)rect;
- (void)hideFocusFrame;
- (void)showFocusFrame:(CGRect)rect status:(CameraFocusFrameStatus)status animated:(BOOL)animated;

@end
