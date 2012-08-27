#include "RandomNumberGenerator.h"

#include <ctime>
#include <cstdlib>
#include <iostream>

RandomNumberGenerator *RandomNumberGenerator::instance = 0;

RandomNumberGenerator::RandomNumberGenerator() {
    srand(time(0));    
}

RandomNumberGenerator::~RandomNumberGenerator() {
    
}

RandomNumberGenerator *RandomNumberGenerator::getInstance() {
    if (!instance) {
        instance = new RandomNumberGenerator();
    }
    return instance;
}

int RandomNumberGenerator::getInt(int min, int max) {
    int interval = max - min + 1;
    return min + int(interval * (double)rand() / ((double)RAND_MAX + 1.0));
}
