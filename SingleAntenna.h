#ifndef _SINGLE_ANTENNA_H
#define _SINGLE_ANTENNA_H

#include "Sensor.h"

class SingleAntenna : public Sensor {
    private:
        double nearestObjectDistance;
    
    public:
        SingleAntenna();
        ~SingleAntenna();
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
};

#endif
