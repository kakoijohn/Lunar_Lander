//
//  Identifiers.h
//  2D_RPG
//
//  Created by John Damits on 2/22/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#ifndef ___D_RPG__Identifiers__
#define ___D_RPG__Identifiers__

#include <stdio.h>

#endif /* defined(___D_RPG__Identifiers__) */

enum Identifiers:int {
    //default
    polygon_drag_start,

    polygon_move,

    polygon_rotate_right,

    polygon_rotate_left,

    //lander
    lander_rotate_right_down = 100,

    lander_rotate_right_up,

    lander_rotate_left_down,

    lander_rotate_left_up,

    lander_rocket_down,

    lander_rocket_up,

    //pause_menu
    single_click = 200,

    up,
};