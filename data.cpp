#include "data.h"

void gather_data() {
    cout << "There are " << NUM_OF_LIGHTS << " light(s) and " << NUM_OF_AREAS << " sensor(s)";
    cout << "\nCurrent light pattern: \n";
    for (int i = 0; i < NUM_OF_LIGHTS; i++) {
        cin >> LIGHT_PATTERN[i];
    }
    cout << "\nCurrent sensor readings: \n";
    for (int i = 0; i < NUM_OF_AREAS; i++) {
        cin >> S_READING[i];
    }
    cout << "\nUser demands at each area: \n";
    for (int i = 0; i < NUM_OF_AREAS; i++) {
        cin >> U_DEMAND[i];
    }
    cout << "\n";
    for (int i = 0; i < NUM_OF_LIGHTS; i++) {
        for (int j = 0; j < NUM_OF_AREAS; j++) {
            EFFICIENCY[i][j] = A_LIGHT[i][j] * 1.0 / E_CONSUMPTON[i];
        }
    }
}

void calculate_natural_lights() {
    for (int i = 0; i < NUM_OF_AREAS; i++) {
        int artificial = 0;
        for (int j = 0; j < NUM_OF_LIGHTS; j++) {
            artificial += LIGHT_PATTERN[j] * A_LIGHT[i][j];
        }
        N_LIGHT[i] = S_READING[i] - artificial;
    }
}
