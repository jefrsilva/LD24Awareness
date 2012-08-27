#include "TitleScreen.h"
#include "GameScreen.h"
#include "Environment.h"
#include "Fadein.h"
#include "Fadeout.h"

namespace Game {
    
TitleScreen::TitleScreen() {
    jumpToGame = false;                 
    
    entryTransition = 0;
    exitTransition = 0;
    title = 0;
    curTransition = 0;    
}

TitleScreen::~TitleScreen() {
                          
}

void TitleScreen::start(Engine * engine) {
    jumpToGame = false;                 
    entryTransition = new Fadein(al_map_rgb(0, 0, 0), 1.0);
    exitTransition = new Fadeout(al_map_rgb(0, 0, 0), 1.0);
    curTransition = entryTransition;    
}

void TitleScreen::stop(Engine * engine) {

}

void TitleScreen::handleEvents(Engine * engine ,ALLEGRO_EVENT *event) {
    if (!curTransition) {
        if(event->type == ALLEGRO_EVENT_KEY_DOWN) {
            
        } else if (event->type == ALLEGRO_EVENT_KEY_UP) {
            switch (event->keyboard.keycode) {
                case ALLEGRO_KEY_ESCAPE:
                    engine->endGame = true;
                    break;
                    
                default:
                    jumpToGame = true;
                    curTransition = exitTransition;
                    break;
            }
        }
    }
}

void TitleScreen::update(Engine *engine, double dts) {
    if (jumpToGame && curTransition) {
        if (curTransition->isFinished()) {
            engine->jumpScreen(1);
        } else {
            curTransition->update(dts);            
        }
    } else {
        if (curTransition) {
            curTransition->update(dts);
            if (curTransition->isFinished()) {
                curTransition = 0;
            }
        }
    }
}

void TitleScreen::render(Engine *engine, double edt) {
    if (!title) {
        title = al_load_bitmap("title.png");        
    }
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(title, 0, 0, 0);
    if (curTransition) {
        curTransition->render(edt);
    }
}

void TitleScreen::flipStateBuffer() {
     
}

}

