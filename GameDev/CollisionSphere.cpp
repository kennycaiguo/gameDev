#include "CollisionSphere.h"

// default constructor
CollisionSphere::CollisionSphere(){
    this->center.setX(0.0);
    this->center.setY(0.0);
    this->center.setZ(0.0);
    this->setRadius(0.0);
}

CollisionSphere::CollisionSphere(float x, float y, float z, float radius){
    this->center.setX(x);
    this->center.setY(y);
    this->center.setZ(z);
    this->setRadius(radius);
}

CollisionSphere::CollisionSphere(Vector3d center, float radius){
    this->center.setX(center.getX());
    this->center.setY(center.getY());
    this->center.setZ(center.getZ());
    this->setRadius(radius);
    this->scaleFactor = 1.0;
}

CollisionSphere::CollisionSphere(Point3d center, float radius){
    this->center.setX(center.getX());
    this->center.setY(center.getY());
    this->center.setZ(center.getZ());
    this->setRadius(radius);
    this->scaleFactor = 1.0;
}
// destructor
CollisionSphere::~CollisionSphere(){
    std::cout << "CollisionSphere destroyed" << std::endl;
}
void CollisionSphere::scaleSphere(){
    this->radius = this->radius * this->scaleFactor;
}
// set radius
void CollisionSphere::setRadius(float radius){
    this->radius = radius;
}
// get radius
float CollisionSphere::getRadius() const{
    return this->radius;
}
// set the sphere'a center point coordinates
void CollisionSphere::setCenter(float x, float y, float z){
    this->center.setX(0.0);
    this->center.setY(0.0);
    this->center.setZ(0.0);
}
// set the sphere'a center point with a vector
void CollisionSphere::setCenter(Vector3d center){
    this->center.setX(center.getX());
    this->center.setY(center.getY());
    this->center.setZ(center.getZ());
}
// set the sphere'a center point with a Point3d
void CollisionSphere::setCenter(Point3d center){
    this->center.setX(center.getX());
    this->center.setY(center.getY());
    this->center.setZ(center.getZ());
}
// get the center point in the form of a Vector3d
Vector3d CollisionSphere::getCenter() const{
    return this->center;
}
// set the scale factory for this sphere
void CollisionSphere::setScaleFactor(float scaleFactor){
    this->scaleFactor = scaleFactor;
}
// get the scale factor
float CollisionSphere::getScaleFactor() const{
    return this->scaleFactor;
}











