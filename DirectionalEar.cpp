#include "DirectionalEar.h"
#include "Environment.h"
#include "Object.h"

ALLEGRO_SAMPLE *DirectionalEar::sound = 0;

DirectionalEar::DirectionalEar() : Sensor("SENSOR_DIRECTIONAL_EAR"){
    nearestObject = 0;
}

DirectionalEar::~DirectionalEar() {
    
}

void DirectionalEar::handleStimulus(Object *object, Environment *environment, double dt) {
    nearestObject = environment->getNearestObject(object);
    if (nearestObject) {
        nearestObjectPosition = nearestObject->getPosition();
    } else {
        nearestObjectPosition = Vector2D(0.0, 0.0);
    }
}

void DirectionalEar::renderFeedback(Object *object, Environment *environment) {
    if (object == environment->getPlayer() && nearestObject) {
        if (nearestObject->getVoiceInterval() <= 0.0) {
            nearestObject->resetVoiceInterval();
            if (!sound) {
                sound = al_load_sample("blip.wav");
            }
            
            Vector2D windowPos = environment->getWindowPos(object->getPosition());        
            Vector2D objectWindowPos = environment->getWindowPos(nearestObjectPosition);
            Vector2D relativePos = objectWindowPos.add(windowPos.mult(-1.0));
            relativePos = relativePos.normalize();
            double pan = relativePos.getX();
            
            double nearestObjectDistance = windowPos.distanceTo(objectWindowPos);
            double gain = 1.0 - (nearestObjectDistance / 1000.0);
            if (gain < 0.0) {
                gain = 0.0;
            }
            
            al_play_sample(sound, gain, pan, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        }
    }
}

Sensor *DirectionalEar::clone() {
    return new DirectionalEar();
}

