//
//  Render.cpp
//  RPGGameEngine
//
//  Created by John Damits on 8/15/14.
//  Copyright (c) 2014 Squirrely Brace. All rights reserved.
//

#include "Render.h"

SDL_Renderer *SDLRender;
Body rectangle(4);
Body base(2);
Manifold man;

Render::Render() {

}

int Render::init(SDL_Window *window) {
    InputEvent::loadState("default");

    rectangle[0] = {0, 0};
    rectangle[1] = {0, 1};
    rectangle[2] = {1, 1};
    rectangle[3] = {1, 0};

    rectangle.resize(50);
    rectangle.set({200, 50});

    rectangle.dragCoef = 0.47;
    rectangle.density = 1;
    rectangle.restitution = 0.5;
    rectangle.damping = -1;
    rectangle.angDamp = -1;
    rectangle.initializeObject();

    base[0] = {0, 490};
    base[1] = {500, 490};

    base.density = 0;
    base.restitution = 0.5;
    base.initializeObject();

    SDLRender = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    return 0;
}

void Render::updateDisplay() {
    SDL_RenderClear(SDLRender);

    man.applyInteractions(rectangle, base);

//    if (man.colliding)
        SDL_SetRenderDrawColor(SDLRender, 255, 0, 0, 255);
//    else
//        SDL_SetRenderDrawColor(SDLRender, 0, 255, 0, 255);

//    if (Collision::isCollidingMouse(triangle))
        rectangle.pollEvents();
//    else
//        Impulse::applyPhysics(triangle, Collision::isColliding(triangle, base));

    rectangle.render(SDLRender);
    
    base.render(SDLRender);

    SDL_SetRenderDrawColor(SDLRender, 255, 255, 0, 255);
    for (int i = 0; i < man.cData.collisionPoints.size(); i++) {
        SDL_RenderDrawPoint(SDLRender, man.cData.collisionPoints[i].x, man.cData.collisionPoints[i].y);
    }

    SDL_SetRenderDrawColor(SDLRender, 0, 0, 0, 255);
    
    SDL_RenderPresent(SDLRender);
}

void Render::freeResources() {
    SDL_DestroyRenderer(SDLRender);
}

