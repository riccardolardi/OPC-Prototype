/**
 * 
 * @file	OLYCamera+Recording.h
 * @brief	OLYCamera(Recording) class interface file.
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
 * @name Olympus camera class: A recording-related category
 *
 * 
 * @{
 */

/**
 * 
 * Type of shooting mode and drive mode.
 *
 * 
 */
enum OLYCameraActionType {	
	
	/**
     * 
	 * Mode is unknown.
	 *
     * 
     */
	OLYCameraActionTypeUnknown,	
	
	/**
     * 
	 * Still image single shooting mode.
	 *
	 * It is a pattern that runs the shooting by a single tap.
	 *
     * 
     */
	OLYCameraActionTypeSingle,	
	
	/**
     * 
	 * Still image continuous shooting mode.
	 *
	 * It is a pattern that user starts shooting at the beginning of the long tap and
	 * to run the end of shooting in the tap end.
	 *
     * 
     */
	OLYCameraActionTypeSequential,	
	
	/**
     * 
	 * Movie recording mode.
	 *
	 * It is a pattern that is recorded at the start of a single tap of the first and
	 * to run the recording end with a single tap of the next.
	 *
     * 
     */
	OLYCameraActionTypeMovie,	
	
};
typedef enum OLYCameraActionType OLYCameraActionType;

/**
 * 
 * Progress of the capturing operation.
 *
 * 
 */
enum OLYCameraTakingProgress {	
	/**
	 * 
	 * Started the auto-focus.
	 *
	 * This notification will be called even during focus lock.
	 *
     * 
     */
	OLYCameraTakingProgressBeginFocusing,	
	
	/**
	 * 
	 * Ended the auto focus.
	 *
	 * This timing is appropriate if the application plays sound effects or
	 * displays on the screen the focus results.
	 *
     * 
     */
	OLYCameraTakingProgressEndFocusing,	
	
	/**
	 * 
	 * Preparation of the exposure has been completed.
	 *
     * 
     */
	OLYCameraTakingProgressReadyCapturing,	
	
	/**
	 * 
	 * Started the exposure.
	 *
	 * This timing is appropriate if the application plays sound effects or
	 * displays on the screen the shutter curtain open.
	 *
     * 
     */
	OLYCameraTakingProgressBeginCapturing,	
	
	/**
	 * 
	 * Started the noise reduction processing.
	 *
	 * The application may not be notified by the value of the shutter speed.
	 *
     * 
     */
	OLYCameraTakingProgressBeginNoiseReduction,	
	
	/**
	 * 
	 * Ended the noise reduction processing.
	 *
	 * The application may not be notified by the value of the shutter speed.
	 *
     * 
     */
	OLYCameraTakingProgressEndNoiseReduction,	
	
	/**
	 * 
	 * Exposure has been completed.
	 *
	 * This timing is appropriate if the application plays sound effects or displays on the screen the shutter curtain close.
	 *
     * 
     */
	OLYCameraTakingProgressEndCapturing,	
	
	/**
	 * 
	 * Shooting action has been completed.
	 *
     * 
     */
	OLYCameraTakingProgressFinished,	
};
typedef enum OLYCameraTakingProgress OLYCameraTakingProgress;

/**
 * 
 * Size parameter of the live view the camera supports.
 *
 * 
 */
