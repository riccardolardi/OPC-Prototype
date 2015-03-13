/**
 * 
 * @file	OLYCamera+CameraSystem.h
 * @brief	OLYCamera(CameraSystem) class interface file.
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
 * @name Olympus camera class: A camera system-related category
 *
 * 
 * @{
 */

/**
 * 
 * Run mode of the camera system.
 *
 * 
 */
enum OLYCameraRunMode {	
	/**
     * 
	 * Mode the SDK does not work.
	 *
	 * Sometimes when the application is not connected or when the mode change is abnormally terminated,
	 * the run mode is this value.
	 *
     * 
     */
	OLYCameraRunModeUnknown,	
	
	/**
     * 
	 * Stand-alone mode.
	 *
	 * The run mode is this value immediately after that is connected to the camera.
	 *
	 * If the application changes to this mode from any other mode,
	 * there are several camera properties returns to the initial state.
	 * Please refer to the documentation of the camera list of properties for more information.
	 *
     * 
     */
	OLYCameraRunModeStandalone,	
	
	/**
     * 
	 * Playback mode.
	 *
	 * This mode is used to view the captured image in the camera.
	 *
     * 
     */
	OLYCameraRunModePlayback,	
	
	/**
     * 
	 * Play-maintenance mode.
	 *
	 * There is no function that is provided now.
	 * This definition is what is provided to extend in the future.
	 *
     * 
     */
	OLYCameraRunModePlaymaintenance,	
	
	/**
     * 
	 * Recording mode.
	 * 
	 * This mode is used to capture still images and to record videos by
	 * the shutter of wireless communication.
	 *
     * 
     */
	OLYCameraRunModeRecording,	
	
	/**
     * 
	 * Maintenance mode.
	 *
	 * There is no function that is provided now.
	 * This definition is what is provided to extend in the future.
	 *
     * 
     */
	OLYCameraRunModeMaintenance,	
	
