//
//  Body.cpp
//  2D_RPG
//
//  Created by John Damits on 3/3/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#include "Body.h"

Body::Body(int vertecies) : Polygon(vertecies) {
    
}

void Body::initializeObject() {
    setArea();
    setMoment();
    setMass();

    vel    = {0, 0};
    angVel = {0, 0};
    force  = {0, 0};
    accel  = {0, 0};
}

void Body::setArea() {
    //http://mathworld.wolfram.com/PolygonArea.html

    for (int i = 0; i < vertecies; i++) {
        if (i == vertecies - 1)
            area += this->at(i).x * this->at(0).y - this->at(0).x - this->at(i).y;
        else
            area += this->at(i).x * this->at(i + 1).y - this->at(i + 1).x - this->at(i).y;
    }

    area = fabsf(0.5f * area);
}

void Body::setMoment() {
    //http://en.wikipedia.org/wiki/Second_moment_of_area#Any_polygon

    for (int i = 0; i < vertecies; i++) {
        if (i == vertecies - 1)
            moment += (this->at(i).x * this->at(0).y + 2 * this->at(0).x * this->at(0).y + this->at(0).x * this->at(i).y) * (this->at(i).x * this->at(0).y - this->at(0).x * this->at(i).y);
        else
            moment += (this->at(i).x * this->at(i + 1).y + 2 * this->at(i + 1).x * this->at(i + 1).y + this->at(i + 1).x * this->at(i).y) * (this->at(i).x * this->at(i + 1).y - this->at(i + 1).x * this->at(i).y);
    }

    moment = fabsf((1/24) * moment);
}

void Body::setMass() {
    mass = density * area;
    if (mass == 0)
        invMass = 0;
    else
        invMass = 1 / mass;
}
