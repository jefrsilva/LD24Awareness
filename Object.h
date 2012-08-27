#ifndef _OBJECT_H
#define _OBJECT_H

#include "Vector2D.h"
#include "BoundingBox.h"
#include "Sensor.h"
#include <vector>
#include <allegro5/allegro_audio.h>

class Animal;
class Food;
class Wall;

enum ObjectType {OBJ_TYPE_WALL, OBJ_TYPE_FOOD, OBJ_TYPE_ANIMAL, OBJ_TYPE_MONSTER};

class Object {
    private:
        ObjectType type;
        bool destroyed;
    
    protected:
        Vector2D screen;      
        Vector2D position;
        BoundingBox bounds;
        double speed;
        std::vector<Sensor *> sensors;

    public:
        static const int OBJECT_WIDTH = 48;
        static const int OBJECT_HEIGHT = 48;
        static const double MAX_ENERGY = 150.0;
        
        Object(ObjectType type);
        virtual ~Object() {};
           
        virtual double getEnergy();   
        ObjectType getType();
        void setPosition(double x, double y);    
        Vector2D getPosition();
        void translate(Vector2D translation);
        BoundingBox getBounds();
        void setScreen(int screenX, int screenY);
        Vector2D getScreen();
        
        double getSpeed();
        
        void addSensor(Sensor *sensor);
        
        virtual void handleStimulus(Environment *environment, double dt) = 0;
        virtual void renderFeedback(Environment *environment) = 0;
        
        virtual void collideWith(Environment *environment, Animal *animal);
        virtual void collideWith(Environment *environment, Wall *wall);
        virtual void collideWith(Environment *environment, Food *food);
        
        void destroy();
        bool shouldDestroy();
        virtual bool isMoving();
        virtual ALLEGRO_SAMPLE *getVoice();
        virtual void resetVoiceInterval();
        virtual double getVoiceInterval();
        
        virtual void render(Environment *environment);
        virtual bool isVisible();
};

#endif
