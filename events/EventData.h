//
//  EventData.h
//  2D_RPG
//
//  Created by John Damits on 2/18/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#ifndef ___D_RPG__EventData__
#define ___D_RPG__EventData__

#include <stdio.h>

#endif /* defined(___D_RPG__EventData__) */

struct eventData {
    const char* action;
    int identifier;
    int key_binding;
    float normalization;
    int modifier;

    bool active;

    int clicks;
    float x;
    float y;
    float xrel;
    float yrel;
    float xwheel;
    float ywheel;
};