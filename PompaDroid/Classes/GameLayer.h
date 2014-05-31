//
//  GameLayer.h
//  PompaDroid
//
//  Created by Matthew Barney on 5/23/14.
//
//

#ifndef PompaDroid_GameLayer_h
#define PompaDroid_GameLayer_h

#include "cocos2d.h"
#include "HeroSprite.h"
#include "RobotSprite.h"
#include "SimpleDPad.h"
#include "HudLayer.h"
#include "Defines.h"
#include "SimpleAudioEngine.h"

#define ROBOT_COUNT 1

USING_NS_CC;

class GameLayer: public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Layer* createLayer();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);
    
    void update(float delta);
    
    //Touches
    virtual void onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event);
    
    //Accessors
    void setTheHudLayer(HudLayer* theHudLayer);
    HeroSprite* getTheHero();
    
private:
    TMXTiledMap* m_pMap;
    SpriteBatchNode *m_pActors;
    HeroSprite* m_pTheHero;
    HudLayer* m_pHudLayer;
    
    Vector<RobotSprite*> m_vTheRobots;
    
    void initTheHero();
    void initTheRobots();
    void initAudio();
    
    //Camera
    void setViewpointCenter(Vec2 position);
    void updatePositions();
    
    //AI
    void updateRobots(float delta);
    
    // Sort
    void reorderActors();
    
    // Menu
    void endGame();
    void restartGame(Ref* pSender);
};

#endif
