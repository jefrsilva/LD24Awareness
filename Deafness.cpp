#include "Deafness.h"
#include "Engine.h"
#include "Environment.h"
#include "Object.h"

Deafness::Deafness() : Sensor("SENSOR_DEAFNESS") {

}

Deafness::~Deafness() {
    
}

void Deafness::handleStimulus(Object *object, Environment *environment, double dt) {
    
}

void Deafness::renderFeedback(Object *object, Environment *environment) {
    
}

Sensor *Deafness::clone() {
    return new Deafness();
}

