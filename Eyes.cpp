#include "Eyes.h"
#include "Engine.h"
#include "Environment.h"
#include "Object.h"
#include <cmath>

Eyes::Eyes() : Sensor("SENSOR_EYES") {

}

Eyes::~Eyes() {
    
}

void Eyes::handleStimulus(Object *object, Environment *environment, double dt) {
    nearestObjects = environment->getNearestObjects(object);
}

void Eyes::renderFeedback(Object *object, Environment *environment) {
    if (object == environment->getPlayer()) {
        Vector2D windowPos = environment->getWindowPos(object->getPosition());        
        
        for (int i = 0; i < nearestObjects.size(); i++) {
            if (nearestObjects[i]->isVisible()) {
                nearestObjects[i]->render(environment);
            }
        }
    }
}

Sensor *Eyes::clone() {
    return new Eyes();    
}

