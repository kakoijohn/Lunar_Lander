//
//  InputEvent.h
//  2D_RPG
//
//  Created by John Damits on 2/12/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#ifndef ___D_RPG__InputEvent__
#define ___D_RPG__InputEvent__

#ifndef Included_NameModel_H
#define Included_NameModel_H

#include <stdio.h>
#include "iostream"
#include "vector"

#include "SDL2/SDL.h"
#include "../data/resources/rapidjson/document.h"
#include "../data/resources/rapidjson/filestream.h"

#include "EventData.h"

#endif
#endif /* defined(___D_RPG__InputEvent__) */

class InputEvent {
public:
    static void EventFilter(SDL_Event*);
    static void loadState(const char*);
    static void loadInputContext(const char*);
    static void clearActive();

    static std::vector<eventData> events;
private:
    static void checkEvent(eventData&, SDL_Event*);
    static void addActiveEvent(eventData&, SDL_Event*);

    static rapidjson::Document KeyBindings;
};
