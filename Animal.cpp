#include "Animal.h"
#include "Food.h"
#include "Environment.h"
#include "RandomNumberGenerator.h"
#include <sstream>
#include <iostream>

ALLEGRO_BITMAP *Animal::shapes = 0;
ALLEGRO_SAMPLE *Animal::voiceSamples[16];
bool Animal::samplesInitialized = false;

Animal::Animal() : Object(OBJ_TYPE_ANIMAL) {
    energy = 80.0;
    speed = 80.0;
    
    if (!samplesInitialized) {
        for (int i = 0; i < 16; i++) {
            voiceSamples[i] = 0;
        }
        samplesInitialized = true;
    }
    
    voice = dna.getVoice();
    RandomNumberGenerator *rng = RandomNumberGenerator::getInstance();
    voiceInterval = ((double) rng->getInt(500, 5000)) / 1000.0;
    addSensor(dna.getSightSensor());
    addSensor(dna.getDigestiveSystem());
    addSensor(dna.getHearingSensor());
    addSensor(dna.getNervousSystem());
}

Animal::Animal(std::string DNASequence) : Object(OBJ_TYPE_ANIMAL) {
    energy = 80.0;
    speed = 80.0;
    this->dna = DNA(DNASequence);

    if (!samplesInitialized) {
        for (int i = 0; i < 16; i++) {
            voiceSamples[i] = 0;
        }
        samplesInitialized = true;
    }
    
    voice = dna.getVoice();    
    RandomNumberGenerator *rng = RandomNumberGenerator::getInstance();    
    voiceInterval = ((double) rng->getInt(500, 5000)) / 1000.0;    
    addSensor(dna.getSightSensor());
    addSensor(dna.getDigestiveSystem());    
    addSensor(dna.getHearingSensor());    
    addSensor(dna.getNervousSystem());
}

Animal::~Animal() {
    
}

ALLEGRO_SAMPLE *Animal::getVoice() {
    if (!voiceSamples[voice]) {
        std::stringstream voiceFilename;
        voiceFilename << "voice" << voice << ".wav";
        voiceSamples[voice] = al_load_sample(voiceFilename.str().c_str());
    }
    return voiceSamples[voice];
}

void Animal::resetVoiceInterval() {
    RandomNumberGenerator *rng = RandomNumberGenerator::getInstance();    
    voiceInterval = ((double) rng->getInt(500, 5000)) / 1000.0;    
}

double Animal::getVoiceInterval() {
    return voiceInterval;
}

std::string Animal::getDNASequence() {
    return dna.getSequence();
}

void Animal::handleStimulus(Environment *environment, double dt) {
    voiceInterval -= dt;
    
    if (this == environment->getPlayer()) {
        Vector2D movement = environment->getMovement();
        movement = movement.mult(dt);
        translate(movement);
        handleCollisions(environment);
        environment->updateObjectScreen(this);
        
        if (movement.distanceTo(Vector2D()) > 1.0e-5) {
            addEnergy(-dt);
        }
        
        for (int i = 0; i < sensors.size(); i++) {
            sensors[i]->handleStimulus(this, environment, dt);
        }
    } else {
        RandomNumberGenerator *rng = RandomNumberGenerator::getInstance();
        if (curAIStateDuration > 0.0) {
            curAIStateDuration -= dt;
        } else {
            curAIStateDuration = ((double) rng->getInt(500, 3000)) / 1000.0;
            curAIDirection = Vector2D(rng->getInt(-1, 1), rng->getInt(-1, 1));
            curAIDirection = curAIDirection.mult(speed);
        }
        
        Vector2D movement = curAIDirection;
        movement = movement.mult(dt);
        translate(movement);
        handleCollisions(environment);
        environment->updateObjectScreen(this);
    }
}

void Animal::renderFeedback(Environment *environment) {
    for (int i = 0; i < sensors.size(); i++) {
        sensors[i]->renderFeedback(this, environment);
    }
}

