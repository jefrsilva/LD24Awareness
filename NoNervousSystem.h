#ifndef _NO_NERVOUS_SYSTEM_H
#define _NO_NERVOUS_SYSTEM_H

#include "Sensor.h"

class NoNervousSystem : public Sensor {
    public:
        NoNervousSystem();
        ~NoNervousSystem();
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
};

#endif
