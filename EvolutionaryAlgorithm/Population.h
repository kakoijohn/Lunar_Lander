//
//  Population.h
//  Evolutionary Algorithm
//
//  Created by John Damits on 3/10/16.
//  Copyright © 2016 John Damits. All rights reserved.
//

#ifndef Population_h
#define Population_h

#include <stdio.h>

#include "Individual.h"

#endif /* Population_h */

class Population : public std::vector<Individual> {
public:
    Population(int);
    void generateNewIndividuals();
    Individual getIndividual(int);
    Individual getFittest();
    void setFittest(Individual);
    void setFittest();
    void calculateFitnesses();
    int getSize();
    void setIndividual(int, Individual);
    void freeResources();
    int getPopSize();
private:
    int size;
    Individual fittestInd;
};