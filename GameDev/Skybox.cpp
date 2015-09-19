#include "Skybox.h"

// default constructor...id's the images with a numerical flag
Skybox::Skybox(){
    for(int i = 0; i < 6; i++){
        images[i] = 999;
    }
}
// overload constructor
Skybox::Skybox(const char* left, const char* back, const char* right,
        const char* front, const char* top, const char* bottom){
    // intialize the images with the is returned by the loadTexture()
    images[SKY_LEFT] = loadTexture(left);
    images[SKY_BACK] = loadTexture(back);
    images[SKY_RIGHT] = loadTexture(right);
    images[SKY_FRONT] = loadTexture(front);
    images[SKY_TOP] = loadTexture(top);
    images[SKY_BOTTOM] = loadTexture(bottom);
}
Skybox::~Skybox(){
    glDeleteTextures(6, &images[0]);
    std::cout << "Skybox deleted" << std::endl;
}
// changes textures
void Skybox::changeSkybox(const char* left, const char* back, const char* right,
                          const char* front, const char* top, const char* bottom){
    if(images[0] != 999)
        glDeleteTextures(6, &images[0]);
    // intialize the images with the is returned by the loadTexture()
    images[SKY_LEFT] = loadTexture(left);
    images[SKY_BACK] = loadTexture(back);
    images[SKY_RIGHT] = loadTexture(right);
    images[SKY_FRONT] = loadTexture(front);
    images[SKY_TOP] = loadTexture(top);
    images[SKY_BOTTOM] = loadTexture(bottom);

}

unsigned int Skybox::loadTexture(const char* filename){
	unsigned int num;	//the id for the texture
	glGenTextures(1,&num);	//we generate a unique one
	SDL_Surface* img = IMG_Load(filename);
    SDL_PixelFormat form = {NULL,32,4,0,0,0,0,8,8,8,8,0xff000000,0x00ff0000,0x0000ff00,0x000000ff,0,255};
	SDL_Surface* img2 = SDL_ConvertSurface(img, &form, SDL_SWSURFACE);
	glBindTexture(GL_TEXTURE_2D,num);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, img2->w, img2->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, img2->pixels);
	SDL_FreeSurface(img);
	SDL_FreeSurface(img2);
	return num;
}
// draws the skybox
void Skybox::drawSkybox(float size){
    	bool b1=glIsEnabled(GL_TEXTURE_2D);	//new, we left the textures turned on, if it was turned on
	bool b2=glIsEnabled(GL_LIGHTING);
	glDisable(GL_LIGHTING);	//turn off lighting, when making the skybox
	glDisable(GL_DEPTH_TEST);	//turn off depth texting
	glEnable(GL_TEXTURE_2D);	//and turn on texturing
	glColor3f(1,1,1);
	glBindTexture(GL_TEXTURE_2D,images[SKY_BACK]);	//use the texture we want
	glBegin(GL_QUADS);	//and draw a face
		//back face
		glTexCoord2f(0,0);	//use the correct texture vector3d
		glVertex3f(size/2,size/2,size/2);	//and a vertex
		glTexCoord2f(1,0);	//and repeat it...
		glVertex3f(-size/2,size/2,size/2);
		glTexCoord2f(1,1);
		glVertex3f(-size/2,-size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(size/2,-size/2,size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,images[SKY_LEFT]);
	glBegin(GL_QUADS);
		//left face
		glTexCoord2f(0,0);
		glVertex3f(-size/2,size/2,size/2);
		glTexCoord2f(1,0);
		glVertex3f(-size/2,size/2,-size/2);
		glTexCoord2f(1,1);
		glVertex3f(-size/2,-size/2,-size/2);
		glTexCoord2f(0,1);
		glVertex3f(-size/2,-size/2,size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,images[SKY_FRONT]);
	glBegin(GL_QUADS);
		//front face
		glTexCoord2f(1,0);
		glVertex3f(size/2,size/2,-size/2);
		glTexCoord2f(0,0);
		glVertex3f(-size/2,size/2,-size/2);
		glTexCoord2f(0,1);
		glVertex3f(-size/2,-size/2,-size/2);
		glTexCoord2f(1,1);
		glVertex3f(size/2,-size/2,-size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,images[SKY_RIGHT]);
	glBegin(GL_QUADS);
		//right face
		glTexCoord2f(0,0);
		glVertex3f(size/2,size/2,-size/2);
		glTexCoord2f(1,0);
		glVertex3f(size/2,size/2,size/2);
		glTexCoord2f(1,1);
		glVertex3f(size/2,-size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(size/2,-size/2,-size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,images[SKY_TOP]);
	glBegin(GL_QUADS);			//top face
		glTexCoord2f(1,0);
		glVertex3f(size/2,size/2,size/2);
		glTexCoord2f(0,0);
		glVertex3f(-size/2,size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(-size/2,size/2,-size/2);
		glTexCoord2f(1,1);
		glVertex3f(size/2,size/2,-size/2);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,images[SKY_BOTTOM]);
	glBegin(GL_QUADS);
		//bottom face
		glTexCoord2f(1,1);
		glVertex3f(size/2,-size/2,size/2);
		glTexCoord2f(0,1);
		glVertex3f(-size/2,-size/2,size/2);
		glTexCoord2f(0,0);
		glVertex3f(-size/2,-size/2,-size/2);
		glTexCoord2f(1,0);
		glVertex3f(size/2,-size/2,-size/2);
	glEnd();
	glEnable(GL_DEPTH_TEST);
	if(!b1)
		glDisable(GL_TEXTURE_2D);
	if(b2)
		glEnable(GL_LIGHTING);	//turn everything back, which we turned on, and turn everything off, which we have turned on.
}
