//
//  Lander.cpp
//  Lunar Lander
//
//  Created by John Damits on 2/27/16.
//  Copyright © 2016 Squirrely Brace. All rights reserved.
//

#include "Lander.h"

Lander::Lander() : Body(32) {
    //initialize lander
    at(0)  = {4, 1};
    at(1)  = {6, 1};
    at(2)  = {7, 2};
    at(3)  = {7, 4};
    at(4)  = {6, 5};
    at(5)  = {4, 5};
    at(6)  = {6, 5};
    at(7)  = {7.5, 5};
    at(8)  = {7.5, 6};
    at(9)  = {7, 6};
    at(10) = {8, 8};
    at(11) = {8.5, 8};
    at(12) = {7.5, 8};
    at(13) = {8, 8};
    at(14) = {7, 6};
    at(15) = {6, 6};
    at(16) = {4, 6};
    at(17) = {6, 6};
    at(18) = {7, 7.3};
    at(19) = {3, 7.3};
    at(20) = {4, 6};
    at(21) = {3, 6};
    at(22) = {2, 8};
    at(23) = {2.5, 8};
    at(24) = {1.5, 8};
    at(25) = {2, 8};
    at(26) = {3, 6};
    at(27) = {2.5, 6};
    at(28) = {2.5, 5};
    at(29) = {4, 5};
    at(30) = {3, 4};
    at(31) = {3, 2};

    resize(2);
    set({200, 50});

    //initialize lander constants
    dragCoef = 0;
    density = 50;
    restitution = 0.1;
    damping = -1;
    angDamp = -1;
    initializeObject();

    turnDregree = 2.5f;

    fuel = 1000.0f;
    rocketForce = .01f;

    landSucVelRangeX = 0.075f;
    landSucVelRangeY = 0.075f;
    landSucRotRange = (5.0f * M_PI) / 180.0f;

    rotate_right_on = 0;
    rotate_left_on = 0;
    rocket_on = 0;

    points = 0;
}

void Lander::pollEvents() {
    std::vector<eventData> &events = InputEvent::events;
    for (int i  = 0; i < (int) events.size(); i++) {
        if (events.at(i).active == true) {
            if (events.at(i).identifier == lander_rotate_right_down)
                rotate_right_on = 1;
            if (events.at(i).identifier == lander_rotate_right_up)
                rotate_right_on = 0;
            if (events.at(i).identifier == lander_rotate_left_down)
                rotate_left_on = 1;
            if (events.at(i).identifier == lander_rotate_left_up)
                rotate_left_on = 0;
            if (events.at(i).identifier == lander_rocket_down)
                rocket_on = 1;
            if (events.at(i).identifier == lander_rocket_up)
                rocket_on = 0;
        }
    }

    if (rotate_right_on)
        rotate_right();
    if (rotate_left_on)
        rotate_left();
    if (rocket_on)
        rocket();
}

void Lander::rocket() {
    if (fuel > 0) {
        rocket_on = 2;

        float forceX = rocketForce * sin(rotation);
        float forceY = -rocketForce * cos(rotation);

        vel = {vel.x + forceX, vel.y + forceY};
    }
}

void Lander::rotate_right() {
    if (fuel > 0) {
        rotate(((turnDregree * M_PI) / 180.0f), centroid());
    }
}

void Lander::rotate_left() {
    if (fuel > 0) {
        rotate(-((turnDregree * M_PI) / 180.0f), centroid());
    }
}

bool Lander::hasLanded() {
    rotate_left_on = false;
    rotate_right_on = false;
    rocket_on = false;

    printf("Vel: (%f, %f), Rotation: %f\n", vel.x, vel.y, rotation);
    if (vel.y <= landSucVelRangeY && vel.y >= -landSucVelRangeY)
        if (vel.x <= landSucVelRangeX && vel.x >= -landSucVelRangeX)
            if (rotation <= landSucRotRange && rotation >= -landSucRotRange) {
                calculatePoints(1);

                rotate(-rotation, centroid());
                vel = {0.0f, 0.0f};

                return true;
            }

    calculatePoints(-1);
    return false;
}

void Lander::calculatePoints(int landStat) {
    float total = landStat;
    float multiplier;
    if (landStat)
        if (vel.x == 0)
            multiplier += 10;
        if (vel.y == 0)
            multiplier += 10;
        if (rotation == 0)
            multiplier += 10;
}

void Lander::render(SDL_Renderer *SDLRender) {
    int winWidth, winHeight;
    SDL_GetRendererOutputSize(SDLRender, &winWidth, &winHeight);
    if (at(0).x > winWidth)
        set({0, at(0).y});
    else if (at(1).x < 0)
        set({(float) winWidth, at(1).y});


    for (int i = 0; i < vertecies; i++)
        if (i == vertecies - 1)
            SDL_RenderDrawLine(SDLRender, this->at(i).x, this->at(i).y, this->at(0).x, this->at(0).y);
        else
            SDL_RenderDrawLine(SDLRender, this->at(i).x, this->at(i).y, this->at(i + 1).x, this->at(i + 1).y);

    if (rocket_on == 2) {
        Vect p1 = at(18);
        Vect p2 = at(19);
        Vect mid = {(p1.x + p2.x)/2.0f, (p1.y + p2.y)/2.0f};

        float angle = rotation + (M_PI / 2);
        float distance = 15 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(15)));

        Vect p3 = {mid.x + (distance * cosf(angle)), mid.y + (distance * sinf(angle))};

        SDL_RenderDrawLine(SDLRender, p1.x, p1.y, p3.x, p3.y);
        SDL_RenderDrawLine(SDLRender, p2.x, p2.y, p3.x, p3.y);
    }
}
