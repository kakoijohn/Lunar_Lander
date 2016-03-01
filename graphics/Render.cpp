//
//  Render.cpp
//  RPGGameEngine
//
//  Created by John Damits on 8/15/14.
//  Copyright (c) 2014 Squirrely Brace. All rights reserved.
//

#include "Render.h"

SDL_Renderer *SDLRender;
Lander lander;
Body base(4);
Manifold man;

Render::Render() {

}

int Render::init(SDL_Window *window) {
    InputEvent::loadState("lander");

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
    //lander.rotate(((10.0f * M_1_PI) / 180.0f), lander.centroid());
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
//    printf("%f\n", lander.rotation);

    SDL_SetRenderDrawColor(SDLRender, 0, 0, 0, 255);
    
    SDL_RenderPresent(SDLRender);
}

void Render::freeResources() {
    SDL_DestroyRenderer(SDLRender);
}

