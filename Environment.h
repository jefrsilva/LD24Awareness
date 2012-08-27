#ifndef _ENVIRONMENT_H
#define _ENVIRONMENT_H

#include <vector>
#include "Vector2D.h"
#include "BoundingBox.h"

class Object;

class Environment {
    private:
        static const int ENV_WIDTH = 9; // environment width in screens
        static const int ENV_HEIGHT = 9; // environment height in screens
        
        Object *player;
        Vector2D windowCenter;
        Vector2D movementVector;
        std::vector<Object *> objects[ENV_WIDTH + 2][ENV_HEIGHT + 2];
        std::vector<Object *> objectsToSpawn;
        
        int prizes;
              
    public:
        Environment();
        ~Environment();
        
        static const int SCREEN_WIDTH = 720;
        static const int SCREEN_HEIGHT = 720;
        
        void addPrize();
        bool isGameOver();
        bool isGameComplete();
        
        Vector2D getRandomSpawnPosition(int screenX, int screenY, int screensWidth, int screensHeight);
        void setupWorld();
        
        BoundingBox getBounds();
        void setPlayer(Object *object);
        Object *getPlayer();
        void addObject(Object *object);
        void removeObject(Object *object);
        std::vector<Object *> getAllObjects();
        Object *getNearestObject(Object *object);
        std::vector<Object *> getNearestObjects(Object *object);
        Vector2D getObjectScreen(Object *object);
        void updateObjectScreen(Object *object);
        
        void setWindowCenter(Vector2D position);
        Vector2D getWindowPos(Vector2D worldPosition);
        
        void resetMovement();
        Vector2D getMovement();
        void movingUp(bool state);
        void movingDown(bool state);
        void movingLeft(bool state);
        void movingRight(bool state);
        
        void render(double dt);
        void updateObjects(double dt);
        void spawnNewObjects();
        void removeDeadObjects();
        void spawnObject(Object *object);
};

#endif
