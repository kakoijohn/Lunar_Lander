//
//  Render.cpp
//  RPGGameEngine
//
//  Created by John Damits on 8/15/14.
//  Copyright (c) 2014 Squirrely Brace. All rights reserved.
//

#include "Render.h"

SDL_Renderer *SDLRender;
Body lander(32);
Body base(4);
Manifold man;

Render::Render() {

}

int Render::init(SDL_Window *window) {
    InputEvent::loadState("default");

    lander[0]  = {4, 1};
    lander[1]  = {6, 1};
    lander[2]  = {7, 2};
    lander[3]  = {7, 4};
    lander[4]  = {6, 5};
    lander[5]  = {4, 5};
    lander[6]  = {6, 5};
    lander[7]  = {7.5, 5};
    lander[8]  = {7.5, 6};
    lander[9]  = {7, 6};
    lander[10] = {8, 8};
    lander[11] = {8.5, 8};
    lander[12] = {7.5, 8};
    lander[13] = {8, 8};
    lander[14] = {7, 6};
    lander[15] = {6, 6};
    lander[16] = {4, 6};
    lander[17] = {6, 6};
    lander[18] = {7, 7.3};
    lander[19] = {3, 7.3};
    lander[20] = {4, 6};
    lander[21] = {3, 6};
    lander[22] = {2, 8};
    lander[23] = {2.5, 8};
    lander[24] = {1.5, 8};
    lander[25] = {2, 8};
    lander[26] = {3, 6};
    lander[27] = {2.5, 6};
    lander[28] = {2.5, 5};
    lander[29] = {4, 5};
    lander[30] = {3, 4};
    lander[31] = {3, 2};

    lander.resize(5);
    lander.set({200, 50});

    lander.dragCoef = 0.47;
    lander.density = 1;
    lander.restitution = 0.1;
    lander.damping = -1;
    lander.angDamp = -1;
    lander.initializeObject();

    base[0] = {0, 490};
    base[1] = {500, 490};
    base[2] = {500, 700};
    base[3] = {0, 700};

    base.density = 0;
    base.restitution = 0.5;
    base.initializeObject();

    SDLRender = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    return 0;
}

void Render::updateDisplay() {
    SDL_RenderClear(SDLRender);

    man.applyInteractions(lander, base);

//    if (man.colliding)
        SDL_SetRenderDrawColor(SDLRender, 255, 0, 0, 255);
//    else
//        SDL_SetRenderDrawColor(SDLRender, 0, 255, 0, 255);

//    if (Collision::isCollidingMouse(triangle))
        lander.pollEvents();
//    else
//        Impulse::applyPhysics(triangle, Collision::isColliding(triangle, base));

    lander.render(SDLRender);
    
    base.render(SDLRender);

    SDL_SetRenderDrawColor(SDLRender, 255, 255, 0, 255);
    for (int i = 0; i < man.cData.collisionPoints.size(); i++) {
        SDL_RenderDrawPoint(SDLRender, man.cData.collisionPoints[i].x, man.cData.collisionPoints[i].y);
    }

//    printf("%f, %f\n", lander.at(0).x, lander.at(0).y);
//    printf("%f, %f\n", lander.vel.x, lander.vel.y);

    SDL_SetRenderDrawColor(SDLRender, 0, 0, 0, 255);
    
    SDL_RenderPresent(SDLRender);
}

void Render::freeResources() {
    SDL_DestroyRenderer(SDLRender);
}

