//
//  ActionSprite.h
//  PompaDroid
//
//  Created by Matthew Barney on 5/28/14.
//
//

#ifndef PompaDroid_HeroSprite_h
#define PompaDroid_HeroSprite_h

#include "ActionSprite.h"

USING_NS_CC;

class HeroSprite: public ActionSprite
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Sprite* createSprite();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HeroSprite);
    
    //scheduled methods
    virtual void update(float dt);
    
    //creation
    virtual void createActions();
    
    //action methods
    virtual void knockout();
    
    //D-Pad
    void didChangeDirectionTo(Vec2 direction);
    void simpleDPadTouchEnded();
    void isHoldingDirection(Vec2 direction);
private:
};

#endif
