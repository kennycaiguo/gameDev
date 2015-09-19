#include "Menu.h"

// constructor
Menu::Menu(unsigned int back, std::vector<CollisionPlane>& pl, std::vector<std::string>& str, CollisionPlane bkPos, Text* t){
	background = back;
	planes = pl;
	strings = str;
	backPosition = new CollisionPlane(bkPos);
	text = t;
	currentSelection = 0;
	isTest = false;
}
// destructor
Menu::~Menu(){
    delete backPosition;
}
// run
int Menu::run(){
	int dy = 0;
	js = SDL_JoystickOpen(0);
	bool b1 = glIsEnabled(GL_LIGHTING);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glLoadIdentity();
	currentSelection = 0;
	Uint32 start;
	SDL_Event event;
	int MENU_FLAG = 0;
	while(true){
		start = SDL_GetTicks();
		glLoadIdentity();
		glClear(GL_COLOR_BUFFER_BIT);
		test();
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_KEYDOWN:
					switch(event.key.keysym.sym){
						case SDLK_ESCAPE:
							if(b1)
								glEnable(GL_LIGHTING);
							glColor3f(1,1,1);
							return 1;
							break;
						case SDLK_UP:
							currentSelection--;
							if(currentSelection < 0)
								 currentSelection = planes.size()-1;
							break;
						case SDLK_DOWN:
							currentSelection++;
							if(currentSelection > planes.size() -1)
								currentSelection = 0;
							break;
						case SDLK_RETURN:
							if(b1)
								glEnable(GL_LIGHTING);
							glColor3f(1,1,1);
							return currentSelection;
							break;
						}
						break;
						// Joystick Axis
						case SDL_JOYAXISMOTION:
							dy = SDL_JoystickGetAxis(js, 1);
						    if(event.jaxis.value < -3200 || event.jaxis.value > 3200){
						    	if(event.jaxis.axis == 1){
						    		if(dy <= 1){
										currentSelection--;
										if(currentSelection < 0)
											 currentSelection = planes.size()-1;
										break;
						    		}else{
										currentSelection++;
										if(currentSelection > planes.size() -1)
											currentSelection = 0;
										break;
						    		}
						      }
						   }
						  break;
	                       case SDL_JOYBUTTONDOWN:
	                     	   if (event.jbutton.button == 0){
	                     		  return currentSelection;
	                     	   }
	                       break;
			}
		}
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,background);
		glColor3f(1,1,1);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0,0.0);
			glVertex3f(backPosition->getPlaneVertex1().x, backPosition->getPlaneVertex1().y, backPosition->getPlaneVertex1().z);
			glTexCoord2f(0.0,1.0);
			glVertex3f(backPosition->getPlaneVertex2().x, backPosition->getPlaneVertex2().y, backPosition->getPlaneVertex2().z);
			glTexCoord2f(1.0,1.0);
			glVertex3f(backPosition->getPlaneVertex3().x, backPosition->getPlaneVertex3().y, backPosition->getPlaneVertex3().z);
			glTexCoord2f(1.0,0.0);
			glVertex3f(backPosition->getPlaneVertex4().x, backPosition->getPlaneVertex4().y, backPosition->getPlaneVertex4().z);
	//		glVertex3f(-1,1,-2);
	//		glVertex3f(-1,-1,-2);
	//		glVertex3f(1,-1,-2);
	//		glVertex3f(1,1,-2);
		glEnd();
		glDisable(GL_TEXTURE_2D);
		std::cout << currentSelection << std::endl;
		for(int i=0;i < planes.size(); i++){
			if(i == currentSelection){
				std::cout << "i n" << std::endl;
				glBegin(GL_QUADS);
					glColor3f(1,0,0);
					glVertex3f(planes[i].getPlaneVertex1().x, planes[i].getPlaneVertex1().y + 0.04, planes[i].getPlaneVertex1().z);
					glColor3f(0,0,0);
					glVertex3f(planes[i].getPlaneVertex1().x, planes[i].getPlaneVertex1().y, planes[0].getPlaneVertex1().z);
					glVertex3f(planes[i].getPlaneVertex1().x +strings[i].length() * 0.032, planes[i].getPlaneVertex1().y, planes[i].getPlaneVertex1().z);
					glColor3f(1,0,0);
					glVertex3f(planes[i].getPlaneVertex1().x + strings[i].length() * 0.032,planes[i].getPlaneVertex1().y + 0.04, planes[i].getPlaneVertex1().z);
				glEnd();
			}
			glColor3f(0,0,0);
			Vector3d texPos(planes[i].getPlaneVertex1().getX() + .01, (planes[i].getPlaneVertex1().getY() + .01), planes[i].getPlaneVertex1().getZ());
			text->drawText(texPos, Vector3d(0, 0, 0), Vector3d(0.035, 0.035, 0.035), strings[i].c_str());
		}
		SDL_GL_SwapBuffers();
		if(1000/30>(SDL_GetTicks() - start))
			SDL_Delay(1000/30-(SDL_GetTicks() - start));
	}
	return 0;
}
// test function
void Menu::test(){
    float tmpX;
    float tmpY;
    float tmpY_1;
    float tmpY_2;
    float tmpY_3;
    float tmpY_4;
    if(isTest){
        Uint8* keys = SDL_GetKeyState(NULL);
        if(keys[SDLK_j]){
            tmpX = planes[0].getPlaneVertex1().x;
            tmpX-=0.1;
            planes[0].getPlaneVertex1().setX(tmpX);
		}
		if(keys[SDLK_l]){
            tmpX = planes[0].getPlaneVertex1().x;
            tmpX+=0.1;
            planes[0].getPlaneVertex1().setX(tmpX);
		}
		if(keys[SDLK_k]){
            tmpY = planes[0].getPlaneVertex1().y;
            tmpY-=0.1;
            planes[0].getPlaneVertex1().setY(tmpY);
		}
		if(keys[SDLK_i]){
            tmpY = planes[0].getPlaneVertex1().y;
            tmpY+=0.1;
            planes[0].getPlaneVertex1().setY(tmpY);
		}
		if(keys[SDLK_u]){
			//backPosition->getPlaneVertex1().y-=0.1;
            tmpY_1 = backPosition->getPlaneVertex1().y;
            tmpY_1-=0.1;
            backPosition->getPlaneVertex1().setY(tmpY_1);
			//backPosition->getPlaneVertex2().y-=0.1;
            tmpY_2 = backPosition->getPlaneVertex2().y;
            tmpY_2-=0.1;
            backPosition->getPlaneVertex2().setY(tmpY_2);
			//backPosition->getPlaneVertex3().y-=0.1;
            tmpY_3 = backPosition->getPlaneVertex3().y;
            tmpY_3-=0.1;
            backPosition->getPlaneVertex3().setY(tmpY_3);
			//backPosition->getPlaneVertex4().y-=0.1;
            tmpY_4 =backPosition->getPlaneVertex4().y;
            tmpY_4-=0.1;
            backPosition->getPlaneVertex4().setY(tmpY_4);
		}
		if(keys[SDLK_o]){
			//backPosition->getPlaneVertex1().y+=0.1;
            tmpY_1 = backPosition->getPlaneVertex1().y;
            tmpY_1+=0.1;
            backPosition->getPlaneVertex1().setY(tmpY_1);
			//backPosition->getPlaneVertex2().y+=0.1;
            tmpY_2 = backPosition->getPlaneVertex2().y;
            tmpY_2+=0.1;
            backPosition->getPlaneVertex2().setY(tmpY_2);
			//backPosition->getPlaneVertex3().y+=0.1;
            tmpY_3 = backPosition->getPlaneVertex3().y;
            tmpY_3+=0.1;
            backPosition->getPlaneVertex3().setY(tmpY_3);
			//backPosition->getPlaneVertex4().y+=0.1;
            tmpY_4 =backPosition->getPlaneVertex4().y;
            tmpY_4+=0.1;
            backPosition->getPlaneVertex4().setY(tmpY_4);
		}
		std::cout << planes[0].getPlaneVertex1()  << std::endl;

	}
}
