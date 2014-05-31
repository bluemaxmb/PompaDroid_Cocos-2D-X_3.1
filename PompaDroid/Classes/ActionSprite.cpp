//
//  ActionSprite.cpp
//  PompaDroid
//
//  Created by Matthew Barney on 5/28/14.
//
//

#include "ActionSprite.h"
#include "Defines.h"

void ActionSprite::update(float dt)
{
    if (m_actionState == kActionStateWalk)
    {
        m_vDesiredPosition = this->getPosition() + (m_vVelocity * dt);
    }
}

//
void ActionSprite::idle()
{
    if (m_actionState != kActionStateIdle)
    {
        stopAllActions();
        runAction(m_idleAction);
        m_actionState = kActionStateIdle;
        m_vVelocity = Vec2::ZERO;
    }
}

void ActionSprite::attack()
{
    if (m_actionState == kActionStateIdle || m_actionState == kActionStateAttack || m_actionState == kActionStateWalk)
    {
        stopAllActions();
        runAction(m_attackAction);
        m_actionState = kActionStateAttack;
    }
}

void ActionSprite::hurtWithDamage(float damage)
{
    if (m_actionState != kActionStateKnockedOut)
    {
        stopAllActions();
        runAction(m_hurtAction);
        m_actionState = kActionStateHurt;
        m_fHitPoints -= damage;
        
        int randomSound = random_range(0, 1);
        
        char fileName[20];
        sprintf(fileName, "pd_hit%d.caf", randomSound);
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(fileName);
        
        if (m_fHitPoints <= 0.0) {
            knockout();
        }
    }
}

void ActionSprite::knockout()
{
    stopAllActions();
    runAction(m_knockedOutAction);
    m_fHitPoints = 0.0;
    m_actionState = kActionStateKnockedOut;
}

void ActionSprite::walkWithDirection(Vec2 direction)
{
    if (m_actionState == kActionStateIdle)
    {
        stopAllActions();
        runAction(m_walkAction);
        m_actionState = kActionStateWalk;
    }
    if (m_actionState == kActionStateWalk)
    {
        m_vVelocity = Vec2(direction.x * m_fWalkSpeed, direction.y * m_fWalkSpeed);
        if (m_vVelocity.x >= 0)
        {
            this->setScaleX(1.0);
        }
        else
        {
            this->setScaleX(-1.0);
        }
    }
}

// Accessors
void ActionSprite::setPosition(const Vec2& pos)
{
    Sprite::setPosition(pos);
    transformBoxes();
}
void ActionSprite::setDesiredPosition(const Vec2& pos)
{
    m_vDesiredPosition = pos;
}

Vec2 ActionSprite::getDesiredPosition()
{
    return m_vDesiredPosition;
}

void ActionSprite::setVelocity(const Vec2& velocity)
{
    m_vVelocity = velocity;
}

Vec2 ActionSprite::getGelocity()
{
    return m_vVelocity;
}

void ActionSprite::setCenterToSides(float centerToSides)
{
    m_fCenterToSides = centerToSides;
}

float ActionSprite::getCenterToSides()
{
    return m_fCenterToSides;
}

void ActionSprite::setCenterToBottom(float centerToBottom)
{
    m_fCenterToBottom = centerToBottom;
}

float ActionSprite::getCenterToBottom()
{
    return m_fCenterToBottom;
}

void ActionSprite::setActionState(ActionState theState)
{
    m_actionState = theState;
}

ActionState ActionSprite::getActionState()
{
    return m_actionState;
}

float ActionSprite::getAttackDamage()
{
    return m_fDamage;
}

BoundingBox ActionSprite::getHitBox()
{
    return m_hitBox;
}

BoundingBox ActionSprite::getAttackBox()
{
    return m_attackBox;
}

// HitBox
BoundingBox ActionSprite::createBoundingBoxWithOrigin(Vec2 origin, Size size)
{
    BoundingBox boundingBox;
    boundingBox.original.origin = origin;
    boundingBox.original.size = size;
    boundingBox.actual.origin = getPosition() + Vec2(boundingBox.original.origin.x, boundingBox.original.origin.y);
    boundingBox.actual.size = size;
    return boundingBox;
}

void ActionSprite::transformBoxes()
{
    m_hitBox.actual.origin = getPosition() + Vec2(m_hitBox.original.origin.x * getScaleX(),
                                                  m_hitBox.original.origin.y * getScaleY());
    m_hitBox.actual.size = Size(m_hitBox.original.size.width * getScaleX(),
                                m_hitBox.original.size.height * getScaleY());
  
    m_attackBox.actual.origin = getPosition() + Vec2(m_attackBox.original.origin.x * getScaleX(),
                                                     m_attackBox.original.origin.y * getScaleY());
    m_attackBox.actual.size = Size(m_attackBox.original.size.width * getScaleX(),
                                   m_attackBox.original.size.height * getScaleY());
}
