//
//  Individual.h
//  Evolutionary Algorithm
//
//  Created by John Damits on 3/10/16.
//  Copyright © 2016 John Damits. All rights reserved.
//

#ifndef Individual_h
#define Individual_h

#include <stdio.h>

#include <vector>
#include <stdlib.h>
#include <string>

#endif /* Individual_h */

class Individual : private std::vector<int> {
public:
    Individual();
    Individual(int);
    float getFitness();
    void setFitness(float);
    void generateIndividual();
    void clearIndividual();
    int getGene(int);
    void setGene(int, int);
    int getGeneLength();
    std::string toString();
private:
    int geneLength;
    float fitness;
};