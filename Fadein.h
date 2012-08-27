#ifndef _FADE_IN_H
#define _FADE_IN_H

#include "Transition.h"
#include <allegro5/allegro.h>

class Fadein : public Transition {
    private:
        ALLEGRO_COLOR color;
        double totalDuration;
        double curDuration;
    
    public:
        Fadein(ALLEGRO_COLOR color, double duration);
        ~Fadein();
        
        void update(double dt);
        void render(double edt);
        bool isFinished();
};

#endif
