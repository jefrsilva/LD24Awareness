#include "AdvancedNervousSystem.h"
#include "Environment.h"
#include "Object.h"

#include <cmath>

ALLEGRO_BITMAP *AdvancedNervousSystem::gradients = 0;

AdvancedNervousSystem::AdvancedNervousSystem() : Sensor("SENSOR_ADVANCED_NERVOUS_SYSTEM"){
    if (!gradients) {
        gradients = al_load_bitmap("gradients.png");
    }
    
    lastValue = 0.0;
    variation = 0.0;
    feedback = 0.0;
    flicker = 0.0;
    show = false;
}

AdvancedNervousSystem::~AdvancedNervousSystem() {
    
}

void AdvancedNervousSystem::handleStimulus(Object *object, Environment *environment, double dt) {
    double curValue = object->getEnergy();
    variation = curValue - lastValue;
    if (std::fabs(variation) > 1.0e-5) {
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

void AdvancedNervousSystem::renderFeedback(Object *object, Environment *environment) {
    if (object == environment->getPlayer()) {
        ALLEGRO_COLOR color = al_map_rgb(255, 255, 255);
        if (variation < 0.0) {
            color = al_map_rgb(255, 0, 0);
        } else if (variation > 0.0) {
            color = al_map_rgb(0, 255, 0);            
        }
        
        double energy = object->getEnergy();
        Vector2D windowPos = environment->getWindowPos(object->getPosition());
        double arcLength = energy / Object::MAX_ENERGY;
        al_draw_arc(windowPos.getX(), windowPos.getY(), 300.0, 1.57 - arcLength * 1.57 * 0.5, arcLength * 3.14 * 0.5, color, 12.0); 
        if (object->getEnergy() >= 100.0) {
            al_draw_arc(windowPos.getX(), windowPos.getY(), 300.0, 1.57 - arcLength * 1.57 * 0.5, arcLength * 3.14 * 0.5, al_map_rgb(255, 255, 0), 16.0);             
        }
    }
}

Sensor *AdvancedNervousSystem::clone() {
    return new AdvancedNervousSystem();
}
