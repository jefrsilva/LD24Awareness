#include "MultiTripleAntenna.h"
#include "Engine.h"
#include "Environment.h"
#include "Object.h"
#include <cmath>

MultiTripleAntenna::MultiTripleAntenna() : Sensor("SENSOR_MULTI_TRIPLE_ANTENNA") {

}

MultiTripleAntenna::~MultiTripleAntenna() {
    
}

void MultiTripleAntenna::handleStimulus(Object *object, Environment *environment, double dt) {
    nearestObjects = environment->getNearestObjects(object);
}

void MultiTripleAntenna::renderFeedback(Object *object, Environment *environment) {
    if (object == environment->getPlayer()) {
        Vector2D windowPos = environment->getWindowPos(object->getPosition());        
        
        int count = 0;
        for (int i = 0; i < nearestObjects.size() && count < 8; i++, count++) {
            if (nearestObjects[i]->isVisible()) {
                Vector2D objectWindowPos = environment->getWindowPos(nearestObjects[i]->getPosition());
                al_draw_line(windowPos.getX(),
                             windowPos.getY(),
                             objectWindowPos.getX(),
                             objectWindowPos.getY(),
                             al_map_rgb(196, 196, 196), 2.0);
            }
        }
    }
}

Sensor *MultiTripleAntenna::clone() {
    return new MultiTripleAntenna();    
}
