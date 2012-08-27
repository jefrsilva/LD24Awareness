#ifndef _MULTI_TRIPLE_ANTENNA_H
#define _MULTI_TRIPLE_ANTENNA_H

#include "Sensor.h"
#include <vector>

class MultiTripleAntenna : public Sensor {
    private:
        std::vector<Object *> nearestObjects;
    
    public:
        MultiTripleAntenna();
        ~MultiTripleAntenna();
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
};

#endif
