#include "Environment.h"
#include "Object.h"
#include "ObjectComparator.h"
#include "RandomNumberGenerator.h"
#include "Flyer.h"
#include "Ghost.h"
#include "Exploder.h"
#include "Animal.h"
#include "Wall.h"
#include "Food.h"
#include "Eyes.h"
#include "MultiDirectionalEar.h"
#include <algorithm>
#include <limits>
#include <iostream>

Environment::Environment() {
    player = NULL;
    prizes = 0;
}

Environment::~Environment() {
    
}

void Environment::addPrize() {
    prizes++;
}

bool Environment::isGameOver() {
    bool result = false;
    
    if (player) {
        if (player->getEnergy() <= 0.0) {
            result = true;
        }
    }
    
    return result;
}

bool Environment::isGameComplete() {
    return prizes >= 4;    
}

Vector2D Environment::getRandomSpawnPosition(int screenX, int screenY, int screensWidth, int screensHeight) {
    RandomNumberGenerator *rng = RandomNumberGenerator::getInstance();
    BoundingBox bounds = 
        BoundingBox(screenX * SCREEN_WIDTH + Object::OBJECT_WIDTH, 
                    screenY * SCREEN_HEIGHT + Object::OBJECT_HEIGHT, 
                    screensWidth * SCREEN_WIDTH - Object::OBJECT_WIDTH, 
                    screensHeight * SCREEN_HEIGHT - Object::OBJECT_HEIGHT);
                    
    return Vector2D(rng->getInt((int) bounds.getMinX(), (int) bounds.getMaxX()),
                    rng->getInt((int) bounds.getMinY(), (int) bounds.getMaxY()));
}

void Environment::setupWorld() {
    for (int i = 0; i < 20; i++) {
        Vector2D position = getRandomSpawnPosition(1, 1, 3, 3);
        Flyer *flyer = new Flyer();
        flyer->setPosition(position.getX(), position.getY());
        addObject(flyer);
    }
    
    for (int i = 0; i < 40; i++) {
        Vector2D position = getRandomSpawnPosition(7, 1, 3, 3);
        Exploder *exploder = new Exploder();
        exploder->setPosition(position.getX(), position.getY());
        addObject(exploder);
    }
    
    for (int i = 0; i < 3; i++) {
        Vector2D position = getRandomSpawnPosition(1, 9, 1, 1);
        Ghost *ghost = new Ghost();
        ghost->setPosition(position.getX(), position.getY());
        addObject(ghost);
    }
    
    for (int i = 0; i < 16; i++) {
        Vector2D position = getRandomSpawnPosition(4, 1, 3, 3);
        Animal *animal = new Animal();
        animal->setPosition(position.getX(), position.getY());
        addObject(animal);
    }
    
    for (int i = 0; i < 48; i++) {
        Vector2D position = getRandomSpawnPosition(1, 4, 9, 3);
        Animal *animal = new Animal();
        animal->setPosition(position.getX(), position.getY());
        addObject(animal);
    }

    for (int i = 0; i < 16; i++) {
        Vector2D position = getRandomSpawnPosition(4, 7, 3, 3);
        Animal *animal = new Animal();
        animal->setPosition(position.getX(), position.getY());
        addObject(animal);
    }    
    
    for (int i = 0; i < 40; i++) {
        Vector2D position = getRandomSpawnPosition(7, 1, 3, 3);
        Wall *wall = new Wall();
        wall->setPosition(position.getX(), position.getY());
        addObject(wall);
    }

    for (int i = 0; i < 100; i++) {
        Vector2D position = getRandomSpawnPosition(1, 1, 9, 9);
        Wall *wall = new Wall();
        wall->setPosition(position.getX(), position.getY());
        addObject(wall);
    }
    
    for (int i = 0; i < 180; i++) {
        Vector2D position = getRandomSpawnPosition(1, 1, 9, 6);
        Food *food = new Food(30.0);
        food->setPosition(position.getX(), position.getY());
        addObject(food);
    }
    
    for (int i = 0; i < 60; i++) {
        Vector2D position = getRandomSpawnPosition(1, 7, 6, 3);
        Food *food = new Food(50.0);
        food->setPosition(position.getX(), position.getY());
        addObject(food);
    }
    
    for (int i = 0; i < 30; i++) {
        Vector2D position = getRandomSpawnPosition(7, 7, 3, 3);
        Food *food = new Food("A", 50.0);
        food->setPosition(position.getX(), position.getY());
        addObject(food);
    }

    for (int i = 0; i < 20; i++) {
        Vector2D position = getRandomSpawnPosition(1, 1, 9, 9);
        Flyer *flyer = new Flyer();
        flyer->setPosition(position.getX(), position.getY());
        addObject(flyer);
    }

    {
        Vector2D position = getRandomSpawnPosition(1, 1, 1, 1);
        Food *food = new Food("1", 0.0);
        food->setPosition(position.getX(), position.getY());
        addObject(food);
    }
    {
        Vector2D position = getRandomSpawnPosition(9, 1, 1, 1);
        Food *food = new Food("2", 0.0);
        food->setPosition(position.getX(), position.getY());
        addObject(food);
    }
    {
        Vector2D position = getRandomSpawnPosition(1, 9, 1, 1);
        Food *food = new Food("3", 0.0);
        food->setPosition(position.getX(), position.getY());
        addObject(food);
    }
    {
        Vector2D position = getRandomSpawnPosition(9, 9, 1, 1);
        Food *food = new Food("4", 0.0);
        food->setPosition(position.getX(), position.getY());
        addObject(food);
    }
    
    Vector2D position = getRandomSpawnPosition(5, 5, 1, 1);
    Animal *player = new Animal();
    player->setPosition(position.getX(), position.getY());
    addObject(player);
    setPlayer(player);
}

