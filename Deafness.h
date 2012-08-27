#ifndef _DEAFNESS_H
#define _DEAFNESS_H

#include "Sensor.h"

class Deafness : public Sensor {
    public:
        Deafness();
        ~Deafness();
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
};

#endif

