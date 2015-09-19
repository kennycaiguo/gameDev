#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED
#include <iostream>
#include <vector>
#include <cstdlib>
#include "Vector3d.h"
#include "SingleObject.h"

// This structure is used to hold the objects position
struct ObjectPosition{
    int id;
    Vector3d position;
    ObjectPosition(int i, Vector3d& pos) : id(i), position(pos){};
};

class Object{

    public:
        Object();
        ~Object();
        void add(std::vector<unsigned int>& frames, std::vector<CollisionPlane>& collisionPlanes, Vector3d position, std::string name, int id);
        void add(int id, Vector3d position);
        void add(std::string name, Vector3d position);
        bool deleteById(int id);
        bool deleteByName(std::string name);

    private:
        std::vector<SingleObject> singleObjects;
        std::vector<ObjectPosition> objectPositions;
};



#endif // OBJECT_H_INCLUDED
