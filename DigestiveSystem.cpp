#include "DigestiveSystem.h"
#include "Animal.h"
#include "Food.h"

#include <iostream>

DigestiveSystem::DigestiveSystem(std::string digestibles, double speed) : Sensor("SENSOR_DIGESTIVE_SYSTEM") {
    this->digestibles = digestibles;    
    this->speed = speed;
}

DigestiveSystem::~DigestiveSystem() {
    
}

void DigestiveSystem::handleStimulus(Object *object, Environment *environment, double dt) {
    Animal *animal = (Animal *)object;    
    std::vector<Food *> stomachContents = animal->getStomachContents();
    if (stomachContents.size() > 0) {
        Food *food = stomachContents[0]; 
        //std::cout << "Digestibles : " << digestibles << std::endl;       
        //std::cout << "Digesting food (" << food->getComposition() << " - " << food->getAmount() << ")" << std::endl;

        if (isGoodFood(food)) {
            double energyProvided = food->digest(speed * dt);
            animal->addEnergy(energyProvided);
            //std::cout << "Good food! Got energy " << energyProvided << std::endl;            
            //std::cout << "Energy : " << animal->getEnergy() << std::endl;
        } else {
            double energyProvided = food->digest(0.5 * speed * dt);
            //std::cout << "Bad food... Lost energy " << -energyProvided * 0.25 << std::endl;                        
            //std::cout << "Energy : " << animal->getEnergy() << std::endl;            
        }
    }
    animal->updateStomachContents();
}

void DigestiveSystem::renderFeedback(Object *object, Environment *environment) {
    
}

Sensor *DigestiveSystem::clone() {
    return new DigestiveSystem(digestibles, speed);
}

bool DigestiveSystem::isGoodFood(Food *food) {
    bool goodFood = false;
    
    std::string composition = food->getComposition();
    int digestiblesQty = 0;
    for (int i = 0; i < digestibles.size(); i++) {
        for (int j = 0; j < composition.size(); j++) {
            if (digestibles[i] == composition[j]) {
                digestiblesQty++;
                break;
            }
        }
    }
    if (digestiblesQty == composition.size()) {
        goodFood = true;
    }
    
    return goodFood;
}

std::string DigestiveSystem::getDigestibles() {
    return digestibles;
}

