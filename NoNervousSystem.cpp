#include "NoNervousSystem.h"
#include "Engine.h"
#include "Environment.h"
#include "Object.h"

NoNervousSystem::NoNervousSystem() : Sensor("SENSOR_NO_NERVOUS_SYSTEM") {

}

NoNervousSystem::~NoNervousSystem() {
    
}

void NoNervousSystem::handleStimulus(Object *object, Environment *environment, double dt) {
    
}

void NoNervousSystem::renderFeedback(Object *object, Environment *environment) {
    
}

Sensor *NoNervousSystem::clone() {
    return new NoNervousSystem();
}

