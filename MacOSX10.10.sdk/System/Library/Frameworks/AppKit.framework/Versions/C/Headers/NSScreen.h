/*
	NSScreen.h
	Application Kit
	Copyright (c) 1994-2014, Apple Inc.
	All rights reserved.
*/

#import <Foundation/NSObject.h>
#import <Foundation/NSGeometry.h>
#import <AppKit/NSGraphics.h>

@class NSArray, NSColorSpace;

typedef struct NSScreenAuxiliary NSScreenAuxiliaryOpaque;

@interface NSScreen : NSObject {
/*All instance variables are private*/
@private
    NSRect _frame;          // cached value, possibly stale
    NSWindowDepth _depth;  
    int _screenNumber;
    id _auxiliaryStorage;
}

+ (NSArray *)screens;		/* All screens; first one is "zero" screen */
+ (NSScreen *)mainScreen;	/* Screen with key window */
+ (NSScreen *)deepestScreen;

/* screensHaveSeparateSpaces returns YES if each screen has its own set of spaces.  This is a system  setting and does not necessarily imply that there are multiple screens, nor that there are multiple spaces on any one screen 
*/
+ (BOOL)screensHaveSeparateSpaces NS_AVAILABLE_MAC(10_9);

@property (readonly) NSWindowDepth depth;
@property (readonly) NSRect frame;
@property (readonly) NSRect visibleFrame;
@property (readonly, copy) NSDictionary *deviceDescription;
@property (readonly, strong) NSColorSpace *colorSpace NS_AVAILABLE_MAC(10_6);

@property (readonly) const NSWindowDepth *supportedWindowDepths NS_RETURNS_INNER_POINTER; /* 0 terminated */

/* Convert to/from the device pixel aligned coordinates sytem of a display 
 */
- (NSRect)convertRectToBacking:(NSRect)aRect NS_AVAILABLE_MAC(10_7);
- (NSRect)convertRectFromBacking:(NSRect)aRect NS_AVAILABLE_MAC(10_7);

/* Uses NSIntegralRectWithOptions() to produce a pixel aligned rectangle on the target screen from the given input rectangle in global screen coordinates.
 */
- (NSRect)backingAlignedRect:(NSRect)aRect options:(NSAlignmentOptions)options NS_AVAILABLE_MAC(10_7);

/* Returns the scale factor representing the number of backing store pixels corresponding to each linear unit in screen space on this NSScreen. This method is provided for rare cases when the explicit scale factor is needed.  Please use -convert*ToBacking: methods whenever possible. 
 */
@property (readonly) CGFloat backingScaleFactor NS_AVAILABLE_MAC(10_7); 

@end

/* Notifications */
APPKIT_EXTERN NSString * const NSScreenColorSpaceDidChangeNotification NS_AVAILABLE_MAC(10_6);  // the notification object is the screen whose profile has changed


@interface NSScreen(NSDeprecated)

/*  This method is deprecated and should not be used by applications targeting Mac OS X 10.7 or later.
 The implementation of this method will always return 1.0.  Please use -convertRectToBacking: or -backingScaleFactor instead.
 */
- (CGFloat)userSpaceScaleFactor NS_DEPRECATED_MAC(10_4, 10_7, "Use -convertRectToBacking: or -backingScaleFactor instead");

@end
