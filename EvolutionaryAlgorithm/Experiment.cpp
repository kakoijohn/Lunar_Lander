//
//  Experiment.cpp
//  Lunar Lander
//
//  Created by John Damits on 3/12/16.
//  Copyright © 2016 Squirrely Brace. All rights reserved.
//

#include "Experiment.h"

Experiment expCopy(50);

Experiment::Experiment(int size) : Population(size) {
    
}

void Experiment::calculateFitnesses() {
    bool calculationInParallel = true;

    if (calculationInParallel) {
        expCopy = *this;

        std::thread thread1(parallelCalculation, 0, getPopSize() / 2);
        std::thread thread2(parallelCalculation, getPopSize() / 2, getPopSize());

        thread1.join();
        thread2.join();

        *this = expCopy;
    } else {
        serialCalculation();
    }
    
    setFittest();
}

void Experiment::parallelCalculation(int start, int finish) {
    Lander lander;
    MoonSurfaceSimple moon;
    Manifold man;
    int simulationStep = 9;


    int geneLength = expCopy.at(0).getGeneLength();
    for (int i = start; i < finish; i++) {
        lander.reset();

        for (int j = 0; j < geneLength; j++) {
            for (int k = 0; k < simulationStep; k++) {
                if (man.colliding) {
                    //printf("Individual: %d\n", i);
                    //printf("Landing Status: %d\n", lander.hasLanded());
                    //printf("Fitness: %f\n", lander.getPoints());
                    lander.hasLanded();
                    lander.getPoints();
                    break;
                } else {
                    if (expCopy.at(i).getGene(j) == 1)
                        lander.rocket();
                    man.interactionsLanderMoon(lander, moon);
                }
            }
            if (man.colliding)
                break;
        }

        //if (!man.colliding) {
        //    printf("Individual %d Timed out...", i);
        //    printf("\t\tX pos: %f, Y pos: %f\n", lander.at(0).x, lander.at(0).y);
        //}
        
        expCopy.at(i).setFitness(lander.getPoints());
    }
}

void Experiment::serialCalculation() {
    Lander lander;
    MoonSurfaceSimple moon;
    Manifold man;
    int simulationStep = 9;

    int geneLength = at(0).getGeneLength();
    for (int i = 0; i < getPopSize(); i++) {
        lander.reset();

        for (int j = 0; j < geneLength; j++) {
            for (int k = 0; k < simulationStep; k++) {
                if (man.colliding) {
                    //printf("Individual: %d\n", i);
                    //printf("Landing Status: %d\n", lander.hasLanded());
                    //printf("Fitness: %f\n", lander.getPoints());
                    lander.hasLanded();
                    lander.getPoints();
                    break;
                } else {
                    if (at(i).getGene(j) == 1)
                        lander.rocket();
                    man.interactionsLanderMoon(lander, moon);
                }
            }
            if (man.colliding)
                break;
        }

        //if (!man.colliding) {
        //    printf("Individual %d Timed out...", i);
        //    printf("\t\tX pos: %f, Y pos: %f\n", lander.at(0).x, lander.at(0).y);
        //}

        at(i).setFitness(lander.getPoints());
    }
}

