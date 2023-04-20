#ifndef GENETIC_ALGORITHM_H_INCLUDED
#define GENETIC_ALGORITHM_H_INCLUDED

#include "data.h"

class Pattern{
public:
    int pattern[NUM_OF_LIGHTS];
    double fitness;

    void calculate_fitness();
    Pattern(int* _pattern);
    Pattern();
    Pattern mate(Pattern p2);
};

bool operator<(const Pattern &p1, const Pattern &p2);

Pattern generate_pattern();
Pattern find_optimized_pattern();
void report_pattern(Pattern p);

#endif // GENETIC_ALGORITHM_H_INCLUDED
