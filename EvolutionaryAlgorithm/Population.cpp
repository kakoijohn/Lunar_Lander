//
//  Population.cpp
//  Evolutionary Algorithm
//
//  Created by John Damits on 3/10/16.
//  Copyright © 2016 John Damits. All rights reserved.
//

#include "Population.h"

Population::Population(int size) : std::vector<Individual>(size) {
    reserve(size);
    this->size = size;
}

void Population::generateNewIndividuals() {
    for (int i = 0; i < size; i++) {
        Individual* ind = new Individual();
        at(i) = *ind;
        at(i).generateIndividual();
        at(i).setFitness(-1000);
    }
}

void Population::calculateFitnesses() {
    int geneLength = at(0).getGeneLength();
    for (int i = 0; i < size; i++) {
        float total = 0;
        for (int j = 0; j < geneLength; j++)
            total += at(i).getGene(j);

        at(i).setFitness(total / geneLength);
    }
}

Individual Population::getIndividual(int index) {
    return at(index);
}

Individual Population::getFittest() {
    return fittestInd;
}

void Population::setFittest() {
    Individual fittest = at(0);
    for (int i = 1; i < size; i++)
        if (at(i).getFitness() > fittest.getFitness())
            fittest = at(i);

    fittestInd = fittest;
}

void Population::setFittest(Individual ind) {
    fittestInd = ind;
}

int Population::getSize() {
    return this->size;
}

void Population::setIndividual(int index, Individual ind) {
    at(index) = ind;
}

void Population::freeResources() {
    for (int i = 0; i < size; i++)
        at(i).clearIndividual();

    this->clear();
    this->shrink_to_fit();
}

int Population::getPopSize() {
    return size;
}