BoundingBox Environment::getBounds() {
    BoundingBox bounds = BoundingBox(SCREEN_WIDTH, 
                                     SCREEN_HEIGHT, 
                                     ENV_WIDTH * SCREEN_WIDTH, 
                                     ENV_HEIGHT * SCREEN_HEIGHT);
    
    return bounds;
}

void Environment::setPlayer(Object *object) {
    player = object;
}

Object *Environment::getPlayer() {
    return player;
}

void Environment::addObject(Object *object) {
    Vector2D objPos = object->getPosition();
    int screenX = (int) ((objPos.getX() / SCREEN_WIDTH));
    int screenY = (int) ((objPos.getY() / SCREEN_HEIGHT));
    objects[screenX][screenY].push_back(object);
    object->setScreen(screenX, screenY);
    
    //std::cout << "Added object to screen " << screenX << ", " << screenY << std::endl;    
}

void Environment::removeObject(Object *object) {
    Vector2D screenCoord = object->getScreen();
    int screenX = (int) screenCoord.getX();
    int screenY = (int) screenCoord.getY();
    std::vector<Object *> &objectList = objects[screenX][screenY];
    objectList.erase(std::find(objectList.begin(), objectList.end(), object));
    
    //std::cout << "Removed object from screen " << screenX << ", " << screenY << std::endl;
}

std::vector<Object *> Environment::getAllObjects() {
    std::vector<Object *> allObjects;
    
    for (int y = 1; y <= ENV_HEIGHT; y++) {
        for (int x = 1; x <= ENV_WIDTH; x++) {
            for (int i = 0; i < objects[x][y].size(); i++) {
                Object *object = objects[x][y][i];
                allObjects.push_back(object);
            }
        }
    }   
    
    return allObjects;
}

Object *Environment::getNearestObject(Object *object) {
    Object *nearestObject = NULL;
    double smallestDistance = std::numeric_limits<double>::max();
    
    int screenX = (int) ((object->getPosition().getX() / SCREEN_WIDTH));
    int screenY = (int) ((object->getPosition().getY() / SCREEN_HEIGHT));
    for (int yOffset = -1; yOffset <= 1; yOffset++) {
        for (int xOffset = -1; xOffset <= 1; xOffset++) {
            std::vector<Object *> &objectList = objects[screenX + xOffset][screenY + yOffset];
            for (int i = 0; i < objectList.size(); i++) {
                if (object != objectList[i]) {
                    double distance = object->getPosition().distanceTo(objectList[i]->getPosition());
                    if (distance < smallestDistance) {
                        nearestObject = objectList[i];
                        smallestDistance = distance;
                    }
                }
            }
        }
    }
    
    return nearestObject;
}

