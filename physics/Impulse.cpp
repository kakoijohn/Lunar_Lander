//
//  Impulse.cpp
//  2D_RPG
//
//  Created by John Damits on 3/2/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#include "Impulse.h"

void Impulse::applyPhysics(Body& obj, CollData& cData) {
    if (obj.mass == 0)
        return;

    //http://buildnewgames.com/gamephysics/

    float dt = Clock::dt();

    //weight force y direction
    float fx = obj.mass * PhysConst::gravity.x;
    float fy = obj.mass * PhysConst::gravity.y;
    //air resistance
    fx += -1 * 0.5 * PhysConst::rhoAir * obj.dragCoef * obj.area * obj.vel.x * obj.vel.x;
    fy += -1 * 0.5 * PhysConst::rhoAir * obj.dragCoef * obj.area * obj.vel.y * obj.vel.y;

    //verlet integration
    float dx = obj.vel.x * dt + (0.5 * obj.accel.x * dt * dt);
    float dy = obj.vel.y * dt + (0.5 * obj.accel.y * dt * dt);

    obj.move({dx * 100, dy * 100});

    float new_ax = fx / obj.mass;
    float avg_ax = 0.5 * (new_ax + obj.accel.x);
    obj.vel.x += avg_ax * dt;

    float new_ay = fy / obj.mass;
    float avg_ay = 0.5 * (new_ay + obj.accel.y);
    obj.vel.y += avg_ay * dt;
}

void Impulse::resolveCollision(Body& objA, Body& objB, CollData& cData) {
    if (objA.mass == 0 && objB.mass == 0)
        return;

    if (objA.mass != 0)
        objA.move(scalar(cData.normal, -cData.MTV));
    else if (objB.mass != 0)
        objB.move(scalar(cData.normal, cData.MTV));

    Vect relVel = subtract(objB.vel, objA.vel);
    float velAlongNormal = relVel.x * cData.normal.x + relVel.y * cData.normal.y;

    if (velAlongNormal > 0)
        return;

    float e = (objA.restitution + objB.restitution) / 2;
    float j = (-(1 + e) * velAlongNormal) / (objA.invMass + objB.invMass);

    Vect impulse = {j * cData.normal.x, j * cData.normal.y};

    if (objA.mass != 0)
        objA.vel = {objA.vel.x - objA.invMass * impulse.x, objA.vel.y - objA.invMass * impulse.y};
    if (objB.mass != 0)
        objB.vel = {objB.vel.x + objB.invMass * impulse.x, objB.vel.y + objB.invMass * impulse.y};
}

void Impulse::positionalCorrection(Body& objA, Body& objB, CollData& cData) {
    //Still a work in progress. Will come back if deemed necessary.

    float percent = 0.2; // 20% to 80%
    float slop = 0.01; // .01 to .1
    float magnitude = fmaxf(cData.MTV - slop, 0.0f) / (objA.invMass + objB.invMass) * percent;
    Vect correction = {magnitude * cData.normal.x, magnitude * cData.normal.y};

    if (objA.mass != 0)
        objA.move({-objA.invMass * correction.x, -objA.invMass * correction.y});
    if (objB.mass != 0)
        objB.move({objB.invMass * correction.x, objB.invMass * correction.y});
}

Vect Impulse::add(Vect a, Vect b) {
    return {a.x + b.x, a.y + b.y};
}

Vect Impulse::subtract(Vect a, Vect b) {
    return {a.x - b.x, a.y - b.y};
}

Vect Impulse::scalar(Vect a, float s) {
    return {a.x * s, a.y * s};
}

float Impulse::dot(Vect a, Vect b) {
    return a.x * b.x + a.y * b.y;
}

float Impulse::cross(Vect a, Vect b) {
    return a.x * b.y - a.y * b.x;
}

float Impulse::distance(Vect a, Vect b) {
    return sqrtf(powf(a.x - b.x, 2) + powf(a.y - b.y, 2));
}