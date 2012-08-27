#include "Object.h"

Object::Object(ObjectType type) {
    this->type = type;
    destroyed = false;
}

double Object::getEnergy() {
    return 0.0;
}

ObjectType Object::getType() {
    return type;
}

void Object::setPosition(double x, double y) {
    position.setX(x);
    position.setY(y);
    bounds = BoundingBox((int) (x - (OBJECT_WIDTH / 2)), 
                         (int) (y - (OBJECT_HEIGHT / 2)), 
                         OBJECT_WIDTH, 
                         OBJECT_HEIGHT);  
}

Vector2D Object::getPosition() {
    return position;
}

void Object::translate(Vector2D translation) {
    position = position.add(translation);
    bounds = BoundingBox((int) (position.getX() - (OBJECT_WIDTH / 2)), 
                         (int) (position.getY() - (OBJECT_HEIGHT / 2)), 
                         OBJECT_WIDTH, 
                         OBJECT_HEIGHT);  
}

BoundingBox Object::getBounds() {
    return bounds;
}

void Object::setScreen(int screenX, int screenY) {
    screen.setX(screenX);
    screen.setY(screenY);
}

Vector2D Object::getScreen() {
    return screen;
}

double Object::getSpeed() {
    return speed;
}

void Object::addSensor(Sensor *sensor) {
    sensors.push_back(sensor);
}

void Object::collideWith(Environment *environment, Animal *animal) {
    
}

void Object::collideWith(Environment *environment, Wall *wall) {
    
}

void Object::collideWith(Environment *environment, Food *food) {
    
}

void Object::destroy() {
    destroyed = true;
}

bool Object::shouldDestroy() {
    return destroyed;
}

bool Object::isMoving() {
    return false;
}

ALLEGRO_SAMPLE *Object::getVoice() {
    return 0;
}

void Object::resetVoiceInterval() {
    
}

double Object::getVoiceInterval() {
    return 1000.0;
}

void Object::render(Environment *environment) {
    
}

bool Object::isVisible() {
    return true;
}
