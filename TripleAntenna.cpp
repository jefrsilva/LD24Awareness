#include "TripleAntenna.h"
#include "Engine.h"
#include "Environment.h"
#include "Object.h"
#include <cmath>

TripleAntenna::TripleAntenna() : Sensor("SENSOR_TRIPLE_ANTENNA") { 
    nearestObject = 0;
}

TripleAntenna::~TripleAntenna() {
    
}

void TripleAntenna::handleStimulus(Object *object, Environment *environment, double dt) {
    nearestObject = environment->getNearestObject(object);
    if (nearestObject) {
        nearestObjectPosition = nearestObject->getPosition();
    } else {
        nearestObjectPosition = Vector2D(0.0, 0.0);
    }
}

void TripleAntenna::renderFeedback(Object *object, Environment *environment) {
    if (object == environment->getPlayer() && nearestObject) {
        if (nearestObject->isVisible()) {
            Vector2D windowPos = environment->getWindowPos(object->getPosition());        
            Vector2D objectWindowPos = environment->getWindowPos(nearestObjectPosition);
            al_draw_line(windowPos.getX(),
                         windowPos.getY(),
                         objectWindowPos.getX(),
                         objectWindowPos.getY(),
                         al_map_rgb(196, 196, 196), 2.0);
        }
    }
}

Sensor *TripleAntenna::clone() {
    return new TripleAntenna();
}
