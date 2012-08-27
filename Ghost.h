#ifndef _GHOST_H
#define _GHOST_H

#include "Object.h"

class Ghost : public Object {
    private:
        static ALLEGRO_SAMPLE *ghostSample;
        double voiceInterval;
                        
    public:
        Ghost();
        ~Ghost();
        
        void handleStimulus(Environment *environment, double dt);
        void renderFeedback(Environment *environment);
        
        void render(Environment *environment);
        
        ALLEGRO_SAMPLE *getVoice();
        void resetVoiceInterval();
        double getVoiceInterval();
        
        bool isVisible();
};

#endif
