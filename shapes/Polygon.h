//
//  Polygon.h
//  2D_RPG
//
//  Created by John Damits on 2/6/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#ifndef ___D_RPG__Polygon__
#define ___D_RPG__Polygon__

#include <stdio.h>
#include "SDL2/SDL.h"

#include "math.h"

#include "../events/InputEvent.h"
#include "../events/Identifiers.h"
#include "../physics/PhysicsConstants.h"

#endif /* defined(___D_RPG__Polygon__) */

class Polygon : public std::vector<Vect> {
public:
    Polygon(int);
    Polygon();

    void addVert(Vect);

    void rotate(float, Vect);
    void setRot(float, Vect);
    void move(Vect);
    void set(Vect);
    void resize(float);
    Vect centroid();
    void render(SDL_Renderer*);
    void pollEvents();
    
    float rotation;
private:
    Vect oPolyPos;
    Vect oMousePos;
};
