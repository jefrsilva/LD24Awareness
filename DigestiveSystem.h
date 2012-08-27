#ifndef _DIGESTIVE_SYSTEM_H
#define _DIGESTIVE_SYSTEM_H

#include "Sensor.h"
#include <string>

class Food;

class DigestiveSystem : public Sensor {
    private:
        std::string digestibles;
        double speed;
    
    public:
        DigestiveSystem(std::string digestibles, double speed);
        ~DigestiveSystem();    
        
        void handleStimulus(Object *object, Environment *environment, double dt);
        void renderFeedback(Object *object, Environment *environment);
        Sensor *clone();
        
        bool isGoodFood(Food *food);
        std::string getDigestibles();
};

#endif
