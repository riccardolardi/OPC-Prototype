/**
 * 
 * @file	OLYCamera+RecordingSupports.h
 * @brief	OLYCamera(RecordingSupports) class interface file.
 *
 * 
 */

/**
 * 
 * @defgroup types Types
 *
 * Type definition and enumerated types that are to be used by Olympus camera class
 *
 * 
 * @{
 */
/**
 * 
 * @name Olympus camera class: A recording auxiliary category
 *
 * 
 * @{
 */

/**
 * 
 * Driving direction of optical zoom.
 *
 * 
 */
enum OLYCameraDrivingZoomLensDirection {	
    /**
     * Towards the wide end to.
     * 
     */
    OLYCameraDrivingZoomLensWide,	
	
    /**
     * Towards the telephoto end to.
     * 
     */
    OLYCameraDrivingZoomLensTele,	
};
typedef enum OLYCameraDrivingZoomLensDirection OLYCameraDrivingZoomLensDirection;

/**
 * Driving speed of optical zoom.
 * 
 */
enum OLYCameraDrivingZoomLensSpeed {	
    /**
     * At low speed.
     * 
     */
    OLYCameraDrivingZoomLensSpeedSlow,	
	
    /**
     * At high speed.
     * 
     */
    OLYCameraDrivingZoomLensSpeedFast,	
	
    /**
     * At medium speed.
     * 
     */
    OLYCameraDrivingZoomLensSpeedNormal,	
	
    /**
     * At once.
     * 
     */
    OLYCameraDrivingZoomLensSpeedBurst,	
};
typedef enum OLYCameraDrivingZoomLensSpeed OLYCameraDrivingZoomLensSpeed;

// This is reserved for vendors. Please do not use.
enum OLYCameraMagnifyingLiveViewScale {	
    // This is reserved for vendors. Please do not use.
    OLYCameraMagnifyingLiveViewScaleX5,	
	
    // This is reserved for vendors. Please do not use.
    OLYCameraMagnifyingLiveViewScaleX7,	
	
    // This is reserved for vendors. Please do not use.
    OLYCameraMagnifyingLiveViewScaleX10,	
	
    // This is reserved for vendors. Please do not use.
    OLYCameraMagnifyingLiveViewScaleX14,	
};
typedef enum OLYCameraMagnifyingLiveViewScale OLYCameraMagnifyingLiveViewScale;

// This is reserved for vendors. Please do not use.
enum OLYCameraMagnifyingLiveViewScrollDirection {	
    // This is reserved for vendors. Please do not use.
    OLYCameraMagnifyingLiveViewScrollDirectionUp,	
	
    // This is reserved for vendors. Please do not use.
    OLYCameraMagnifyingLiveViewScrollDirectionLeft,	
	
    // This is reserved for vendors. Please do not use.
    OLYCameraMagnifyingLiveViewScrollDirectionRight,	
	
    // This is reserved for vendors. Please do not use.
    OLYCameraMagnifyingLiveViewScrollDirectionDown,	
};
typedef enum OLYCameraMagnifyingLiveViewScrollDirection OLYCameraMagnifyingLiveViewScrollDirection;

/** @} */
/** @} */

/**
 * 
 * @defgroup constants Constants
 *
 * Constants referenced by Olympus camera class
 *
 * 
 * @{
 */
/**
 * 
 * @name Olympus camera class: A recording auxiliary category
 *
 * 
 * @{
 */

/**
 * Dictionary key for accessing 'Orientation' elements of the level gauge information.
 */
extern NSString *const OLYCameraLevelGaugeOrientationKey;	

/**
 * Dictionary key for accessing 'Roll' elements of the level gauge information.
 */
extern NSString *const OLYCameraLevelGaugeRollingKey;	

/**
 * Dictionary key for accessing 'Pitch' elements of the level gauge information.
 */
extern NSString *const OLYCameraLevelGaugePitchingKey;	

/**
 * Dictionary key for accessing 'Minimum zoom scale' elements of the level gauge information.
 */
extern NSString *const OLYCameraDigitalZoomScaleRangeMinimumKey;	

/**
 * Dictionary keys to access 'Maximum zoom scale' elements of the digital zoom information.
 */
extern NSString *const OLYCameraDigitalZoomScaleRangeMaximumKey;	

// ;-)

// ;-)

