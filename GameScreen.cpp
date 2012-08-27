#include "GameScreen.h"
#include "Environment.h"
#include "Animal.h"
#include "Wall.h"
#include "Food.h"
#include "MultiDirectionalEar.h"
#include "TripleAntenna.h"
#include "PrimitiveEyes.h"
#include "AdvancedNervousSystem.h"
#include "Exploder.h"
#include "Ghost.h"
#include "Flyer.h"

namespace Game {
    
GameScreen::GameScreen() {
                         
}

GameScreen::~GameScreen() {
                          
}

void GameScreen::start(Engine * engine) {
    environment = new Environment();
    environment->setupWorld();
}

void GameScreen::stop(Engine * engine) {

}

void GameScreen::handleEvents(Engine * engine ,ALLEGRO_EVENT *event) {
    double speed = 30.0;

    if(event->type == ALLEGRO_EVENT_KEY_DOWN) {
        switch(event->keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                key[KEY_UP] = true;
                environment->movingUp(true);
                break;
         
            case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN] = true;
                environment->movingDown(true);
                break;
         
            case ALLEGRO_KEY_LEFT: 
                key[KEY_LEFT] = true;
                environment->movingLeft(true);
                break;
         
            case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = true;
                environment->movingRight(true);
                break;
        }
    }
    else if(event->type == ALLEGRO_EVENT_KEY_UP) {
        switch(event->keyboard.keycode) {
            case ALLEGRO_KEY_UP:
                key[KEY_UP] = false;
                environment->movingUp(false);
                break;
         
            case ALLEGRO_KEY_DOWN:
                key[KEY_DOWN] = false;
                environment->movingDown(false);
                break;
         
            case ALLEGRO_KEY_LEFT: 
                key[KEY_LEFT] = false;
                environment->movingLeft(false);                
                break;
         
            case ALLEGRO_KEY_RIGHT:
                key[KEY_RIGHT] = false;
                environment->movingRight(false);                
                break;
         
            case ALLEGRO_KEY_ESCAPE:
                engine->endGame = true;
                break;
        }
    }
}

void GameScreen::update(Engine *engine, double dts) {
    if (environment->isGameOver()) {
        engine->jumpScreen(2);
    } else if (environment->isGameComplete()) {
        engine->jumpScreen(3);
    }
    Object *object = GameScreen::environment->getPlayer();
    if (object) {
        object->handleStimulus(environment, dts);    
        environment->setWindowCenter(object->getPosition());
    }
    environment->updateObjects(dts);
    environment->removeDeadObjects();
    environment->spawnNewObjects();
}

void GameScreen::render(Engine *engine, double edt) {
    al_clear_to_color(al_map_rgb(0,0,0));
    environment->render(edt);    
}

void GameScreen::flipStateBuffer() {
     
}

}

