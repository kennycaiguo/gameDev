#include "Camera.h"

// default constructor
Camera::Camera(){
    this->location.setX(0.0);
    this->location.setY(0.0);
    this->location.setZ(0.0);
    this->cameraYaw = 0.0;
    this->cameraPitch = 0.0;
    this->cameraSpeed = 0.2;
    this->mouseSpeed = 0.2;
    this->mi = false;

}

Camera::Camera(const Vector3d& location){
    this->location.setX(location.getX());
    this->location.setY(location.getY());
    this->location.setZ(location.getZ());
    this->cameraYaw = 0.0;
    this->cameraPitch = 0.0;
    this->cameraSpeed = 0.2;
    this->mouseSpeed = 0.2;
    this->mi = false;
}

Camera::Camera(const Vector3d& location, const float& yaw, const float& pitch){
    this->location.setX(location.getX());
    this->location.setY(location.getY());
    this->location.setZ(location.getZ());
    this->cameraYaw = yaw;
    this->cameraPitch = pitch;
    this->cameraSpeed = 0.2;
    this->mouseSpeed = 0.2;
    this->mi = false;
}

Camera::Camera(const Vector3d& location, const float& yaw, const float& pitch, const float& speed, const float& mousespeed){
    this->location.setX(location.getX());
    this->location.setY(location.getY());
    this->location.setZ(location.getZ());
    this->cameraYaw = yaw;
    this->cameraPitch = pitch;
    this->cameraSpeed = speed;
    this->mouseSpeed = mousespeed;
    this->mi = false;
}
// destructor
Camera::~Camera(){
    std::cout << "Camera destroyed" << std::endl;
}

void Camera::keyboardControl(){
	if(mi){
        int MidX = 1280 / 2;
		int MidY = 1040 / 2;
		SDL_ShowCursor(SDL_DISABLE);
		int tmpx,tmpy;
		SDL_GetMouseState(&tmpx,&tmpy);
		this->cameraYaw += mouseSpeed * (MidX-tmpx);
		this->cameraPitch += mouseSpeed * (MidY-tmpy);
		lockCamera();
		SDL_WarpMouse(MidX,MidY);
		Uint8* state = SDL_GetKeyState(NULL);
		if(state[SDLK_w]){
				moveCamera(0.0);
		}else if(state[SDLK_s]){
				moveCamera(180.0);
		}
		if(state[SDLK_a])
			moveCamera(90.0);
		else if(state[SDLK_d])
			moveCamera(270);
	}
	glRotatef(-this->cameraPitch, 1.0, 0.0, 0.0);
	glRotatef(-this->cameraYaw, 0.0, 1.0, 0.0);
}

void Camera::joystickControl(SDL_Joystick* joystick){
	int x_move, y_move;
	float yaw, pitch;
	SDL_ShowCursor(SDL_DISABLE);
	x_move = SDL_JoystickGetAxis(joystick, 0);
	y_move = SDL_JoystickGetAxis(joystick, 1);
	yaw = SDL_JoystickGetAxis(joystick, 3);
	pitch = SDL_JoystickGetAxis(joystick, 4);
	//float h = sqrt((float(x_move) * float(x_move)) + (float(y_move) * float(y_move)));
	this->cameraYaw += cameraSpeed * (yaw / 3600);
	this->cameraPitch += cameraSpeed * (pitch / 3600);
	lockCamera();
	float velocity = 0.5;
	if( x_move > 3200 ){
		moveCamera(180.0, velocity);
	}
	if( x_move < -3200 ){
		moveCamera(0.0, velocity);
	}
	if( y_move > 3200 ){
		moveCamera(270.0, velocity);
	}
	if( y_move < -3200 ){
		moveCamera(90.0, velocity);
	}
	glRotatef(this->cameraPitch, 1.0, 0.0, 0.0);
	glRotatef(this->cameraYaw, 0.0, 1.0, 0.0);
}

void Camera::update(){
    glTranslatef(-location.x, -location.y, -location.z);
}

Vector3d Camera::getCameraVector() const{
    Math3d math;
    return (Vector3d(-cos(math.degreesToRadians(cameraPitch)) * sin(math.degreesToRadians(cameraYaw)),
                      sin(math.degreesToRadians(cameraPitch)),
                     -cos(math.degreesToRadians(cameraPitch)) * cos(math.degreesToRadians(cameraYaw))));
}

void Camera::setCameraLocation(const Vector3d& newPosition){
    this->location = newPosition;
}

Vector3d Camera::getCameraLocation() const{
    return this->location;
}

float Camera::getCameraYaw() const{
    return this->cameraYaw;
}

float Camera::getCameraPitch() const{
    return this->cameraPitch;
}

void Camera::lookAt(const float& yaw, const float& pitch){
    this->cameraYaw = yaw;
    this->cameraPitch = pitch;
}

void Camera::mouseIn(){
    this->mi = true;
}

void Camera::mouseOut(){
    this->mi = false;
}

bool Camera::isMouseIn(){
    return this->mi;
}

void Camera::setCameraSpeed(float speed){
    this->cameraSpeed = speed;
    this->mouseSpeed = 0.2;
}

void Camera::setMouseCameraSpeed(float speed, float ms){
    this->cameraSpeed = speed;
    this->mouseSpeed = ms;
}

void Camera::lockCamera(){
    if(cameraPitch > 90.0) cameraPitch = 90.0;
    if(cameraPitch < -90.0) cameraPitch = -90.0;
    if(cameraYaw < 0.0) cameraYaw += 360.0;
    if(cameraYaw > 360.0) cameraYaw -= 360.0;
}

void Camera::moveCamera(const float& direction){
    Math3d math;
    float rad = math.degreesToRadians(this->cameraYaw + direction);
    std::cout << "rad: " << rad << std::endl;
    this->location.x -= sin(rad) * this->cameraSpeed;
    std::cout << "x: " << location.x << std::endl;
    this->location.z -= cos(rad) * this->cameraSpeed;
    std::cout << "z: " << location.z << std::endl;
}

void Camera::moveCamera(const float& direction, float velocity){
    Math3d math;
    float rad = math.degreesToRadians(this->cameraYaw + direction);
    std::cout << "rad: " << rad << std::endl;
    this->location.x -= cos(rad) * velocity;
    std::cout << "x: " << location.x << std::endl;
    this->location.z -= sin(rad) * velocity;
    std::cout << "z: " << location.z << std::endl;
}

void Camera::moveCameraUp(const float& direction){
    Math3d math;
    float rad = math.degreesToRadians(this->cameraPitch + direction);
    this->location.y += sin(rad) * this->cameraSpeed;
}
