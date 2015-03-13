/**
 * @mainpage
 *
 * 
 *
 * @par Summary
 *
 * OLYCameraKit is a software development kit for Olympus wireless camera.
 *
 * Using the OLYCameraKit, you can easily create applications that control a camera via wireless.
 *
 * @par Outline
 *
 * - The following classes are available for a fetch of information and various operations by connecting a camera.
 *   - @ref OLYCamera
 * - The following protocols are available for the state of the communication network camera or to notify the change.
 *   - @ref OLYCameraConnectionDelegate ... The protocol will receive that state on the communication channel with the camera has changed.
 *   - @ref OLYCameraLiveViewDelegate ... The protocol will receive that the state on the live view image is changed.
 *   - @ref OLYCameraPropertyDelegate ... The protocol will receive that the state on property values or a list of property values has changed.
 *   - @ref OLYCameraRecordingDelegate ... The protocol will receive that a change that affects the still image or movie user is capturing occurs.
 *   - @ref OLYCameraRecordingSupportsDelegate ... The protocol will receive that the state relating to the operation of capturing has changed.
 * - As support for debugging the application, class of log output and error code are available.
 *
 * @par How to use
 *
 * First, please connect to the camera as the SDK after performing the settings for communication with the camera.
 * (There is no need to change the communication settings usually.)
 * Please establish a connection with the camera and smartphone via Wi-Fi by the application or user
 * before calling the above procedure.
 *
 * The camera has several run modes. The available functions are different in each mode.
 * It is set in the stand-alone mode is just connected to the camera.
 * To movie recording or photographed:
 * Connect to the camera, change to recording mode, set the drive mode and shooting mode,
 * call the capturing start and then end of capturing.
 *
 * When using the camera is unnecessary, the application need to disconnect SDK from the camera explicitly.
 * If the application supports multitasking, please be in such a mechanism:
 * The application disconnects from the camera when enters in the background mode
 * and so connect to the camera again when enters in the foreground mode.
 * So that other applications can use the camera when the application does not use the camera.
 *
 * 
 */
/**
 * 
 * @file	OLYCamera.h
 * @brief	OLYCamera class interface file.
 *
 * 
 */

#import <UIKit/UIKit.h>								// UIKit.framework
#import <Foundation/Foundation.h>					// Foundation.framework
#import <ImageIO/ImageIO.h>							// ImageIO.framework
#import <CFNetwork/CFNetwork.h>						// CFNetwork.framework
#import <SystemConfiguration/SystemConfiguration.h> // SystemConfiguration.framework

#import "OLYCameraError.h"
#import "OLYCameraLog.h"

/**
 * 
 * @defgroup types Types
 *
 * Type definition and enumerated types that are to be used by Olympus camera class
 *
 * 
 * @{
 */
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
 * 
 * Version of Olympus camera kit.
 *
 * Please check this value first when you guess the behavior of the SDK is incorrect.
 * The problem may have been resolved in the latest version of the SDK.
 *
 * 
 */
extern NSString *const OLYCameraKitVersion;

/**
 * 
 * Build number of Olympus camera kit.
 *
 * 
 */
extern NSString *const OLYCameraKitBuildNumber;

/** @} */
/** @} */

/**
 * 
 *
 * Olympus camera class.
 *
 * This class provides the operation and display of live view, such as content acquisition in the camera
 * and capturing of still images and recording movies by connecting to the camera.
 * This class has several categories.
 *
 * Please refer to each category for details of the interface.
 * - @ref OLYCamera(CameraConnection)
 *    - It is a camera communication-related category of Olympus camera class.
 *      This category provides the connection and disconnection to the camera.
 * - @ref OLYCamera(CameraSystem)
 *    - It is a camera system-related category of Olympus camera class.
 *      This category provides to get or to set the camera settings (Camera property) and change the run mode.
 *    - For example, The application can get or set the camera following properties:
 *      - Basic settings (F value, shutter speed, and exposure mode, etc.)
 *      - Color tone and finish setting (white balance, the art filter, etc.)
 *      - Focus settings (focus mode, such as focus lock)
 *      - Image quality and saving settings (save size, compression ratio, image quality mode, etc.)
 *      - Camera status (battery level, angle of view, etc.)
 *      - Recording auxiliary (face detection and, sound volume level, etc.)
 *    - Please refer to the camera list of properties for more information.
 * - @ref OLYCamera(Maintenance)
 *    - It is a maintenance-related category of Olympus camera class.
 *      There is no function that is provided now.
 *      This definition is what is provided to extend in the future.
 * - @ref OLYCamera(Playback)
 *    - It is a playback-related category of Olympus camera class.
 *      This category provides download and editing of video and still images that have been saved in the camera.
 * - @ref OLYCamera(PlaybackMaintenance)
 *    - It is a playback auxiliary category of Olympus camera class.
 *      There is no function that is provided now.
 *      This definition is what is provided to extend in the future.
 * - @ref OLYCamera(Recording)
 *    - It is a recording-related category of Olympus camera class.
 *      This category provides taking still pictures and recording video, exposure control, and focus control.
 * - @ref OLYCamera(RecordingSupports)
 *    - It is a recording auxiliary category of Olympus camera class.
 *      This category provides zoom control, and live view image display.
 *
 * Several functions are provided for the vendor. These are not available in the user's application.
 *
 * 
 */
@interface OLYCamera : NSObject

// See categories.

@end

#import "OLYCamera+CameraConnection.h"
#import "OLYCamera+CameraSystem.h"
#import "OLYCamera+Playback.h"
#import "OLYCamera+PlaybackMaintenance.h"
#import "OLYCamera+Recording.h"
#import "OLYCamera+RecordingSupports.h"
#import "OLYCamera+Maintenance.h"
#import "OLYCamera+Functions.h"

// EOF
