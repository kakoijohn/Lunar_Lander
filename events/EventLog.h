//
//  EventLog.h
//  2D_RPG
//
//  Created by John Damits on 2/8/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#ifndef ___D_RPG__EventLog__
#define ___D_RPG__EventLog__

#include <stdio.h>

#include "iostream"

#include "SDL2/SDL.h"

#endif /* defined(___D_RPG__EventLog__) */

class EventLog {
public:
    static int EventFilter(void*, SDL_Event*);
};