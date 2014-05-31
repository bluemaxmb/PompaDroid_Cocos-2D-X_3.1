//
//  HudLayer.h
//  PompaDroid
//
//  Created by Matthew Barney on 5/23/14.
//
//

#ifndef PompaDroid_HudLayer_h
#define PompaDroid_HudLayer_h


#include "cocos2d.h"
#include "SimpleDPad.h"

USING_NS_CC;

class HudLayer: public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Layer* createLayer();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HudLayer);
    
    //Accessors
    SimpleDPad* getTheDPad();
    
private:
    SimpleDPad* m_pTheDPad;
};


#endif
