/**
 * 
 * @file	OLYCameraError.h
 * @brief	OLYCameraError definition file.
 *
 * 
 */

#import <UIKit/UIKit.h>								// UIKit.framework
#import <Foundation/Foundation.h>					// Foundation.framework

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
 * @name Errors related
 *
 * 
 * @{
 */

/**
 * NSError codes in the OLYCameraErrorDomain.
 * 
 */
enum OLYCameraError {
	/**
     * An unknown error occurred.
     * 
     */
	OLYCameraErrorUnknown = 0x0bad0001,
	
	/**
     * 
	 * The invalid parameters.
	 *
	 * There is an error in the value specified in the property or method argument.
	 * Please make sure the value you whether the specified along with the specifications of the camera.
	 *
     * 
     */
	OLYCameraErrorInvalidParameters = 0x0bad0002,
	
	/**
     * 
	 * The invalid operation.
	 *
	 * The application may have tried to call the operation not allowed on current mode.
	 * Please change the program so that those operations do not call.
	 *
     * 
     */
	OLYCameraErrorInvalidOperations = 0x0bad0003,
	
	/**
     * The operation is not supported.
     * 
     */
	OLYCameraErrorUnsupportedOperations = 0x0bad0004,
	
	/**
     * 
	 * Connecting to the camera failed.
	 *
	 * There is a possibility that the camera and the smartphone is not connected.
	 * Please check whether the smartphone is connected to the camera before the program work with using SDK.
	 *
     * 
     */
	OLYCameraErrorConnectionFailed = 0x0bad0005,
	
	/**
     * 
	 * Not connected to the camera.
	 *
	 * To operate the camera, the program must be connected to the camera using the SDK first.
	 * Please make sure the program is calling the connection method for the first time.
	 *
     * 
     */
	OLYCameraErrorNotConnected = 0x0bad0006,
	
	/**
     * 
	 * Sending a command to the camera failed.
	 *
	 * There is a possibility that the specification of the camera firmware and specifications of the SDK
	 * does not match, or the state of the network is unstable.
	 *
     * 
     */
	OLYCameraErrorCommandFailed = 0x0bad0007,
	
	/**
     * 
	 * The data that returned from the camera is broken or is unexpected format.
	 *
	 * There is a possibility that the specification of the camera firmware and specifications of the SDK
	 * does not match, or the state of the network is unstable.
	 *
     * 
     */
	OLYCameraErrorBadResponse = 0x0bad0008,
	
	/**
     * 
	 * The command was rejected because the camera is busy processing other tasks.
	 *
	 * There is a possibility to be successful when the application sends the same command again at a later time of some.
	 *
     * 
	 *
	 */
	OLYCameraErrorCameraBusy = 0x0bad0009,
	
	/**
     * 
	 * The operation is aborted.
	 *
	 * There may have been aborted during processing, such as by user operation.
	 *
     * 
     */
	OLYCameraErrorOperationAborted = 0x0bad000a,
	
	/**
     * 
	 * Focusing by the camera failed.
	 *
	 * There is a possibility that user tried to focus on the subject that cannot be recognized by the camera's autofocus.
	 * The operation may be successful from running again with changing the position of the subject and framing of the viewfinder.
	 *
     * 
     */
	OLYCameraErrorFocusFailed = 0x0bad000b,
	
};
typedef enum OLYCameraError OLYCameraError;

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
 * @name Errors related
 *
 * 
 * @{
 */

/**
 * OLYCameraKit errors.
 * 
 */
extern NSString *const OLYCameraErrorDomain;

/**
 * Dictionary key for accessing error detail elements in user's information of NSError instance.
 * 
 */
extern NSString *const OLYCameraErrorDetailKey;

/** @} */
/** @} */

// EOF
