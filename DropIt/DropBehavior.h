//
//  DropBehavior.h
//  DropIt
//
//  Created by Chao Wu on 3/1/14.
//  Copyright (c) 2014 Chao Wu. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface DropBehavior : UIDynamicBehavior

- (void) addItem:(id <UIDynamicItem>) item;
- (void) removeItem:(id <UIDynamicItem>) item;

@end
