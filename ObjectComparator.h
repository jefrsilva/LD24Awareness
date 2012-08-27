#ifndef _OBJECT_COMPARATOR_H
#define _OBJECT_COMPARATOR_H

class Object;

class ObjectComparator {
    protected:
        Object *sortObj;
        
    public:
        ObjectComparator(Object *sortObj);
        ~ObjectComparator();
        
        bool operator()(Object *objA, Object *objB);
};

#endif
