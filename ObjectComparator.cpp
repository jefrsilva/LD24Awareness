#include "ObjectComparator.h"
#include "Object.h"

ObjectComparator::ObjectComparator(Object *object) {
    sortObj = object;
}

ObjectComparator::~ObjectComparator() {
    
}

bool ObjectComparator::operator()(Object *objA, Object *objB) {
    double distAToObj = objA->getPosition().distanceTo(sortObj->getPosition());
    double distBToObj = objB->getPosition().distanceTo(sortObj->getPosition());
    
    return distAToObj < distBToObj;
}