	// This is reserved for vendors. Please do not use.
	OLYCameraRunModePlaystream,
	
};
typedef enum OLYCameraRunMode OLYCameraRunMode;

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
 * @name Olympus camera class: A camera system-related category
 *
 * 
 * @{
 */

/**
 * Dictionary key for accessing 'Camera model name' elements of camera hardware information.
 * 
 */
extern NSString *const OLYCameraHardwareInformationCameraModelNameKey;	

/**
 * Dictionary key for accessing 'Camera firmware version' elements of camera hardware information.
 */
extern NSString *const OLYCameraHardwareInformationCameraFirmwareVersionKey;	

/**
 * Dictionary key for accessing 'Lens type' elements of camera hardware information.
 */
extern NSString *const OLYCameraHardwareInformationLensTypeKey;	

/**
 * Dictionary key for accessing 'Lens ID' elements of camera hardware information.
 */
extern NSString *const OLYCameraHardwareInformationLensIdKey;	

/**
 * Dictionary key for accessing 'Lens firmware version' elements of camera hardware information.
 */
extern NSString *const OLYCameraHardwareInformationLensFirmwareVersionKey;	

/**
 * Dictionary key for accessing 'Flash ID' elements of camera hardware information.
 */
extern NSString *const OLYCameraHardwareInformationFlashIdKey;	

/**
 * Dictionary key for accessing 'Flash firmware version' elements of camera hardware information.
 */
extern NSString *const OLYCameraHardwareInformationFlashFirmwareVersionKey;	

/**
 * Dictionary key for accessing 'Accessory ID' elements of camera hardware information.
 */
extern NSString *const OLYCameraHardwareInformationAccessoryIdKey;	

/**
 * Dictionary key for accessing 'Accessory firmware version' elements of camera hardware information.
 */
extern NSString *const OLYCameraHardwareInformationAccessoryFirmwareVersionKey;	

/** @} */
/** @} */

@protocol OLYCameraPropertyDelegate;

#pragma mark -

/**
 * 
 * It is a camera system-related category of Olympus camera class.
 *
 * This category provides to get or set the camera settings (Camera property) and change the run mode.
 *
 * For example, The application can get or set the camera following properties:
 *   - Basic settings (F value, shutter speed, and exposure mode, etc.)
 *   - Color tone and finish settings (white balance, the art filter, etc.)
 *   - Focus settings (focus mode, such as focus lock)
 *   - Image quality and saving settings (save size, compression ratio, image quality mode, etc.)
 *   - Camera status (battery level, angle of view, etc.)
 *   - Recording auxiliary (face detection and, sound volume level, etc.)
 *
 * Please refer to the camera list of properties for more information.
 *
 * 
 * @category OLYCamera(CameraSystem)
 */
@interface OLYCamera(CameraSystem)

/**
 * 
 * List of property names camera currently available.
 *
 * The application must be operation after checking the camera properties must be contained in the list.
 *
 * @see OLYCamera::cameraPropertyValue:error:
 * @see OLYCamera::cameraPropertyValueList:error:
 * @see OLYCamera::setCameraPropertyValue:value:error:
 *
 * 
 */
@property (strong, nonatomic, readonly) NSArray *cameraPropertyNames;	

/**
 * 
 * The object that acts as the delegate of receiving that the camera property has changed.
 *
 * 
 */
@property (weak, nonatomic) id<OLYCameraPropertyDelegate> cameraPropertyDelegate;	

/**
 * 
 * Current run mode of the camera system.
 *
 * @see OLYCamera::changeRunMode:error:
 *
 * 
 */
@property (assign, nonatomic, readonly) OLYCameraRunMode runMode;	

/**
 * 
 * Indicates whether the inside of camera is in high-temperature condition.
 *
 * You can also check in the lighting state of the LED on the camera body.
 * If the inside of the camera is a high-temperature state, please stop using the camera immediately,
 * and please wait for the camera becomes normal temperature.
 *
 * 
 */
@property (assign, nonatomic, readonly) BOOL highTemperatureWarning;	

/**
 * 
 * Indicates the status of lens mount.
 *
 * Statuses are followings:
 *   - (nil) ... It is not connected to the camera, or the state is unknown.
 *   - "normal" ... Available the lens already mounted. If the lens has some additional functions,
 *     the following items are added to the end of "normal".
 *     - "+electriczoom" ... The lens is equipped with a motorized zoom.
 *     - "+macro" ... The lens is equipped with a macro mode.
 *   - "down" ... The lens is mounted. But disabled by collapsed.
 *   - "nolens" ... Disabled by the lens is not mounted.
 *   - "cantshoot" ... Disabled by other reasons.
 *
 *
 * 
 */
@property (strong, nonatomic, readonly) NSString *lensMountStatus;	

/**
 * 
 * Indicates the status of media mount.
 *
 * Statuses are followings:
 *   - (nil) ... It is not connected to the camera, or the state is unknown.
 *   - "normal" ... Available in the media already mounted.
 *   - "readonly" ... The media is already mounted. But cannot write for that the media is read-only.
 *   - "cardfull" ... The media is already mounted. But cannot write for that the media is no free space.
 *   - "unmount" ... Disabled by the media is not mounted.
 *   - "error" ... Disabled by a media mount error.
 *
 * 
 */
@property (strong, nonatomic, readonly) NSString *mediaMountStatus;	

/**
 * 
 * Indicates whether the camera is writing to the media.
 *
 * You can also check in the lighting state of the LED on the camera body.
 * While the camera is writing to the media, you will see a response API is slow.
 *
 * @see OLYCamera::startTakingPicture:progressHandler:completionHandler:errorHandler:
 * @see OLYCamera::stopTakingPicture:completionHandler:errorHandler:
 * @see OLYCamera::takePicture:progressHandler:completionHandler:errorHandler:
 * @see OLYCamera::startRecordingVideo:completionHandler:errorHandler:
 * @see OLYCamera::stopRecordingVideo:errorHandler:
 *
 * 
 */
@property (assign, nonatomic, readonly) BOOL mediaBusy;	

/**
 * 
 * Indicates whether the media I/O error is occurred.
 *
 * There is a possibility that the media is broken.
 * Please replace the new media if it occurs frequently.
 *
 * 
 */
@property (assign, nonatomic, readonly) BOOL mediaError;	

/**
 * 
 * Free space of the media attached to the camera. The unit is the number of bytes.
 *
 * 
 */
@property (assign, nonatomic, readonly) NSUInteger remainingMediaCapacity;	

/**
 * 
 * The maximum number of capturing images that can be stored in the camera.
 *
 * This value does not indicate the exact value depends on the data for the compression ratio of the captured image.
 * Sometimes the value does not change after capturing.
 *
 * @see OLYCamera::startTakingPicture:progressHandler:completionHandler:errorHandler:
 * @see OLYCamera::stopTakingPicture:completionHandler:errorHandler:
 * @see OLYCamera::takePicture:progressHandler:completionHandler:errorHandler:
 *
 * 
 */
@property (assign, nonatomic, readonly) NSUInteger remainingImageCapacity;	

/**
 * 
 * The maximum number of seconds of recording a movie that can be stored in the camera.
 *
 * This value does not indicate the exact value depends on the data for the compression ratio of the captured video.
 *
 * @see OLYCamera::startRecordingVideo:completionHandler:errorHandler:
 * @see OLYCamera::stopRecordingVideo:errorHandler:
 *
 * 
 */
@property (assign, nonatomic, readonly) NSTimeInterval remainingVideoCapacity;	

/**
 * 
 * Gets the hardware information of the camera.
 *
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return The hardware information of the camera.
 *
 * Hardware information acquired is a dictionary format.
 * The following keys are defined in order to access each element.
 *   - #OLYCameraHardwareInformationCameraModelNameKey ... The camera model name.
 *   - #OLYCameraHardwareInformationCameraFirmwareVersionKey ... The camera firmware version.
 *   - #OLYCameraHardwareInformationLensTypeKey
 *   - #OLYCameraHardwareInformationLensIdKey
 *   - #OLYCameraHardwareInformationLensFirmwareVersionKey
 *   - #OLYCameraHardwareInformationFlashIdKey
 *   - #OLYCameraHardwareInformationFlashFirmwareVersionKey
 *   - #OLYCameraHardwareInformationAccessoryIdKey
 *   - #OLYCameraHardwareInformationAccessoryFirmwareVersionKey
 *
 * Please refer to the related documentation for more information.
 *
 * 
 */
- (NSDictionary *)inquireHardwareInformation:(NSError **)error;	

/**
 * 
 * Gets the title of the camera property.
 *
 * If the application specifies a value that does not exist in the list of camera properties currently available,
 * the application will get an error.
 * Please refer to the documentation of the camera list of properties for more information.
 *
 * @param name The camera property name.
 * @return The title on Human readable format.
 *
 * @see OLYCamera::cameraPropertyNames
 *
 * 
 */
- (NSString *)cameraPropertyTitle:(NSString *)name;	

/**
 * 
 * Gets a list of the camera can be set property values.
 *
 * If the application specifies a value that does not exist in the list of camera properties currently available,
 * the application will get an error.
 * If the application changes the settings such as the shooting mode,
 * there are times when the contents of the list is changed.
 * Please refer to the documentation of the camera list of properties for more information.
 *
 * @param name The camera property name.
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return The list of the camera can be set property values.
 *
 * @see OLYCamera::cameraPropertyNames
 * @see OLYCamera::cameraPropertyValue:error:
 *
 * 
 */
- (NSArray *)cameraPropertyValueList:(NSString *)name error:(NSError **)error;	

/**
 * 
 * Gets the value that is set in the camera properties.
 *
 * If the application specifies a value that does not exist in the list of camera properties currently available,
 * the application will get an error.
 * Depending on the setting value of the shooting mode and connection type and etc.,
 * there are several properties that is read-only access or prohibited.
 * Please refer to the documentation of the camera list of properties for more information.
 *
 * @param name The camera property name.
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return The value that is set in the camera properties.
 *
 * @see OLYCamera::cameraPropertyNames
 * @see OLYCamera::canSetCameraProperty:
 * @see OLYCamera::setCameraPropertyValue:value:error:
 *
 * 
 */
- (NSString *)cameraPropertyValue:(NSString *)name error:(NSError **)error;	

/**
 * 
 * Gets the values that are set in the camera properties.
 *
 * If the application specifies a value that does not exist in the list of camera properties currently available,
 * the application will get an error.
 * Depending on the setting value of the shooting mode and connection type and etc.,
 * there are several properties that is read-only access or prohibited.
 * Please refer to the documentation of the camera list of properties for more information.
 *
 * @param names The camera property names. Each element is as a string.
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return The values that is set in the camera properties.
 *
 * The retrieved values is a dictionary format.
 * The dictionary key is the camera property name.
 * Setting of the camera property is stored in the value corresponding to the key.
 *
 * @see OLYCamera::cameraPropertyNames
 * @see OLYCamera::setCameraPropertyValues:error:
 *
 * 
 */
- (NSDictionary *)cameraPropertyValues:(NSSet *)names error:(NSError **)error;	

/**
 * 
 * Gets a title of the camera can be set property values.
 *
 * If the application specifies a value that does not exist in the list of camera properties currently available,
 * the application will get an error.
 * Depending on the setting value of the shooting mode and connection type and etc.,
 * there are several properties that is read-only access or prohibited.
 * Please refer to the documentation of the camera list of properties for more information.
 *
 * @param value The camera property value.
 * @return The title on Human readable format.
 *
 * @see OLYCamera::cameraPropertyNames
 * @see OLYCamera::cameraPropertyValue:error:
 *
 * 
 */
- (NSString *)cameraPropertyValueTitle:(NSString *)value;	

/**
 * 
 * Checks to see if it can set the value to the camera properties.
 *
 * If the application specifies a value that does not exist in the list of camera properties currently available,
 * the application will get an error.
 * Depending on the setting value of the shooting mode and connection type and etc.,
 * there are several properties that is read-only access or prohibited.
 * Please refer to the documentation of the camera list of properties for more information.
 *
 * @param name The camera property name.
 * @return If true, the camera can be set property. If false, the camera cannot be set property.
 *
 * @see OLYCamera::cameraPropertyNames
 * @see OLYCamera::setCameraPropertyValue:value:error:
 *
 * 
 */
- (BOOL)canSetCameraProperty:(NSString *)name;	

/**
 * 
 * Sets a value to the camera properties.
 *
 * If the application specifies a value that does not exist in the list of camera properties currently available,
 * the application will get an error.
 * Depending on the setting value of the shooting mode and connection type and etc.,
 * there are several properties that is read-only access or prohibited.
 * Please refer to the documentation of the camera list of properties for more information.
 *
 * @param name The camera property name.
 * @param value The camera property value.
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, the operation was successful. If false, the operation was abnormal termination.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *   - #OLYCameraRunModeMaintenance
 *
 * @see OLYCamera::cameraPropertyNames
 * @see OLYCamera::cameraPropertyValue:error:
 * @see OLYCamera::canSetCameraProperty:
 *
 * 
 */
- (BOOL)setCameraPropertyValue:(NSString *)name value:(NSString *)value error:(NSError **)error;	

/**
 * 
 * Sets values to the camera properties.
 *
 * If the application specifies a value that does not exist in the list of camera properties currently available,
 * the application will get an error.
 * Depending on the setting value of the shooting mode and connection type and etc.,
 * there are several properties that is read-only access or prohibited.
 * Please refer to the documentation of the camera list of properties for more information.
 *
 * @param values The pairs of the camera property value and name.
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, the operation was successful. If false, the operation was abnormal termination.
 *
 * Name-value pairs of the camera properties that can be specified in dictionary format.
 * The application must specify the camera property name in the dictionary key,
 * and store the value associated with that key the new value of the camera properties.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModeRecording
 *   - #OLYCameraRunModeMaintenance
 *
 * @see OLYCamera::cameraPropertyNames
 * @see OLYCamera::cameraPropertyValues:error:
 * @see OLYCamera::setCameraPropertyValue:value:error:
 *
 * 
 */
- (BOOL)setCameraPropertyValues:(NSDictionary *)values error:(NSError **)error;	

/**
 * 
 * Changes run mode of the camera system.
 *
 * The available features of camera is different by run mode.
 * For example: The application should change the mode to #OLYCameraRunModePlayback when shooting of the photograph,
 * and should change the mode to #OLYCameraRunModeRecording when getting a list of the camera contents.
 * Please refer to the related documentation for more information of relationship between
 * run mode and available features of camera.
 *
 * The camera tries to change run mode in shooting or writing and etc., you will see a response API is slow.
 *
 * @param mode Run mode of the camera system.
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, the operation was successful. If false, the operation was abnormal termination.
 *
 * @see OLYCamera::runMode
 *
 * 
 */
- (BOOL)changeRunMode:(OLYCameraRunMode)mode error:(NSError **)error;	

// ;-)

/**
 * 
 * Registers the geolocation information to the camera.
 *
 * After the application registered the current geo-location in the camera,
 * the geo-location will be set as the GPS information to the meta-data of the picture when user takes a picture.
 *
 * The geo-location information specified by the application must be configured with sentences of GGA and RMC that are formatted by NMEA0183.
 *
 * @param location The new geo-location information.
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, the operation was successful. If false, the operation was abnormal termination.
 *
 * @see OLYCamera::clearGeolocation:
 *
 * 
 */
- (BOOL)setGeolocation:(NSString *)location error:(NSError **)error;	

/**
 * 
 * Discards the geo-location information of the registered.
 *
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, the operation was successful. If false, the operation was abnormal termination.
 *
 * @see OLYCamera::setGeolocation:error:
 *
 * 
 */
- (BOOL)clearGeolocation:(NSError **)error;	

// ;-)

@end

#pragma mark -
#pragma mark Related Delegates

/**
 * 
 * The delegate to receive that the camera property has changed.
 *
 * 
 */
@protocol OLYCameraPropertyDelegate <NSObject>	
@optional

/**
 * 
 * Tells the delegate that the list of camera property values ​​or camera property value has been updated.
 *
 * @param camera Instances it is detected that the camera property has changed.
 * @param name Name of the camera property there is a change in setting.
 *
 * 
 */
- (void)camera:(OLYCamera *)camera didChangeCameraProperty:(NSString *)name;	

@end

// EOF
