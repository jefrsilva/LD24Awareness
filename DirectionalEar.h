#ifndef _DIRECTIONAL_EAR_H
#define _DIRECTIONAL_EAR_H

#include "Sensor.h"
#include "Vector2D.h"
#include <allegro5/allegro_audio.h>

class DirectionalEar : public Sensor {
    private:
        static ALLEGRO_SAMPLE *sound;
        Object *nearestObject;
        Vector2D nearestObjectPosition;
    
    public:
        DirectionalEar();
        ~DirectionalEar();
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
};

#endif

