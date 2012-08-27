#ifndef _EXPLODER_H
#define _EXPLODER_H

#include "Object.h"

class Exploder : public Object {
    private:
        static ALLEGRO_BITMAP *exploderShape;
        bool activated;
        double delay;
    
    public:
        Exploder();
        ~Exploder();
        
        void handleStimulus(Environment *environment, double dt);
        void renderFeedback(Environment *environment);
        
        void render(Environment *environment);
};

#endif
