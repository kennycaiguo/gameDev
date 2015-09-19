#include "Collision.h"

// gets the area of a triangle using the Heron formula
float Collision::triangleArea(Vector3d p1, Vector3d p2, Vector3d p3){
    // get the length of the triagle's sides....a,b, and c
    float a = sqrt((p2.getX() - p1.getX()) * (p2.getX() - p1.getX()) +
                   (p2.getY() - p1.getY()) * (p2.getY() - p1.getY()) +
                   (p2.getZ() - p1.getZ()) * (p2.getZ() - p1.getZ()));
    float b = sqrt((p3.getX() - p2.getX()) * (p3.getX() - p2.getX()) +
                   (p3.getY() - p2.getY()) * (p3.getY() - p2.getY()) +
                   (p3.getZ() - p2.getZ()) * (p3.getZ() - p2.getZ()));
    float c = sqrt((p3.getX() - p1.getX()) * (p3.getX() - p1.getX()) +
                   (p3.getY() - p1.getY()) * (p3.getY() - p1.getY()) +
                   (p3.getZ() - p1.getZ()) * (p3.getZ() - p1.getZ()));
    // triangle's semi-parameter s
    float s = (a + b + c) / 2;
    return (sqrt(s * ((s - a) * (s - b) * (s - c))));
}
// gets the area of a triangle using the Heron formula
float Collision::triangleArea(Point3d p1, Point3d p2, Point3d p3){
    // get the length of the triagle's sides....a,b, and c
    float a = sqrt((p2.getX() - p1.getX()) * (p2.getX() - p1.getX()) +
                   (p2.getY() - p1.getY()) * (p2.getY() - p1.getY()) +
                   (p2.getZ() - p1.getZ()) * (p2.getZ() - p1.getZ()));
    float b = sqrt((p3.getX() - p2.getX()) * (p3.getX() - p2.getX()) +
                   (p3.getY() - p2.getY()) * (p3.getY() - p2.getY()) +
                   (p3.getZ() - p2.getZ()) * (p3.getZ() - p2.getZ()));
    float c = sqrt((p3.getX() - p1.getX()) * (p3.getX() - p1.getX()) +
                   (p3.getY() - p1.getY()) * (p3.getY() - p1.getY()) +
                   (p3.getZ() - p1.getZ()) * (p3.getZ() - p1.getZ()));
    // triangle's semi-parameter s
    float s = (a + b + c) / 2;
    return (sqrt(s * ((s - a) * (s - b) * (s - c))));
}
// Ray Sphere Collision - returns true if collsion exists
bool Collision::RaySphere(float centerSphereX, float centerSphereY, float centerSphereZ,
                          float directionX, float directionY, float directionZ,
                          float initialX, float initialY, float initialZ,
                          float radiusSphere, float* dist, Vector3d* collisionPoint){
    float b = 2 * (directionX * (initialX - centerSphereX) +
                   directionY * (initialY - centerSphereY) +
                   directionZ * (initialZ - centerSphereZ));
    float c = initialX * initialX - 2 * initialX * centerSphereX + centerSphereX * centerSphereX +
              initialY * initialY - 2 * initialY * centerSphereY + centerSphereY * centerSphereY +
              initialZ * initialZ - 2 * initialZ * centerSphereZ + centerSphereZ * centerSphereZ -
              radiusSphere * radiusSphere;
    float descriminant = (b * b - 4 * c);
    // if the descriminant < 0...no intersection
    if(descriminant < 0){
        return false;
    } else{
        if(dist != NULL){
            (*dist) = (-b + sqrt(descriminant)) / 2;
            if(collisionPoint != NULL){
                float x = initialX + (*dist) * directionX;
                float y = initialY + (*dist) * directionY;
                float z = initialZ + (*dist) * directionZ;
                collisionPoint->changeVectorComponents(x, y, z);
            }
        }
        return true;
    }
}
// Ray Plane Collision - returns true if collsion exists
bool Collision::RayPlane(const float& normalX, const float& normalY, const float& normalZ, float pointOnPlaneX, float pointOnPlaneY, float pointOnPlaneZ,
                         float initialX, float initialY, float initialZ, float directionX, float directionY, float directionZ,
                         Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4, float* distance, Vector3d* collisionPoint){

    // if the dot product == 0 then there is no collision
    if((directionX * normalX + directionY * normalY + directionZ * normalZ) == 0){
        return false;
    }
    float t = ((pointOnPlaneX * normalX + pointOnPlaneY * normalY + pointOnPlaneZ * normalZ -
                normalX * initialX - normalY * initialY - normalZ * initialZ) /
               (directionX * normalX + directionY * normalY + directionZ * normalZ));
    // if t is a negative.....or (in this case) < 0 the intersection point
    // is in the opposite direction... this indicates there is no collision
    // i like to think as t representing scalar time here....since time is directed
    // along a negative axis (which cant be)...it would denote no collision and evaluate to false.
    if(t < 0){
        return false;
    }
    // intialize a point that is used for testing the collision of the ray and a triangle of the plane.
    float x = initialX + t * directionX;
    float y = initialY + t * directionY;
    float z = initialZ + t * directionZ;
    Vector3d rayPoint(x, y, z);
    float precision = 0.3;
    // test to see if the sum of the three sub triangles equals the triangle from which they
    // are derived...precision is used here in case the subtraction of the triangles are off by say like .0000000001
    // exgerated i know, but used to illustrate the point. p1, p2, p3, and p4 are the vertices of the plane.
    // the first test in the if statement is for the first triangle after the quad was subdivided
    // simularly the second test in the if statement is for the other triangle.
    if(std::abs(triangleArea(p1, p2, p3) - (triangleArea(p1, p2, rayPoint) +
                triangleArea(p2, p3, rayPoint) + triangleArea(p1, p3, rayPoint))) < precision ||
       std::abs(triangleArea(p1, p3, p4) - (triangleArea(p1, p3, rayPoint) +
                triangleArea(p3, p4, rayPoint) + triangleArea(p1, p4, rayPoint))) < precision){
        if(distance != NULL){
            (*distance) = t;
            if(collisionPoint != NULL){
                collisionPoint->setX(x);
                collisionPoint->setY(y);
                collisionPoint->setZ(z);
            }
        }
        return true;

    }
    return false;
}
// Ray Plane Collision - returns true if collsion exists
bool Collision::RayPlane(const float& normalX, const float& normalY, const float& normalZ, float pointOnPlaneX, float pointOnPlaneY, float pointOnPlaneZ,
                         float initialX, float initialY, float initialZ, float directionX, float directionY, float directionZ,
                         Point3d p1, Point3d p2, Point3d p3, Point3d p4, float* distance, Vector3d* collisionPoint){

    // if the dot product == 0 then there is no collision
    if((directionX * normalX + directionY * normalY + directionZ * normalZ) == 0){
        return false;
    }
    float t = ((pointOnPlaneX * normalX + pointOnPlaneY * normalY + pointOnPlaneZ * normalZ -
                normalX * initialX - normalY * initialY - normalZ * initialZ) /
               (directionX * normalX + directionY * normalY + directionZ * normalZ));
    // if t is a negative.....or (in this case) < 0 the intersection point
    // is in the opposite direction... this indicates there is no collision
    // i like to think as t representing scalar time here....since time is directed
    // along a negative axis (which cant be)...it would denote no collision and evaluate to false.
    if(t < 0){
        return false;
    }
    // intialize a point that is used for testing the collision of the ray and a triangle of the plane.
    float x = initialX + t * directionX;
    float y = initialY + t * directionY;
    float z = initialZ + t * directionZ;
    Point3d rayPoint(x, y, z);
    float precision = 0.3;
    // test to see if the sum of the three sub triangles equals the triangle from which they
    // are derived...precision is used here in case the subtraction of the triangles are off by say like .0000000001
    // exgerated i know, but used to illustrate the point. p1, p2, p3, and p4 are the vertices of the plane.
    // the first test in the if statement is for the first triangle after the quad was subdivided
    // simularly the second test in the if statement is for the other triangle.
    if(std::abs(triangleArea(p1, p2, p3) - (triangleArea(p1, p2, rayPoint) +
                triangleArea(p2, p3, rayPoint) + triangleArea(p1, p3, rayPoint))) < precision ||
       std::abs(triangleArea(p1, p3, p4) - (triangleArea(p1, p3, rayPoint) +
                triangleArea(p3, p4, rayPoint) + triangleArea(p1, p4, rayPoint))) < precision){
        if(distance != NULL){
            (*distance) = t;
            if(collisionPoint != NULL){
                collisionPoint->setX(x);
                collisionPoint->setY(y);
                collisionPoint->setZ(z);
            }
        }
        return true;

    }
    return false;
}
// Sphere Plane Collision - returns true if collsion exists - takes Vector3d as params
bool Collision::SpherePlane(Vector3d& centerSphere, float radiusSphere,
                            Vector3d planeNormal, Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4){
    float dist1 = 0.0;
    float dist2 = 0.0;
    // this checks for the collsion on both sides of the plane
    if(RayPlane(planeNormal.getX(), planeNormal.getY(), planeNormal.getZ(), p1.getX(), p1.getY(), p1.getZ(),
                centerSphere.getX(), centerSphere.getY(), centerSphere.getZ(), -planeNormal.getX(), -planeNormal.getY(), -planeNormal.getZ(),
                p1, p2, p3, p4, &dist1) || RayPlane(-planeNormal.getX(), -planeNormal.getY(), -planeNormal.getZ(), p1.getX(), p1.getY(), p1.getZ(),
                centerSphere.getX(), centerSphere.getY(), centerSphere.getZ(), planeNormal.getX(), planeNormal.getY(), planeNormal.getZ(),
                p1, p2, p3, p4, &dist2)){
        if(dist1 > radiusSphere || dist2 > radiusSphere){ // if either distance is > the radiusSphere....no collision
            return false;
        }
        // indicates that we are on the side where dist1 has been determined to be > 0
        // the else is the other side of the plane. This calculates the point as well
        // as the new location of the sphere
        if(dist1 > 0 ){
            centerSphere.setX(centerSphere.getX() + planeNormal.getX() * (radiusSphere - dist1));
            centerSphere.setY(centerSphere.getY() + planeNormal.getY() * (radiusSphere - dist1));
            centerSphere.setZ(centerSphere.getZ() + planeNormal.getZ() * (radiusSphere - dist1));
        }else{
            centerSphere.setX(centerSphere.getX() + planeNormal.getX() * (radiusSphere - dist2));
            centerSphere.setY(centerSphere.getY() + planeNormal.getY() * (radiusSphere - dist2));
            centerSphere.setZ(centerSphere.getZ() + planeNormal.getZ() * (radiusSphere - dist2));
        }
        return true;
    }
    return false;
}
// Sphere Plane Collision - returns true if collsion exists - takes Point3d params
bool Collision::SpherePlane(Vector3d& centerSphere, float radiusSphere,
                            Vector3d planeNormal, Point3d p1, Point3d p2, Point3d p3, Point3d p4){
    float dist1 = 0.0;
    float dist2 = 0.0;
    // this checks for the collsion on both sides of the plane
    if(RayPlane(planeNormal.getX(), planeNormal.getY(), planeNormal.getZ(), p1.getX(), p1.getY(), p1.getZ(),
                centerSphere.getX(), centerSphere.getY(), centerSphere.getZ(), -planeNormal.getX(), -planeNormal.getY(), -planeNormal.getZ(),
                p1, p2, p3, p4, &dist1) || RayPlane(-planeNormal.getX(), -planeNormal.getY(), -planeNormal.getZ(), p1.getX(), p1.getY(), p1.getZ(),
                centerSphere.getX(), centerSphere.getY(), centerSphere.getZ(), planeNormal.getX(), planeNormal.getY(), planeNormal.getZ(),
                p1, p2, p3, p4, &dist2)){
        if(dist1 > radiusSphere || dist2 > radiusSphere){ // if either distance is > the radiusSphere....no collision
            return false;
        }
        // indicates that we are on the side where dist1 has been determined to be > 0
        // the else is the other side of the plane. This calculates the point as well
        // as the new location of the sphere
        if(dist1 > 0 ){
            centerSphere.setX(centerSphere.getX() + planeNormal.getX() * (radiusSphere - dist1));
            centerSphere.setY(centerSphere.getY() + planeNormal.getY() * (radiusSphere - dist1));
            centerSphere.setZ(centerSphere.getZ() + planeNormal.getZ() * (radiusSphere - dist1));
        }else{
            centerSphere.setX(centerSphere.getX() + planeNormal.getX() * (radiusSphere - dist2));
            centerSphere.setY(centerSphere.getY() + planeNormal.getY() * (radiusSphere - dist2));
            centerSphere.setZ(centerSphere.getZ() + planeNormal.getZ() * (radiusSphere - dist2));
        }
        return true;
    }
    return false;
}
// Sphere Sphere Collision - returns true if collsion exists
bool Collision::SphereSphere(Vector3d& centerSphere1, float radiusSphere1, Vector3d& centerSphere2, float radiusSphere2){
    Vector3d vec1;
    float dist = vec1.inverseVectorDistanceSquared(centerSphere1, centerSphere2);
    if(dist <= (radiusSphere1 + radiusSphere2) * (radiusSphere1 + radiusSphere2)){
        float a = sqrt((dist) - (radiusSphere1 - radiusSphere2));
        Vector3d vec2(centerSphere1 - centerSphere2);
        vec2.normalize();
        centerSphere1 = centerSphere1 + vec2 * a;
        return 1;
    }
    return 0;
}














