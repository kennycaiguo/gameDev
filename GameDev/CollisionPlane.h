#ifndef COLLISIONPLANE_H_INCLUDED
#define COLLISIONPLANE_H_INCLUDED
#include <iostream>
#include "Point3d.h"
#include "Vector3d.h"

class CollisionPlane{

    public:
        CollisionPlane(float norm_x, float norm_y, float norm_z,
                       float vert1_x, float vert1_y, float vert1_z,
                       float vert2_x, float vert2_y, float vert2_z,
                       float vert3_x, float vert3_y, float vert3_z,
                       float vert4_x, float vert4_y, float vert4_z);
        CollisionPlane(Vector3d normal, Vector3d vert1, Vector3d vert2, Vector3d vert3, Vector3d vert4);
        ~CollisionPlane();
        bool isPlaneNormalValid();
        // accessors
        Vector3d getPlaneVertex1();
        Vector3d getPlaneVertex2();
        Vector3d getPlaneVertex3();
        Vector3d getPlaneVertex4();
        Vector3d getPlaneNormal();

    private:
        Vector3d planeVertex[4]; // the vertices of the plane
        Vector3d normal; // the planes normal


};



#endif // COLLISIONPLANE_H_INCLUDED
