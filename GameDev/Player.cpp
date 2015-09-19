#include "Player.h"

// constructor
Player::Player(std::string n, CollisionSphere cs, float speed, float looksp, float spSpeed){
    // constructor parms
    this->setPlayersName(n);
    this->playerCollSphere = cs;
    //this->cam.setCameraSpeed(speed, lookSpeed);
    this->cam.setCameraSpeed(speed);
    this->sprintSpeed = spSpeed;
    this->normalSpeed = speed;
    this->lookSpeed = speed;
    // predetermined
    this->force.changeVectorComponents(0.0, -0.3, 0.0);
    this->direction.changeVectorComponents(0.0, 0.0, 0.0); // reset the player's direction
    this->setPlayersPosition(Vector3d(0.0, 10.0, 0.0)); // sets the spawn point
    this->isSprint = false;
    // intialize player stats
    this->health = 500;
    this->energy = 1000;
    this->points = 0;


}
// destrcutor
Player::~Player(){
    std::cout << "Player destroyed" << std::endl;
}

// Updates the player
void Player::update(std::vector<CollisionPlane>& cp){
    // gravitational force is in the negative direction here...see force initialization
    // in the contructor
    //std::cout << "direction.y" << direction.y << std::endl;
    //std::cout << "force.y" << force.y << std::endl;
    if(direction.y >= force.y){
        direction += force;
    }
    // get new position
    Vector3d newPosition(cam.getCameraLocation());
    newPosition += direction;
    // testPosition
    Vector3d testPos(newPosition);
    // check for sphere-plane collision
    for(int i = 0; i < cp.size(); i++){
        //SpherePlane(Vector3d& centerSphere, float radiusSphere, Vector3d planeNormal, Vector3d p1, Vector3d p2, Vector3d p3, Vector3d p4);
        Collision::SpherePlane(newPosition, playerCollSphere.getRadius(), cp[i].getPlaneNormal(),
                    cp[i].getPlaneVertex1(), cp[i].getPlaneVertex2(), cp[i].getPlaneVertex3(), cp[i].getPlaneVertex4());
    }
    if(newPosition.y > testPos.y){
        isGrounded = true;
    }
    this->setPlayersPosition(newPosition);
    // update player's energy
    if(energy < 10 && !isSprint){
        energy += 0.01;
    }
    // disable player's sprint ability while energy level is insufficient
    if(energy <= 0){
        this->setSprint(false);
    }

}
// checks if the player is on the ground...if so increases y component of
// the directional vector
void Player::jump(){
    if(isGrounded){
        isGrounded = false;
        direction.changeComponentY(2.0);
    }
}
// decreases a player's health status
void Player::decreaseHealth(int dh){
    this->health -= dh;
}
// increases a player's health status
void Player::increaseHealth(int dh){
    this->health += dh;
}
// toogles the player's movement as sprinting or not sprinting. If the player's energy level
// is greater than 3 (hard coded for for now)...then let the player sprint.
void Player::setSprint(bool isSprint){
    if(energy > 3){
        isSprint = true;
        //cam.setMouseCameraSpeed(sprintSpeed, lookSpeed);
        cam.setCameraSpeed(sprintSpeed);
    }else{
        isSprint = false;
        //cam.setMouseCameraSpeed(sprintSpeed, lookSpeed);
        cam.setCameraSpeed(normalSpeed);
    }
}
// returns the state of the sprint flag
bool Player::isSprinting(){
    return isSprint;
}
// adds points to the players current running total.
void Player::addPoints(int points){
    this->points += points;
}
// returns the current running total of the player's points
int Player::getPoints(){
    return this->points;
}
// returns the players bounding collision sphere
CollisionSphere Player::getPlayersCollisionSphere(){
    return this->playerCollSphere;
}
// gets the players name
std::string Player::getPlayersName(){
    return this->name;
}
// gets the players name
void Player::setPlayersName(std::string n){
    this->name = n;
}
// gets the player's camera
Camera* Player::getPlayersCamera(){
    return &this->cam;
}
// sets the player's current camera posisition and the player's bounding
// collision sphere
void Player::setPlayersPosition(Vector3d position){
    this->cam.setCameraLocation(position);
    this->playerCollSphere.setCenter(position);
}
// returns the players current health status
int Player::getPlayersHealth(){
    return this->health;
}
// sets the player's current health status
void Player::setPlayersHealth(int h){
    this->health = h;
}
