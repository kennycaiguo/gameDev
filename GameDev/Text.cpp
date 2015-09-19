#include "Text.h"

// constructor
Text::Text(std::vector<unsigned int>& ch, float w, float h){
	characters = ch;
	isTest = false;
	width = w;
	height = h;
	isLocked = false;
}
// destructor
Text::~Text(){
    std::cout << "Text deleted" << std::endl;
}
// this assignes the font
void Text::assignFont(std::vector<unsigned int>& ch, float w, float h){
	characters = ch;
	width = w;
	height = h;
}
// draws the text
void Text::drawText(Vector3d pos, Vector3d rot, Vector3d scale, const char* tex){

    bool b1 = glIsEnabled(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_2D);
    glColor3f(1, 1, 1);
    glPushMatrix();
    int g = 0;
    if(!isLocked){
        changePosition = pos;
        changeRotation = rot;
        changeScale = scale;
        isLocked = true;
    }
    if(isTest){
        test(changePosition, changeRotation, changeScale);
        glTranslatef(changePosition.getX(), changePosition.getY(), changePosition.getZ());
        glRotatef(changeRotation.getX(), 1.0 , 0.0, 0.0);
        glRotatef(changeRotation.getY(), 0.0 , 1.0, 0.0);
        glRotatef(changeRotation.getZ(), 0.0 , 0.0, 1.0);
    } else{
        glTranslatef(pos.getX(), pos.getY(), pos.getZ());
        glRotatef(rot.getX(), 1.0 , 0.0, 0.0);
        glRotatef(rot.getY(), 0.0 , 1.0, 0.0);
        glRotatef(rot.getZ(), 0.0 , 0.0, 1.0);
    }
    for(int i=0; i < strlen(tex); i++){
        if(tex[i] == '\n'){
            glTranslatef( -g*width, -height, 0);
            g = 0;
            continue;
        }
        if(tex[i] == ' '){
            glTranslatef( width * changeScale.getX(), 0.0, 0.0);
            g++;
            continue;
        }
        if(((int)tex[i])<33 || ((int)tex[i])>126)
            continue;
        glPushMatrix();
        if(isTest){
            glScalef(changeScale.getX(), changeScale.getY(), changeScale.getZ());
        }else{
            glScalef(scale.getX(), scale.getY(), scale.getZ());
        }
        glCallList(characters.at((int)tex[i] - 33));
        g++;
        glPopMatrix();
        glTranslatef(width * changeScale.getX(), 0.0, 0.0);
    }
    glPopMatrix();
    if(b1)
        glEnable(GL_TEXTURE_2D);
}
// used for test
void Text::test(Vector3d& pos, Vector3d& rot, Vector3d& scale){

    Uint8* key = SDL_GetKeyState(NULL);
	if(key[SDLK_f])
		pos.x -= 0.01;
	else if(key[SDLK_h])
		pos.x += 0.01;
	else if(key[SDLK_t])
		pos.y += 0.01;
	else if(key[SDLK_g])
		pos.y -= 0.01;
	else if(key[SDLK_z])
		pos.z -= 0.01;
	else if(key[SDLK_u])
		pos.z += 0.01;
	else if(key[SDLK_x]){
		scale.x += 0.005;
		scale.y += 0.005;
		scale.z += 0.005;
	}
	else if(key[SDLK_y]){
		scale.x -= 0.005;
		scale.y -= 0.005;
		scale.z -= .005;
	}
	std::cout << pos << rot << scale << std::endl;
}
// sets the test flag
void Text::setTest(bool b){
    isTest = b;
}
