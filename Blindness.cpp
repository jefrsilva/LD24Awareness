#include "Blindness.h"
#include "Engine.h"
#include "Environment.h"
#include "Object.h"

Blindness::Blindness() : Sensor("SENSOR_BLINDNESS") {

}

Blindness::~Blindness() {
    
}

void Blindness::handleStimulus(Object *object, Environment *environment, double dt) {
    
}

void Blindness::renderFeedback(Object *object, Environment *environment) {
    
}

Sensor *Blindness::clone() {
    return new Blindness();
}

