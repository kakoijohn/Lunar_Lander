//
//  Lander.h
//  Lunar Lander
//
//  Created by John Damits on 2/27/16.
//  Copyright © 2016 Squirrely Brace. All rights reserved.
//

#ifndef Lander_h
#define Lander_h

#include <stdio.h>

#include "../physics/Manifold.h"

#endif /* Lander_hpp */

class Lander : public Body {
public:
    Lander();
    void pollEvents();
    void rocket();
    void rotate_right();
    void rotate_left();
private:
    float turnDregree;
    float fuel;
    float rocketForce;

    int rotate_right_on;
    int rotate_left_on;
    int rocket_on;
};