std::vector<Object *> Environment::getNearestObjects(Object *object) {
    std::vector<Object *> objectsSortedByDist;
    
    int screenX = (int) ((object->getPosition().getX() / SCREEN_WIDTH));
    int screenY = (int) ((object->getPosition().getY() / SCREEN_HEIGHT));
    for (int yOffset = -1; yOffset <= 1; yOffset++) {
        for (int xOffset = -1; xOffset <= 1; xOffset++) {
            std::vector<Object *> &objectList = objects[screenX + xOffset][screenY + yOffset];
            for (int i = 0; i < objectList.size(); i++) {
                if (object != objectList[i]) {
                    objectsSortedByDist.push_back(objectList[i]);
                }
            }
        }
    }
    
    sort(objectsSortedByDist.begin(), objectsSortedByDist.end(), ObjectComparator(object));
    return objectsSortedByDist;
}

Vector2D Environment::getObjectScreen(Object *object) {
    int screenX = (int) ((object->getPosition().getX() / SCREEN_WIDTH));
    int screenY = (int) ((object->getPosition().getY() / SCREEN_HEIGHT));
    
    return Vector2D(screenX, screenY);    
}

void Environment::updateObjectScreen(Object *object) {
    Vector2D screenBefore = object->getScreen();
    Vector2D screenAfter = getObjectScreen(object);
    
    if (!screenBefore.equals(screenAfter)) {
        removeObject(object);
        addObject(object);
    }
}

void Environment::setWindowCenter(Vector2D position) {
    windowCenter.setX(position.getX());
    windowCenter.setY(position.getY());
}

Vector2D Environment::getWindowPos(Vector2D worldPosition) {
    Vector2D windowWorldPosition = windowCenter.add(Vector2D(-SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2));
    Vector2D windowPosition = worldPosition.add(windowWorldPosition.mult(-1.0));
    
    return windowPosition;
}

void Environment::resetMovement() {
    movementVector = Vector2D(0.0, 0.0);
}

Vector2D Environment::getMovement() {
    return movementVector;
}

void Environment::movingUp(bool state) {
    if (player)  {
        if (state) {
            movementVector = movementVector.add(Vector2D(0.0, -player->getSpeed()));
        } else {
            movementVector = movementVector.add(Vector2D(0.0, player->getSpeed()));        
        }
    }
}

void Environment::movingDown(bool state) {
    if (player) {
        if (state) {
            movementVector = movementVector.add(Vector2D(0.0, player->getSpeed()));
        } else {
            movementVector = movementVector.add(Vector2D(0.0, -player->getSpeed()));        
        }
    }
}

void Environment::movingLeft(bool state) {
    if (player) {
        if (state) {
            movementVector = movementVector.add(Vector2D(-player->getSpeed(), 0.0));
        } else {
            movementVector = movementVector.add(Vector2D(player->getSpeed(), 0.0));        
        }
    }
}

void Environment::movingRight(bool state) {
    if (player) {
        if (state) {
            movementVector = movementVector.add(Vector2D(player->getSpeed(), 0.0));
        } else {
            movementVector = movementVector.add(Vector2D(-player->getSpeed(), 0.0));        
        }
    }
}

void Environment::render(double dt) {
    if (player) {
        player->renderFeedback(this);
        player->render(this);
    }
}

void Environment::updateObjects(double dt) {
    for (int y = 1; y <= ENV_HEIGHT; y++) {
        for (int x = 1; x <= ENV_WIDTH; x++) {
            std::vector<Object *> objectList = objects[x][y];
            for (int i = 0; i < objectList.size(); i++) {
                objectList[i]->handleStimulus(this, dt);
            }
        }
    }
}

void Environment::spawnNewObjects() {
    for (int i = 0; i < objectsToSpawn.size(); i++) {
        addObject(objectsToSpawn[i]);
    }
    objectsToSpawn.clear();
}

void Environment::removeDeadObjects() {
    for (int y = 1; y <= ENV_HEIGHT; y++) {
        for (int x = 1; x <= ENV_WIDTH; x++) {
            std::vector<Object *> &objectList = objects[x][y];
            std::vector<Object *>::iterator it = objectList.begin();
            while (it != objectList.end()) {
                Object *object = (*it);
                if (object->shouldDestroy()) {
                    it = objectList.erase(it);   
                } else {
                    it++;
                }             
            }
        }
    }
}

void Environment::spawnObject(Object *object) {
    objectsToSpawn.push_back(object);
}
