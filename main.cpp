//
//  main.cpp
//  2D_RPG
//
//  Created by John Damits on 1/1/15.
//  Copyright (c) 2015 Squirrely Brace. All rights reserved.
//

#include <iostream>
#include <stdlib.h>

#include "SDL2/SDL.h"

#include <ctime>

//#include "graphics/Display.h"

#include "Evolution.h"

int main(int argc, char** argv){
    Clock::start();
    std::clock_t start;
    double duration;

    Experiment* pop = new Experiment(50);

    Evolution evol;

    int generationCount = 0;
    pop->generateNewIndividuals();
    printf("Generated First Individuals.\n");
    pop->calculateFitnesses();
    printf("Calculated Initial Fitnesses.\n");

    while (pop->getFittest().getFitness() < 0) {
        start = std::clock();

        generationCount++;
        printf("Generation: %d, Fittest: %f\n", generationCount, pop->getFittest().getFitness());
        std::cout << "\tCode: " << pop->getFittest().toString() << "\n";
        evol.evolvePopulation(pop);

        duration = (std::clock() - start ) / (double) CLOCKS_PER_SEC;
        printf("Simulation took: %f seconds to calculate.\n", duration);
    }

    printf("Solution Found.\n");
    printf("Generation: %d, Fittest: %f\n", generationCount, pop->getFittest().getFitness());
    std::cout << "Solution Code: " << pop->getFittest().toString() << "\n";

    pop->freeResources();
    delete pop;
    

    //Display d(1001, 500);
    
    return 0;
}
