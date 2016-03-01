//
//  Clock.cpp
//  2D_RPG
//
//  Created by John Damits on 2/26/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#include "Clock.h"

float Clock::deltaT;

void Clock::start() {
    deltaT = 1.0f / 60.0f;
}

float Clock::dt() {
    return deltaT;
}
