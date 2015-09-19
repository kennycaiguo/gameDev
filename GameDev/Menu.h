#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <iostream>
#include <GL/glu.h>
#include <GL/gl.h>
#include <SDL/SDL.h>
#include <vector>
#include <string>
#include "CollisionPlane.h"
#include "Collision.h"
#include "Text.h"

class Menu{

    public:
        Menu(unsigned int back, std::vector<CollisionPlane>& pl, std::vector<std::string>& str, CollisionPlane bkPos, Text* t);
        ~Menu();
        int run();

    private:
        unsigned int background;
        std::vector<CollisionPlane> planes;
        std::vector<std::string> strings;
        Text* text;
        CollisionPlane* backPosition;
        SDL_Joystick *js;
        int currentSelection;
        bool isTest;
        void test();
};



#endif // MENU_H_INCLUDED
