#include <iostream>
#include <cstdlib>
#include "Vector3d.h"
#include "Point3d.h"
#include "Math3d.h"

int main_1(int argc, char* argv[]){
    // Point3d
    Point3d* point1 = new Point3d();
    Point3d* point2 = new Point3d(27.9345, 35.6735);
    Point3d* point3 = new Point3d(7.9345, 5.6735, 6.487);
    // Vector3d
    Vector3d* vec1 = new Vector3d();
    Vector3d* vec2 = new Vector3d(27.9345, 45.6735);
    Vector3d* vec3 = new Vector3d(27.9345, 45.6735, 26.487);
    Vector3d* vec4 = vec3->morphPoint3dToVector3d(point3);
    std::cout << "============ VEC-1 ===============" << std::endl;
    std::cout << "x: " << vec1->getX() << std::endl;
    std::cout << "y: " << vec1->getY() << std::endl;
    std::cout << "z: " << vec1->getZ() << std::endl;
    std::cout << "============ VEC-2 ===============" << std::endl;
    std::cout << "x: " << vec2->getX() << std::endl;
    std::cout << "y: " << vec2->getY() << std::endl;
    std::cout << "z: " << vec2->getZ() << std::endl;
    std::cout << "============ VEC-3 ===============" << std::endl;
    std::cout << "x: " << vec3->getX() << std::endl;
    std::cout << "y: " << vec3->getY() << std::endl;
    std::cout << "z: " << vec3->getZ() << std::endl;
    std::cout << "========== VEC-4 (morphed) =========" << std::endl;
    std::cout << "x: " << vec4->getX() << std::endl;
    std::cout << "y: " << vec4->getY() << std::endl;
    std::cout << "z: " << vec4->getZ() << std::endl;
    std::cout << "========== Dot Product =========" << std::endl;
    std::cout << "dotProduct: " << vec4->dotProduct(vec3) << std::endl;
    std::cout << "========== Cross Product =========" << std::endl;
    Vector3d vec5 = vec4->crossProduct(vec3);
    std::cout << "dotProduct x: " << vec5.getX() << std::endl;
    std::cout << "dotProduct y: " << vec5.getY() << std::endl;
    std::cout << "dotProduct z: " << vec5.getZ() << std::endl;
    std::cout << "========== Magnitude =========" << std::endl;
    std::cout << "vec 5 mag: " << vec5.getMagnitude() << std::endl;
    std::cout << "========== VEC Components =========" << std::endl;
    Vector3d vec6(23.1, 34.2, 45.3);
    vec4->changeVectorComponents(vec6.getX(), vec6.getY(), vec6.getZ());
    std::cout << "vec4 x: " << vec4->getX() << std::endl;
    std::cout << "vec4 y: " << vec4->getY() << std::endl;
    std::cout << "vec4 z: " << vec4->getZ() << std::endl;
    vec4->changeComponentX(11.2);
    vec4->changeComponentY(22.3);
    vec4->changeComponentZ(33.4);
    std::cout << "vec4 x: " << vec4->getX() << std::endl;
    std::cout << "vec4 y: " << vec4->getY() << std::endl;
    std::cout << "vec4 z: " << vec4->getZ() << std::endl;
    std::cout << "========== Normalized =========" << std::endl;
    vec4->normalize();
    std::cout << "vec4 x: " << vec4->getX() << std::endl;
    std::cout << "vec4 y: " << vec4->getY() << std::endl;
    std::cout << "vec4 z: " << vec4->getZ() << std::endl;
    std::cout << "new magnitude: " << vec4->getMagnitude() << std::endl;
    std::cout << "========== Overload Add Tests =========" << std::endl;
    Vector3d vec7 = *(vec4) + vec6;
    std::cout << "vec7 x: " << vec7.getX() << std::endl;
    std::cout << "vec7 y: " << vec7.getY() << std::endl;
    std::cout << "vec7 z: " << vec7.getZ() << std::endl;
    std::cout << "new magnitude: " << vec7.getMagnitude() << std::endl;
    std::cout << "========== Overload Subtract Tests =========" << std::endl;
    Vector3d vec8 = *(vec4) - vec6;
    std::cout << "vec8 x: " << vec8.getX() << std::endl;
    std::cout << "vec8 y: " << vec8.getY() << std::endl;
    std::cout << "vec8 z: " << vec8.getZ() << std::endl;
    std::cout << "new magnitude: " << vec8.getMagnitude() << std::endl;
    std::cout << "======== Overload multiply scalar =========" << std::endl;
    Vector3d vec9 = *(vec4) * 2;
    std::cout << "vec9 x: " << vec9.getX() << std::endl;
    std::cout << "vec9 y: " << vec9.getY() << std::endl;
    std::cout << "vec9 z: " << vec9.getZ() << std::endl;
    std::cout << "new magnitude: " << vec9.getMagnitude() << std::endl;
    std::cout << "======== Overload divide scalar =========" << std::endl;
    Vector3d vec10 = *(vec4) / 2;
    std::cout << "vec10 x: " << vec10.getX() << std::endl;
    std::cout << "vec10 y: " << vec10.getY() << std::endl;
    std::cout << "vec10 z: " << vec10.getZ() << std::endl;
    std::cout << "new magnitude: " << vec10.getMagnitude() << std::endl;
    std::cout << "======== Overload Addition =========" << std::endl;
    Vector3d vec11 = *(vec4) += vec6;
    std::cout << "vec11 x: " << vec11.getX() << std::endl;
    std::cout << "vec11 y: " << vec11.getY() << std::endl;
    std::cout << "vec11 z: " << vec11.getZ() << std::endl;
    std::cout << "new magnitude: " << vec11.getMagnitude() << std::endl;
    vec10 += vec11;
    std::cout << "vec10 x: " << vec10.getX() << std::endl;
    std::cout << "vec10 y: " << vec10.getY() << std::endl;
    std::cout << "vec10 z: " << vec10.getZ() << std::endl;
    std::cout << "new magnitude: " << vec10.getMagnitude() << std::endl;
    std::cout << "======== Overload Subtraction =========" << std::endl;
    Vector3d vec12 = *(vec2) -= vec11;
    std::cout << "vec12 x: " << vec12.getX() << std::endl;
    std::cout << "vec12 y: " << vec12.getY() << std::endl;
    std::cout << "vec12 z: " << vec12.getZ() << std::endl;
    std::cout << "new magnitude: " << vec12.getMagnitude() << std::endl;
    vec12 -= vec11;
    std::cout << "vec12 x: " << vec12.getX() << std::endl;
    std::cout << "vec12 y: " << vec12.getY() << std::endl;
    std::cout << "vec12 z: " << vec12.getZ() << std::endl;
    std::cout << "new magnitude: " << vec12.getMagnitude() << std::endl;
    std::cout << "======== Scalar Multiplication =========" << std::endl;
    vec12 *= 2;
    std::cout << "vec12 x: " << vec12.getX() << std::endl;
    std::cout << "vec12 y: " << vec12.getY() << std::endl;
    std::cout << "vec12 z: " << vec12.getZ() << std::endl;
    std::cout << "new magnitude: " << vec12.getMagnitude() << std::endl;
    std::cout << "======== Scalar Division =========" << std::endl;
    vec12 /= 2;
    std::cout << "vec12 x: " << vec12.getX() << std::endl;
    std::cout << "vec12 y: " << vec12.getY() << std::endl;
    std::cout << "vec12 z: " << vec12.getZ() << std::endl;
    std::cout << "new magnitude: " << vec12.getMagnitude() << std::endl;
    std::cout << "======== vectors equalization =========" << std::endl;
    Vector3d* vec13 = new Vector3d(12.34, 423.21321, 645.323);
    Vector3d* vec14 = new Vector3d(10.00, 10.00, 10.00);
    bool isTrue1 = vec13 == vec13;
    std::cout << "vec13 == vec13: " << isTrue1 << std::endl;
    bool isTrue2 = vec13 == vec14;
    std::cout << "vec13 == vec14: " << isTrue2 << std::endl;
    bool isTrue3 = vec13 != vec13;
    std::cout << "vec13 != vec13: " << isTrue3 << std::endl;
    bool isTrue4 = vec13 != vec14;
    std::cout << "vec13 != vec14: " << isTrue4 << std::endl;
    vec11.x = 25.0;
    std::cout << *vec13 << std::endl;
    std::cout << vec11 << std::endl;







    delete vec1, vec2, vec3;

    float x = 50.0000;
    float y = 25.0000;
    float h = 55.9017;
    float ang = 26.56505118;

    Math3d math;
    std::cout << "========== sin-cos-tan =========" << std::endl;
    std::cout << "sinAng: " << math.sine(y, h) << std::endl;
    std::cout << "cosAng: " << math.cosine(x, h) << std::endl;
    std::cout << "tanAng: " << math.tangent(y, x) << std::endl;
    std::cout << "degrees->radians: " << math.degreesToRadians(26.56505118) << std::endl;
    std::cout << "radians->degrees" << math.radiansToDegrees(math.degreesToRadians(26.56505118)) << std::endl;
    std::cout << "hypotenuse: " << math.hypotenuse(x, y, 90.000) << std::endl;








    return EXIT_SUCCESS;
}
