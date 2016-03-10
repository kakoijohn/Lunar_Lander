//
//  Manifold.cpp
//  2D_RPG
//
//  Created by John Damits on 3/25/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#include "Manifold.h"

Manifold::Manifold() {
    colliding = false;
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
        //Impulse::positionalCorrection(objA, objB, cData);
    }
}

Body moonPart(2);

void Manifold::interactionsLanderMoon(Body& lander, Body& moon) {
    for (int i = 0; i < moon.vertecies - 1; i++) {
        moonPart[0] = moon[i];
        moonPart[1] = moon[i + 1];

        cData = Collision::isCollidingMTV(lander, moonPart);

        if (cData.MTV == -1)
            oneCol = false;
        else
            oneCol = true;

        if (oneCol) {
            Impulse::resolveCollision(lander, moon, cData);

            colliding = true;
        }
    }

    Impulse::applyPhysics(lander, cData);
}