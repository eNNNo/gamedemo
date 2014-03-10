//
//  UIBeizerPathView.m
//  DropIt
//
//  Created by Chao Wu on 3/3/14.
//  Copyright (c) 2014 Chao Wu. All rights reserved.
//

#import "UIBeizerPathView.h"

@implementation UIBeizerPathView

- (void) setPath:(UIBezierPath *)path
{
    _path = path;
    [self setNeedsDisplay];
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code
    }
    return self;
}


// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect
{
    // Drawing code
    [self.path stroke];
}


@end
