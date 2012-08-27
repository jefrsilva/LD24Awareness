#include "PrimitiveEyes.h"
#include "Engine.h"
#include "Environment.h"
#include "Object.h"
#include <cmath>

PrimitiveEyes::PrimitiveEyes() : Sensor("SENSOR_PRIMITIVE_EYES") {

}

PrimitiveEyes::~PrimitiveEyes() {
    
}

void PrimitiveEyes::handleStimulus(Object *object, Environment *environment, double dt) {
    nearestObjects = environment->getNearestObjects(object);
}

void PrimitiveEyes::renderFeedback(Object *object, Environment *environment) {
    if (object == environment->getPlayer()) {
        Vector2D windowPos = environment->getWindowPos(object->getPosition());        
        
        for (int i = 0; i < nearestObjects.size(); i++) {
            if (nearestObjects[i]->isVisible()) {
                Vector2D objectWindowPos = environment->getWindowPos(nearestObjects[i]->getPosition());
                if (windowPos.distanceTo(objectWindowPos) <= 160.0) {
                    nearestObjects[i]->render(environment);
                } else {
                    al_draw_filled_circle(objectWindowPos.getX(), 
                                          objectWindowPos.getY(), 
                                          24, 
                                          al_map_rgb(196, 196, 196));
                }
            }
        }
    }
}

Sensor *PrimitiveEyes::clone() {
    return new PrimitiveEyes();    
}
