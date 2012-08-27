#include "Ghost.h"
#include "Environment.h"
#include "Animal.h"
#include "RandomNumberGenerator.h"

ALLEGRO_SAMPLE *Ghost::ghostSample = 0;

Ghost::Ghost() : Object(OBJ_TYPE_MONSTER) {
    speed = 40.0;
    RandomNumberGenerator *rng = RandomNumberGenerator::getInstance();
    voiceInterval = ((double) rng->getInt(1500, 2500)) / 1000.0;
}

Ghost::~Ghost() {

}

void Ghost::handleStimulus(Environment *environment, double dt) {
    Object *player = environment->getPlayer();
    if (player) {
        if (player->getPosition().distanceTo(getPosition()) < 720.0) {
            voiceInterval -= dt;
            
            Vector2D movement = Vector2D(getPosition(), player->getPosition());
            movement = movement.normalize();
            movement = movement.mult(speed * dt);
            translate(movement);
            environment->updateObjectScreen(this);
            
            if (player->getPosition().distanceTo(getPosition()) < 48.0) {
                Animal *animal = (Animal *) player;
                animal->addEnergy(-1000.0);
                this->destroy();
            }
        }
    }
}

void Ghost::renderFeedback(Environment *environment) {
    
}

void Ghost::render(Environment *environment) {
    
}

ALLEGRO_SAMPLE *Ghost::getVoice() {
    if (!ghostSample) {
        ghostSample = al_load_sample("ghost.wav");
    }
    return ghostSample;
}

void Ghost::resetVoiceInterval() {
    RandomNumberGenerator *rng = RandomNumberGenerator::getInstance();    
    voiceInterval = ((double) rng->getInt(1500, 2500)) / 1000.0;    
}

double Ghost::getVoiceInterval() {
    return voiceInterval;
}

bool Ghost::isVisible() {
    return false;
}


