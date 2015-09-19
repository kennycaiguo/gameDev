#include "Math3d.h"

Math3d::Math3d(){
}

Math3d::~Math3d(){
    std::cout << "Math3d destroyed" << std::endl;
}

float Math3d::sine(float y, float h){
    return y / h;
}

float Math3d::cosine(float x, float h){
    return x / h;
}

float Math3d::tangent(float y, float x){
    return y / x;
}

float Math3d::degreesToRadians(float degrees){
    return (Math::PI / 180) * degrees;
}

float Math3d::radiansToDegrees(float radians){
    return (180 / Math::PI) * radians;
}

float Math3d::hypotenuse(float a, float b, float ddAngle){
    return sqrt(a * a + b * b - 2 * a * b * cos(degreesToRadians(ddAngle)));
}




