#include "Flyer.h"
#include "Environment.h"
#include "Animal.h"
#include "RandomNumberGenerator.h"

ALLEGRO_BITMAP *Flyer::flyerShape = 0;
ALLEGRO_SAMPLE *Flyer::flyerSample = 0;

Flyer::Flyer() : Object(OBJ_TYPE_MONSTER) {
    speed = 500.0;
    RandomNumberGenerator *rng = RandomNumberGenerator::getInstance();
    voiceInterval = ((double) rng->getInt(1500, 2500)) / 1000.0;
    
    charging = 0;
    chargeDuration = 0;
}

Flyer::~Flyer() {

}

void Flyer::handleStimulus(Environment *environment, double dt) {
    Object *player = environment->getPlayer();
    if (player) {
        if (player->getPosition().distanceTo(getPosition()) < 720.0) {
            if (chargeDuration <= 0.0) {
                if (charging >= 1.0) {
                    charging = 1.0;
                    chargeDuration = 2.0;            
                    chargeDirection = Vector2D(getPosition(), player->getPosition());
                    chargeDirection = chargeDirection.normalize();
                    voiceInterval = 0.0;
                } else {
                    charging += dt;                
                }
            } else {
                chargeDuration -= dt;
                if (chargeDuration <= 0.0) {
                    charging = 0.0;
                    chargeDuration = 0;
                }
                
                Vector2D movement = chargeDirection;
                movement = movement.mult(speed * dt);
                translate(movement);

                Vector2D boundsCorrection;
                if (getBounds().getMinX() < environment->getBounds().getMinX()) {
                    boundsCorrection.setX(environment->getBounds().getMinX() - getBounds().getMinX());
                }
                if (getBounds().getMinY() < environment->getBounds().getMinY()) {
                    boundsCorrection.setY(environment->getBounds().getMinY() - getBounds().getMinY());
                }
                if (getBounds().getMaxX() > environment->getBounds().getMaxX()) {
                    boundsCorrection.setX(environment->getBounds().getMaxX() - getBounds().getMaxX());
                }
                if (getBounds().getMaxY() > environment->getBounds().getMaxY()) {
                    boundsCorrection.setY(environment->getBounds().getMaxY() - getBounds().getMaxY());
                }
                translate(boundsCorrection);
                
                environment->updateObjectScreen(this);
    
                if (player->getPosition().distanceTo(getPosition()) < 48.0) {
                    Animal *animal = (Animal *) player;
                    animal->addEnergy(-1000.0);
                    this->destroy();
                }
            }
        }
    }
}

void Flyer::renderFeedback(Environment *environment) {
    
}

void Flyer::render(Environment *environment) {
    if (!flyerShape) {
        flyerShape = al_load_bitmap("flyer.png");
    }

    ALLEGRO_COLOR color = al_map_rgb(255, 196, 0);

    if (charging > 0.0) {
        double t = (charging) / 2.0;
        if (t < 0.0) {
            t = 0.0;
        }
        if (t > 1.0) {
            t = 1.0;
        }
        color = al_map_rgb(255, 196 + (unsigned char) (t * 59), (unsigned char) (t * 255));
    }
    
    Vector2D objWindowPos = environment->getWindowPos(getPosition());
    al_draw_tinted_scaled_bitmap(flyerShape, color, 0, 0, 24, 24, objWindowPos.getX() - 24, objWindowPos.getY() - 24, 48, 48, 0);    
}

ALLEGRO_SAMPLE *Flyer::getVoice() {
    if (!flyerSample) {
        flyerSample = al_load_sample("flyer.wav");
    }
    return flyerSample;
}

void Flyer::resetVoiceInterval() {
    RandomNumberGenerator *rng = RandomNumberGenerator::getInstance();    
    voiceInterval = ((double) rng->getInt(1500, 2500)) / 1000.0;    
}

double Flyer::getVoiceInterval() {
    return voiceInterval;
}

bool Flyer::isVisible() {
    return true;
}



