#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#ifndef GL_UNSIGNED_SHORT_5_6_5
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif
#include "Globals.h"

//enum GAME_CONTROLLER{KEYBOARD = 0, STEEL_SERIES_3GC, XBOX, GENERIC};

class Game{

    public:
        Game();
        ~Game();
        void start();
        void update();
        void show();

    private:
        ObjectLoader objLoader;
        Player* player1;
        bool running;
        unsigned int loadTexture(const char* filename);
        void showPosition(float x, float y, float z);
        void showInventoryMenu();
        void drawMenu(int health, float x, float y, float z, int point);
        void applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination);
        SDL_Surface* loadImage(std::string filename);
        void drawMenuBackground();
        void drawInventoryBackground();
        Vector3d direction;
        Vector3d startPoint;
        Vector3d camDirection;
        std::vector<Map> levels;
        Text* tex;
        MainMenu* mainMenu;
        TTF_Font *font;
        Menu* gameMenu;
        Mix_Music* music;
        Menu* bgTexture;
        std::ofstream out;
        std::vector<unsigned int> models;
        std::vector<unsigned int> textures;
        SDL_Event event;
        SDL_Surface* baseScreen;
        SDL_Surface* gameScreen;
        SDL_Surface* image = NULL;
        SDL_Surface* background = NULL;
        SDL_Joystick *js;
        int num_js;
        SDL_Rect* rect;

        //bool addTopList(int point, const char* name);

        // constants
        static const int FPS = 30;
        static const int SCREEN_WIDTH = 1280;
        static const int SCREEN_HEIGHT = 1040;
        static const int SCREEN_BPP = 32;

};



#endif // GAME_H_INCLUDED
