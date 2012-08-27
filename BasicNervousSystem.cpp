#include "BasicNervousSystem.h"
#include "Environment.h"
#include "Object.h"

#include <cmath>

ALLEGRO_BITMAP *BasicNervousSystem::gradients = 0;

BasicNervousSystem::BasicNervousSystem() : Sensor("SENSOR_BASIC_NERVOUS_SYSTEM") {
    if (!gradients) {
        gradients = al_load_bitmap("gradients.png");
    }
    
    lastValue = 0.0;
    variation = 0.0;
    feedback = 0.0;
    flicker = 0.0;
    show = false;
}

BasicNervousSystem::~BasicNervousSystem() {
    
}

void BasicNervousSystem::handleStimulus(Object *object, Environment *environment, double dt) {
    double curValue = object->getEnergy();
    variation = curValue - lastValue;
    if (variation > 0.0) {
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

void BasicNervousSystem::renderFeedback(Object *object, Environment *environment) {
    if (object == environment->getPlayer()) {
        ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
        if (variation > 0.0) {
            color = al_map_rgb(0, 255, 0);            
        }
        
        al_draw_tinted_scaled_bitmap(gradients, color, 
                              1, 0, 1, 64, 
                              0, -64 + (int)feedback, Environment::SCREEN_WIDTH, 64, 0);        
        al_draw_tinted_scaled_bitmap(gradients, color, 
                              0, 0, 1, 64, 
                              0, Environment::SCREEN_HEIGHT - (int)feedback, Environment::SCREEN_WIDTH, 64, 0);  
    }
}

Sensor *BasicNervousSystem::clone() {
    return new BasicNervousSystem();
}
