//
//  Lander.cpp
//  Lunar Lander
//
//  Created by John Damits on 2/27/16.
//  Copyright © 2016 Squirrely Brace. All rights reserved.
//

#include "Lander.h"

Lander::Lander() : Body(32) {
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

    resize(5);
    set({200, 50});

    dragCoef = 0;
    density = 1;
    restitution = 0.1;
    damping = -1;
    angDamp = -1;
    initializeObject();

    turnDregree = 30.0f;

    fuel = 1000.0f;
    rocketForce = .025f;

    rotate_right_on = 0;
    rotate_left_on = 0;
    rocket_on = 0;
}

void Lander::pollEvents() {
    std::vector<eventData> &events = InputEvent::events;
    for (int i  = 0; i < (int) events.size(); i++) {
        if (events.at(i).active == true) {
            if (events.at(i).identifier == lander_rotate_right_down)
                rotate_right_on = 1;
            else if (events.at(i).identifier == lander_rotate_right_up)
                rotate_right_on = 0;
            if (events.at(i).identifier == lander_rotate_left_down)
                rotate_left_on = 1;
            else if (events.at(i).identifier == lander_rotate_left_up)
                rotate_left_on = 0;
            if (events.at(i).identifier == lander_rocket_down)
                rocket_on = 1;
            else if (events.at(i).identifier == lander_rocket_up)
                rocket_on = 0;
        }
    }

    if (rotate_right_on == 1)
        rotate_right();
    if (rotate_left_on == 1)
        rotate_left();
    if (rocket_on == 1)
        rocket();
}

void Lander::rocket() {
    if (fuel > 0) {
        float forceX = rocketForce * sin(rotation);
        float forceY = -rocketForce * cos(rotation);

        vel = {vel.x + forceX, vel.y + forceY};
    }
}

void Lander::rotate_right() {
    if (fuel > 0) {
        rotate(((turnDregree * M_1_PI) / 180.0f), centroid());
//        printf("hello\n");
    }
}

void Lander::rotate_left() {
    if (fuel > 0) {
        rotate(-((turnDregree * M_1_PI) / 180.0f), centroid());
//        printf("hello\n");
    }
}
