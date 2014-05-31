//
//  HudLayer.cpp
//  PompaDroid
//
//  Created by Matthew Barney on 5/23/14.
//
//

#include "HudLayer.h"

Layer* HudLayer::createLayer()
{
    // 'layer' is an autorelease object
    auto layer = HudLayer::create();
    
    // return the layer
    return layer;
}

// on "init" you need to initialize your instance
bool HudLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_pTheDPad = (SimpleDPad*)SimpleDPad::createSprite();
    this->addChild(m_pTheDPad);
    
    return true;
}

SimpleDPad* HudLayer::getTheDPad()
{
    return m_pTheDPad;
}