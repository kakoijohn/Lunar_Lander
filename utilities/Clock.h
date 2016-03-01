//
//  Clock.h
//  2D_RPG
//
//  Created by John Damits on 2/26/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#ifndef ___D_RPG__Clock__
#define ___D_RPG__Clock__

#include <stdio.h>

#include "SDL2/SDL.h"

#endif /* defined(___D_RPG__Clock__) */

class Clock {
public:
    static void start();
    static float dt();

private:
    static float deltaT;
};