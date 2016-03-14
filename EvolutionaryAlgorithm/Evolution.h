//
//  Evolution.h
//  Evolutionary Algorithm
//
//  Created by John Damits on 3/11/16.
//  Copyright © 2016 John Damits. All rights reserved.
//

#ifndef Evolution_h
#define Evolution_h

#include <stdio.h>

#include "Experiment.h"

#endif /* Evolution_h */

class Evolution {
public:
    void evolvePopulation(Experiment*);
    Individual crossOver(Individual, Individual);
    void mutate(Individual&);
    Individual tournamentSelection(int size);
private:
    const float uniformRate = 0.5f;
    const float mutationRate = 0.015;
    const int tournamentSize = 5;
};