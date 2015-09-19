#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <GL/gl.h>
#include <GL/glu.h>

const int NUM_MENU_ITEMS = 2; // number of menu items in the main menu
static const int FPS = 30;
static const int SCREEN_WIDTH = 1280;
static const int SCREEN_HEIGHT = 1040;
static const int SCREEN_BPP = 32;
// menu items
static const int START = 0;
static const int  EXIT = 1;

class MainMenu{

    public:
        MainMenu();
        ~MainMenu();
        int showMainMenu();
        SDL_Surface* loadImage(std::string fname);
        void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination);

    private:
        const char* labels[NUM_MENU_ITEMS];
        SDL_Surface* menus[NUM_MENU_ITEMS];
        bool selected[NUM_MENU_ITEMS];
        SDL_Color color[2];
        SDL_Surface* alpha;
        SDL_Surface* screen;
        SDL_Surface* image = NULL;
        SDL_Surface* logo = NULL;
        TTF_Font* font;
        SDL_Joystick *js;
        Mix_Music* music;


};



#endif // MAINMENU_H_INCLUDED
