/**
 * 
 * @file	OLYCamera+Functions.h
 * @brief	OLYCamera function interface file.
 *
 * 
 */

/**
 * 
 * @defgroup functions Functions
 *
 * Functions that support Olympus camera class
 *
 * 
 * @{
 */

#pragma mark Image Processing Utilities

/**
 * 
 * @name Image processing utilities
 *
 * 
 * @{
 */

/**
 * 
 * Converts the image data to image for UI.
 *
 * @param data The data of the image.
 * @param metadata The metadata of the image data.
 * @return The image for UI.
 *
 * 
 */
UIImage *OLYCameraConvertDataToImage(NSData *data, NSDictionary *metadata);	

/** @} */

#pragma mark Coordinate Conversion Utilities

/**
 * 
 * @name Coordinate conversion utilities
 *
 * These utilities provide to convert between
 * the coordinate values of the viewfinder coordinate system and
 * the coordinate values of the live view coordinate system.
 *
 * The live view coordinate system is a coordinate system in units of pixels for live view image.
 * The origin is the upper left corner.
 * Coordinate axes of the vertical and horizontal matches to that of the image display of the smartphone.
 * If user has in the camera vertically, the origin is still in the upper left,
 * but the size of the width and height of the image and the direction of rotation of the image
 * that is reflected will be exchanged.
 * It is used to represent a pixel position on the image when user touches the live view.
 *
 * The viewfinder coordinate system,
 * It is a coordinate system that is normalized to width = 1.0 and height = 1.0 for live view image.
 * The origin is the upper left corner.
 * Coordinate axes of the vertical and horizontal matches to the imaging sensor in camera.
 * Even if user holds to the camera vertically or horizontally,
 * the size of the width and height of the image and the direction of rotation of the picture will not turnover.
 * It is used to represent the in-focus position and the position of the specified auto focus lock.
 *
 * 
 * @{
 */

/**
 * 
 * Converts the point coordinates of the live view coordinate system
 * into the point coordinates of the viewfinder coordinate system.
 *
 * @param point The point coordinates of the live view coordinate system.
 * @param liveImage The live view image.
 * @return The point coordinates of the viewfinder coordinate system.
 *
 * 
 */
CGPoint OLYCameraConvertPointOnLiveImageIntoViewfinder(CGPoint point, UIImage *liveImage);	

/**
 * 
 * Converts the point coordinates of the viewfinder coordinate system
 * into the point coordinates of the live view coordinate system.
 *
 * @param point The point coordinates of the viewfinder coordinate system.
 * @param liveImage The live view image.
 * @return The point coordinates of the live view coordinate system.
 *
 * 
 */
CGPoint OLYCameraConvertPointOnViewfinderIntoLiveImage(CGPoint point, UIImage *liveImage);	

/**
 * 
 * Converts the rectangular coordinates of the live view coordinate system
 * into the rectangular coordinates of the viewfinder coordinate system.
 *
 * @param rect The rectangular coordinates of the live view coordinate system.
 * @param liveImage The live view image.
 * @return The rectangular coordinates of the viewfinder coordinate system.
 *
 * 
 */
CGRect OLYCameraConvertRectOnLiveImageIntoViewfinder(CGRect rect, UIImage *liveImage);	

/**
 * 
 * Converts the rectangular coordinates of the viewfinder coordinate system
 * into the rectangular coordinates of the live view coordinate system.
 *
 * @param rect The rectangular coordinates of the viewfinder coordinate system.
 * @param liveImage The live view image.
 * @return The rectangular coordinates of the live view coordinate system.
 *
 * 
 */
CGRect OLYCameraConvertRectOnViewfinderIntoLiveImage(CGRect rect, UIImage *liveImage);	

/** @} */

/** @} */

// EOF
