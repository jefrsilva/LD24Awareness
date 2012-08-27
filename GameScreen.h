#ifndef _GAME_SCREEN_H
#define _GAME_SCREEN_H

#include "Game.h"
#include <allegro5/allegro.h>

class Environment;

namespace Game {

class GameScreen : public Screen {
    private:
        enum MYKEYS {KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
        Environment *environment;
      
    public:
        bool key[4];
             
        GameScreen();
        ~GameScreen();
             
        void start(Engine * engine);
        void stop(Engine * engine);

        void handleEvents(Engine * engine ,ALLEGRO_EVENT *event);
        void update(Engine * engine ,double dts);
        void render(Engine * engine ,double edt);
        void flipStateBuffer();
};

}

#endif

