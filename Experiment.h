//
//  Experiment.h
//  Lunar Lander
//
//  Created by John Damits on 3/12/16.
//  Copyright © 2016 Squirrely Brace. All rights reserved.
//

#ifndef Experiment_h
#define Experiment_h

#include <stdio.h>

#include "MoonSurface.h"
#include "Population.h"

#include <thread>
#include <functional>

#endif /* Experiment_h */

class Experiment : public Population {
public:
    Experiment(int);
    void calculateFitnesses();
private:
    static void parallelCalculation(int, int);
    void serialCalculation();
};