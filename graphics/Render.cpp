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
MoonSurfaceSimple moon;
Manifold man;

Render::Render() {
    
}

int Render::init(SDL_Window *window) {
    InputEvent::loadState("lander");

    SDLRender = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    return 0;
}

void Render::updateDisplay() {
    SDL_RenderClear(SDLRender);

    if (man.colliding) {
        printf("Landing Status: %d\n", lander.hasLanded());
        printf("Fitness: %f\n", lander.getPoints());
    } else {
        lander.pollEvents();
        man.interactionsLanderMoon(lander, moon);
    }

    SDL_SetRenderDrawColor(SDLRender, 255, 255, 255, 255);
    lander.render(SDLRender);
    moon.render(SDLRender);

//    SDL_SetRenderDrawColor(SDLRender, 255, 255, 0, 255);
//    for (int i = 0; i < (int) man.cData.collisionPoints.size(); i++) {
//        SDL_RenderDrawPoint(SDLRender, man.cData.collisionPoints[i].x, man.cData.collisionPoints[i].y);
//    }

//    printf("%f, %f\n", lander.at(0).x, lander.at(0).y);
//    printf("%f, %f\n", lander.vel.x, lander.vel.y);
//    printf("%f\n", lander.rotation);

    SDL_SetRenderDrawColor(SDLRender, 0, 0, 0, 255);
    
    SDL_RenderPresent(SDLRender);
}

void Render::freeResources() {
    SDL_DestroyRenderer(SDLRender);
}

