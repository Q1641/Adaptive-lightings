#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include<iostream>

using std::cout;
using std::cin;

//Variables that are precalculated/fixed
const int NUM_OF_LIGHTS = 5;
const int NUM_OF_AREAS = 4;
const int E_CONSUMPTON[NUM_OF_LIGHTS] = {1, 1, 1, 1, 2};
const int A_LIGHT[NUM_OF_LIGHTS][NUM_OF_AREAS] =    {7, 3, 3, 7,
                                                     7, 7, 3, 3,
                                                     3, 7, 7, 3,
                                                     3, 3, 7, 7,
                                                     7, 7, 7, 7};
const int MAX_LIGHT_LEVEL = 10;

//Variables for genetic algorithm
const int ALPHA = 2;
const int BETA = 1;
const int DELTA = 5;
const int MAX_GENERATION = 100;
const int MAX_POPULATION = 100;

//Variable that changes
inline int S_READING[NUM_OF_AREAS] = {0, 0, 0, 0};
inline int U_DEMAND[NUM_OF_AREAS] = {77, 77, 77, 77};
inline int LIGHT_PATTERN[NUM_OF_LIGHTS] = {0, 0, 0, 0, 0};
inline int N_LIGHT[NUM_OF_AREAS] = {0, 0, 0, 0};
inline double EFFICIENCY[NUM_OF_LIGHTS][NUM_OF_AREAS];

//Data-gathering functions
void gather_data();
void calculate_natural_lights();

#endif // DATA_H_INCLUDED
