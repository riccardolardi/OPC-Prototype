//
//  CameraLiveImageView.m
//  ImageCaptureSample
//
//  Copyright (c) 2014 Olympus Imaging Corporation. All rights reserved.
//

#import "CameraLiveImageView.h"

@interface CameraLiveImageView()

@property (strong, nonatomic) NSTimer *focusFrameHideTimer;

@end

@implementation CameraLiveImageView

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (!self) {
		return nil;
    }
	[self initComponent];
    return self;
}

- (id)initWithCoder:(NSCoder *)decoder
{
    self = [super initWithCoder:decoder];
    if (!self) {
		return nil;
    }
	[self initComponent];
	return self;
}

- (void)initComponent
{
	CALayer *focusFrameLayer = [CALayer layer];
	focusFrameLayer.frame = self.bounds;
	[self.layer addSublayer:focusFrameLayer];
}

- (void)dealloc
{
	[self.focusFrameHideTimer invalidate];
	self.focusFrameHideTimer = nil;
}

/**
 * Converts a point on image area to a point on view area.
 *
 * @param point A point on image area. (e.g. a live preview image)
 * @return A point on view area. (e.g. a touch panel view)
 */
- (CGPoint)convertPointFromImageArea:(CGPoint)point
{
	if (!self.image) {
		return CGPointZero;
	}

	CGPoint viewPoint = point;
	CGSize imageSize = self.image.size;
	CGSize viewSize  = self.bounds.size;
	CGFloat ratioX = viewSize.width / imageSize.width;
	CGFloat ratioY = viewSize.height / imageSize.height;
	CGFloat scale = 0.0;

	switch (self.contentMode) {
		case UIViewContentModeScaleToFill:	// go to next label.
		case UIViewContentModeRedraw:
			viewPoint.x *= ratioX;
			viewPoint.y *= ratioY;
			break;
		case UIViewContentModeScaleAspectFit:
			scale = MIN(ratioX, ratioY);
			viewPoint.x *= scale;
			viewPoint.y *= scale;
			viewPoint.x += (viewSize.width  - imageSize.width  * scale) / 2.0f;
			viewPoint.y += (viewSize.height - imageSize.height * scale) / 2.0f;
			break;
		case UIViewContentModeScaleAspectFill:
			scale = MAX(ratioX, ratioY);
			viewPoint.x *= scale;
			viewPoint.y *= scale;
			viewPoint.x += (viewSize.width  - imageSize.width  * scale) / 2.0f;
			viewPoint.y += (viewSize.height - imageSize.height * scale) / 2.0f;
			break;
		case UIViewContentModeCenter:
			viewPoint.x += viewSize.width / 2.0  - imageSize.width  / 2.0f;
			viewPoint.y += viewSize.height / 2.0 - imageSize.height / 2.0f;
			break;
		case UIViewContentModeTop:
			viewPoint.x += viewSize.width / 2.0 - imageSize.width / 2.0f;
			break;
		case UIViewContentModeBottom:
			viewPoint.x += viewSize.width / 2.0 - imageSize.width / 2.0f;
			viewPoint.y += viewSize.height - imageSize.height;
			break;
		case UIViewContentModeLeft:
			viewPoint.y += viewSize.height / 2.0 - imageSize.height / 2.0f;
			break;
		case UIViewContentModeRight:
			viewPoint.x += viewSize.width - imageSize.width;
			viewPoint.y += viewSize.height / 2.0 - imageSize.height / 2.0f;
			break;
		case UIViewContentModeTopRight:
			viewPoint.x += viewSize.width - imageSize.width;
			break;
		case UIViewContentModeBottomLeft:
			viewPoint.y += viewSize.height - imageSize.height;
			break;
		case UIViewContentModeBottomRight:
			viewPoint.x += viewSize.width  - imageSize.width;
			viewPoint.y += viewSize.height - imageSize.height;
			break;
		case UIViewContentModeTopLeft:	// go to next label.
		default:
			break;
	}
	
    return viewPoint;
}

