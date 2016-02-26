//
//  Display.h
//  RPGGameEngine
//
//  Created by John Damits on 8/15/14.
//  Copyright (c) 2014 Squirrely Brace. All rights reserved.
//

#ifndef __RPGGameEngine__Display__
#define __RPGGameEngine__Display__

#include <stdio.h>

#include "iostream"
#include "memory"

#include "Render.h"
#include "../events/EventLog.h"

#endif /* defined(__RPGGameEngine__Display__) */

class Display {
public:
    Display(int, int);
    int setFPS(int);
    void destroyWindow();
    static bool remainingEvents;
private:
    void createWindow(int, int);
    int FPS;
    int ticksPerFrame;
};
