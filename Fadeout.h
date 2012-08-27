#ifndef _FADE_OUT_H
#define _FADE_OUT_H

#include "Transition.h"

#include <allegro5/allegro.h>

class Fadeout : public Transition {
    private:
        ALLEGRO_COLOR color;
        double totalDuration;
        double curDuration;
    
    public:
        Fadeout(ALLEGRO_COLOR color, double duration);
        ~Fadeout();
        
        void update(double dt);
        void render(double edt);
        bool isFinished();
};

#endif
