#ifndef _EYES_H
#define _EYES_H

#include "Sensor.h"
#include <vector>

class Eyes : public Sensor {
    private:
        std::vector<Object *> nearestObjects;
    
    public:
        Eyes();
        ~Eyes();
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
};

#endif
