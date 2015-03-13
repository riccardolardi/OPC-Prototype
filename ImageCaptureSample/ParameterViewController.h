//
//  ParameterViewController.h
//  ImageCaptureSample
//
//  Copyright (c) 2014 Olympus Imaging Corporation. All rights reserved.
//

#import <UIKit/UIKit.h>

extern NSString *ICSParameterListTitleKey;
extern NSString *ICSParameterListValueKey;

@interface ParameterViewController : UITableViewController

- (void)setList:(NSArray *)list value:(NSString *)value handler:(void (^)(NSString *value))handler;
- (void)removeList;

@end
