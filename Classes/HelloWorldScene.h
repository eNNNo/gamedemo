#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::LayerColor
{
private:
    int killed;
    int escaped;
    
    cocos2d::LabelTTF *labelKilled;
    cocos2d::LabelTTF *labelEscaped;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void addTarget();
    void gameLogic(float dt);
    void update(float delta);
    
    void updateKilledLabel();
    void updateEscapedLabel();
    
    bool onTouchBeganAddShuriken(cocos2d::Touch *pTouches, cocos2d::Event *pEvent);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
