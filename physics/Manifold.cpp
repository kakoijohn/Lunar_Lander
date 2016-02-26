//
//  Manifold.cpp
//  2D_RPG
//
//  Created by John Damits on 3/25/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#include "Manifold.h"

Manifold::Manifold() {

}

void Manifold::applyInteractions(Body& objA, Body& objB) {
    cData = Collision::isCollidingMTV(objA, objB);

    if (cData.MTV == -1)
        colliding = false;
    else
        colliding = true;

    Impulse::applyPhysics(objA, cData);
    Impulse::applyPhysics(objB, cData);

    if (colliding) {
        Impulse::resolveCollision(objA, objB, cData);
        Impulse::positionalCorrection(objA, objB, cData);
    }
}