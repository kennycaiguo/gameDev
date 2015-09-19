#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Collision.h"
#include "CollisionPlane.h"
#include "CollisionSphere.h"
#include "Vector3d.h"
#include "Skybox.h"

class Map{

    public:
        Map(unsigned int m, std::vector<CollisionPlane>& cp, std::string n,
            std::vector<std::string>& skyImages, std::vector<Vector3d>& sp);
        void update();
        void show();
        std::vector<CollisionPlane>& getCollisionPlanes();
        std::string& getName();
        Skybox* getSkybox();
        void change(unsigned int m, std::vector<CollisionPlane>& cp, std::string n, std::string skyImages[]);
        std::vector<Vector3d>* getSpawnPoints();
        Vector3d* getRandomSpawnPoints();

    private:
        unsigned int mesh;
        std::vector<CollisionPlane> cp;
        std::vector<Vector3d> spawnPoints;
        std::string name;
        Skybox* sky;
};



#endif // LEVEL_H_INCLUDED
