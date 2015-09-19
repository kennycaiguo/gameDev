
#include "Vector3d.h"

Vector3d::Vector3d(){
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

Vector3d::Vector3d(float x, float y){
    this->x = x;
    this->y = y;
    this->z = 0.0;
}

Vector3d::Vector3d(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}

Vector3d::~Vector3d(){
    std::cout << "Vector3d destroyed" << std::endl;
}
// morph a point object to a vector
Vector3d* Vector3d::morphPoint3dToVector3d(Point3d* point){
    float x = point->getX();
    float y = point->getY();
    float z = point->getZ();
    return new Vector3d(x, y, z);
}
// returns the dot product of this vector and the one vector passed in
float Vector3d::dotProduct(const Vector3d* vector){
    return this->getX() * vector->getX() + this->getY() * vector->getY() + this->getZ() * vector->getZ();
}
// returns a new vectro (cross product) of this vector and the one passed in
Vector3d Vector3d::crossProduct(const Vector3d* vector){
    return (Vector3d(this->getY() * vector->getZ() - this->getZ() * vector->getY(),
                     this->getX() * vector->getZ() - this->getZ() * vector->getX(),
                     this->getX() * vector->getY() - this->getY() * vector->getX()));
}
// returns this vector's magnitude
float Vector3d::getMagnitude() const{
    return sqrt(this->getX() * this->getX() + this->getY() * this->getY() + this->getZ() * this->getZ());
}
// changes this vector's components
void Vector3d::changeVectorComponents(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}
// change this vector's x component
void Vector3d::changeComponentX(float x){
    this->x = x;
}
// change this vector's y component
void Vector3d::changeComponentY(float y){
    this->y = y;
}
// change this vector's z component
void Vector3d::changeComponentZ(float z){
    this->z = z;
}
// normalize this vector
void Vector3d::normalize(){
    float mag = this->getMagnitude();
    if(mag != 0){
        this->x /= mag;
        this->y /= mag;
        this->z /= mag;
    }
}
float Vector3d::inverseVectorDistance(Vector3d v1, Vector3d v2){
    Vector3d tmpVector(v1.getX() - v2.getX(),
                       v1.getY() - v2.getY(),
                       v1.getZ() - v2.getZ());
    return(sqrt(tmpVector.getX() * tmpVector.getX() +
                tmpVector.getY() * tmpVector.getY() +
                tmpVector.getZ() * tmpVector.getZ()));
}
float Vector3d::inverseVectorDistanceSquared(Vector3d v1, Vector3d v2){
     Vector3d tmpVector(v1.getX() - v2.getX(),
                        v1.getY() - v2.getY(),
                        v1.getZ() - v2.getZ());
    return(tmpVector.getX() * tmpVector.getX() +
           tmpVector.getY() * tmpVector.getY() +
           tmpVector.getZ() * tmpVector.getZ());
}
// adds a vector to this one and returns a new one
Vector3d Vector3d::operator + (const Vector3d& vector){
    return (Vector3d(this->getX() + vector.getX(), this->getY() + vector.getY(), this->getZ() + vector.getZ()));
}
// adds a vector to this one and returns a new one
Vector3d Vector3d::operator + (const Vector3d* vector){
    return (Vector3d(this->getX() + vector->getX(), this->getY() + vector->getY(), this->getZ() + vector->getZ()));
}
// subtracts a vector from this one and returns a new one
Vector3d Vector3d::operator - (const Vector3d& vector){
    return (Vector3d(this->getX() - vector.getX(), this->getY() - vector.getY(), this->getZ() - vector.getZ()));
}
// subtracts a vector from this one and returns a new one
Vector3d Vector3d::operator - (const Vector3d* vector){
     return (Vector3d(this->getX() - vector->getX(), this->getY() - vector->getY(), this->getZ() - vector->getZ()));
}
// multiplies this vector by a scalar quantity and returns a new vector
Vector3d Vector3d::operator * (const float scalar){
    return (Vector3d(this->getX() * scalar, this->getY() * scalar, this->getZ() * scalar));
}
// divides this vector by a scalar quantity and returns a new vector
Vector3d Vector3d::operator / (const float scalar){
    return (Vector3d(this->getX() / scalar, this->getY() / scalar, this->getZ() / scalar));
}
// adds a vector to this one
Vector3d& Vector3d::operator += (const Vector3d& vector){
    this->setX(this->getX() + vector.getX());
    this->setY(this->getY() + vector.getY());
    this->setZ(this->getZ() + vector.getZ());
    return *this;
}
// adds a vector to this one
Vector3d& Vector3d::operator += (const Vector3d* vector){
    this->setX(this->getX() + vector->getX());
    this->setY(this->getY() + vector->getY());
    this->setZ(this->getZ() + vector->getZ());
    return *this;
}
// subtracts a vector to this one
Vector3d& Vector3d::operator -= (const Vector3d& vector){
    this->setX(this->getX() - vector.getX());
    this->setY(this->getY() - vector.getY());
    this->setZ(this->getZ() - vector.getZ());
    return *this;
}
// subtracts a vector to this one
Vector3d& Vector3d::operator -= (const Vector3d* vector){
    this->setX(this->getX() - vector->getX());
    this->setY(this->getY() - vector->getY());
    this->setZ(this->getZ() - vector->getZ());
    return *this;
}
// multiplies a vector to this
Vector3d& Vector3d::operator *= (const float scalar){
    this->setX(this->getX() * scalar);
    this->setY(this->getY() * scalar);
    this->setZ(this->getZ() * scalar);
    return *this;
}
Vector3d& Vector3d::operator /= (const float scalar){
    this->setX(this->getX() / scalar);
    this->setY(this->getY() / scalar);
    this->setZ(this->getZ() / scalar);
    return *this;
}
bool Vector3d::operator == (const Vector3d& vector){
    return (this->x == vector.getX() && this->y == vector.getY() && this->z == vector.getZ());
}
bool Vector3d::operator == (const Vector3d* vector){
    return (this->x == vector->getX() && this->y == vector->getY() && this->z == vector->getZ());
}
bool Vector3d::operator != (const Vector3d& vector){
    return (this->x != vector.getX() && this->y != vector.getY() && this->z != vector.getZ());
}
bool Vector3d::operator != (const Vector3d* vector){
    return (this->x != vector->getX() && this->y != vector->getY() && this->z != vector->getZ());
}
std::ostream& operator << (std::ostream& out, Vector3d vector){
    out << "x: " << vector.getX() << "\t" << "y: " << vector.getY() << "\t" << "z: " << vector.getZ() << std::endl;
    return out;
}
// set the x coord
void Vector3d::setX(float x){
    this->x = x;
}
// get the x coord
float Vector3d::getX() const{
    return this->x;
}
// set the y coord
void Vector3d::setY(float y){
    this->y = y;
}
// get the y coord
float Vector3d::getY() const{
    return this->y;
}
// set the z coord
void Vector3d::setZ(float z){
    this->z = z;
}
// get the z coord
float Vector3d::getZ() const{
    return this->z;
}

