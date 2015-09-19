#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include "Vector3d.h"
#include "Collision.h"
#include "CollisionSphere.h"
#include "CollisionPlane.h"
#include "Camera.h"

class Player{

    public:
        Player(std::string n, CollisionSphere cs, float speed, float looksp, float spSpeed);
        ~Player();
        Camera cam;
        void update(std::vector<CollisionPlane>& cp);
        void jump();
        void decreaseHealth(int dh);
        void increaseHealth(int dh);
        void setSprint(bool isSprint);
        bool isSprinting();
        void addPoints(int points);
        int getPoints();

        // Accessor's
        CollisionSphere getPlayersCollisionSphere();
        void setPlayersName(std::string n);
        std::string getPlayersName();
        Camera* getPlayersCamera();
        void setPlayersPosition(Vector3d position);
        int getPlayersHealth();
        void setPlayersHealth(int h);


    private:
        std::string name;
        CollisionSphere playerCollSphere;
        int health;
        Vector3d force;
        Vector3d direction;
        bool isGrounded;
        bool isCollision;
        float sprintSpeed;
        float normalSpeed;
        float lookSpeed;
        bool isSprint;
        float energy;
        int points;

};



#endif // PLAYER_H_INCLUDED
