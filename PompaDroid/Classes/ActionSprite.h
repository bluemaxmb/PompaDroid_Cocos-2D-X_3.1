//
//  ActionSprite.h
//  PompaDroid
//
//  Created by Matthew Barney on 5/28/14.
//
//

#ifndef PompaDroid_ActionSprite_h
#define PompaDroid_ActionSprite_h

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

typedef enum _ActionState {
    kActionStateNone = 0,
    kActionStateIdle,
    kActionStateAttack,
    kActionStateWalk,
    kActionStateHurt,
    kActionStateKnockedOut
} ActionState;

typedef struct _BoundingBox {
    Rect actual;
    Rect original;
} BoundingBox;

class ActionSprite: public cocos2d::Sprite
{
public:
    //scheduled methods
    virtual void update(float dt) = 0;
    
    // creation
    virtual void createActions() = 0;
    
    //action methods
    virtual void idle();
    virtual void attack();
    virtual void hurtWithDamage(float damage);
    virtual void knockout();
    virtual void walkWithDirection(Vec2 direction);
    
    //accessor methods
    virtual void setPosition(const Vec2& pos);
    void setDesiredPosition(const Vec2& pos);
    Vec2 getDesiredPosition();
    void setVelocity(const Vec2& velocity);
    Vec2 getGelocity();
    
    void setCenterToSides(float centerToSides);
    float getCenterToSides();
    void setCenterToBottom(float centerToBottom);
    float getCenterToBottom();
    
    void setActionState(ActionState theState);
    ActionState getActionState();
    
    float getAttackDamage();
    
    BoundingBox getHitBox();
    BoundingBox getAttackBox();
    
private:

    
protected:
    //actions
    Action* m_idleAction;
    Action* m_attackAction;
    Action* m_walkAction;
    Action* m_hurtAction;
    Action* m_knockedOutAction;
    
    //states
    ActionState m_actionState;
    
    //attributes
    float m_fWalkSpeed;
    float m_fHitPoints;
    float m_fDamage;
    
    //movement
    Vec2 m_vVelocity;
    Vec2 m_vDesiredPosition;
    
    //measurements
    float m_fCenterToSides;
    float m_fCenterToBottom;
    
    // Collision
    BoundingBox m_hitBox;
    BoundingBox m_attackBox;
    
    BoundingBox createBoundingBoxWithOrigin(Vec2 origin, Size size);
    void transformBoxes();
};

#endif