/** @} */
/** @} */

@protocol OLYCameraRecordingSupportsDelegate;

#pragma mark -

/**
 * 
 * It is a recording auxiliary category of Olympus camera class.
 *
 * This category provides zoom control, and live view image display.
 *
 * 
 * @category OLYCamera(RecordingSupports)
 */
@interface OLYCamera(RecordingSupports)

/**
 * 
 * The object that acts as the delegate of receiving that the state about recording operations is changed.
 *
 * There are properties that were also similar to the recording-related category,
 * but this will support those that do not directly relate to the photographing operation mainly.
 *
 * 
 */
@property (weak, nonatomic) id<OLYCameraRecordingSupportsDelegate> recordingSupportsDelegate;	

/**
 * 
 * Indicates the optical zoom is driving in the camera.
 *
 * @see OLYCamera::startDrivingZoomLensForDirection:speed:error:
 * @see OLYCamera::startDrivingZoomLensToFocalLength:error:
 * @see OLYCamera::stopDrivingZoomLens:
 * @see OLYCameraRecordingSupportsDelegate::cameraDidStopDrivingZoomLens:
 *
 * 
 */
@property (assign, nonatomic, readonly) BOOL drivingZoomLens;	

// This is reserved for vendors. Please do not use.
@property (assign, nonatomic, readonly) BOOL magnifyingLiveView;	

/**
 * 
 * Information of the level gauge.
 *
 * The following information is included.
 *   - #OLYCameraLevelGaugeOrientationKey ... Inclination and orientation on the camera body.
 *     - "landscape" ... The lens mount tilt is 0 degrees.
 *       The camera body is positioned in a horizontal direction.
 *       This is the normal state.
 *     - "portrait_left" ... The lens mount tilt is 90 degrees with clockwise.
 *       The camera body is positioned in a horizontal direction.
 *     - "landscape_upside_down" ... The lens mount tilt is 180 degrees.
 *       The camera body is positioned in a horizontal direction.
 *       This is upside down state.
 *     - "portrait_right" ... The lens mount tilt is 270 degrees with clockwise.
 *       The camera body is positioned in a horizontal direction.
 *     - "faceup" ...  The face of camera body is upward. Horizontal orientation is undefined.
 *     - "facedown" ... The face of camera body is down. Horizontal orientation is undefined.
 *   - #OLYCameraLevelGaugeRollingKey ... Rolling amounts of the camera body relative to the horizontal.
 *     Unit is in degrees. If the angle cannot be determined is NaN.
 *   - #OLYCameraLevelGaugePitchingKey ... Pitching amounts of the camera body relative to the horizontal.
 *     Unit is in degrees. If the angle cannot be determined is NaN.
 *
 * This property does not set the values ​is valid If you do not align to the following conditions.
 *   - Run mode is set to recording mode.
 *   - The library has started receiving live view information. (It does not have to be using a delegate)
 *
 * 
 */
@property (strong, nonatomic, readonly) NSDictionary *levelGauge;	

/**
 * 
 * Face recognition results.
 *
 * Coordinate information of the face detected by the camera is stored in a dictionary format.
 * The dictionary key is a number string that represents the identification number.
 * To track the coordinates of once recognized face using the specific identification number is not possible.
 *
 * This property does not set the values ​is valid If you do not align to the following conditions.
 *   - Run mode is set to recording mode.
 *   - The library has started receiving live view information. (It does not have to be using a delegate)
 *
 * 
 */
@property (strong, nonatomic, readonly) NSDictionary *detectedHumanFaces;	

/**
 * 
 * Starts driving the optical zoom by using the rate and the direction.
 *
 * Lens that is attached to the camera must support electric zoom.
 * If the optical zoom is driving already, the application will get an error.
 *
 * @param direction The driving direction.
 * @param speed The speed of driving.
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, The operation was successful. If false, The operation was abnormal termination.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::lensMountStatus
 * @see OLYCamera::drivingZoomLens
 * @see OLYCameraRecordingSupportsDelegate::cameraDidStopDrivingZoomLens:
 *
 * 
 */
- (BOOL)startDrivingZoomLensForDirection:(OLYCameraDrivingZoomLensDirection)direction speed:(OLYCameraDrivingZoomLensSpeed)speed error:(NSError **)error;	

