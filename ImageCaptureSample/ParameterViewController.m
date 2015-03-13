//
//  ParameterViewController.m
//  ImageCaptureSample
//
//  Copyright (c) 2014 Olympus Imaging Corporation. All rights reserved.
//

#import "AppDelegate.h"
#import "ParameterViewController.h"

NSString const *ICSParameterListTitleKey = @"title";
NSString const *ICSParameterListValueKey = @"value";

@interface ParameterViewController ()

@property (strong, nonatomic) NSArray *list;
@property (strong, nonatomic) NSString *value;
@property (copy, nonatomic) void (^handler)(NSString *value);

@end

@implementation ParameterViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

- (void)dealloc
{
	self.list = nil;
	self.value = nil;
	self.handler = nil;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	if (self.list) {
		return  self.list.count;
	}
    return 0;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *parameterCell = [tableView dequeueReusableCellWithIdentifier:@"ParameterCell" forIndexPath:indexPath];
	NSDictionary *item = self.list[indexPath.row];
	parameterCell.textLabel.text = item[ICSParameterListTitleKey];
	if ([self.value isEqualToString:item[ICSParameterListValueKey]]) {
		parameterCell.accessoryType = UITableViewCellAccessoryCheckmark;
	} else {
		parameterCell.accessoryType = UITableViewCellAccessoryNone;
	}
    return parameterCell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
	if (!self.list || !self.handler) {
		return;
	}
	NSDictionary *item = self.list[indexPath.row];
	self.value = item[ICSParameterListValueKey];
	[tableView reloadData];
	(self.handler)(self.value);
}

- (void)setList:(NSArray *)list value:(NSString *)value handler:(void (^)(NSString *value))handler
{
	self.list = list;
	self.value = value;
	self.handler = handler;
	[self.tableView reloadData];
}

- (void)removeList
{
	self.list = nil;
	self.value = nil;
	self.handler = nil;
	[self.tableView reloadData];
}

@end
