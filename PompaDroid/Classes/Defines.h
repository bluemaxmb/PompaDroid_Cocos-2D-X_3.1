//
//  Defines.h
//  PompaDroid
//
//  Created by Matthew Barney on 5/28/14.
//
//

#pragma once
#ifndef PompaDroid_Defines_h
#define PompaDroid_Defines_h

#include <time.h>

// 1 - convenience measurements
#define SCREEN() Director::getInstance()->getWinSize()
#define CENTER() Vec2(SCREEN().width/2, SCREEN().height/2)


// The original sample made use of iOS specific timer functions.
// This *should* work about the same while being platform independent.
static inline double CURTIME()
{
    time_t timer;
    time(&timer);
    return (double)timer;
}

// 2 - convenience functions
#define random_range(low,high) (arc4random()%(high-low+1))+low
#define frandom (float)arc4random()/UINT64_C(0x100000000)
#define frandom_range(low,high) ((high-low)*frandom)+low

#endif