/**
 * 
 * Starts driving the optical zoom to the specified focal length.
 *
 * Lens that is attached to the camera must support electric zoom.
 * If the optical zoom is driving already, the application will get an error.
 *
 * @param focalLength The focal length.
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, The operation was successful. If false, The operation was abnormal termination.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::lensMountStatus
 * @see OLYCamera::drivingZoomLens
 * @see OLYCameraRecordingSupportsDelegate::cameraDidStopDrivingZoomLens:
 *
 * 
 */
- (BOOL)startDrivingZoomLensToFocalLength:(float)focalLength error:(NSError **)error;	

/**
 * 
 * Stops driving the optical zoom.
 *
 * Lens that is attached to the camera must support electric zoom.
 * If the optical zoom is driving already, the application will get an error.
 *
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, The operation was successful. If false, The operation was abnormal termination.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::lensMountStatus
 * @see OLYCamera::drivingZoomLens
 *
 * 
 */
- (BOOL)stopDrivingZoomLens:(NSError **)error;	

/**
 * 
 * Gets a configurable range to the magnification of the digital zoom.
 *
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return The configurable range. The acquired information is a dictionary format.
 *
 * The following information is included.
 *  - #OLYCameraDigitalZoomScaleRangeMinimumKey ... Magnification of the minimum.
 *  - #OLYCameraDigitalZoomScaleRangeMaximumKey ... Magnification of the maximum.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::changeDigitalZoomScale:error:
 *
 * 
 */
- (NSDictionary *)digitalZoomScaleRange:(NSError **)error;	

/**
 * 
 * Changes the magnification of digital zoom.
 *
 * If the application specified a magnification that are not included in the configurable range,
 * the application will get an error.
 * When changing run-mode to other than recording mode, the magnification is changed back to x1 automatically.
 *
 * @param scale Magnification of digital zoom.
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, The operation was successful. If false, The operation was abnormal termination.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::digitalZoomScaleRange:
 *
 * 
 */
- (BOOL)changeDigitalZoomScale:(float)scale error:(NSError **)error;	

// ;-)

// ;-)

// ;-)

// ;-)

// ;-)

// ;-)

// ;-)

@end

#pragma mark -
#pragma mark Related Delegates

/**
 * 
 * The delegate for receiving the state relating to the recording operation is changed.
 *
 * There are delegate that were also similar to the photographing operation related category,
 * but this will support those that do not directly relate to the photographing operation mainly.
 *
 * 
 */
@protocol OLYCameraRecordingSupportsDelegate <NSObject>	
@optional

/**
 * 
 * Tells the delegate that the library receives the preview image.
 *
 * The application will be notified when the generation of preview image after taking picture of camera property is enabled.
 * Please refer to the documentation of the camera properties list for more information about the camera properties.
 *
 * The application will be notified even without shooting start and end of shooting by the application,
 * and to shoot the user presses the release button of the camera body.
 *
 * @param camera Instance that receives the image data.
 * @param data Binary data of the captured image for preview.
 * @param metadata Meta data of the captured image for preview.
 *
 * Argument
 *   - metadata ... Meta data of the image will be set.
 *     There are cases where the following information is included in addition to the EXIF information.
 *     - "detectversion" ... Reserved for vendor.
 *     - "detectid" ... Reserved for vendor.
 *
 * 
 */
- (void)camera:(OLYCamera *)camera didReceiveCapturedImagePreview:(NSData *)data metadata:(NSDictionary *)metadata;	

/**
 * 
 * Tells the delegate that the library receives the original size image after shooting.
 *
 * This is sent at the end of the shot if captured image storage location of the camera properties is set to smartphone.
 * Please refer to the documentation of the camera properties list for more information about the camera properties.
 *
 * @param camera Instance that receives the image data.
 * @param data Binary data of the captured images for storage.
 *
 * 
 */
- (void)camera:(OLYCamera *)camera didReceiveCapturedImage:(NSData *)data;	

/**
 * 
 * Tells the delegate that the driving of the optical zoom is stopped due to reasons on the camera side.
 *
 * Some of the following as the cause to be notified.
 *   - It reaches the telephoto end or the wide end before calling the stop of the optical zoom.
 *
 * @param camera Instances it is detected that the camera has stopped recording.
 *
 * 
 */
- (void)cameraDidStopDrivingZoomLens:(OLYCamera *)camera;	

@end

// EOF
