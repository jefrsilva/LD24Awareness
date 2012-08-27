#ifndef _MULTI_DIRECTIONAL_EAR_H
#define _MULTI_DIRECTIONAL_EAR_H

#include "Sensor.h"
#include "Vector2D.h"
#include <vector>
#include <allegro5/allegro_audio.h>

class MultiDirectionalEar : public Sensor {
    private:
        std::vector<Object *> nearestObjects;
   
    public:
        MultiDirectionalEar();
        ~MultiDirectionalEar();
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
};

#endif

