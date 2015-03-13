/**
 * 
 * @file	OLYCamera+Playback.h
 * @brief	OLYCamera(Playback) class interface file.
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
 * @name Olympus camera class: A playback-related category
 *
 * 
 * @{
 */

/**
 * 
 * Resizing parameter of the image that the camera supports.
 *
 * 
 */
typedef CGFloat OLYCameraImageResize;	

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
 * @name Olympus camera class: A playback-related category
 *
 * 
 * @{
 */

/**
 * To resize the long side of the image to be 1024 pixels.
 * 
 */
extern const OLYCameraImageResize OLYCameraImageResize1024;	

/**
 * To resize the long side of the image to be 1600 pixels.
 * 
 */
extern const OLYCameraImageResize OLYCameraImageResize1600;	

/**
 * To resize the long side of the image to be 1920 pixels.
 * 
 */
extern const OLYCameraImageResize OLYCameraImageResize1920;	

/**
 * To resize the long side of the image to be 2048 pixels.
 * 
 */
extern const OLYCameraImageResize OLYCameraImageResize2048;	

/**
 * To use the original size of the image. (Does not resize the image.)
 * 
 */
extern const OLYCameraImageResize OLYCameraImageResizeNone;	

/**
 * Dictionary key for accessing 'Directory path' elements of the content information.
 * 
 */
extern NSString *const OLYCameraContentListDirectoryKey;	

/**
 * Dictionary key for accessing 'File name' elements of the content information.
 * 
 */
extern NSString *const OLYCameraContentListFilenameKey;	

/**
 * Dictionary key for accessing 'File size' elements of the content information.
 * 
 */
extern NSString *const OLYCameraContentListFilesizeKey;	

/**
 * Dictionary key for accessing 'File type' elements of the content information.
 * 
 */
extern NSString *const OLYCameraContentListFiletypeKey;	

/**
 * Dictionary key for accessing 'File attribute list' elements of the content information.
 * 
 */
extern NSString *const OLYCameraContentListAttributesKey;	

/**
 * Dictionary key for accessing 'File modified date' elements of the content information.
 * 
 */
extern NSString *const OLYCameraContentListDatetimeKey;	

/**
 * Dictionary key for accessing 'Extension' elements of the content information.
 * 
 */
extern NSString *const OLYCameraContentListExtensionKey;	

/** @} */
/** @} */

@protocol OLYCameraPlaybackDelegate;

#pragma mark -

/**
 * 
 * It is a playback-related category of Olympus camera class.
 *
 * This category provides download and editing of video and still images that have been saved in the camera.
 *
 * 
 * @category OLYCamera(Playback)
 */
@interface OLYCamera(Playback)

/**
 * 
 * The object that acts as the delegate of receiving that the state about playback operations is changed.
 *
 * 
 */
@property (weak, nonatomic) id<OLYCameraPlaybackDelegate> playbackDelegate;	

/**
 * 
 * Downloads the contents list in the camera.
 *
 * Downloads a list of files in a media that is mounted on the camera of /DCIM directory.
 * Regardless of whether the picture and video files, a list file can contain all.
 * After removing the content that the application does not support it is determined that
 * the file name extension and whether contained in a specific pattern from the content list obtained,
 * please use the list.
 *
 * @param handler Callback that is called when the download is complete.
 *
 * Argument of download completion callback.
 *   - list ... Content list that the method downloaded is stored in an array format.
 *   - error ... Error details will be set when the operation is abnormally terminated.
 *
 * Array element of the list of contents was acquired is a dictionary format.
 * Dictionary key is defined to access the element.
 *   - #OLYCameraContentListDirectoryKey ... Directory path.
 *   - #OLYCameraContentListFilenameKey ... File name.
 *   - #OLYCameraContentListFilesizeKey ... File size.
 *   - #OLYCameraContentListFiletypeKey ... File type.
 *     The following are the file type.
 *     - "directory" ... Directory.
 *     - "file" ... File.
 *   - #OLYCameraContentListAttributesKey ... Array of file attributes. Array is set to an empty normally.
 *     The following are the file attributes.
 *      - "protected" ... Content that has been protected. (Delete content of prohibition)
 *      - "hidden" ... Content hidden.
 *   - #OLYCameraContentListDatetimeKey ... Date object that represents the date and time the file was changed.
 *   - #OLYCameraContentListExtensionKey ... Array of extended information.
 *
 * Please refer to the related documentation for more information on the extended information.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModePlayback
 *
 * 
 */
- (void)downloadContentList:(void (^)(NSMutableArray *list, NSError *error))handler;	

/**
 * 
 * Downloads the thumbnail image for the content in the camera.
 *
 * String that the application specifies in the file path of the content, must be one that
 * combines the directory path and file name obtained from the contents list download.
 * If the application specifies otherwise, the application will get an error.
 *
 * @param path File path of the content.
 * @param progressHandler Callback that will be called every time the progress of the download changes.
 * @param completionHandler Callback that is called when the download is complete.
 * @param errorHandler Callback that is called when the download was aborted.
 *
 * Argument of progress callback
 *   - progress ... Progress rate is set. 0.0 immediately after the start, 1.0 is complete.
 *   - stop ... If set to true, abnormal termination callback is invoked download is canceled.
 *
 * Argument of download completion callback
 *   - data ... Binary data of the thumbnail image that the method downloads will be set.
 *   - metadata ... Meta data of the thumbnail image that the method downloads will be set.
 *     There are cases where the following information is included in addition to the EXIF information.
 *     - "gpstag" ... 1 if the content has positioning information. 0 If do not have.
 *     - "moviesec" ... In the case of video content that can be acquired is play time, play the number of seconds.
 *     - "detectversion" ... Reserved for vendor.
 *     - "detectid" ... Reserved for vendor.
 *     - "groupid" ... Reserved for vendor.
 *
 * Argument of abnormal termination callback
 *   - error ... Error details will be set when the operation is abnormally terminated.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModePlayback
 *
 *
 * 
 */
- (void)downloadContentThumbnail:(NSString *)path progressHandler:(void (^)(float progress, BOOL *stop))progressHandler completionHandler:(void (^)(NSData *data, NSMutableDictionary *metadata))completionHandler errorHandler:(void (^)(NSError *error))errorHandler;	

/**
 * 
 * Downloads the screen nail image for the content in the camera.
 *
 * String that the application specifies in the file path of the content, must be one that
 * combines the directory path and file name obtained from the contents list download.
 * If the application specifies otherwise, the application will get an error.
 *
 * @param path File path of the content.
 * @param progressHandler Callback that will be called every time the progress of the download changes.
 * @param completionHandler Callback that is called when the download is complete.
 * @param errorHandler Callback that is called when the download was aborted.
 *
 * Argument of progress callback
 *   - progress ... Progress rate is set. 0.0 immediately after the start, 1.0 is complete.
 *   - stop ... If set to true, abnormal termination callback is invoked download is canceled.
 *
 * Argument of download completion callback
 *   - data ... Binary data of the screen nail image that the method downloads will be set.
 *
 * Argument of abnormal termination callback
 *   - error ... Error details will be set when the operation is abnormally terminated.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModePlayback
 *
 * 
 */
- (void)downloadContentScreennail:(NSString *)path progressHandler:(void (^)(float progress, BOOL *stop))progressHandler completionHandler:(void (^)(NSData *data))completionHandler errorHandler:(void (^)(NSError *error))errorHandler;	

/**
 * 
 * Downloads a resize-processed still image content in the camera.
 *
 * String that the application specifies in the file path of the content, must be one that
 * combines the directory path and file name obtained from the contents list download.
 * If the application specifies otherwise, the application will get an error.
 *
 * @param path File path of the content.
 * @param resize Pixel size after resize-processing.
 * @param progressHandler Callback that will be called every time the progress of the download changes.
 * @param completionHandler Callback that is called when the download is complete.
 * @param errorHandler Callback that is called when the download was aborted.
 *
 * Argument of progress callback
 *   - progress ... Progress rate is set. 0.0 immediately after the start, 1.0 is complete.
 *   - stop ... If set to true, abnormal termination callback is invoked download is canceled.
 *
 * Argument of download completion callback
 *   - data ... Binary data of the image that the method downloads will be set.
 *
 * Argument of abnormal termination callback
 *   - error ... Error details will be set when the operation is abnormally terminated.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModePlayback
 *
 * 
 */
- (void)downloadImage:(NSString *)path withResize:(OLYCameraImageResize)resize progressHandler:(void (^)(float progress, BOOL *stop))progressHandler completionHandler:(void (^)(NSData *data))completionHandler errorHandler:(void (^)(NSError *error))errorHandler;	

/**
 * 
 * Downloads a content in the camera.
 *
 * String that the application specifies in the file path of the content, must be one that
 * combines the directory path and file name obtained from the contents list download.
 * If the application specifies otherwise, the application will get an error.
 *
 * @param path File path of the content.
 * @param progressHandler Callback that will be called every time the progress of the download changes.
 * @param completionHandler Callback that is called when the download is complete.
 * @param errorHandler Callback that is called when the download was aborted.
 *
 * Argument of progress callback
 *   - progress ... Progress rate is set. 0.0 immediately after the start, 1.0 is complete.
 *   - stop ... If set to true, abnormal termination callback is invoked download is canceled.
 *
 * Argument of download completion callback
 *   - data ... Binary data that the method downloads will be set.
 *
 * Argument of abnormal termination callback
 *   - error ... Error details will be set when the operation is abnormally terminated.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModePlayback
 *
 * 
 */
- (void)downloadContent:(NSString *)path progressHandler:(void (^)(float progress, BOOL *stop))progressHandler completionHandler:(void (^)(NSData *data))completionHandler errorHandler:(void (^)(NSError *error))errorHandler;	

/**
 * 
 * Count the number of content in the camera.
 *
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return Number of content.
 *
 * If the number of the acquired content is zero, an error might have occurred.
 * If the application wants to know the exact number of content, the application should check that
 * a error details is not setting.
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModePlayback
 *
 * 
 */
- (NSInteger)countNumberOfContents:(NSError **)error;	

/**
 * 
 * Gets the information to the content in the camera.
 *
 * String that the application specifies in the file path of the content, must be one that
 * combines the directory path and file name obtained from the contents list download.
 * If the application specifies otherwise, the application will get an error.
 *
 * @param path File path of the content.
 * @param error Error details will be set when the operation is abnormally terminated.
 * @return The information to the content in the camera.
 *
 * Information about the still-image content
 *   - Please refer to the related documentation for detailed information.
 *   - The application can also see the EXIF information that is included in the meta data to download the content.
 *
 * Information about the video content
 *   - "playtime" ... A string that represents the number of seconds of playback video.
 *   - "moviesize" ... A string that represents the pixel size of the video frame. The format is "HeightxWidth".
 *   - "shootingdatetime" ... A string that represents the date and time taken. The format is "YYYYMMDDThhmm".
 *
 * @par Supported run modes
 * This method call is allowed only in run mode the following.
 * The application will get an error when called in run mode other than these.
 *   - #OLYCameraRunModePlayback
 *
 * 
 */
- (NSDictionary *)inquireContentInformation:(NSString *)path error:(NSError **)error;	

// ;-)

// ;-)

// ;-)

@end

#pragma mark -
#pragma mark Related Delegates

/**
 * 
 * The delegate for receiving the state relating to the playback operation is changed.
 *
 * 
 */
@protocol OLYCameraPlaybackDelegate <NSObject>	
@optional

// something functions will come...

@end

// EOF
