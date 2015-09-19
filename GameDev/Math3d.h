#ifndef MATH3D_H_INCLUDED
#define MATH3D_H_INCLUDED
#include <iostream>
#include <cmath>
#include "Constants.cpp"
#include "Vector3d.h"
#include "Point3d.h"

class Math3d{

    public:
        // constructor/destructor
        Math3d();
        ~Math3d();
        // class member functions
        float sine(float y, float h);
        float cosine(float x, float h);
        float tangent(float y, float x);
        float degreesToRadians(float degrees);
        float radiansToDegrees(float radians);
        float hypotenuse(float a, float b, float ddAngle);

        // constants
        //const float PI = 3.141592654;

};



#endif // MATH3D_H_INCLUDED
