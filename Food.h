#ifndef _FOOD_H
#define _FOOD_H

#include "Object.h"
#include <string>
#include <map>

class Environment;

class Food : public Object {
    private:
        std::string composition;
        double amount;
        static ALLEGRO_BITMAP *foodShapes;  
        static std::map<std::string, int> foodShapeIndexes;      
        int fruitShape;
    
    public:
        Food(double amount);
        Food(std::string composition, double amount);
        ~Food();
             
        void handleStimulus(Environment *environment, double dt);
        void renderFeedback(Environment *environment);
        
        std::string getComposition();
        double digest(double amountToDigest);
        double getAmount();
        void render(Environment *environment);        
};

#endif
