#ifndef SINGLEOBJECT_H_INCLUDED
#define SINGLEOBJECT_H_INCLUDED
#include <vector>
#include <cstdlib>
#include <iostream>
#include "CollisionPlane.h"

class SingleObject{

    public:
        SingleObject(std::vector<unsigned int>& frames, std::vector<CollisionPlane>& collisionPlane, std::string& name, int id);
        ~SingleObject();
        std::string& getName();
        int getId() const;

    private:
        std::vector<unsigned int> frames;
        std::vector<CollisionPlane> collisionPlanes;
        std::string name;
        int id;

};



#endif // SINGLEOBJECT_H_INCLUDED
