#ifndef _GAME_
#define _GAME_

#include "Engine.h"
#include <stdio.h>
#include <allegro5/allegro.h>

namespace Game {
    
    class Screen {
        public:
            static const int BACK_BUFFER = 0;
			static const int FRONT_BUFFER = 1;
        
            virtual ~Screen() {};
            
            virtual void start(Engine * engine) = 0;
            virtual void stop(Engine * engine) = 0;

            virtual void handleEvents(Engine * engine ,ALLEGRO_EVENT *event) = 0;
            virtual void update(Engine * engine ,double deltaTimeSecond) = 0;
            virtual void render(Engine * engine ,double deltaTimeSecond) = 0;
            virtual void flipStateBuffer() = 0;
    };

}

#endif
