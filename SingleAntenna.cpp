#include "SingleAntenna.h"
#include "Engine.h"
#include "Environment.h"
#include "Object.h"

SingleAntenna::SingleAntenna() : Sensor("SENSOR_SINGLE_ANTENNA") {
    nearestObjectDistance = 0.0;
}

SingleAntenna::~SingleAntenna() {
    
}

void SingleAntenna::handleStimulus(Object *object, Environment *environment, double dt) {
    Object *nearestObject = environment->getNearestObject(object);
    if (nearestObject) {
        if (nearestObject->isVisible()) {        
            nearestObjectDistance = object->getPosition().distanceTo(nearestObject->getPosition());
        } else {
            nearestObjectDistance = 0.0;            
        }
    } else {
        nearestObjectDistance = 0.0; 
    }
}

void SingleAntenna::renderFeedback(Object *object, Environment *environment) {
    if (object == environment->getPlayer()) {
        Vector2D windowPos = environment->getWindowPos(object->getPosition());
        al_draw_circle(windowPos.getX(), 
                       windowPos.getY(), 
                       nearestObjectDistance, 
                       al_map_rgb(196, 196, 196), 2.0);
    }
}

Sensor *SingleAntenna::clone() {
    return new SingleAntenna();
}
