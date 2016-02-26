//
//  EventLog.cpp
//  2D_RPG
//
//  Created by John Damits on 2/8/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#include "EventLog.h"

//Event Filter
//Polls events earlier in the thread so that it updates immediately each frame with no buffer. Much more efficient than using SDL_Event.
int EventLog::EventFilter(void* userData, SDL_Event* event) {
    switch (event->type) {
        case SDL_KEYDOWN:
            SDL_Log("Key Down %d", event->key.keysym.sym);
            return 0;
        case SDL_KEYUP:
            SDL_Log("Key Up %d", event->key.keysym.sym);
            return 0;
        case SDL_MOUSEMOTION:
            SDL_Log("Mouse Moved. X=%d, Y=%d, Relative Y=%d", event->motion.x, event->motion.y, event->motion.yrel);
            return 0;
        case SDL_MOUSEBUTTONDOWN:
            SDL_Log("Mouse Button Down %d", event->button.button);
            return 0;
        case SDL_MOUSEBUTTONUP:
            SDL_Log("Mouse Button Up %d", event->button.button);
            return 0;
        case SDL_MOUSEWHEEL:
            SDL_Log("Mouse Wheel");
            return 0;

        case SDL_JOYAXISMOTION:
            SDL_Log("Controller Axis Motion. Val=%d", event->jaxis.value);
        case SDL_JOYBUTTONDOWN:
            SDL_Log("Controller Button Down: %d", event->jbutton.button);
    }

    return 1;
}
