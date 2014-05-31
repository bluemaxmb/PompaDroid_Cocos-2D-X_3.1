//
//  GameLayer.cpp
//  PompaDroid
//
//  Created by Matthew Barney on 5/23/14.
//
//

#include "GameLayer.h"
#include "GameScene.h"

Layer* GameLayer::createLayer()
{
    // 'layer' is an autorelease object
    auto layer = GameLayer::create();
    
    // return the layer
    return layer;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_pMap = TMXTiledMap::create("pd_tilemap.tmx");
    this->addChild(m_pMap, -6);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pd_sprites.plist");
    m_pActors = SpriteBatchNode::create("pd_sprites.pvr.ccz");
    m_pActors->getTexture()->setAliasTexParameters();
    this->addChild(m_pActors, -5);
    
    initAudio();
    initTheHero();
    initTheRobots();
    
    setTouchEnabled(true);
    
    this->scheduleUpdate();
    
    return true;
}

void GameLayer::initTheHero()
{
    m_pTheHero = (HeroSprite*)HeroSprite::createSprite();
    m_pActors->addChild(m_pTheHero);
    m_pTheHero->setPosition(Vec2(m_pTheHero->getCenterToSides(), 80));
    m_pTheHero->setDesiredPosition(m_pTheHero->getPosition());
    m_pTheHero->idle();
}

void GameLayer::initTheRobots()
{
    for (int i = 0; i < ROBOT_COUNT; i++)
    {
        RobotSprite* robot = RobotSprite::create();
        m_pActors->addChild(robot);
        m_vTheRobots.pushBack(robot);
        
        int minX = SCREEN().width + robot->getCenterToSides();
        int maxX = m_pMap->getMapSize().width * m_pMap->getTileSize().width - robot->getCenterToSides();
        int minY = robot->getCenterToBottom();
        int maxY = 3 * m_pMap->getTileSize().height + robot->getCenterToBottom();
        robot->setScaleX(-1);
        robot->setPosition(Vec2(50,50/*random_range(minX, maxX), random_range(minY, maxY)*/));
        robot->setDesiredPosition(robot->getPosition());
        robot->idle();
    }
}

void GameLayer::initAudio()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("latin_industries.aifc");
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("latin_industries.aifc");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pd_hit0.caf");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pd_hit1.caf");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pd_herodeath.caf");
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("pd_botdeath.caf");
}

void GameLayer::update(float delta)
{
    m_pTheHero->update(delta);
    updateRobots(delta);
    updatePositions();
    reorderActors();
    setViewpointCenter(m_pTheHero->getPosition());
}

// Touches
void GameLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event *unused_event)
{
    m_pTheHero->attack();
    
    if (m_pTheHero->getActionState() == kActionStateAttack)
    {
        for (Vector<RobotSprite*>::iterator robotIterator = m_vTheRobots.begin() ; robotIterator != m_vTheRobots.end(); ++robotIterator)
        {
            RobotSprite* currentRobot = (RobotSprite*)*robotIterator;
            if (currentRobot->getActionState() != kActionStateKnockedOut)
            {
                float fYDifference = fabsf(m_pTheHero->getPosition().y - currentRobot->getPosition().y);
                if (fYDifference < 10)
                {
                    Rect flippedRobotRect = currentRobot->getHitBox().actual;
                    //flippedRobotRect.size.width *= currentRobot->getScaleX();
                    
                    Rect flippedHeroRect = m_pTheHero->getAttackBox().actual;
                    //flippedHeroRect.size.width *= m_pTheHero->getScaleX();
                    
                    bool bInteresects = flippedHeroRect.intersectsRect(flippedRobotRect);
                    
                    if (bInteresects)
                    {
                        currentRobot->hurtWithDamage(m_pTheHero->getAttackDamage());
                    }
                }
            }
        }
    }
}

// Accessors
void GameLayer::setTheHudLayer(HudLayer* theHudLayer)
{
    m_pHudLayer = theHudLayer;
}

HeroSprite* GameLayer::getTheHero()
{
    return m_pTheHero;
}

// Camera
void GameLayer::setViewpointCenter(Vec2 position)
{
    Size winSize = Director::getInstance()->getWinSize();
    
    int x = MAX(position.x, winSize.width / 2);
    int y = MAX(position.y, winSize.height / 2);
    x = MIN(x, (m_pMap->getMapSize().width * m_pMap->getTileSize().width)
            - winSize.width / 2);
    y = MIN(y, (m_pMap->getMapSize().height * m_pMap->getTileSize().height)
            - winSize.height/2);
    Vec2 actualPosition = Vec2(x, y);
    
    Vec2 centerOfView = Vec2(winSize.width/2, winSize.height/2);
    Vec2 viewPoint = centerOfView - actualPosition;
    this->setPosition(viewPoint);
}

