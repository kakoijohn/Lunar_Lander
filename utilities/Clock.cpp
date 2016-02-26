//
//  Clock.cpp
//  2D_RPG
//
//  Created by John Damits on 2/26/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#include "Clock.h"

Uint32 Clock::currTime;
float Clock::deltaT;
float Clock::timeStep;

void Clock::start() {
    currTime = SDL_GetTicks();
}

void Clock::tick() {
    deltaT = ((SDL_GetTicks() - currTime) * .001f) * timeStep;
    currTime = SDL_GetTicks();
}

float Clock::dt() {
    return deltaT;
}
