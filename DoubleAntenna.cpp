#include "DoubleAntenna.h"
#include "Engine.h"
#include "Environment.h"
#include "Object.h"
#include <cmath>

DoubleAntenna::DoubleAntenna() : Sensor("SENSOR_DOUBLE_ANTENNA"){
    nearestObject = 0;
}

DoubleAntenna::~DoubleAntenna() {
    
}

void DoubleAntenna::handleStimulus(Object *object, Environment *environment, double dt) {
    nearestObject = environment->getNearestObject(object);
    if (nearestObject) {
        double nearestObjectDistanceX = std::fabs(object->getPosition().getX() - nearestObject->getPosition().getX());
        double nearestObjectDistanceY = std::fabs(object->getPosition().getY() - nearestObject->getPosition().getY());
        nearestObjectDistance = Vector2D(nearestObjectDistanceX, nearestObjectDistanceY);
    } else {
        nearestObjectDistance = Vector2D(0.0, 0.0);
    }
}

void DoubleAntenna::renderFeedback(Object *object, Environment *environment) {
    if (object == environment->getPlayer() && nearestObject) {
        if (nearestObject->isVisible()) {
            Vector2D windowPos = environment->getWindowPos(object->getPosition());        
            al_draw_line(windowPos.getX() - nearestObjectDistance.getX(),
                         windowPos.getY(),
                         windowPos.getX() + nearestObjectDistance.getX(),
                         windowPos.getY(),
                         al_map_rgb(196, 196, 196), 2.0);
            
            al_draw_line(windowPos.getX(),
                         windowPos.getY() - nearestObjectDistance.getY(),
                         windowPos.getX(),
                         windowPos.getY() + nearestObjectDistance.getY(),
                         al_map_rgb(196, 196, 196), 2.0);
        }
    }
}

Sensor *DoubleAntenna::clone() {
    return new DoubleAntenna();
}
