//
//  ActionSprite.cpp
//  PompaDroid
//
//  Created by Matthew Barney on 5/28/14.
//
//

#include "HeroSprite.h"

Sprite* HeroSprite::createSprite()
{
    // 'sprite' is an autorelease object
    auto sprite = HeroSprite::create();
    
    // return the layer
    return sprite;
}

// on "init" you need to initialize your instance
bool HeroSprite::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Sprite::initWithSpriteFrameName("hero_idle_00.png") )
    {
        return false;
    }
    
    m_fCenterToBottom = 39.0;
    m_fCenterToSides = 29.0;
    m_fHitPoints = 100.0;
    m_fDamage = 20.0;
    m_fWalkSpeed = 80;
    
    createActions();
    
    m_hitBox = createBoundingBoxWithOrigin(Vec2(-m_fCenterToSides, -m_fCenterToBottom),
                                           Size(m_fCenterToSides * 2, m_fCenterToBottom * 2));
    
    m_attackBox = createBoundingBoxWithOrigin(Vec2(m_fCenterToSides, -10),
                                              Size(20, 20));
    
    return true;
}

void HeroSprite::update(float dt)
{
    ActionSprite::update(dt);
}

// Creation
void HeroSprite::createActions()
{
    //idle animation
    Vector<SpriteFrame*> idleFrames;
    for (int i = 0; i < 6; ++i)
    {
        char fileName[20];
        sprintf(fileName, "hero_idle_%02d.png", i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
        idleFrames.pushBack(frame);
    }
    
    Animation* idleAnimation = Animation::createWithSpriteFrames(idleFrames, 1.0/12.0);
    m_idleAction = RepeatForever::create((Animate::create(idleAnimation)));
    m_idleAction->retain();
    
    // attack animation
    Vector<SpriteFrame*> attackFrames;
    for (int i = 0; i < 3; ++i)
    {
        char fileName[20];
        sprintf(fileName, "hero_attack_00_%02d.png", i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
        attackFrames.pushBack(frame);
    }
    
    Animation* attackAnimation = Animation::createWithSpriteFrames(attackFrames, 1.0/24.0);
    
    // This is some wacky C++11 stuff that I don't really understand.
    std::function<void()> idleCB = [=]() { idle(); };
    
    m_attackAction = Sequence::create((Animate::create(attackAnimation)), CallFunc::create(idleCB), NULL);
    m_attackAction->retain();
    
    // Walk Action
    Vector<SpriteFrame*> walkFrames;
    for (int i = 0; i < 8; ++i)
    {
        char fileName[20];
        sprintf(fileName, "hero_walk_%02d.png", i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
        walkFrames.pushBack(frame);
    }
    
    Animation *walkAnimation = Animation::createWithSpriteFrames(walkFrames, 1.0/12.0);
    m_walkAction = RepeatForever::create((Animate::create(walkAnimation)));
    m_walkAction->retain();
    
    //hurt animation
    Vector<SpriteFrame*> hurtFrames;
    for (int i = 0; i < 3; ++i)
    {
        char fileName[20];
        sprintf(fileName, "hero_hurt_%02d.png", i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
        hurtFrames.pushBack(frame);
    }
    
    Animation* hurtAnimation = Animation::createWithSpriteFrames(hurtFrames, 1.0/12.0);
    m_hurtAction = Sequence::create((Animate::create(hurtAnimation)), CallFunc::create(idleCB), NULL);
    m_hurtAction->retain();
    
    //knocked out animation
    Vector<SpriteFrame*> knockedOutFrames;
    for (int i = 0; i < 5; ++i)
    {
        char fileName[25];
        sprintf(fileName, "hero_knockout_%02d.png", i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(fileName);
        knockedOutFrames.pushBack(frame);
    }
    Animation* knockedOutAnimation = Animation::createWithSpriteFrames(knockedOutFrames, 1.0/12.0);
    m_knockedOutAction = Sequence::create((Animate::create(knockedOutAnimation)), Blink::create(2.0, 10), NULL);
    m_knockedOutAction->retain();
}


//Action States
void HeroSprite::knockout()
{
    ActionSprite::knockout();
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("pd_herodeath.caf");
}

//D-Pad
void HeroSprite::didChangeDirectionTo(Vec2 direction)
{
    walkWithDirection(direction);
}

void HeroSprite::simpleDPadTouchEnded()
{
    if (m_actionState == kActionStateWalk)
    {
        idle();
    }
}

void HeroSprite::isHoldingDirection(Vec2 direction)
{
    walkWithDirection(direction);
}