typedef CGSize OLYCameraLiveViewSize;	

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
 * @name Olympus camera class: A recording-related category
 *
 * 
 * @{
 */

/**
 * Displaying to fit in QVGA(320x240) size live view.
 * 
 */
extern const OLYCameraLiveViewSize OLYCameraLiveViewSizeQVGA;	

/**
 * Displaying to fit in VGA(640x480) size live view.
 * 
 */
extern const OLYCameraLiveViewSize OLYCameraLiveViewSizeVGA;	

/**
 * Displaying to fit in SVGA(800x600) size live view.
 * 
 */
extern const OLYCameraLiveViewSize OLYCameraLiveViewSizeSVGA;	

/**
 * Displaying to fit in XGA(1024x768) size live view.
 * 
 */
extern const OLYCameraLiveViewSize OLYCameraLiveViewSizeXGA;	

/**
 * Displaying to fit in Quad-VGA(1280x960) size live view.
 * 
 */
extern const OLYCameraLiveViewSize OLYCameraLiveViewSizeQuadVGA;	

/**
 * 
 * Dictionary keys to access elements 'Limits the number of shots of continuous shooting' option parameter
 * that specifies the shooting at the start.
 * 
 */
extern NSString *const OLYCameraStartTakingPictureOptionLimitShootingsKey;	

/**
 * 
 * Dictionary key to access the results focusing elements of the additional information is passed
 * to the progress callback of starting to take picture.
 * 
 */
extern NSString *const OLYCameraTakingPictureProgressInfoFocusResultKey;	

/**
 * 
 * Dictionary key to access the coordinate focused elements of the additional information is passed
 * to the progress callback of starting to take picture.
 * 
 */
extern NSString *const OLYCameraTakingPictureProgressInfoFocusRectKey;	

/** @} */
/** @} */

@protocol OLYCameraLiveViewDelegate;
@protocol OLYCameraRecordingDelegate;

#pragma mark -

/**
 * 
 * It is a recording-related category of Olympus camera class.
 *
 * This category provides taking still pictures and recording video, exposure control, and focus control.
 *
 * The application can configure using the camera properties manipulation methods of
 * @ref OLYCamera(CameraSystem) categories such as 
 * settings for the development and exposure, settings for shooting action,
 * setting related to the shooting of the other.
 * Please refer to the camera list of properties for more information.
 *
 * 
 * @category OLYCamera(Recording)
 */
@interface OLYCamera(Recording)

/**
 * 
 * Pixel size of the live view.
 *
 * @see OLYCamera::changeLiveViewSize:error:
 *
 * 
 */
@property (assign, nonatomic, readonly) OLYCameraLiveViewSize liveViewSize;	

/**
 * 
 * The object that acts as the delegate of receiving that the information of live view is changed.
 *
 * 
 */
@property (weak, nonatomic) id<OLYCameraLiveViewDelegate> liveViewDelegate;	

/**
 * 
 * The object that acts as the delegate of receiving that the state about recording operations is changed.
 *
 * 
 */
@property (weak, nonatomic) id<OLYCameraRecordingDelegate> recordingDelegate;	

/**
 * 
 * Indicates that photo shooting is in progress at the camera.
 *
 * When shooting is in progress, the application cannot change the value of the camera properties.
 *
 * @see OLYCamera::startTakingPicture:progressHandler:completionHandler:errorHandler:
 * @see OLYCamera::stopTakingPicture:completionHandler:errorHandler:
 *
 * 
 */
@property (assign, nonatomic, readonly) BOOL takingPicture;	

/**
 * 
 * Indicates that video recording is in progress at the camera.
 *
 * When recording is in progress, the application cannot change the value of the camera properties.
 *
 * @see OLYCamera::startRecordingVideo:completionHandler:errorHandler:
 * @see OLYCamera::stopRecordingVideo:errorHandler:
 * @see OLYCameraRecordingDelegate::cameraDidStopRecordingVideo:
 *
 * 
 */
@property (assign, nonatomic, readonly) BOOL recordingVideo;	

/**
 * 
 * The current focal length of the lens attached to the camera.
 *
 * @see OLYCamera::startDrivingZoomLensForDirection:speed:error:
 * @see OLYCamera::startDrivingZoomLensToFocalLength:error:
 * @see OLYCamera::stopDrivingZoomLens:
 *
 * 
 */
@property (assign, nonatomic, readonly) float actualFocalLength;	

/**
 * 
 * The focal length at the wide end of the zoom lens mounted on the camera.
 * This is the shortest focal length of the zoom lens.
 *
 * @see OLYCamera::startDrivingZoomLensForDirection:speed:error:
 * @see OLYCamera::startDrivingZoomLensToFocalLength:error:
 *
 * 
 */
@property (assign, nonatomic, readonly) float minimumFocalLength;	

/**
 * 
 * The focal length at the telephoto end of the zoom lens mounted on the camera.
 * This is the longest focal length of the zoom lens.
 *
 * @see OLYCamera::startDrivingZoomLensForDirection:speed:error:
 * @see OLYCamera::startDrivingZoomLensToFocalLength:error:
 *
 * 
 */
@property (assign, nonatomic, readonly) float maximumFocalLength;	

/**
 * 
 * Coordinates focused with autofocus.
 *
 * Viewfinder coordinate system will be used in this coordinate value.
 * The application can convert the coordinates in the live view image using
 * the coordinate conversion utility #OLYCameraConvertPointOnViewfinderIntoLiveImage.
 *
 * @see OLYCamera::setAutoFocusPoint:error:
 * @see OLYCamera::clearAutoFocusPoint:
 *
 * 
 */
@property (assign, nonatomic, readonly) CGPoint actualAutoFocusPoint;	

/**
 * 
 * F values that are used in lens and camera.
 *
 * There are cases where this value can change depending on the state of the object by
 * the value of the shooting mode of the camera properties.
 * This value can be changed in case of changing the focal length in the state set to the minimum aperture.
 * This value may be different from the value set in the aperture value of the camera.
 * Minimum aperture value is set to this value if the value is set to the aperture value of
 * the camera properties minimum aperture is also more small.
 * Please refer to the documentation of the camera list of properties for more information.
 *
 * This property does not set the values is valid If you do not align to the following conditions.
 *   - A lens is mounted.
 *   - Run mode is set to recording mode.
 *   - The library has started receiving live view information. (It does not have to be using a delegate)
 *
 * 
 */
@property (strong, nonatomic, readonly) NSString *actualApertureValue;	


/**
 * 
 * Shutter speed that is used in camera.
 *
 * There are cases where this value can change depending on the state of the object by
 * the value of the shooting mode of the camera properties.
 * Please refer to the documentation of the camera list of properties for more information.
 *
 * This property does not set the values is valid If you do not align to the following conditions.
 *   - A lens is mounted.
 *   - Run mode is set to recording mode.
 *   - The library has started receiving live view information. (It does not have to be using a delegate)
 *
 * 
 */
@property (strong, nonatomic, readonly) NSString *actualShutterSpeed;	

/**
 * 
 * Exposure compensation value that is used in camera.
 *
 * There are cases where this value can change depending on the state of the object by
 * the value of the shooting mode of the camera properties.
 * Please refer to the documentation of the camera list of properties for more information.
 *
 * This property does not set the values is valid If you do not align to the following conditions.
 *   - A lens is mounted.
 *   - Run mode is set to recording mode.
 *   - The library has started receiving live view information. (It does not have to be using a delegate)
 *
 * 
 */
@property (strong, nonatomic, readonly) NSString *actualExposureCompensation;	

/**
 * 
 * ISO sensitivity that is used in camera.
 *
 * When ISO sensitivity of the camera property is set the automatic,
 * the value that the camera has determined will be set.
 * There are cases where this value can change depending on the state of the object by
 * the value of the shooting mode of the camera properties.
 * Please refer to the documentation of the camera list of properties for more information.
 *
 * This property does not set the values is valid If you do not align to the following conditions.
 *   - A lens is mounted.
 *   - Run mode is set to recording mode.
 *   - The library has started receiving live view information. (It does not have to be using a delegate)
 *
 * 
 */
@property (strong, nonatomic, readonly) NSString *actualIsoSensitivity;	

/**
 * 
 * Indicates that out of range warning of the ISO sensitivity is occurring on the camera.
 *
 * When the shooting during the warning, there is a case of obtaining a result
 * that is not the correct exposure such as underexposed or overexposed.
 *
 * 
 */
@property (assign, nonatomic, readonly) BOOL actualIsoSensitivityWarning;	

/**
 * 
 * Indicates that out of range warning of the exposure is occurring on the camera.
 *
 * It is a state that can not be determined ISO sensitivity or shutter speed or aperture value corresponding
 * to the current value of EV.
 * When the shooting during the warning, there is a case of obtaining a result
 * that is not the correct exposure such as underexposed or overexposed.
 *
 * 
 */
@property (assign, nonatomic, readonly) BOOL exposureWarning;	

/**
 * 
 * Indicates that warning of the exposure metering is occurring on the camera.
 *
 * It is a state subject too dark or too bright enough can not be measured in the camera's exposure meter.
 * When the shooting during the warning, there is a case of obtaining a result
 * that is not the correct exposure such as underexposed or overexposed.
 *
 * 
 */
@property (assign, nonatomic, readonly) BOOL exposureMeteringWarning;	

/**
 * 
 * Changes the size of the live view.
 *
 * @param size The size of the live view.
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, The operation was successful. If false, The operation was abnormal termination.
 *
 * @see OLYCamera::liveViewSize
 *
 */
- (BOOL)changeLiveViewSize:(OLYCameraLiveViewSize)size error:(NSError **)error;	

/**
 * 
 * Gets the type of shooting mode and drive mode.
 *
 * The application can determine whether to perform in any shooting processing
 * with response to a user tap by referring this value.
 * Please refer to the description of #OLYCameraActionType.
 *
 * 
 */
- (OLYCameraActionType)actionType;	

/**
 * 
 * Starts shooting the photo.
 *
 * Cannot be called when a video recording mode and shooting process is progress.
 * To stop the shooting operation that has started, the application must call the end of shooting.
 *
 * @param options Not used on current version.
 * @param progressHandler Callback that will be called every time the progress of the shooting operation changes.
 * @param completionHandler Callback that is called when the shooting start has been completed.
 * @param errorHandler Callback that is called when the shooting start was aborted.
 *
 * Argument of progress callback
 *   - progress ... Progress of the photographing operation.
 *   - info ... Focus information is set in the dictionary format at the time of the auto-focus end.
 *     - #OLYCameraTakingPictureProgressInfoFocusResultKey ... Focusing result.
 *       - "ok" ... In focus.
 *       - "ng" ... Did not focus.
 *       - "none" ... AF did not work. Lens is set to MF mode or is not supported AF.
 *     - #OLYCameraTakingPictureProgressInfoFocusRectKey ... Rectangular coordinates focused.
 *       Viewfinder coordinate system will be used in this coordinate value.
 *
 * Argument of abnormal termination callback
 *   - error ... Error details will be set when the operation is abnormally terminated.
 *
 * The application can convert the rectangular coordinates in the live view image using
 * the coordinate conversion utility #OLYCameraConvertRectOnViewfinderIntoLiveImage.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::stopTakingPicture:completionHandler:errorHandler:
 * @see OLYCamera::takePicture:progressHandler:completionHandler:errorHandler:
 *
 * 
 */
- (void)startTakingPicture:(NSDictionary *)options progressHandler:(void (^)(OLYCameraTakingProgress progress, NSDictionary *info))progressHandler completionHandler:(void (^)())completionHandler errorHandler:(void (^)(NSError *error))errorHandler;	

/**
 * 
 * Finishes shooting the photo.
 *
 * Cannot be called when a video recording mode and shooting process is not progress.
 *
 * @param progressHandler Callback that will be called every time the progress of the shooting operation changes.
 * @param completionHandler Callback that is called when the end of shooting has been completed.
 * @param errorHandler Callback that is called when the end of shooting was aborted.
 *
 * Argument of progress callback
 *   - progress ... Progress of the photographing operation.
 *   - info ... Not used on current version.
 *
 * Argument of the shooting end completion callback
 *   - info ... Not used on current version.
 *
 * Argument of abnormal termination callback
 *   - error ... Error details will be set when the operation is abnormally terminated.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::startTakingPicture:progressHandler:completionHandler:errorHandler:
 * @see OLYCamera::takePicture:progressHandler:completionHandler:errorHandler:
 *
 * 
 */
- (void)stopTakingPicture:(void (^)(OLYCameraTakingProgress progress, NSDictionary *info))progressHandler completionHandler:(void (^)(NSDictionary *info))completionHandler errorHandler:(void (^)(NSError *error))errorHandler;	

/**
 * 
 * Collectively runs up to end of shooting from the start of shooting photos.
 *
 * Cannot be called when a video recording mode and shooting process is progress.
 *
 * @param options Not used on current version.
 * @param progressHandler Callback that will be called every time the progress of the shooting operation changes.
 * @param completionHandler Callback that is called when the shooting has been completed.
 * @param errorHandler Callback that is called when the shooting was aborted.
 *
 * Argument of progress callback
 *   - progress ... Progress of the photographing operation.
 *   - info ... Focus information is set in the dictionary format at the time of the auto-focus end.
 *     - #OLYCameraTakingPictureProgressInfoFocusResultKey ... Focusing result.
 *       - "ok" ... In focus.
 *       - "ng" ... Did not focus.
 *       - "none" ... AF did not work. Lens is set to MF mode or is not supported AF.
 *     - #OLYCameraTakingPictureProgressInfoFocusRectKey ... Rectangular coordinates focused.
 *       Viewfinder coordinate system will be used in this coordinate value.
 *
 * Argument of shooting completion callback
 *   - info ... Not used on current version.
 *
 * Argument of abnormal termination callback
 *   - error ... Error details will be set when the operation is abnormally terminated.
 *
 * The application can convert the rectangular coordinates in the live view image using
 * the coordinate conversion utility #OLYCameraConvertRectOnViewfinderIntoLiveImage.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::startTakingPicture:progressHandler:completionHandler:errorHandler:
 * @see OLYCamera::stopTakingPicture:completionHandler:errorHandler:
 *
 * 
 */
- (void)takePicture:(NSDictionary *)options progressHandler:(void (^)(OLYCameraTakingProgress progress, NSDictionary *info))progressHandler completionHandler:(void (^)(NSDictionary *info))completionHandler errorHandler:(void (^)(NSError *error))errorHandler;	

/**
 * 
 * Starts recording the movie.
 *
 * Cannot be called when a still image shooting mode and recording process is progress.
 * To stop the recording operation that has started, the application must call the end of recording.
 *
 * @param options Not used on current version.
 * @param completionHandler Callback that is called when the recording start has been completed.
 * @param errorHandler Callback that is called when the recording start was aborted.
 *
 * Argument of abnormal termination callback
 *   - error ... Error details will be set when the operation is abnormally terminated.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::stopRecordingVideo:errorHandler:
 * @see OLYCameraRecordingDelegate::cameraDidStopRecordingVideo:
 *
 * 
 */
- (void)startRecordingVideo:(NSDictionary *)options completionHandler:(void (^)())completionHandler errorHandler:(void (^)(NSError *error))errorHandler;	

/**
 * 
 * Finishes recording the movie.
 *
 * Cannot be called when a still image shooting mode and recording process is not progress.
 *
 * @param completionHandler Callback that is called when the end of recording has been completed.
 * @param errorHandler Callback that is called when the recording end is abnormally terminated.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::startRecordingVideo:completionHandler:errorHandler:
 * @see OLYCameraRecordingDelegate::cameraDidStopRecordingVideo:
 *
 * 
 */
- (void)stopRecordingVideo:(void (^)(NSDictionary *info))completionHandler errorHandler:(void (^)(NSError *error))errorHandler;	

/**
 * 
 * Locks the autofocus operation.
 *
 * Focus the camera to the specified coordinates. And then lock so that the auto focus does not work later.
 * The application must have set the coordinates focusing autofocus in advance.
 * The application must have call the unlock to resume operation of the auto focus.
 *
 * @param completionHandler Callback that is called when the lock has been completed.
 * @param errorHandler Callback that is called when the lock was aborted.
 *
 * Argument of lock completion callback
 *   - info ... Focus information is set in the dictionary format at the time of the S-AF modes of auto focus.
 *     - #OLYCameraTakingPictureProgressInfoFocusResultKey ... Focusing result.
 *       - "ok" ... In focus.
 *       - "ng" ... Did not focus.
 *       - "none" ... AF did not work. Lens is set to MF mode or is not supported AF.
 *     - #OLYCameraTakingPictureProgressInfoFocusRectKey ... Rectangular coordinates focused.
 *       Viewfinder coordinate system will be used in this coordinate value.
 *
 * Argument of abnormal termination callback
 *   - error ... Error details will be set when the operation is abnormally terminated.
 *
 * The application can convert the rectangular coordinates in the live view image using
 * the coordinate conversion utility #OLYCameraConvertRectOnViewfinderIntoLiveImage.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::setAutoFocusPoint:error:
 * @see OLYCamera::unlockAutoFocus:
 * @see OLYCameraRecordingDelegate::camera:didChangeAutoFocusResult:
 *
 * 
 */
- (void)lockAutoFocus:(void (^)(NSDictionary *info))completionHandler errorHandler:(void (^)(NSError *error))errorHandler;	

/**
 * 
 * Unlocks the autofocus operation.
 *
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, The operation was successful. If false, The operation was abnormal termination.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::lockAutoFocus:errorHandler:
 *
 * 
 */
- (BOOL)unlockAutoFocus:(NSError **)error;	

/**
 * 
 * Sets the coordinates that focus it using the auto focus.
 *
 * The application must prior to locking the focus operation,
 * the application set the coordinates to focus it in this method.
 * The application will get an error when try to set a value that exceeds the valid range of-focus coordinate.
 *
 * @param point Coordinates the application want to focus.
 * Viewfinder coordinate system will be used to coordinate values.
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, The operation was successful. If false, The operation was abnormal termination.
 *
 * The application can convert the focusing coordinates from the coordinates in the live view image
 * touched using the coordinate conversion utility #OLYCameraConvertPointOnLiveImageIntoViewfinder.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::lockAutoFocus:errorHandler:
 * @see OLYCamera::autoFocusEffectiveArea:
 * @see OLYCameraRecordingDelegate::camera:didChangeAutoFocusResult:
 *
 * 
 */
- (BOOL)setAutoFocusPoint:(CGPoint)point error:(NSError **)error;	

/**
 * 
 * Clears the coordinates that focus it using the auto focus.
 *
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, The operation was successful. If false, The operation was abnormal termination.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::setAutoFocusPoint:error:
 *
 * 
 */
- (BOOL)clearAutoFocusPoint:(NSError **)error;	

/**
 * 
 * Locks the operation of the automatic exposure control.
 *
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, The operation was successful. If false, The operation was abnormal termination.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::unlockAutoExposure:
 *
 * 
 */
- (BOOL)lockAutoExposure:(NSError **)error;	

/**
 * 
 * Releases the lock behavior of automatic exposure control.
 *
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, The operation was successful. If false, The operation was abnormal termination.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::lockAutoExposure:
 *
 * 
 */
- (BOOL)unlockAutoExposure:(NSError **)error;	

/**
 * 
 * The application specifies the coordinates that the target of the proper exposure at
 * the time of the automatic exposure control.
 *
 * The application must set the coordinates of the target in this method prior
 * to locking the operation of the automatic exposure control.
 * The application will get an error when try to set a value that exceeds the valid range of target coordinate.
 *
 * @param point Coordinates which are the target.
 * Viewfinder coordinate system will be used to coordinate values.
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, The operation was successful. If false, The operation was abnormal termination.
 *
 * The application can convert the focusing coordinates from the coordinates in the live view image
 * touched using the coordinate conversion utility #OLYCameraConvertPointOnLiveImageIntoViewfinder.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::clearAutoExposurePoint:
 * @see OLYCamera::autoExposureEffectiveArea:
 *
 * 
 */
- (BOOL)setAutoExposurePoint:(CGPoint)point error:(NSError **)error;	

/**
 * 
 * Releases the coordinates specified that the application have set as a target for proper exposure.
 *
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, The operation was successful. If false, The operation was abnormal termination.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::setAutoExposurePoint:error:
 *
 * 
 */
- (BOOL)clearAutoExposurePoint:(NSError **)error;	

/**
 * 
 * Gets a valid range as coordinates focus it using the auto focus.
 *
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return Rectangular coordinates indicating the effective range.
 * Viewfinder coordinate system will be used to coordinate values.
 *
 * The application can convert to rectangular coordinates for live view image on the rectangular coordinates
 * indicating the range using the coordinate conversion utility #OLYCameraConvertRectOnViewfinderIntoLiveImage.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::setAutoFocusPoint:error:
 *
 * 
 */
- (CGRect)autoFocusEffectiveArea:(NSError **)error;	

/**
 * 
 * Gets a valid range as the target coordinates of the automatic exposure control.
 *
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return Rectangular coordinates indicating the effective range.
 * Viewfinder coordinate system will be used to coordinate values.
 *
 * The application can convert to rectangular coordinates for live view image on the rectangular coordinates
 * indicating the range using the coordinate conversion utility #OLYCameraConvertRectOnViewfinderIntoLiveImage.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *
 * @see OLYCamera::setAutoExposurePoint:error:
 *
 * 
 */
- (CGRect)autoExposureEffectiveArea:(NSError **)error;	

@end

#pragma mark -
#pragma mark Related Delegates

/**
 * 
 * The delegate for receiving the information of live view is changed.
 *
 * 
 */
@protocol OLYCameraLiveViewDelegate <NSObject>	
@optional

/**
 * 
 * Tells the delegate that the image for live view has been updated.
 *
 * The application can be updated in real time live view by using an image that has been attached to this notice.
 *
 * @param camera Instances it is detected that the image for live view is changed.
 * @param data Binary data of the image of the new live view.
 * @param metadata Meta data of the image of the new live view.
 *
 * 
 */
- (void)camera:(OLYCamera *)camera didUpdateLiveView:(NSData *)data metadata:(NSDictionary *)metadata;	

@end

#pragma mark -
#pragma mark Related Delegates

/**
 * 
 * The delegate for receiving the state relating to the recording operation is changed.
 *
 * 
 */
@protocol OLYCameraRecordingDelegate <NSObject>	
@optional

/**
 * 
 * Tells the delegate that the recording was stopped by reason of the camera side.
 *
 * Some of the following as the cause to be notified.
 *   - If it reaches the recording time that the application specifies.
 *   - If the media becomes full during recording.
 *
 * @param camera Instances it is detected that the camera has stopped recording.
 *
 * 
 */
- (void)cameraDidStopRecordingVideo:(OLYCamera *)camera;	

/**
 * 
 * Tells the delegate that the focus result of auto focus has changed.
 *
 * @param camera Instances it is detected that the focus result changes.
 * @param result Focusing result.
 *
 * Focusing result is passed in dictionary format.
 *   - #OLYCameraTakingPictureProgressInfoFocusResultKey ... Focusing result.
 *     - "ok" ... In focus.
 *     - "ng" ... Did not focus.
 *     - "none" ... AF did not work. lens is set to MF mode or is not supported AF.
 *   - #OLYCameraTakingPictureProgressInfoFocusRectKey ... Rectangular coordinates focused.
 *     Viewfinder coordinate system will be used in this coordinate value.
 *
 * The application can convert the rectangular coordinates in the live view image using
 * the coordinate conversion utility #OLYCameraConvertRectOnViewfinderIntoLiveImage.
 *
 * 
 */
- (void)camera:(OLYCamera *)camera didChangeAutoFocusResult:(NSDictionary *)result;	

@end

// EOF
