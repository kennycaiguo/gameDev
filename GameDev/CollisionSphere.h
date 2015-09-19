#ifndef COLLISIONSPHERE_H_INCLUDED
#define COLLISIONSPHERE_H_INCLUDED
#include <iostream>
#include "Vector3d.h"
#include "Point3d.h"

class CollisionSphere{

    public:
        // constructors/destructor
        CollisionSphere();
        CollisionSphere(float centerX, float centerY, float centerZ, float radius);
        CollisionSphere(Vector3d center, float radius);
        CollisionSphere(Point3d center, float radius);
        ~CollisionSphere();

        // class mathods - the default is one...you have to change it with the setter
        void scaleSphere();

        // accessor methods
        void setRadius(float radius);
        float getRadius() const;
        void setCenter(float x, float y, float z);
        void setCenter(Vector3d center);
        void setCenter(Point3d center);
        Vector3d getCenter() const;
        void setScaleFactor(float scaleFactor);
        float getScaleFactor() const;

    private:
        float scaleFactor;
        float radius;
        Vector3d center;
};



#endif // COLLISIONSPHERE_H_INCLUDED
