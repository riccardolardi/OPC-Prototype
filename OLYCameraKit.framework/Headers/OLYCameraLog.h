/**
 * 
 * @file	OLYCameraLog.h
 * @brief	OLYCameraLog class interface file.
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
 * @name Log management class
 *
 * 
 * @{
 */

/**
 * Log output level
 * 
 */
enum OLYCameraLogLevel {
	/**
	 * Error.
	 * 
	 */
	OLYCameraLogLevelError,
	/**
	 * Warning.
	 * 
	 */
	OLYCameraLogLevelWarning,
	/**
	 * Information.
	 * 
	 */
	OLYCameraLogLevelInfo,
	/**
	 * Debug.
	 * 
	 */
	OLYCameraLogLevelDebug,
};
typedef enum OLYCameraLogLevel OLYCameraLogLevel;

/** @} */
/** @} */

@protocol OLYCameraLogDelegate;

/**
 * 
 * Olympus camera SDK log management class.
 *
 * By default, the logger output to syslog or console log messages of higher priority level than the debug level.
 * However, the logger will output log messages of all levels if the SDK is the debug build.
 *
 * 
 */
@interface OLYCameraLog : NSObject

/**
 * Delegate to receive log messages.
 * 
 */
@property (weak, nonatomic) id<OLYCameraLogDelegate> delegate;

/**
 * 
 * Returns the shared instance.
 *
 * 
 */
+ (id)sharedLog;

/**
 * 
 * Sets the new delegate.
 *
 * 
 */
+ (void)setDelegate:(id<OLYCameraLogDelegate>)delegate;

/**
 * 
 * Restores the delegate to preset.
 *
 * 
 */
+ (void)resetDelegate;

@end

/**
 * 
 * The delegate to receive log messages from Olympus camera SDK.
 *
 * 
 */
@protocol OLYCameraLogDelegate <NSObject>
@optional

/**
 * 
 * Tells the delegate that Olympus camera SDK outputs a log message.
 *
 * @param log The logger that should output a log message.
 * @param message The log message.
 * @param level The log level.
 *
 * 
 */
- (void)log:(OLYCameraLog *)log shouldOutputMessage:(NSString *)message level:(OLYCameraLogLevel)level;

@end

// EOF
