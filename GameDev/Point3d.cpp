#include "Point3d.h"

// default 3d point
Point3d::Point3d(){
    this->x = 0.0;
    this->y = 0.0;
    this->z = 0.0;
}
// 2d point
Point3d::Point3d(float x, float y){
    this->x = x;
    this->y = y;
    this->z = 0.0;
}
// 3d point
Point3d::Point3d(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}
// destructor
Point3d::~Point3d(){
    std::cout << "Point3d destroyed" << std::endl;
}
Point3d& Point3d::translatePoint(float trans_x, float trans_y, float trans_z){
    this->setX(trans_x);
    this->setY(trans_y);
    this->setZ(trans_z);
    return *this;
}
// returns the inverse distance or magnitude bewteen two points
float Point3d::inversePointDistance(Point3d p1, Point3d p2){
    Point3d tmpPoint(p1.getX() - p2.getX(),
                     p1.getY() - p2.getY(),
                     p1.getZ() - p2.getZ());
    return(sqrt(tmpPoint.getX() * tmpPoint.getX() +
                tmpPoint.getY() * tmpPoint.getY() +
                tmpPoint.getZ() * tmpPoint.getZ()));
}
// returns the inverse squared or magnitude squared bewteen two points
float Point3d::inversePointDistanceSquared(Point3d p1, Point3d p2){
    Point3d tmpPoint(p1.getX() - p2.getX(),
                     p1.getY() - p2.getY(),
                     p1.getZ() - p2.getZ());
    return(tmpPoint.getX() * tmpPoint.getX() +
           tmpPoint.getY() * tmpPoint.getY() +
           tmpPoint.getZ() * tmpPoint.getZ());
}
std::ostream& operator << (std::ostream& out, Point3d point){
    out << "x: " << point.getX() << "\t" << "y: " << point.getY() << "\t" << "z: " << point.getZ() << std::endl;
    return out;
}
// set x coord
void Point3d::setX(float x){
    this->x = x;
}
// set y coord
void Point3d::setY(float y){
    this->y = y;
}
// set z coord
void Point3d::setZ(float z){
    this->z = z;
}
// get x coord
float Point3d::getX() const{
    return this->x;
}
// get y coord
float Point3d::getY() const{
    return this->y;
}
// get z coord
float Point3d::getZ() const{
    return this->z;
}














