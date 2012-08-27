#ifndef _TRIPLE_ANTENNA_H
#define _TRIPLE_ANTENNA_H

#include "Sensor.h"
#include "Vector2D.h"

class TripleAntenna : public Sensor {
    private:
        Object *nearestObject;
        Vector2D nearestObjectPosition;
    
    public:
        TripleAntenna();
        ~TripleAntenna();
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
};

#endif
