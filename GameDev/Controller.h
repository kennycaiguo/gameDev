#ifndef CONTROLLER_H_
#define CONTROLLER_H_
#include <iostream>

enum GAME_CONTROLLER{KEYBOARD = 0, STEEL_SERIES_3GC, XBOX, GENERIC};

class Controller {

	public:
		Controller();
		virtual ~Controller();
		void setType(GAME_CONTROLLER type);
		GAME_CONTROLLER getType() const;

	private:
		GAME_CONTROLLER type;
};

#endif /* CONTROLLER_H_ */
