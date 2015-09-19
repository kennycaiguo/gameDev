#include "SDL/SDL.h"
#include "GL/gl.h"
#include "GL/glut.h"
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdio>
#include <iostream>

#include "Camera.h"
#include "ObjectLoader.h"
#include "Player.h"

// screen attributes
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 1040;
const int SCREEN_BPP = 32;
// surfaces
SDL_Surface* screen = NULL;
// SDL event structure
SDL_Event event;
// object id's for the call list
int cubeId;
// object rotation angle
float angle = 0.0;
// object loader
ObjectLoader objectloader;
// Camera object used for this test
Camera cam;

Player player1("Tommy", CollisionSphere(Vector3d(0.0, 0.0, 0.0), 3.0), 0.2, 0.2, 0.7);


bool init(){
	// initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
		return false;
	}
	// get screen
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_OPENGL);
	// check screen initialized correctly
	if(screen != NULL){
		// initialize openGL
		glClearColor(0.0, 0.0, 0.75, 1.0);
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
        glLoadIdentity();
		gluPerspective(45, SCREEN_WIDTH / SCREEN_HEIGHT, 1.0, 500.0);
		glMatrixMode(GL_MODELVIEW);
		glEnable(GL_DEPTH_TEST);
		//cubeId = load_object("cube.obj");
		cubeId = objectloader.load("arena_floor.obj", NULL);
        //glEnable(GL_LIGHTING);  //we enable lighting, to make the 3D object to 3D
        //glEnable(GL_LIGHT0);
        //float col[]={1.0,1.0,1.0,1.0};  //light color is white
        //glLightfv(GL_LIGHT0,GL_DIFFUSE,col);
	}
	// set screen title
	SDL_WM_SetCaption("ObjectLoader Test", NULL);
	return true;
}
void update(){
    Vector3d norm(0.0, 1.0, 0.0);
    Vector3d p1(-100.0, -1.0, -100.0);
    Vector3d p2(-100.0, -1.0, 100.0);
    Vector3d p3(100.0, -1.0, 100.0);
    Vector3d p4(100.0, -1.0, -100.0);
    std::vector<CollisionPlane> collisionPlanes;
    collisionPlanes.push_back(CollisionPlane(norm, p1, p2, p3, p4));

    player1.update(collisionPlanes);

}

void draw(){

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    player1.getPlayersCamera()->keyboardControl();
    player1.getPlayersCamera()->update();
    //cam.control();
    //cam.update();
    //float pos[]={-1.0,1.0,-2.0,1.0};        //set the position
    //glLightfv(GL_LIGHT0,GL_POSITION,pos);
    //glTranslatef(0.0,0.0,-10.0);
	//glRotatef(30,1.0,0.0,0.0);
    //glRotatef(angle,0.0,1.0,0.0);
    glCallList(cubeId);



}

void clean_up(){
	// delete surfaces
	SDL_FreeSurface(screen);
	SDL_Quit();
}

int mainxxxxxx(int argc, char* argv[]){
	// looping flag
	bool isRunning = true;
	Uint32 start;
	if(init() == false){
		return EXIT_FAILURE;
	}

	while(isRunning){
		// check event que
		start = SDL_GetTicks();
		while(SDL_PollEvent(&event)){
		    switch(event.type){
		        case SDL_KEYDOWN :
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE :
                            isRunning = false;
                            break;
                    }
                    break;
                // mouse in to start camera
                case SDL_MOUSEBUTTONDOWN :
                    if(!player1.cam.isMouseIn()){
                        player1.cam.mouseIn();
                        break;
                    }
                // exit out of loop
                case SDL_QUIT :
                    isRunning = false;
                    break;
		    }

		}
		//update();
        draw();
        SDL_GL_SwapBuffers();
        angle+=0.5;
        if(angle>360)
        	angle-=360;
        if(1000/30>(SDL_GetTicks()-start))
            SDL_Delay(1000/30-(SDL_GetTicks()-start));

	}
	clean_up();
	return EXIT_SUCCESS;
}










