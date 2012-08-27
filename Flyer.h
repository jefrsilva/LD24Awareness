#ifndef _FLYER_H
#define _FLYER_H

#include "Object.h"

class Flyer : public Object {
    private:
        static ALLEGRO_BITMAP *flyerShape;
        static ALLEGRO_SAMPLE *flyerSample;
        double voiceInterval;
        
        double charging;
        double chargeDuration;
        Vector2D chargeDirection;
                        
    public:
        Flyer();
        ~Flyer();
        
        void handleStimulus(Environment *environment, double dt);
        void renderFeedback(Environment *environment);
        
        void render(Environment *environment);
        
        ALLEGRO_SAMPLE *getVoice();
        void resetVoiceInterval();
        double getVoiceInterval();
        
        bool isVisible();
};

#endif

