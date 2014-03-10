//
//  GameOverScene.cpp
//  mygame
//
//  Created by Zhui on 3/9/14.
//
//

#include "GameOverScene.h"
#include "HelloWorldScene.h"

Scene* GameOverScene::sceneWithWon(bool won)
{
    // 'scene' is an autorelease object
    Scene *scene = Scene::create();
    
    // 'layer' is an autorelease object
    GameOverScene *layer = GameOverScene::create();
    layer->initWithWon(won);
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameOverScene::initWithWon(int won){
    if (!LayerColor::initWithColor(cocos2d::Color4B(255,255,255,255))) {
        return false;
    }
    LabelTTF *label = nullptr;
    char *message;
    if (won) {
        label = LabelTTF::create("You Win\nHappy Birthday, Stephen!", "Arial", 33);
    }else{
        label = LabelTTF::create("You Lose\nHappy Birthday, Stephen!", "Arial", 33);
    }
    Size winSize = Director::getInstance()->getWinSize();
    label->setColor(Color3B(0, 0, 0));
    label->setPosition(Point(winSize.width/2, winSize.height/2));
    this->addChild(label);
    
    message = NULL;
    
    this->runAction(
                    Sequence::create(DelayTime::create(5)
                                     ,CallFunc::create(
                                                       [](){
                                                           //gameOverDone
                                                           Director::getInstance()->replaceScene(HelloWorld::createScene());
                                                       })
                                     , NULL));
    
    return true;
}