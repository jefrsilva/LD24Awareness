#include "PrimitiveEar.h"
#include "Environment.h"
#include "Object.h"

ALLEGRO_SAMPLE *PrimitiveEar::sound = 0;

PrimitiveEar::PrimitiveEar() : Sensor("SENSOR_PRIMITIVE_EAR"){
    nearestObject = 0;
}

PrimitiveEar::~PrimitiveEar() {
    
}

void PrimitiveEar::handleStimulus(Object *object, Environment *environment, double dt) {
    nearestObject = environment->getNearestObject(object);
}

void PrimitiveEar::renderFeedback(Object *object, Environment *environment) {
    if (object == environment->getPlayer() && nearestObject) {
        if (nearestObject->getVoiceInterval() < 0.0) {
            nearestObject->resetVoiceInterval();
            if (!sound) {
                sound = al_load_sample("blip.wav");
            }
            al_play_sample(sound, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
        }
    }
}

Sensor *PrimitiveEar::clone() {
    return new PrimitiveEar();
}
