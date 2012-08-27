#ifndef _PRIMITIVE_EYES_H
#define _PRIMITIVE_EYES_H

#include "Sensor.h"
#include <vector>

class PrimitiveEyes : public Sensor {
    private:
        std::vector<Object *> nearestObjects;
    
    public:
        PrimitiveEyes();
        ~PrimitiveEyes();
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
};

#endif
