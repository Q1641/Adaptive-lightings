#include <ctime>
#include "data.h"
#include "genetic_algorithm.h"

int main() {
    srand(time(0));
    //gather_data();
    //calculate_natural_lights();
    Pattern best_pattern = find_optimized_pattern();
    report_pattern(best_pattern);
    return 0;
}
