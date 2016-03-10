//
//  PhysicsConstants.cpp
//  2D_RPG
//
//  Created by John Damits on 3/3/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#include "PhysicsConstants.h"

Vect PhysConst::gravity = {0, 0.5f};//9.8m/s^2 on earth, 1.622m/s^2 on moon
float PhysConst::rhoAir  = 0.0f;//1.2f on earth, 0 on moon