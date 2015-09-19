#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED
#include <iostream>
#include <string>
#include <cstring>
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>
#include "Vector3d.h"

class Text{

    public:
        Text(std::vector<unsigned int>& ch, float w, float h);
        ~Text();
        void assignFont(std::vector<unsigned int>& ch, float w, float h);
        void drawText(Vector3d pos, Vector3d rot, Vector3d scale, const char* tex);
        void test(Vector3d& pos, Vector3d& rot, Vector3d& scale);
        void setTest(bool b);

    private:
        std::vector<unsigned int> characters;
        float width;
        float height;
        bool isTest;
        bool isLocked;
        Vector3d changePosition;
        Vector3d changeRotation;
        Vector3d changeScale;

};



#endif // TEXT_H_INCLUDED
