//
//  Evolution.cpp
//  Evolutionary Algorithm
//
//  Created by John Damits on 3/11/16.
//  Copyright © 2016 John Damits. All rights reserved.
//

#include "Evolution.h"

void Evolution::evolvePopulation(Experiment* pop) {
    Experiment* newPop = new Experiment(pop->getSize());
    
    Individual fittest = pop->getFittest();
    mutate(fittest);

    newPop->setIndividual(0, fittest);

    bool foundSolution = false;
    for (int i = 1; i < pop->getSize(); i++) {
        Individual ind1 = tournamentSelection(pop->getSize());
        Individual ind2 = tournamentSelection(pop->getSize());

        if (ind1.getFitness() > 0) {
            newPop->setIndividual(i, ind1);
            newPop->setFittest(ind1);
            foundSolution = true;
            break;
        } else if (ind2.getFitness() > 0) {
            newPop->setIndividual(i, ind2);
            newPop->setFittest(ind2);
            foundSolution = true;
            break;
        } else {
            Individual newInd = crossOver(ind1, ind2);
            mutate(newInd);

            newPop->setIndividual(i, newInd);
        }
    }

    if (!foundSolution)
        newPop->calculateFitnesses();

    pop->freeResources();

    *pop = *newPop;
}

Individual Evolution::crossOver(Individual ind1, Individual ind2) {
    Individual* newSol = new Individual();
    
    for (int i = 0; i < ind1.getGeneLength(); i++) {
        float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        if (random <= uniformRate)
            newSol->setGene(i, ind1.getGene(i));
        else
            newSol->setGene(i, ind2.getGene(i));
    }

    return *newSol;
}

void Evolution::mutate(Individual& ind) {
    for (int i = 0; i < ind.getGeneLength(); i++) {
        float random = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        if (random <= mutationRate) {
            int gene = rand() % 2;
            ind.setGene(i, gene);
        }
    }
}

Individual Evolution::tournamentSelection(int size) {
    Experiment* tournament = new Experiment(size);
    tournament->generateNewIndividuals();
    tournament->calculateFitnesses();

    Individual fittest = tournament->getFittest();

    tournament->freeResources();
    delete tournament;

    return fittest;
}
