//
//  GameOverScene.h
//  mygame
//
//  Created by Zhui on 3/9/14.
//
//

#ifndef __mygame__GameOverScene__
#define __mygame__GameOverScene__

#include "cocos2d.h"

USING_NS_CC;

class GameOverScene:public cocos2d::LayerColor
{
public:
    bool initWithWon(int won);
    static cocos2d::Scene* sceneWithWon(bool won);
    
    CREATE_FUNC(GameOverScene);
};

#endif /* defined(__mygame__GameOverScene__) */
