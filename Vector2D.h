#ifndef _VECTOR2D_h
#define _VECTOR2D_h

class Vector2D {
      private:
              double x, y;
      
      public:
             Vector2D();
             Vector2D(double x, double y);
             Vector2D(Vector2D src, Vector2D dest);
             ~Vector2D();
             
             void setX(double x);
             double getX();
             void setY(double y);
             double getY();
             Vector2D add(Vector2D vector);
             Vector2D mult(double scalar);
             double distanceTo(Vector2D vector);
             Vector2D normalize();
             bool equals(Vector2D &vector);
};

#endif
