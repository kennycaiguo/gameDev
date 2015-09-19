#ifndef COLLISION_H_INCLUDED
#define COLLISION_H_INCLUDED
#include <cmath>
#include <iostream>
#include "Vector3d.h"
#include "Point3d.h"
#include "Math3d.h"

class Collision{

    public:
        // gets the area of a triangle using the Heron formula
        static float triangleArea(Vector3d p1, Vector3d p2, Vector3d p3);
        // gets the area of a triangle using the Heron formula
        static float triangleArea(Point3d p1, Point3d p2, Point3d p3);
        // checks for a Ray Sphere Collsion
        static bool RaySphere(float centerSphereX, float centerSphereY, float centerSphereZ, float directionX, float directionY, float directionZ,
                              float initialX, float initialY, float initialZ, float radiusSphere, float* dist=NULL, Vector3d* collisionPoint=NULL);
        // checks for a Ray Plane Collsion - takes a Vector3d for the plane vertices
        static bool RayPlane(const float& normalX, const float& normalY, const float& normalZ, float pointOnPlaneX, float pointOnPlaneY, float pointOnPlaneZ,
                             float initialX, float initialY, float initialZ, float directionX, float directionY, float directionZ,
                             Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4, float* distance = NULL, Vector3d* collisionPoint = NULL);
        // checks for a Ray Plane Collsion - takes a Vector3d for the plane vertices
        static bool RayPlane(const float& normalX, const float& normalY, const float& normalZ, float pointOnPlaneX, float pointOnPlaneY, float pointOnPlaneZ,
                             float initialX, float initialY, float initialZ, float directionX, float directionY, float directionZ,
                             Point3d p1, Point3d p2, Point3d p3, Point3d p4, float* distance = NULL, Vector3d* collisionPoint = NULL);
        // checks for a sphere plane collison - takes Vector3d params
        static bool SpherePlane(Vector3d& centerSphere, float radiusSphere, Vector3d planeNormal, Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4);
        // checks for a sphere plane collison - takes a Vector3d for the plane vertices
        static bool SpherePlane(Vector3d& centerSphere, float radiusSphere, Vector3d planeNormal, Point3d p1, Point3d p2, Point3d p3, Point3d p4);
        // checks for a sphere plane collison - takes a Point3d for the plane vertices
        static bool SphereSphere(Vector3d& centerSphere1, float radiusSphere1, Vector3d& centerSphere2, float radiusSphere2);

};


#endif // COLLISION_H_INCLUDED
