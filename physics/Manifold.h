//
//  Manifold.h
//  2D_RPG
//
//  Created by John Damits on 3/25/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#ifndef ___D_RPG__Manifold__
#define ___D_RPG__Manifold__

#include <stdio.h>

#include "Collision.h"

#endif /* defined(___D_RPG__Manifold__) */

class Manifold {
public:
    CollData cData;

    bool colliding;

    Manifold();

    void applyInteractions(Body&, Body&);
    void interactionsLanderMoon(Body&, Body&);
private:
    bool oneCol;
};