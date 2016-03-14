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

#include "Manifold.h"

#endif /* Lander_hpp */

class Lander : public Body {
public:
    Lander();
    void pollEvents();
    void rocket();
    void rotate_right();
    void rotate_left();
    void render(SDL_Renderer*);
    bool hasLanded();
    float getPoints();
    void reset();
private:
    void calculatePoints(int);
    float points;

    float turnDregree;
    float fuel;
    float rocketForce;

    float landSucVelRangeX;
    float landSucVelRangeY;
    float landSucRotRange;

    int rotate_right_on;
    int rotate_left_on;
    int rocket_on;
};