#include <algorithm>
#include <cmath>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include "genetic_algorithm.h"

using std::vector;

Pattern::Pattern(int* _pattern) {
    for(int i = 0; i < NUM_OF_LIGHTS; i++) {
        pattern[i] = _pattern[i];
    }
    calculate_fitness();
}

Pattern::Pattern() {
    for (int i = 0; i < NUM_OF_LIGHTS; i++) {
        pattern[i] = 0;
    }
}

Pattern Pattern::mate(Pattern p2) {
    int tmp[NUM_OF_LIGHTS];
    for (int i = 0; i < NUM_OF_LIGHTS; i++) {
        int mutation = rand() % 100;
        int mutated_value = rand() % DELTA;
        if (mutation < 10) {
            int new_gene = this->pattern[i] + mutation;
            tmp[i] = new_gene > MAX_LIGHT_LEVEL ? MAX_LIGHT_LEVEL : new_gene;
        } else if (mutation < 20) {
            int new_gene = this->pattern[i] - mutated_value;
            tmp[i] = new_gene < 0 ? 0 : new_gene;
        } else if (mutation < 60) {
            tmp[i] = this->pattern[i];
        } else {
            tmp[i] = p2.pattern[i];
        }
    }
    return Pattern(tmp);
}

void Pattern::calculate_fitness() {
    double energy = 0;
    double penalty = 0;
    for (int i = 0; i < NUM_OF_LIGHTS; i++) {
        energy += E_CONSUMPTON[i] * pattern[i];
    }
    for (int i = 0; i < NUM_OF_AREAS; i++) {
        int artificial = 0;
        for (int j = 0; j < NUM_OF_LIGHTS; j++) {
            artificial += A_LIGHT[j][i] * pattern[j];
        }
        int difference = U_DEMAND[i] - artificial - N_LIGHT[i];
        if (difference > 0) {
            penalty += pow(ALPHA, difference/BETA);
        }
    }
    fitness = energy + penalty;
}

bool operator<(const Pattern &p1, const Pattern &p2) {
    return p1.fitness < p2.fitness;
}

Pattern generate_pattern() {
    int rand_area = rand() % NUM_OF_AREAS;
    while (U_DEMAND[rand_area] <= 0) {
        rand_area = (rand_area + 1) % NUM_OF_AREAS;
    }
    int lights[NUM_OF_LIGHTS];
    for (int i = 0; i < NUM_OF_LIGHTS; i++) {
        lights[i] = 0;
    }
    int demand = U_DEMAND[rand_area] - N_LIGHT[rand_area];
    while (demand > 0) {
        int rand_light = rand() % NUM_OF_LIGHTS;
        while (lights[rand_light] == MAX_LIGHT_LEVEL) {
            rand_light = (rand_light + 1) % NUM_OF_LIGHTS;
        }
        lights[rand_light] = lights[rand_light] + 1;
        demand -= A_LIGHT[rand_light][rand_area];
    }
    return Pattern(lights);
}

Pattern find_optimized_pattern(){
    //1. Initialization
    vector <Pattern> population;
    int size = 0;
    while(size < MAX_POPULATION) {
        Pattern tmp = generate_pattern();
        population.push_back(tmp);
        size++;
    }
    int prev_gen = population[0].fitness;
    for (int i = 0; i < MAX_GENERATION; i++) {
        sort(population.begin(), population.end());
        if (population[0].fitness != prev_gen) {
            cout << "Generation no." << i + 1 << " : " << population[0].fitness << "\n";
            prev_gen = population[0].fitness;
        }
        vector <Pattern> new_population;
        int elites = MAX_POPULATION/20;
        int eliminated = MAX_POPULATION/2;
        int crossovers = MAX_POPULATION - elites;
        //adding 5% of the best samples to the next generation
        for (int j = 0; j < elites; j++) {
            new_population.push_back(population[j]);
        }
        //eliminating all the weakest ones
        for (int j = 0; j < eliminated; j++) {
            population.pop_back();
        }
        for (int j = 0; j < crossovers; j++) {
            int parent1 = rand() % eliminated;
            int parent2 = rand() % eliminated;
            Pattern child = population[parent1].mate(population[parent2]);
            new_population.push_back(child);
        }
        population = new_population;
    }
    return population[0];
}

void report_pattern(Pattern p) {
    cout << "\nProposed pattern: ";
    for (int i = 0; i < NUM_OF_LIGHTS; i++) {
        cout << p.pattern[i] << "  ";
    }
    cout << "\nLumination achieved with this pattern: ";
    for (int i = 0; i < NUM_OF_AREAS; i++) {
        int lumination = N_LIGHT[i];
        for (int j = 0; j < NUM_OF_LIGHTS; j++) {
            lumination +=  p.pattern[j] * A_LIGHT[j][i];
        }
        cout << lumination << "  ";
    }
    cout << "\nEnergy consumption: ";
    int energy = 0;
    for (int i = 0; i < NUM_OF_LIGHTS; i++) {
        energy += p.pattern[i] * E_CONSUMPTON[i];
    }
    cout << energy
         << "\nFitness score of this suggestion: " << p.fitness << "\n";
}
