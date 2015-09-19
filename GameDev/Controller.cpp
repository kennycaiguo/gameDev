#include "Controller.h"
// default constructor..defaults to keyboard
Controller::Controller() {
	this->setType(KEYBOARD);
}

Controller::~Controller() {
	std::cout << "Controller destroyed" << std::endl;
}
// set the type of controller
void Controller::setType(GAME_CONTROLLER type){
	this->type = type;
}
// get the type of controller
GAME_CONTROLLER Controller::getType() const{
	return this->type;
}

