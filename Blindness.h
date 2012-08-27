#ifndef _BLINDNESS_H
#define _BLINDNESS_H

#include "Sensor.h"

class Blindness : public Sensor {
    public:
        Blindness();
        ~Blindness();
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
};

#endif
