//
//  GameScene.h
//  PompaDroid
//
//  Created by Matthew Barney on 5/23/14.
//
//

#ifndef PompaDroid_GameScene_h
#define PompaDroid_GameScene_h

#include "cocos2d.h"
#include "GameLayer.h"
#include "HudLayer.h"

USING_NS_CC;

class GameScene: public cocos2d::Scene
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
private:
    GameLayer* m_pGameLayer;
    HudLayer* m_pHudLayer;
};

#endif
