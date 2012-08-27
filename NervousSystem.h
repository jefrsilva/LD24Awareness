#ifndef _NERVOUS_SYSTEM_H
#define _NERVOUS_SYSTEM_H

#include "Sensor.h"
#include <string>
#include <allegro5/allegro.h>

class NervousSystem : public Sensor {
    private:
        static ALLEGRO_BITMAP *gradients;
        static const double FLICKER_INTERVAL = 0.1;
        double lastValue;
        double variation;
        double feedback;
        double flicker;
        bool show;
        
    public:
        NervousSystem();
        ~NervousSystem();    
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
};

#endif

