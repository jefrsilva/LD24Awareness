#include "BoundingBox.h"
#include <algorithm>

BoundingBox::BoundingBox() {
    
}

BoundingBox::BoundingBox(Vector2D a, Vector2D b) {
    upperLeft.setX(std::min(a.getX(), b.getX()));
    upperLeft.setY(std::min(a.getY(), b.getY()));
    lowerRight.setX(std::max(a.getX(), b.getX()));
    lowerRight.setY(std::max(a.getY(), b.getY()));
}

BoundingBox::BoundingBox(int x, int y, int width, int height) {
    upperLeft.setX(x);
    upperLeft.setY(y);
    lowerRight.setX(x + width);
    lowerRight.setY(y + height);
}

BoundingBox::~BoundingBox() {
    
}

double BoundingBox::getMinX() {
    return upperLeft.getX();
}

double BoundingBox::getMaxX() {
    return lowerRight.getX();
}

double BoundingBox::getMinY() {
    return upperLeft.getY();
}

double BoundingBox::getMaxY() {
    return lowerRight.getY();
}
    
bool BoundingBox::intersects(BoundingBox box) {
    bool intersects = true;
    
    if (getMaxX() < box.getMinX() || 
        getMinX() > box.getMaxX() || 
        getMaxY() < box.getMinY() || 
        getMinY() > box.getMaxY()) {
        intersects = false;
    }
        
    return intersects;
}
