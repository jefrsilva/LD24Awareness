#include "NervousSystem.h"
#include "Environment.h"
#include "Object.h"

#include <cmath>

ALLEGRO_BITMAP *NervousSystem::gradients = 0;

NervousSystem::NervousSystem() : Sensor("SENSOR_NERVOUS_SYSTEM"){
    if (!gradients) {
        gradients = al_load_bitmap("gradients.png");
    }
    
    lastValue = 0.0;
    variation = 0.0;
    feedback = 0.0;
    flicker = 0.0;
    show = false;
}

NervousSystem::~NervousSystem() {
    
}

void NervousSystem::handleStimulus(Object *object, Environment *environment, double dt) {
    double curValue = object->getEnergy();
    variation = curValue - lastValue;
    if (object->getEnergy() <= 50.0 || object->getEnergy() >= 100.0) {
        feedback += 16.0 * dt;
    } else {    
        feedback -= 16.0 * dt;
    }
    if (feedback < 0.0) {
        feedback = 0.0;
    }
    if (feedback > 64.0) {
        feedback = 64.0;
    }
    lastValue = curValue;
    
    flicker -= dt;
    while (flicker < 0.0) {
        show = show ? false : true;
        flicker += FLICKER_INTERVAL;            
    }
}

void NervousSystem::renderFeedback(Object *object, Environment *environment) {
    if (object == environment->getPlayer()) {
        ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
        if (object->getEnergy() <= 50.0) {
            color = al_map_rgb(255, 0, 0);
        } else if (object->getEnergy() >= 100.0) {
            color = al_map_rgb(255, 255, 0);            
        }
        
        al_draw_tinted_scaled_bitmap(gradients,
                              color, 
                              1, 0, 1, 64, 
                              0, -64 + (int)feedback, Environment::SCREEN_WIDTH, 64, 0);        
        al_draw_tinted_scaled_bitmap(gradients, 
                              color,        
                              0, 0, 1, 64, 
                              0, Environment::SCREEN_HEIGHT - (int)feedback, Environment::SCREEN_WIDTH, 64, 0);  
    }
}

Sensor *NervousSystem::clone() {
    return new NervousSystem();
}
