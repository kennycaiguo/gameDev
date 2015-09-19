#include "Object.h"

Object::Object(){

}

Object::~Object(){
    std::cout << "Object deleted" << std::endl;
}
// adds single object's and their position's
void Object::add(std::vector<unsigned int>& frames,
                           std::vector<CollisionPlane>& collisionPlanes,
                           Vector3d position, std::string name, int id){
    for(int i = 0; i < singleObjects.size(); i++){
        if(singleObjects[i].getId() == id){
            objectPositions.push_back(ObjectPosition(id, position));
            return;
        }else{
            singleObjects.push_back(SingleObject(frames, collisionPlanes, name, id));
            objectPositions.push_back(ObjectPosition(id, position));
            return;
        }
    }
}
// adds an objects' position by comparing the id
void Object::add(int id, Vector3d position){
    for(int j = 0; j < singleObjects.size(); j++){
        if(singleObjects[j].getId() == id){
           objectPositions.push_back(ObjectPosition(id, position));
           return;
        }
    }
}
// adds an object's position by comparing the name
void Object::add(std::string name, Vector3d position){
    for(int j = 0; j < singleObjects.size(); j++){
        if(singleObjects[j].getName() == name){
           objectPositions.push_back(ObjectPosition(singleObjects[j].getId(), position));
           return;
        }
    }
}
// removes a single object from the list by the object's id
bool Object::deleteById(int id){
    for(int k = 0; k < singleObjects.size(); k++){
        if(singleObjects[k].getId() == id){
            singleObjects.erase(singleObjects.begin() + k);
            return 1;
        }
    }
    return 0;
}
// removes a single object from the list by the object's name
bool Object::deleteByName(std::string name){
    for(int m = 0; m < singleObjects.size(); m++){
        if(singleObjects[m].getName() == name){
            singleObjects.erase(singleObjects.begin() + m);
            return 1;
        }
    }
    return 0;
}