/**
 * Converts a point on view area to a point on image area.
 *
 * @param point A point on view area. (e.g. a touch panel view)
 * @return A point on image area. (e.g. a live preview image)
 */
- (CGPoint)convertPointFromViewArea:(CGPoint)point
{
	if (!self.image) {
		return CGPointZero;
	}
	
	CGPoint imagePoint = point;
	CGSize imageSize = self.image.size;
	CGSize viewSize  = self.bounds.size;
	CGFloat ratioX = viewSize.width / imageSize.width;
	CGFloat ratioY = viewSize.height / imageSize.height;
	CGFloat scale = 0.0;
    
    switch (self.contentMode) {
        case UIViewContentModeScaleToFill:	// go to next label.
        case UIViewContentModeRedraw:
            imagePoint.x /= ratioX;
            imagePoint.y /= ratioY;
            break;
        case UIViewContentModeScaleAspectFit:
			scale = MIN(ratioX, ratioY);
            imagePoint.x -= (viewSize.width  - imageSize.width  * scale) / 2.0f;
            imagePoint.y -= (viewSize.height - imageSize.height * scale) / 2.0f;
            imagePoint.x /= scale;
            imagePoint.y /= scale;
            break;
        case UIViewContentModeScaleAspectFill:
			scale = MAX(ratioX, ratioY);
            imagePoint.x -= (viewSize.width  - imageSize.width  * scale) / 2.0f;
            imagePoint.y -= (viewSize.height - imageSize.height * scale) / 2.0f;
            imagePoint.x /= scale;
            imagePoint.y /= scale;
            break;
        case UIViewContentModeCenter:
            imagePoint.x -= (viewSize.width - imageSize.width)  / 2.0f;
            imagePoint.y -= (viewSize.height - imageSize.height) / 2.0f;
            break;
        case UIViewContentModeTop:
            imagePoint.x -= (viewSize.width - imageSize.width)  / 2.0f;
            break;
        case UIViewContentModeBottom:
            imagePoint.x -= (viewSize.width - imageSize.width)  / 2.0f;
            imagePoint.y -= (viewSize.height - imageSize.height);
            break;
        case UIViewContentModeLeft:
            imagePoint.y -= (viewSize.height - imageSize.height) / 2.0f;
            break;
        case UIViewContentModeRight:
            imagePoint.x -= (viewSize.width - imageSize.width);
            imagePoint.y -= (viewSize.height - imageSize.height) / 2.0f;
            break;
        case UIViewContentModeTopRight:
            imagePoint.x -= (viewSize.width - imageSize.width);
            break;
        case UIViewContentModeBottomLeft:
            imagePoint.y -= (viewSize.height - imageSize.height);
            break;
        case UIViewContentModeBottomRight:
            imagePoint.x -= (viewSize.width - imageSize.width);
            imagePoint.y -= (viewSize.height - imageSize.height);
            break;
        case UIViewContentModeTopLeft:		// go to next label.
        default:
            break;
    }
    
    return imagePoint;
}

/**
 * Converts a rectangle on image area to a rectangle on view area.
 *
 * @param rect A rectangle on image area. (e.g. a live preview image)
 * @return A rectangle on view area. (e.g. a touch panel view)
 */
- (CGRect)convertRectFromImageArea:(CGRect)rect
{
	if (!self.image) {
		return CGRectZero;
	}
	
	CGPoint imageTopLeft = rect.origin;
	CGPoint imageBottomRight = CGPointMake(CGRectGetMaxX(rect), CGRectGetMaxY(rect));

	CGPoint viewTopLeft = [self convertPointFromImageArea:imageTopLeft];
	CGPoint viewBottomRight = [self convertPointFromImageArea:imageBottomRight];

	CGFloat viewWidth = ABS(viewBottomRight.x - viewTopLeft.x);
	CGFloat viewHeight = ABS(viewBottomRight.y - viewTopLeft.y);
	CGRect viewRect = CGRectMake(viewTopLeft.x, viewTopLeft.y, viewWidth, viewHeight);
    
	return viewRect;
}

