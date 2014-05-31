//
//  GameScene.cpp
//  PompaDroid
//
//  Created by Matthew Barney on 5/23/14.
//
//

#include "GameScene.h"

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = GameScene::create();
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    m_pGameLayer = (GameLayer*)GameLayer::createLayer();
    
    // add layer as a child to scene
    this->addChild(m_pGameLayer, 0);
    
    m_pHudLayer = (HudLayer*)HudLayer::createLayer();
    
    // So this is kind of icky, but the original sample made use of Obj-C's
    // to do delegates. I'm going to try and find a better solution soon.
    m_pHudLayer->getTheDPad()->setTheHero(m_pGameLayer->getTheHero());
    
    this->addChild(m_pHudLayer, 1);
    
    m_pGameLayer->setTheHudLayer(m_pHudLayer);
    
    return true;
}