void Animal::handleCollisions(Environment *environment) {
    Vector2D boundsCorrection;
    if (getBounds().getMinX() < environment->getBounds().getMinX()) {
        boundsCorrection.setX(environment->getBounds().getMinX() - getBounds().getMinX());
    }
    if (getBounds().getMinY() < environment->getBounds().getMinY()) {
        boundsCorrection.setY(environment->getBounds().getMinY() - getBounds().getMinY());
    }
    if (getBounds().getMaxX() > environment->getBounds().getMaxX()) {
        boundsCorrection.setX(environment->getBounds().getMaxX() - getBounds().getMaxX());
    }
    if (getBounds().getMaxY() > environment->getBounds().getMaxY()) {
        boundsCorrection.setY(environment->getBounds().getMaxY() - getBounds().getMaxY());
    }
    translate(boundsCorrection);
    
    std::vector<Object *> nearestObjects = environment->getNearestObjects(this);
    for (int k = 0; k < nearestObjects.size(); k++) {
        Object *nearestObject = nearestObjects[k];
        double distance = getPosition().distanceTo(nearestObject->getPosition());
        double radius = (OBJECT_WIDTH / 2);
        if (distance < 2.0 * radius) {
            Vector2D overlapVector = Vector2D(nearestObject->getPosition(), getPosition());        
            overlapVector = overlapVector.normalize();
            
            double overlapLength = 2.0 * radius - distance;
            overlapVector = overlapVector.mult(overlapLength);
            
            translate(overlapVector);
            
            handleCollision(environment, nearestObject);
        }
    }
}
 
void Animal::handleCollision(Environment *environment, Object *object) {
    if (object->getType() == OBJ_TYPE_FOOD) {
        collideWith(environment, (Food *) object);
    } else if (object->getType() == OBJ_TYPE_ANIMAL) {
        collideWith(environment, (Animal *) object);
    }
} 

void Animal::collideWith(Environment *environment, Food *food) {
    if (food->getComposition()[0] == '1' ||
        food->getComposition()[0] == '2' ||
        food->getComposition()[0] == '3' ||
        food->getComposition()[0] == '4') {
        if (this == environment->getPlayer() && !food->shouldDestroy()) {
            food->destroy();
            printf( "destroy\n");
            environment->addPrize();
        }    
    } else {
        swallow(food);
        food->destroy();
    }
}

void Animal::swallow(Food *food) {
    stomach.push_back(food);
}

std::vector<Food *> Animal::getStomachContents() {
    return stomach;
}

void Animal::updateStomachContents() {
    std::vector<Food *>::iterator it = stomach.begin();
    while (it != stomach.end()) {
        Food *food = (*it);
        if (food->getAmount() <= 0.0) {
            it = stomach.erase(it);
        } else {
            it++;
        }
    }
}

void Animal::collideWith(Environment *environment, Animal *animal) {
    if (this == environment->getPlayer() && energy > 100.0 && !animal->shouldDestroy()) {
        Animal *offspring = new Animal(dna.crossoverAndMutate(animal->getDNASequence()));
        offspring->setPosition(getPosition().getX(), getPosition().getY());
        environment->spawnObject(offspring);
        this->destroy();
        animal->destroy();
        environment->setPlayer(offspring);
        
        //std::cout << "First DNA Sequence     : " << this->getDNASequence() << std::endl;
        //std::cout << "Second DNA Sequence    : " << animal->getDNASequence() << std::endl;
        //std::cout << "Offspring DNA Sequence : " << offspring->getDNASequence() << std::endl;
    }
}

void Animal::addEnergy(double amount) {
    energy += amount;
    if (energy > MAX_ENERGY) {
        energy = MAX_ENERGY;
    }
}

bool Animal::isMoving() {
    bool isMoving = false;
    if (curAIDirection.distanceTo(Vector2D()) > 1.0e-5) {
        isMoving = true;
    }
    return isMoving;
}

double Animal::getEnergy() {
    return energy;
}

void Animal::render(Environment *environment) {
    if (!shapes) {
        shapes = al_load_bitmap("shapes.png");
    }
    
    int ears = dna.getEarsShape();
    int antennaEyes = dna.getAntennaEyesShape();
    int head = dna.getHeadShape();
    int body = dna.getBodyShape();
    ALLEGRO_COLOR color = dna.getColor();
    
    Vector2D objWindowPos = environment->getWindowPos(getPosition());
    al_draw_tinted_scaled_bitmap(shapes, color, 72, ears * 24, 12, 24, objWindowPos.getX() - 28, objWindowPos.getY() - 24, 24, 48, 0);
    al_draw_tinted_scaled_bitmap(shapes, color, 84, ears * 24, 12, 24, objWindowPos.getX() + 4, objWindowPos.getY() - 24, 24, 48, 0);    
    al_draw_tinted_scaled_bitmap(shapes, color, 0, antennaEyes * 24, 24, 24, objWindowPos.getX() - 24, objWindowPos.getY() - 28, 48, 48, 0);
    al_draw_tinted_scaled_bitmap(shapes, color, 24, head * 24, 24, 24, objWindowPos.getX() - 24, objWindowPos.getY() - 24, 48, 48, 0);
    al_draw_tinted_scaled_bitmap(shapes, color, 48, body * 24, 24, 24, objWindowPos.getX() - 24, objWindowPos.getY() - 24, 48, 48, 0);    
}