/**
 * Converts a rectangle on view area to a rectangle on image area.
 *
 * @param rect A rectangle on view area. (e.g. a touch panel view)
 * @return A rectangle on image area. (e.g. a live preview image)
 */
- (CGRect)convertRectFromViewArea:(CGRect)rect
{
	if (!self.image) {
		return CGRectZero;
	}
	
	CGPoint viewTopLeft = rect.origin;
	CGPoint viewBottomRight = CGPointMake(CGRectGetMaxX(rect), CGRectGetMaxY(rect));

	CGPoint imageTopLeft = [self convertPointFromViewArea:viewTopLeft];
	CGPoint imageBottomRight = [self convertPointFromViewArea:viewBottomRight];

	CGFloat imageWidth = ABS(imageBottomRight.x - imageTopLeft.x);
	CGFloat imageHeight = ABS(imageBottomRight.y - imageTopLeft.y);
	CGRect imageRect = CGRectMake(imageTopLeft.x, imageTopLeft.y, imageWidth, imageHeight);
    
    return imageRect;
}

/**
 * Hides the forcus frame.
 */
- (void)hideFocusFrame
{
	[self.focusFrameHideTimer invalidate];
	self.focusFrameHideTimer = nil;
	
	// Prepare a canvas.
	CALayer *focusFrameLayer = [CALayer layer];
	focusFrameLayer.frame = self.bounds;
	
	// Clear the canvas.
	UIGraphicsBeginImageContextWithOptions(focusFrameLayer.frame.size, NO, 0);
	CGContextRef context = UIGraphicsGetCurrentContext();
	CGContextClearRect(context, focusFrameLayer.frame);
	focusFrameLayer.contents = (id)[UIGraphicsGetImageFromCurrentImageContext() CGImage];
	UIGraphicsEndImageContext();
	
	// Display the canvas.
	[self.layer replaceSublayer:(self.layer.sublayers)[0] with:focusFrameLayer];
}

/**
 * Shows the focus frame.
 *
 * @param rect A rectangle of the focus frame on view area.
 * @param status A status of the focus frame.
 * @param animated If YES, The focus frame is hidden later.
 */
- (void)showFocusFrame:(CGRect)rect status:(CameraFocusFrameStatus)status animated:(BOOL)animated
{
	[self.focusFrameHideTimer invalidate];
	self.focusFrameHideTimer = nil;

	// Prepare a canvas.
	CALayer *focusFrameLayer = [CALayer layer];
	focusFrameLayer.frame = self.bounds;
	
	// Draw a rectangle to the canvas.
	UIGraphicsBeginImageContextWithOptions(focusFrameLayer.frame.size, NO, 0);
	CGContextRef context = UIGraphicsGetCurrentContext();
	CGContextClearRect(context, focusFrameLayer.frame);
	CGColorRef focusFrameColorRef;
	switch (status) {
		case CameraFocusFrameStatusRunning:
			focusFrameColorRef = [UIColor whiteColor].CGColor;
			break;
		case CameraFocusFrameStatusFocused:
			focusFrameColorRef = [UIColor greenColor].CGColor;
			break;
		case CameraFocusFrameStatusFailed:
			focusFrameColorRef = [UIColor redColor].CGColor;
			break;
	}
	CGFloat focusFrameStrokeWidth = 2.0;
	CGContextSetStrokeColorWithColor(context, focusFrameColorRef);
	CGContextStrokeRectWithWidth(context, rect, focusFrameStrokeWidth);
	focusFrameLayer.contents = (id)[UIGraphicsGetImageFromCurrentImageContext() CGImage];
	UIGraphicsEndImageContext();

	// Display the canvas.
	[self.layer replaceSublayer:(self.layer.sublayers)[0] with:focusFrameLayer];
	
	if (animated) {
		self.focusFrameHideTimer = [NSTimer scheduledTimerWithTimeInterval:1.0 target:self selector:@selector(focusFrameHideTimerDidFire:) userInfo:nil repeats:NO];
	}
}

- (void)focusFrameHideTimerDidFire:(NSTimer *)timer
{
	[self hideFocusFrame];
}

@end
