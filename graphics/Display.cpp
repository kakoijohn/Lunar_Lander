//
//  Display.cpp
//  RPGGameEngine
//
//  Created by John Damits on 8/15/14.
//  Copyright (c) 2014 Squirrely Brace. All rights reserved.
//

#include "Display.h"

bool Display::remainingEvents;

Display::Display(int width, int height) {
    FPS = 60;
    ticksPerFrame = 1000 / FPS;
    createWindow(width, height);
}

//create window
void Display::createWindow(int width, int height) {
    //initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0)
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
    
    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);
    
    //create window
    SDL_Window *window = SDL_CreateWindow("RPG Game Engine", 4, 4, width, height, SDL_WINDOW_SHOWN);
    if (window == 0)
        SDL_Quit();

    //event handlers
//    SDL_AddEventWatch(EventLog::EventFilter, nullptr);
    InputEvent::loadInputContext("data/configuration/key_bindings.json");
    SDL_Event event;

    //Renderer
    std::unique_ptr<Render> render = std::unique_ptr<Render>(new Render());
    render->init(window);

    //FPS
    Uint32 fpsTimer = SDL_GetTicks();

    //Global Clock
    Clock::start();

    //Joysticks
    SDL_Joystick* gameController = nullptr;
    if (SDL_NumJoysticks() > 0)
        gameController = SDL_JoystickOpen(0);

	//display loop
    bool done = false;
    while (!done) {
        fpsTimer = SDL_GetTicks();

        SDL_PumpEvents();
        while (SDL_PollEvent(&event)) {
            InputEvent::EventFilter(&event);
            if (event.type == SDL_QUIT) {
                done = true;
                break;
            }
        }

        //Update Display
        render->updateDisplay();

        fpsTimer = SDL_GetTicks() - fpsTimer;
        if (fpsTimer < ticksPerFrame)
            SDL_Delay(ticksPerFrame - fpsTimer);
    }
    
	render->freeResources();
    SDL_JoystickClose(gameController);
    gameController = nullptr;

	//close window and clean up
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int Display::setFPS(int FPS) {
    if (FPS <= 0)
        return -1;

    this->FPS = FPS;
    ticksPerFrame = 1000 / FPS;

    return 0;
}
