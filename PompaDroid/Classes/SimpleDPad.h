//
//  SimpleDPad.h
//  PompaDroid
//
//  Created by Matthew Barney on 5/28/14.
//
//

#ifndef PompaDroid_SimpleDPad_h
#define PompaDroid_SimpleDPad_h

#include "cocos2d.h"
#include "HeroSprite.h"

USING_NS_CC;

class SimpleDPad : public cocos2d::Sprite/*, public cocos2d::TargetedTouchDelegate*/
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Sprite* createSprite();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(SimpleDPad);
    
    //scheduled methods
    virtual void update(float dt);
    
    //Event handlers
    virtual void onEnterTransitionDidFinish();
    virtual void onExit();
    
    //Touches
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    
    void updateDirectionForTouchLocation(Vec2 location);
    
    //Accessors
    void setTheHero(HeroSprite* thePlayer);
    
private:
    Vec2 m_vDirection;
    float m_fRadius;
    bool m_bIsHeld;
    HeroSprite* m_pThePlayer;
    
    EventListenerTouchOneByOne* m_pEventListener;
};

#endif
