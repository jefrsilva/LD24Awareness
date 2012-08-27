#ifndef _PRIMITIVE_EAR_H
#define _PRIMITIVE_EAR_H

#include "Sensor.h"
#include <allegro5/allegro_audio.h>

class PrimitiveEar : public Sensor {
    private:
        static ALLEGRO_SAMPLE *sound;
        Object *nearestObject;
    
    public:
        PrimitiveEar();
        ~PrimitiveEar();
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
};

#endif
