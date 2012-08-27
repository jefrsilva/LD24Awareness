#ifndef _BOUNDING_BOX_H
#define _BOUNDING_BOX_H

#include "Vector2D.h"

class BoundingBox {
    private:
        Vector2D upperLeft;
        Vector2D lowerRight;
    
    public:
        BoundingBox();
        BoundingBox(Vector2D a, Vector2D b);
        BoundingBox(int x, int y, int width, int height);
        ~BoundingBox();
        
        double getMinX();
        double getMaxX();
        double getMinY();
        double getMaxY();
        bool intersects(BoundingBox box);
};

#endif
