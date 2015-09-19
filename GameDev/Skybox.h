#ifndef SKYBOX_H_INCLUDED
#define SKYBOX_H_INCLUDED
#ifndef GL_UNSIGNED_SHORT_5_6_5
#define GL_UNSIGNED_SHORT_5_6_5 0x8363
#endif
#ifndef GL_CLAMP_TO_EDGE
#define GL_CLAMP_TO_EDGE 0x812F
#endif
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>

class Skybox{

    public:
        Skybox();
        Skybox(const char* left, const char* back, const char* right,
               const char* front, const char* top, const char* bottom);
        ~Skybox();
        void changeSkybox(const char* left, const char* back, const char* right,
                          const char* front, const char* top, const char* bottom);
        void drawSkybox(float size);

    private:
        unsigned int images[6];
        enum {SKY_LEFT = 0, SKY_BACK, SKY_RIGHT, SKY_FRONT, SKY_TOP, SKY_BOTTOM};
        unsigned int loadTexture(const char* filename);
};



#endif // SKYBOX_H_INCLUDED
