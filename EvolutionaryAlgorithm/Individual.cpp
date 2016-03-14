//
//  Individual.cpp
//  Evolutionary Algorithm
//
//  Created by John Damits on 3/10/16.
//  Copyright © 2016 John Damits. All rights reserved.
//

#include "Individual.h"

Individual::Individual() : std::vector<int>(64) {
    reserve(64);
    geneLength = 64;
}

Individual::Individual(int size) : std::vector<int>(size) {
    reserve(size);
    geneLength = size;
}

float Individual::getFitness() {
    return this->fitness;
}

void Individual::setFitness(float fitness) {
    this->fitness = fitness;
}

void Individual::generateIndividual() {
    for (int i = 0; i < geneLength; i++) {
        int gene = rand() % 2;

        at(i) = gene;
    }
}

void Individual::clearIndividual() {
    clear();
    shrink_to_fit();
}

int Individual::getGene(int index) {
    return at(index);
}

void Individual::setGene(int index, int value) {
    at(index) = value;
}

int Individual::getGeneLength() {
    return geneLength;
}

std::string Individual::toString() {
    std::string gene = "";
    for (int i = 0; i < geneLength; i++)
        gene += std::to_string(at(i));

    return gene;
}