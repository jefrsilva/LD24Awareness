#ifndef _DISTANCE_EAR_H
#define _DISTANCE_EAR_H

#include "Sensor.h"
#include <allegro5/allegro_audio.h>

class DistanceEar : public Sensor {
    private:
        static ALLEGRO_SAMPLE *sound;
        Object *nearestObject;
        double nearestObjectDistance;        
    
    public:
        DistanceEar();
        ~DistanceEar();
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
};

#endif
