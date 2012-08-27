#ifndef _ANIMAL_H
#define _ANIMAL_H

#include "Object.h"
#include "DNA.h"
#include <string>
#include <vector>
#include <allegro5/allegro_audio.h>

class Environment;
class Food;

class Animal : public Object {
    private:
        DNA dna;
        double energy;
        std::vector<Food *> stomach;
        
        static ALLEGRO_BITMAP *shapes;
        static ALLEGRO_SAMPLE *voiceSamples[16];
        static bool samplesInitialized;
        int voice;
        double voiceInterval;

        double curAIStateDuration;
        Vector2D curAIDirection;
    
    public:
        Animal();
        Animal(std::string DNASequence);
        ~Animal();
        
        ALLEGRO_SAMPLE *getVoice();
        void resetVoiceInterval();
        double getVoiceInterval();
        std::string getDNASequence();
             
        void handleStimulus(Environment *environment, double dt);
        void renderFeedback(Environment *environment);
        void handleCollisions(Environment *environment);
        void handleCollision(Environment *, Object *object);
        
        void swallow(Food *food);
        std::vector<Food *> getStomachContents();
        void updateStomachContents();
        
        void collideWith(Environment *environment, Food *food);
        void collideWith(Environment *environment, Animal *animal);
        void addEnergy(double amount);
        bool isMoving();
        
        double getEnergy();
        void render(Environment *environment);
        
        
};

#endif
