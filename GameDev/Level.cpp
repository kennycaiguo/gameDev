#include "Level.h"
// constructor
Map::Map(unsigned int m, std::vector<CollisionPlane>& cp, std::string n,
std::vector<std::string>& skyImages, std::vector<Vector3d>& sp){
    this->mesh = m;
    this->cp = cp;
    this->name = n;
    this->sky = new Skybox(skyImages[0].c_str(), skyImages[1].c_str(), skyImages[2].c_str(),
                           skyImages[3].c_str(),skyImages[4].c_str(),skyImages[5].c_str());
    this->spawnPoints = sp;
}
// updates this map
void Map::update(){
    // TODO : code this out
}
// identify a call list with the mesh
void Map::show(){
    glCallList(mesh);
}
// returns this collision planes
std::vector<CollisionPlane>& Map::getCollisionPlanes(){
    return this->cp;
}
// returns the name of this map
std::string& Map::getName(){
    return this->name;
}
// returns the sky box used for this map
Skybox* Map::getSkybox(){
    return this->sky;
}
// change this level
void Map::change(unsigned int m, std::vector<CollisionPlane>& cp, std::string n, std::string skyImages[]){
    this->mesh = m;
    this->cp = cp;
    this->name = n;
    this->sky->changeSkybox(skyImages[0].c_str(), skyImages[1].c_str(), skyImages[2].c_str(),
                            skyImages[3].c_str(),skyImages[4].c_str(),skyImages[5].c_str());
}
// returns this maps spawnpoint list
std::vector<Vector3d>* Map::getSpawnPoints(){
    return &spawnPoints;
}
// returns a random spawn point for this map
Vector3d* Map::getRandomSpawnPoints(){
    return &(spawnPoints[rand()%spawnPoints.size()]);
}
