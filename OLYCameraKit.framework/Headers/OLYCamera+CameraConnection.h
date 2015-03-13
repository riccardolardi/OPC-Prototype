/**
 * 
 * @file	OLYCamera+CameraConnection.h
 * @brief	OLYCamera(CameraConnection) class interface file.
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
 * @name Olympus camera class: A camera communication-related category
 *
 * 
 * @{
 */

// This is reserved for vendors. Please do not use.
enum OLYCameraConnectionType {	
    // This is reserved for vendors. Please do not use.
    OLYCameraConnectionTypeNotConnected,	
	
    // This is reserved for vendors. Please do not use.
    OLYCameraConnectionTypeWiFi,	
	
};
typedef enum OLYCameraConnectionType OLYCameraConnectionType;

/** @} */
/** @} */

@protocol OLYCameraConnectionDelegate;

#pragma mark -

/**
 * 
 * It is a camera communication-related category of Olympus camera class.
 *
 * This category provides the connection and disconnection to the camera.
 *
 * 
 * @category OLYCamera(CameraConnection)
 */
@interface OLYCamera(CameraConnection)

// This is reserved for vendors. Please do not use.
@property (strong, nonatomic) NSString *host;	

// This is reserved for vendors. Please do not use.
@property (assign, nonatomic, readonly) NSInteger commandPort;	

// This is reserved for vendors. Please do not use.
@property (assign, nonatomic) NSInteger liveViewStreamingPort;	

// This is reserved for vendors. Please do not use.
@property (assign, nonatomic) NSInteger eventPort;	

// This is reserved for vendors. Please do not use.
@property (assign, nonatomic, readonly) OLYCameraConnectionType connectionType;	

/**
 * 
 * The object that acts as the delegate of receiving that communication state of the camera has changed.
 *
 * 
 */
@property (weak, nonatomic) id<OLYCameraConnectionDelegate> connectionDelegate;	

/**
 * 
 * Indicates whether the camera is currently connected.
 *
 * 
 */
@property (assign, nonatomic, readonly) BOOL connected;	

/**
 * 
 * Connects to the camera.
 *
 * Connection to the camera is complete, the application will be able to use features of the SDK.
 *
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, the operation was successful. If false, the operation was abnormal termination.
 *
 * 
 */
- (BOOL)connect:(NSError **)error;	

// ;-)

/**
 * 
 * Disconnects from the camera.
 *
 * You can also power off the camera when you disconnect from the camera.
 * Disconnecting is successful, the value of the property and the state of the camera will be cleared.
 * (Except for communication settings of the camera connection.)
 *
 * @param powerOff If true, the camera will be powered off with the disconnection from the camera.
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return If true, the operation was successful. If false, the operation was abnormal termination.
 *
 * 
 */
- (BOOL)disconnectWithPowerOff:(BOOL)powerOff error:(NSError **)error;	

@end

#pragma mark -
#pragma mark Related Delegates

/**
 * 
 * The delegate to receive that communication state of the camera has changed.
 *
 * 
 */
@protocol OLYCameraConnectionDelegate <NSObject>	
@optional

/**
 * 
 * Tells the delegate that connection path to the camera is lost by an error.
 *
 * @param camera Instance that has lost a communication path with the camera.
 * @param error Error contents.
 *
 * 
 */
- (void)camera:(OLYCamera *)camera disconnectedByError:(NSError *)error;	

@end

// EOF