void GameLayer::updatePositions()
{
    //Hero
    float posX = MIN(m_pMap->getMapSize().width * m_pMap->getTileSize().width - m_pTheHero->getCenterToSides(),
                     MAX(m_pTheHero->getCenterToSides(), m_pTheHero->getDesiredPosition().x));
    float posY = MIN(3 * m_pMap->getTileSize().height + m_pTheHero->getCenterToBottom(),
                     MAX(m_pTheHero->getCenterToBottom(), m_pTheHero->getDesiredPosition().y));
    m_pTheHero->setPosition(Vec2(posX, posY));
    
    //Robots
    for (Vector<RobotSprite*>::iterator robotIterator = m_vTheRobots.begin() ; robotIterator != m_vTheRobots.end(); ++robotIterator)
    {
        RobotSprite* currentRobot = (RobotSprite*)*robotIterator;
        posX = MIN(m_pMap->getMapSize().width * m_pMap->getTileSize().width - currentRobot->getCenterToSides(),
                   MAX(currentRobot->getCenterToSides(), currentRobot->getDesiredPosition().x));
        posY = MIN(3 * m_pMap->getTileSize().height + currentRobot->getCenterToBottom(),
                   MAX(currentRobot->getCenterToBottom(), currentRobot->getDesiredPosition().y));
        currentRobot->setPosition(Vec2(posX, posY));
    }
}

// AI
void GameLayer::updateRobots(float dt)
{
    int alive = 0;
    float distanceSQ;
    int randomChoice = 0;
    
    for (Vector<RobotSprite*>::iterator robotIterator = m_vTheRobots.begin() ; robotIterator != m_vTheRobots.end(); ++robotIterator)
    {
        RobotSprite* currentRobot = (RobotSprite*)*robotIterator;
        
        currentRobot->update(dt);
        
        if (currentRobot->getActionState() != kActionStateKnockedOut)
        {
            //1
            alive++;
            
            //2
            if (CURTIME() > currentRobot->getNextDecisionTime())
            {
                distanceSQ = (currentRobot->getPosition() - m_pTheHero->getPosition()).getLengthSq();
                
                //3
                if (distanceSQ <= 50 * 50)
                {
                    currentRobot->setNextDecisionTime(CURTIME() + frandom_range(0.1, 0.5));
                    randomChoice = random_range(0, 1);
                    
                    if (randomChoice == 0) {
                        if (m_pTheHero->getPosition().x > currentRobot->getPosition().x)
                        {
                            currentRobot->setScaleX(1.0);
                        }
                        else
                        {
                            currentRobot->setScaleX(-1.0);
                        }
                        
                        //4
                        currentRobot->attack();
                        if (currentRobot->getActionState() == kActionStateAttack)
                        {
                            if (fabsf(m_pTheHero->getPosition().y - currentRobot->getPosition().y) < 10)
                            {
                                bool bInteresects = m_pTheHero->getHitBox().actual.intersectsRect(currentRobot->getAttackBox().actual);
                                if (bInteresects)
                                {
                                    m_pTheHero->hurtWithDamage(currentRobot->getAttackDamage());
                                    
                                    
                                    if (m_pTheHero->getActionState() == kActionStateKnockedOut &&
                                        m_pHudLayer->getChildByTag(5) == nullptr)
                                    {
                                        endGame();
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        currentRobot->idle();
                    }
                }
                else if (distanceSQ <= SCREEN().width * SCREEN().width)
                {
                    //5
                    currentRobot->setNextDecisionTime(CURTIME() + frandom_range(0.5, 1.0));
                    randomChoice = random_range(0, 2);
                    if (randomChoice == 0)
                    {
                        Vec2 moveDirection = (m_pTheHero->getPosition() - currentRobot->getPosition()).getNormalized();
                        currentRobot->walkWithDirection(moveDirection);
                    }
                    else
                    {
                        currentRobot->idle();
                    }
                }
            }
        }
    }
    
    if (alive == 0 && m_pHudLayer->getChildByTag(5) == nullptr)
    {
        endGame();
    }
}

// Sort
void GameLayer::reorderActors()
{
    // The original tutorial made use of a cocos for each macro here,
    // but that macro doesn't seem to be compatible with the new cocos::Vector type
    Vector<Node*> childNodes = m_pActors->getChildren();
    for (Vector<Node*>::iterator it = childNodes.begin() ; it != childNodes.end(); ++it)
    {
        ActionSprite *sprite = (ActionSprite*)*it;
        
        int zOrder = (m_pMap->getMapSize().height * m_pMap->getTileSize().height) - sprite->getPosition().y;
        m_pActors->reorderChild(*it, zOrder);
    }
}

// Menu
void GameLayer::endGame()
{
    Menu* pMenu = CCMenu::create();
    pMenu->setPosition(CENTER());
    
    MenuItemFont* restartLabel = MenuItemFont::create("RESTART");
    restartLabel->setFontName("Arial");
    restartLabel->setFontSize(30);
    restartLabel->setCallback(CC_CALLBACK_1(GameLayer::restartGame, this));
    
    pMenu->addChild(restartLabel);
    pMenu->setTag(5);
    
    m_pHudLayer->addChild(pMenu, 5);
}

void GameLayer::restartGame(Ref* pSender)
{
    Director::getInstance()->replaceScene(GameScene::createScene());
}