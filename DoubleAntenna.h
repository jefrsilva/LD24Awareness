#ifndef _DOUBLE_ANTENNA_H
#define _DOUBLE_ANTENNA_H

#include "Sensor.h"
#include "Vector2D.h"

class DoubleAntenna : public Sensor {
    private:
        Object *nearestObject;
        Vector2D nearestObjectDistance;
    
    public:
        DoubleAntenna();
        ~DoubleAntenna();
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
};

#endif
