#ifndef POINT3D_H_INCLUDED
#define POINT3D_H_INCLUDED
#include <iostream>
#include <cmath>

class Point3d{

    public:
        // constructors / destructor
        Point3d();
        Point3d(float x, float y);
        Point3d(float x, float y, float z);
        Point3d& translatePoint(float trans_x, float trans_y, float trans_z);
        ~Point3d();
        float inversePointDistance(Point3d p1, Point3d p2);
        float inversePointDistanceSquared(Point3d v1, Point3d v2);

        // accessor methods
        void setX(float x);
        void setY(float y);
        void setZ(float z);
        float getX() const;
        float getY() const;
        float getZ() const;

    private:
        float x, y, z;
};



#endif // POINT3D_H_INCLUDED
