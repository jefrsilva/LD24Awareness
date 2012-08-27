#ifndef _MULTI_SINGLE_ANTENNA_H
#define _MULTI_SINGLE_ANTENNA_H

#include "Sensor.h"
#include <vector>

class MultiSingleAntenna : public Sensor {
    private:
        std::vector<Object *> nearestObjects;
    
    public:
        MultiSingleAntenna();
        ~MultiSingleAntenna();
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
};

#endif
