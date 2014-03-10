//
//  DropBehavior.m
//  DropIt
//
//  Created by Chao Wu on 3/1/14.
//  Copyright (c) 2014 Chao Wu. All rights reserved.
//

#import "DropBehavior.h"

@interface DropBehavior()
@property (nonatomic,strong) UIGravityBehavior *gravity;
@property (nonatomic,strong) UICollisionBehavior *collide;
@property (nonatomic,strong) UIDynamicItemBehavior *itemBehavior;
@end

@implementation DropBehavior



- (UIDynamicItemBehavior *)itemBehavior
{
    if (!_itemBehavior)
    {
        _itemBehavior = [[UIDynamicItemBehavior alloc]init];
        _itemBehavior.allowsRotation = NO;
    }
    return _itemBehavior;
}

- (UIGravityBehavior *) gravity
{
    if (!_gravity)
    {
        _gravity = [[UIGravityBehavior alloc]init];
        _gravity.magnitude = 0.9;
    }
    return _gravity;
}

- (UICollisionBehavior *)collide
{
    if (!_collide) {
        _collide = [[UICollisionBehavior alloc]init];
        _collide.translatesReferenceBoundsIntoBoundary = YES;
    }
    return _collide;
}

- (void)addItem:(id<UIDynamicItem>)item
{
    [self.gravity addItem:item];
    [self.collide addItem:item];
    [self.itemBehavior addItem:item];
}

- (void)removeItem:(id<UIDynamicItem>)item
{
    [self.gravity removeItem:item];
    [self.collide removeItem:item];
    [self.itemBehavior removeItem:item];
}

- (instancetype)init
{
    self = [super init];
    
    [self addChildBehavior:self.gravity];
    [self addChildBehavior:self.collide];
    [self addChildBehavior:self.itemBehavior];
    
    return self;
}

@end
