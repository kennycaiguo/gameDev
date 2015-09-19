#include "SingleObject.h"

SingleObject::SingleObject(std::vector<unsigned int>& frames,
                           std::vector<CollisionPlane>& collisionPlane,
                           std::string& name, int id){
    this->frames = frames;
    this->collisionPlanes = collisionPlane;
    this->name = name;
    this->id = id;
}

SingleObject::~SingleObject(){
    std::cout << "SingleObject destroyed" << std::endl;
}
// returns the name of this single object
std::string& SingleObject::getName(){
    return this->name;
}
// returns the id of this single object
int SingleObject::getId() const{
    return this->id;
}
