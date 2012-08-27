#ifndef _GAMEOVER_SCREEN_H
#define _GAMEOVER_SCREEN_H

#include "Game.h"
#include <allegro5/allegro.h>

class Environment;
class Transition;

namespace Game {

class GameOverScreen : public Screen {
    private:
        ALLEGRO_BITMAP *title;
        enum MYKEYS {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
        Environment *environment;
        bool jumpToGame;
        Transition *entryTransition;
        Transition *exitTransition;        
        Transition *curTransition;
      
    public:
        bool key[4];
             
        GameOverScreen();
        ~GameOverScreen();
             
        void start(Engine * engine);
        void stop(Engine * engine);

        void handleEvents(Engine * engine ,ALLEGRO_EVENT *event);
        void update(Engine * engine ,double dts);
        void render(Engine * engine ,double edt);
        void flipStateBuffer();
};

}

#endif

