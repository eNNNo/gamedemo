//
//  ViewController.m
//  DropIt
//
//  Created by Chao Wu on 3/1/14.
//  Copyright (c) 2014 Chao Wu. All rights reserved.
//

#import "ViewController.h"
#import "DropBehavior.h"
#import "UIBeizerPathView.h"

@interface ViewController () <UIDynamicAnimatorDelegate>
@property (weak, nonatomic) IBOutlet UIBeizerPathView *gameView;
@property (nonatomic,strong) UIDynamicAnimator *animator;
@property (nonatomic,strong) DropBehavior *dropbehavior;
@property (nonatomic,strong) UIView *droppingView;
@property (nonatomic,strong) UIAttachmentBehavior *attachment;
@end

@implementation ViewController

#define DEFAULT_BOX_WIDTH 40

- (UIDynamicAnimator *) animator
{
    if (!_animator) {
        _animator = [[UIDynamicAnimator alloc]initWithReferenceView:self.gameView];
        _animator.delegate = self;
       
    }
    return _animator;
}

- (DropBehavior *) dropbehavior
{
    if (!_dropbehavior)
    {
        _dropbehavior = [[DropBehavior alloc]init];
        [self.animator addBehavior:_dropbehavior];
    }
    return _dropbehavior;
}

- (void) dynamicAnimatorDidPause:(UIDynamicAnimator *)animator
{
    [self eraseFilledRow];
}

- (void) eraseFilledRow
{
    
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)tap:(UITapGestureRecognizer *)sender {
    [self drop];
}
- (IBAction)pan:(UIPanGestureRecognizer *)sender {
    CGPoint guesturePos = [sender locationInView:self.gameView];
    if (sender.state == UIGestureRecognizerStateBegan) {
        [self attachDroptoAnchor:guesturePos];
    }
    
    else if(sender.state == UIGestureRecognizerStateChanged)
    {
        self.attachment.anchorPoint = guesturePos;
    }
    
    else if(sender.state == UIGestureRecognizerStateEnded)
    {
        [self.animator removeBehavior:self.attachment];
        self.gameView.path = nil;
    }
}

- (void) attachDroptoAnchor:(CGPoint) anchor
{
    if (self.droppingView)
    {
        self.attachment = [[UIAttachmentBehavior alloc]initWithItem:self.droppingView attachedToAnchor:anchor];
        __weak ViewController* weakSelf = self;
        UIView *droppingview = self.droppingView;
        self.attachment.action =^{
            UIBezierPath *path = [[UIBezierPath alloc]init];
            [path moveToPoint:droppingview.center];
            [path addLineToPoint:weakSelf.attachment.anchorPoint];
            weakSelf.gameView.path = path;
        };
        self.droppingView = nil;
        [self.animator addBehavior:self.attachment];
    }
}

- (void) drop
{
    CGRect frame;
    frame.origin = CGPointZero;
    frame.size = CGSizeMake(DEFAULT_BOX_WIDTH, DEFAULT_BOX_WIDTH);
    
    frame.origin.x = (arc4random()%(int)self.gameView.bounds.size.width)/DEFAULT_BOX_WIDTH;
    
    frame.origin.x *= DEFAULT_BOX_WIDTH;
    
    UIView *dropView = [[UIView alloc]initWithFrame:frame];
    dropView.backgroundColor = [self randomColor];
    
    [self.gameView addSubview:dropView];
    [self.dropbehavior addItem:dropView];
    self.droppingView = dropView;
    
    
}

- (UIColor *) randomColor
{
    int rand = arc4random()%5;
    
    switch (rand) {
        case 0:
            return [UIColor blackColor];
        case 1:
            return [UIColor redColor];
        case 2:
            return [UIColor blueColor];
        case 3:
            return [UIColor yellowColor];
        case 4:
            return [UIColor greenColor];
        default:
            return nil;
    }
}

@end
