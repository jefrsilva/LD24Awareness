#include "MultiSingleAntenna.h"
#include "Engine.h"
#include "Environment.h"
#include "Object.h"
#include <cmath>

MultiSingleAntenna::MultiSingleAntenna()  : Sensor("SENSOR_MULTI_SINGLE_ANTENNA") {

}

MultiSingleAntenna::~MultiSingleAntenna() {
    
}

void MultiSingleAntenna::handleStimulus(Object *object, Environment *environment, double dt) {
    nearestObjects = environment->getNearestObjects(object);
}

void MultiSingleAntenna::renderFeedback(Object *object, Environment *environment) {
    if (object == environment->getPlayer()) {
        Vector2D windowPos = environment->getWindowPos(object->getPosition());        
        
        int count = 0;
        for (int i = 0; i < nearestObjects.size() && count < 8; i++, count++) {
            if (nearestObjects[i]->isVisible()) {
                Vector2D objectWindowPos = environment->getWindowPos(nearestObjects[i]->getPosition());
                double nearestObjectDistance = objectWindowPos.distanceTo(windowPos);
                al_draw_circle(windowPos.getX(), 
                               windowPos.getY(), 
                               nearestObjectDistance, 
                               al_map_rgb(196, 196, 196), 2.0);
            }
        }
    }
}

Sensor *MultiSingleAntenna::clone() {
    return new MultiSingleAntenna();
}
