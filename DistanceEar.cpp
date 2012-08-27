#include "DistanceEar.h"
#include "Environment.h"
#include "Object.h"

ALLEGRO_SAMPLE *DistanceEar::sound = 0;

DistanceEar::DistanceEar() : Sensor("SENSOR_DISTANCE_EAR") {
    nearestObject = 0;    
}

DistanceEar::~DistanceEar() {
    
}

void DistanceEar::handleStimulus(Object *object, Environment *environment, double dt) {
    nearestObject = environment->getNearestObject(object);
    if (nearestObject) {
        nearestObjectDistance = object->getPosition().distanceTo(nearestObject->getPosition());
    } else {
        nearestObjectDistance = 0.0;
    }
}

void DistanceEar::renderFeedback(Object *object, Environment *environment) {
    if (object == environment->getPlayer() && nearestObject) {
        if (nearestObject->getVoiceInterval() < 0.0) {
            nearestObject->resetVoiceInterval();
            if (!sound) {
                sound = al_load_sample("blip.wav");
            }
            double gain = 1.0 - (nearestObjectDistance / 1000.0);
            if (gain < 0.0) {
                gain = 0.0;
            }
            
            al_play_sample(sound, gain, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        }
    }
}

Sensor *DistanceEar::clone() {
    return new DistanceEar();
}

