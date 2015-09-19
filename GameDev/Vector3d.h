#ifndef VECTOR3D_H_INCLUDED
#define VECTOR3D_H_INCLUDED
#include <iostream>
#include "Point3d.h"
#include "Math3d.h"

class Vector3d{

    public:
        Vector3d();
        Vector3d(Point3d* point);
        Vector3d(float x, float y);
        Vector3d(float x, float y, float z);
        ~Vector3d();
        // accessors
        float getX() const;
        float getY() const;
        float getZ() const;
        void setX(float x);
        void setY(float y);
        void setZ(float z);
        // memeber functions
        Vector3d* morphPoint3dToVector3d(Point3d* point);
        float dotProduct(const Vector3d* vector);
        Vector3d crossProduct(const Vector3d* vector);
        float getMagnitude() const;
        void changeVectorComponents(float x, float y, float z);
        void changeComponentX(float x);
        void changeComponentY(float y);
        void changeComponentZ(float z);
        void normalize();
        float inverseVectorDistance(Vector3d v1, Vector3d v2);
        float inverseVectorDistanceSquared(Vector3d v1, Vector3d v2);
        // vector operators
        Vector3d operator + (const Vector3d& vector);
        Vector3d operator + (const Vector3d* vector);
        Vector3d operator - (const Vector3d& vector);
        Vector3d operator - (const Vector3d* vector);
        Vector3d operator * (const float scalar);
        Vector3d operator / (const float scalar);
        Vector3d& operator += (const Vector3d& vector);
        Vector3d& operator += (const Vector3d* vector);
        Vector3d& operator -= (const Vector3d& vector);
        Vector3d& operator -= (const Vector3d* vector);
        Vector3d& operator *= (const float scalar);
        Vector3d& operator /= (const float scalar);
        bool operator == (const Vector3d& vector);
        bool operator == (const Vector3d* vector);
        bool operator != (const Vector3d& vector);
        bool operator != (const Vector3d* vector);
        friend std::ostream& operator << (std::ostream& out, Vector3d vector);
        float x, y, z;
};



#endif // VECTOR3D_H_INCLUDED
