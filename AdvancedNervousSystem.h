#ifndef _ADVANCED_NERVOUS_SYSTEM_H
#define _ADVANCED_NERVOUS_SYSTEM_H

#include "Sensor.h"
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

class AdvancedNervousSystem : public Sensor {
    private:
        static ALLEGRO_BITMAP *gradients;
        static const double FLICKER_INTERVAL = 0.1;
        double lastValue;
        double variation;
        double feedback;
        double flicker;
        bool show;
        
    public:
        AdvancedNervousSystem();
        ~AdvancedNervousSystem();    
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
};

#endif

