#include "Exploder.h"
#include "Environment.h"
#include "Animal.h"

ALLEGRO_BITMAP *Exploder::exploderShape = 0;

Exploder::Exploder() : Object(OBJ_TYPE_MONSTER) {
    speed = 0.0;
    activated = false;
    delay = 1.0;
}

Exploder::~Exploder() {

}

void Exploder::handleStimulus(Environment *environment, double dt) {
    Object *player = environment->getPlayer();
    if (player) {
        if (!activated) {
            if (player->getPosition().distanceTo(getPosition()) < 160.0) {
                activated = true;
            }
        } else {
            delay -= dt;
            if (delay <= 0.0) {
                this->destroy();
                if (player->getPosition().distanceTo(getPosition()) < 160.0) {            
                    Animal *animal = (Animal *) player;
                    animal->addEnergy(-1000.0);
                }
            }        
        }
    }
}

void Exploder::renderFeedback(Environment *environment) {
}

void Exploder::render(Environment *environment) {
    if (!exploderShape) {
        exploderShape = al_load_bitmap("exploder.png");
    }
    
    ALLEGRO_COLOR color = al_map_rgb(196, 0, 255);
    if (activated) {
        double t = 1.0 - delay;
        if (t < 0.0) {
            t = 0.0;
        }
        if (t > 1.0) {
            t = 1.0;
        }
        color = al_map_rgb(196 + (unsigned char) (t * 59), (unsigned char) (t * 255), 255);
    }
    Vector2D objWindowPos = environment->getWindowPos(getPosition());
    al_draw_tinted_scaled_bitmap(exploderShape, color, 0, 0, 24, 24, objWindowPos.getX() - 24, objWindowPos.getY() - 24, 48, 48, 0);    
}


