#include "HelloWorldScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;

const int TAG_PLAYER = 0;
const int TAG_TARGET = 1;
const int TAG_PROJECTILE = 2;
const int TAG_DEL = 3;
const int MAX_ESCAPE = 20;
const int MAX_KILL = 20;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void HelloWorld::addTarget()
{
    auto target = Sprite::create("Target.png", Rect(0, 0, 27, 40));
    Size winSize = Director::getInstance()->getWinSize();
    int minY = target->getContentSize().height / 2;
    int maxY = winSize.height - minY;
    int rangeY = maxY - minY;
    int actualY = rand() % rangeY + minY;
    target->setPosition(Point(winSize.width+target->getContentSize().width/2, actualY));
    target->setTag(TAG_TARGET);
    this->addChild(target);
    
    int actualDuration = rand() % 2 + 2;
    auto actionMove = MoveTo::create(actualDuration, Point(0-target->getContentSize().width/2, actualY));
    auto actionMoveDone = CallFuncN::create( [this](Node *sender)->void {
        this->removeChild(sender);
        ++escaped;
        updateEscapedLabel();
        if (escaped >= MAX_ESCAPE) {
            Director::getInstance()->replaceScene(GameOverScene::sceneWithWon(false));
        }
        
            });
    target->runAction(Sequence::create(actionMove,actionMoveDone, NULL));
}

void HelloWorld::gameLogic(float dt){
    std::cout << dt << std::endl;
    this->addTarget();
}

bool HelloWorld::onTouchBeganAddShuriken(Touch *pTouches, Event *pEvent)
{
    Point location = this->convertToNodeSpace(pTouches->getLocation());
    
    Size winSize = Director::getInstance()->getWinSize();
    Sprite *projectile = Sprite::create("Projectile.png",Rect(0,0,20,20));
    projectile->setPosition(Point(20, winSize.height/2));
    
    int offX = location.x - projectile->getPosition().x;
    int offY = location.y - projectile->getPosition().y;
    
    if (offX <= 0) {
        return false;
    }
    projectile->setTag(TAG_PROJECTILE);
    this->addChild(projectile);
    
    int realX = winSize.width + projectile->getContentSize().width/2;
    float ratio = (float)offY/(float)offX;
    int realY = ratio * (realX -  projectile->getPosition().x) + projectile->getPosition().y;
    if(realY > winSize.height + projectile->getContentSize().height/2) {
        realY = winSize.height + projectile->getContentSize().height/2;
        realX = (realY -  projectile->getPosition().y) / ratio + projectile->getPosition().x;
    }
    
    Point realDest = Point(realX,realY);
    
    int realOffX = realX - projectile->getPosition().x;
    int realOffY = realY - projectile->getPosition().y;
    int len = sqrt(realOffX*realOffX + realOffY*realOffY);
    float velocity = 300/1;//300px/s
    float realDuration = len/velocity;
    projectile->runAction(Sequence::create(
                                           MoveTo::create(realDuration, realDest)
                                           , CallFuncN::create([this](Node *sender){this->removeChild(sender);})
                                           , NULL));
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pew-pew-lei.wav");
    
    return true;
}

void HelloWorld::updateEscapedLabel() {
    char buf[32];
    sprintf(buf, "Escaped: %d/%d", escaped, MAX_ESCAPE);
    std::string s = buf;
    labelEscaped->setString(s);
}

void HelloWorld::updateKilledLabel() {
    char buf[32];
    sprintf(buf, "Killed: %d/%d", killed, MAX_KILL);
    std::string s = buf;
    labelKilled->setString(s);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(255, 255, 255, 255)) )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    Size winSize = Director::getInstance()->getWinSize();
    labelKilled = LabelTTF::create("", "Arial", 20);
    labelKilled->setColor(Color3B(0, 0, 0));
    labelKilled->setPosition(Point(winSize.width - 300, winSize.height - 25));
    this->addChild(labelKilled);
    labelEscaped = LabelTTF::create("", "Arial", 20);
    labelEscaped->setColor(Color3B(0, 0, 0));
    labelEscaped->setPosition(Point(winSize.width - 100, winSize.height - 25));
    this->addChild(labelEscaped);
    updateEscapedLabel();
    updateKilledLabel();

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    /*
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    */
    
    auto player = Sprite::create("Player.png", Rect(0, 0, 27, 40));
    player->setPosition(Point(player->getContentSize().width/2, winSize.height/2));
    player->setTag(TAG_PLAYER);
    this->addChild(player);
    
    // register touch event listener
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBeganAddShuriken, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    this->schedule(schedule_selector(HelloWorld::gameLogic), 1.0f);
    this->scheduleUpdate();
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("atkins_chet_yakety.mp3", true);
    
    killed = 0;
    escaped = 0;
    
    return true;
}

void HelloWorld::update(float delta) {
    bool hasWon = false;
    Vector<Node *> spriteList = this->getChildren();
    for (Vector<Node *>::iterator it1 = spriteList.begin(); it1 != spriteList.end(); it1++) {
        if ((*it1)->getTag() != TAG_PROJECTILE) {
            continue;
        }
        for(Vector<Node *>::iterator it2 = spriteList.begin(); it2 != spriteList.end(); it2++) {
            if ((*it2)->getTag() != TAG_TARGET) {
                continue;
            }
            if ((*it1)->getBoundingBox().intersectsRect((*it2)->getBoundingBox())) {
                (*it1)->setTag(TAG_DEL);
                (*it2)->setTag(TAG_DEL);
                if (++killed >= MAX_KILL) {
                    hasWon = true;
                }
            }
        }
    }
    
    for (Vector<Node *>::iterator it1 = spriteList.begin(); it1 != spriteList.end(); it1++) {
        if((*it1)->getTag() == TAG_DEL) {
            this->removeChild(*it1);
        }
    }
    
    updateKilledLabel();
    if(hasWon) {
        Director::getInstance()->replaceScene(GameOverScene::sceneWithWon(true));
    }
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
