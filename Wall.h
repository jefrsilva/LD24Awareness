#ifndef _WALL_H
#define _WALL_H

#include "Object.h"
class Environment;

class Wall : public Object {
    private:
        static ALLEGRO_BITMAP *wallShapes;  
                
    public:
        Wall();
        ~Wall();
             
        void handleStimulus(Environment *environment, double dt);
        void renderFeedback(Environment *environment);
        void render(Environment *environment);                
};

#endif
