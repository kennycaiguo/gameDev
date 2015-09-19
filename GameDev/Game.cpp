#include "Game.h"
const int triangle = 1;
int menuId;
// constructor
Game::Game(){
    out.open("report.txt");
    srand(time(NULL));
    SDL_Init(SDL_INIT_EVERYTHING);
    //rect->w = 600;
    //rect->h = 600;
    //rect->x = 0;
    //rect->y = 0;
    this->gameScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_OPENGL | SDL_DOUBLEBUF | SDL_HWPALETTE | SDL_FULLSCREEN);
    //this->gameScreen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_OPENGL | SDL_DOUBLEBUF | SDL_HWPALETTE);
    menuId = loadTexture("data/cf.png");
    const SDL_VideoInfo* videoInfo = SDL_GetVideoInfo();
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    //SDL_SetClipRect(gameScreen, rect);
    Controller gc;
    //gc.setType(STEEL_SERIES_3GC);
    out << "Controller Type: " << gc.getType() << "\n";
    num_js = SDL_NumJoysticks();
    out << "Joystick Count: " << num_js << "\n";
    out << "Video Info: " << videoInfo->current_h << "\n";
    /* Print out information about each joystick. */
    for (int a = 0; a < num_js; a++){
    	js = SDL_JoystickOpen(a);
    	if (js == NULL){
    		out << "Unable to open joystick " << a << std::endl;
    	}else{
    		out << "Joystick:" <<  a << std::endl;
    		out << "\tName:" << SDL_JoystickName(a) << std::endl;
    		out << "\tAxes:" << SDL_JoystickNumAxes(js) << std::endl;
    		out << "\tTrackballs:" << SDL_JoystickNumBalls(js) << std::endl;
    		out << "\tButtons:" << SDL_JoystickNumButtons(js) << std::endl;
    		SDL_JoystickClose(js);
    	}
    }
    // open our joystick
    js = SDL_JoystickOpen(0);
    if (js == NULL){
    	out << "Unable to open joystick:1 - " << SDL_GetError() << std::endl;
    }

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,SCREEN_WIDTH / SCREEN_HEIGHT, 0.1, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	float col[]={0.5, 0.5, 0.5, 1.0};
	float amb[]={0.3, 0.3, 0.3, 1.0};
	player1 = new Player("Tommy", CollisionSphere(Vector3d(0.0, 0.0, 0.0), 3.0), 0.2, 0.2, 0.7);
    char tmp[10][300];
	int tmparr[10];
	float floatarr[12];
    //in.open("spawn.dat");
    std::ifstream in("spawn.dat");
	std::vector<Vector3d> sp;
	while(!in.eof()){
		in.getline(tmp[0],300);
		sscanf(tmp[0],"%d %d %d",&tmparr[0],&tmparr[1],&tmparr[2]);
		sp.push_back(Vector3d(tmparr[0],tmparr[1],tmparr[2]));
	}
	in.close();
    //std::ifstream in("game.dat");
    in.open("game.dat");
	out << "2\n";
    std::vector<std::string> skyb;
	std::vector<CollisionPlane> cp;
	//std::vector<Vector3d> sp;
	//isfired=false;
    in.getline(tmp[9], 300);
	out << "3\n";
    sscanf(tmp[9],"%s %s %s %s %s %s %s %s",tmp[0],tmp[1],tmp[2],tmp[3],tmp[4],tmp[5],tmp[6],tmp[7]);
    out << tmp[0] << std::endl;
    for(int i=1; i < 7; i++)
        out << tmp[i] << "\t";
    for(int i=1; i < 7; i++)
        skyb.push_back(tmp[i]);
	out << "4\n";
    out << tmp[7] << std::endl;
    unsigned int m = objLoader.load(tmp[7], &cp);
    levels.push_back(Map(m, cp, tmp[0], skyb, sp));
    std::cout << "cp size: " << cp.size() << std::endl;
    for(int i=0; i < cp.size(); i++)
        std::cout << cp[i].getPlaneNormal()
        << "p1 x: " << cp[i].getPlaneVertex1().getX() << "p1 y: " << cp[i].getPlaneVertex1().getY() << "p1 z: " << cp[i].getPlaneVertex1().getZ()
        << "p2 x: " << cp[i].getPlaneVertex2().getX() << "p2 y: " << cp[i].getPlaneVertex2().getY() << "p2 z: " << cp[i].getPlaneVertex2().getZ()
        << "p3 x: " << cp[i].getPlaneVertex3().getX() << "p3 y: " << cp[i].getPlaneVertex3().getY() << "p3 z: " << cp[i].getPlaneVertex3().getZ()
        << "p4 x: " << cp[i].getPlaneVertex4().getX() << "p4 y: " << cp[i].getPlaneVertex4().getY() << "p4 z: " << cp[i].getPlaneVertex4().getZ()
        << std::endl;
	in.close();

    std::vector<unsigned int> chars;
	char c[50];
	for(int i=0; i< 94; i++){
		sprintf(c,"font/%d.obj",i);
		unsigned int tmp = objLoader.load(c,NULL);
		chars.push_back(tmp);
	}
	tex = new Text(chars,0.8,0.8);
    out << "Text" << std::endl;
    // menu
	unsigned int texture = loadTexture("data/cf.png");
	std::vector<CollisionPlane> cps;
	cps.push_back(CollisionPlane(0, 0, 1, -0.13, 0.16, -1, -0.13, 0.16, -1, -0.13, 0.16, -1, -0.13, 0.16, -1));
	cps.push_back(CollisionPlane(0, 0, 1, -0.13, 0.08, -1, -0.13, 0.16, -1, -0.08, 0.16, -1, -0.13, 0.16, -1));
	std::vector<std::string> strs;
	strs.push_back(std::string("Continue"));
	strs.push_back(std::string("Exit"));
	CollisionPlane xyz(0,0,1,-1.33,1,-2.4,-1.33,-1,-2.4,1.33,-1,-2.4,1.33,1,-2.4);
	gameMenu = new Menu(texture, cps, strs, xyz, tex);
	music=Mix_LoadMUS("data/sound/hive.wav");
	Mix_PlayMusic(music,-1);

}
// game destructor
Game::~Game(){
    for(std::vector<unsigned int>::const_iterator it=textures.begin();it!=textures.end();it++){
		glDeleteTextures(1,&(*it));
	}
	SDL_FreeSurface(baseScreen);
	SDL_FreeSurface(gameScreen);
	SDL_FreeSurface(image);
	SDL_FreeSurface(background);
    SDL_JoystickClose(js);
	//for(int i=0;i<sounds.size();i++)
	//	Mix_FreeChunk(sounds[i]);
	Mix_FreeMusic(music);
	Mix_CloseAudio();
	SDL_Quit();
}
// this is used for the menus and the font textures
unsigned int Game::loadTexture(const char* filename){
    SDL_Surface* img = IMG_Load(filename);
    if(!img)
		std::cout << "problem loading texture" << std::endl;
	out << "filename :" << filename << std::endl;
	SDL_PixelFormat form = {NULL,32,4,0,0,0,0,8,8,8,8,0xff000000,0x00ff0000,0x0000ff00,0x000000ff,0,255};
	SDL_Surface* img2 = SDL_ConvertSurface(img, &form, SDL_SWSURFACE);
    if(!img2)
		std::cout << "problem converting texture" << std::endl;
	unsigned int num;
	glGenTextures(1,&num);
	glBindTexture(GL_TEXTURE_2D,num);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img2->w,img2->h,0,GL_RGBA, GL_UNSIGNED_INT_8_8_8_8,img2->pixels);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	std::cout << glGetError() << std::endl;
	SDL_FreeSurface(img);
	SDL_FreeSurface(img2);
	this->textures.push_back(num);
	std::cout << "texId: " << num << "filename: " << filename << std::endl;
	return num;
}
// updates the game components
void Game::update(){
    player1->update(levels[0].getCollisionPlanes());
	levels[0].update();
}
// what to show in the game
void Game::show(){
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	//glDisable(GL_DEPTH_TEST);
	float camX = 0;
	float camY = 0;
	float camZ = 0;

	player1->getPlayersCamera()->joystickControl(js);
	//player1->getPlayersCamera()->keyboardControl();
	levels[0].getSkybox()->drawSkybox(200.0);
	player1->getPlayersCamera()->update();
    camX = player1->getPlayersCamera()->getCameraLocation().getX();
	camY = player1->getPlayersCamera()->getCameraLocation().getY();
	camZ = player1->getPlayersCamera()->getCameraLocation().getZ();
	//glEnable(GL_DEPTH_TEST);
	levels[0].show();
	glLoadIdentity();
	showPosition(camX, camY, camZ);
	//drawInventoryBackground();


}
void Game::drawInventoryBackground(){
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, menuId);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glColor4f(0.25f, 0.25f, 0.25f, 0.33f);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_QUADS);
		//glNormal3f(0.0f, 0.0f, 1.0f);
		//glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-1.0f, -0.25f, -2.5f);
		//glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-1.0f, -1.0f, -2.5f);
		//glTexCoord2f(1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, -2.5f);
		//glTexCoord2f(0.0f, 1.0f);
		glVertex3f(1.0f, -0.25f, -2.5f);
	glEnd();

}
void Game::drawMenuBackground(){
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glColor4f(0.25f, 0.25f, 0.25f, 0.33f);
	//glEnable(GL_TEXTURE_2D);
	//glBindTexture(GL_TEXTURE_2D, loadTexture("data/cf.png"));
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBegin(GL_QUADS);
		//glNormal3f(0.0f, 0.0f, 1.0f);
		//glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.45f, 0.67f, -2.5f);
		//glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.45f, 0.97f, -2.5f);
		//glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.95f, 0.97f, -2.5f);
		//glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.95f, 0.67f, -2.5f);
	glEnd();

}

void Game::start(){
	// looping flag
	bool isRunning = true;
	bool showInventory = false;
	Uint32 start;
	int menuoption = 0;
	Vector3d pp;
	while(isRunning){
		// check event que
		start = SDL_GetTicks();
		while(SDL_PollEvent(&event)){
		    switch(event.type){
		        case SDL_KEYDOWN :
                    switch(event.key.keysym.sym){
                        case SDLK_ESCAPE:
                            menuoption = gameMenu->run();
							switch(menuoption){
								case 0:
									break;
								case 1:
									isRunning = false;
									break;
							}
							break;
                    }
                    break;
                // mouse in to start camera
                case SDL_MOUSEBUTTONDOWN :
                    if(!player1->cam.isMouseIn()){
                        player1->cam.mouseIn();
                        break;
                    }
                    break;
                // Joystick Axis
                case SDL_JOYAXISMOTION:
                	if(event.jaxis.axis == 0 || event.jaxis.axis == 1){
                		player1->getPlayersCamera()->joystickControl(js);
                	}
                	if(event.jaxis.axis == 3 || event.jaxis.axis == 4){
                		player1->getPlayersCamera()->joystickControl(js);
                	}
                break;
                // Joystick Buttons
            	case SDL_JOYBUTTONUP:
            	    if (event.jbutton.button == 9){
            	    	if(showInventory)
            	    		showInventory = true;
            	    	else
            	    		showInventory = false;
            	    	break;
            	    }
            	    break;
            	case SDL_JOYBUTTONDOWN:
            	    if (event.jbutton.button == 2){
            	    	player1->jump();
            	    	break;
            	    }
            	    if (event.jbutton.button == 9){
            	    	if(!showInventory)
            	    		showInventory = true;
            	    	else
            	    		showInventory = false;
            	    	break;
            	    }
            	    if (event.jbutton.button == 8){
                        menuoption = gameMenu->run();
						switch(menuoption){
							case 0:
								break;
							case 1:
								isRunning = false;
								break;
						}
						break;
            	    }
            	    break;
                // exit out of loop
                case SDL_QUIT :
                    isRunning = false;
                    break;
		    }
		}
		update();
        show();
        if(showInventory){
        	showInventoryMenu();
        }

        SDL_GL_SwapBuffers();
        if(1000/30>(SDL_GetTicks()-start))
            SDL_Delay(1000/30-(SDL_GetTicks()-start));
	}
}

void Game::showInventoryMenu(){

    //unsigned int texture = loadTexture("data/future_city.jpg");
    //SDL_Surface* image = loadImage("data/future_city.jpg");
    //applySurface(10, 10, gameScreen, image);
	//SDL_Flip(screen);
	drawInventoryBackground();
    char tmp[200];
	sprintf(tmp,"Menu Item:%f", 1);
	tex->drawText(Vector3d(-0.20,-0.15,-1), Vector3d(0,0,0), Vector3d(0.025,0.025,0.025), tmp);
	//sprintf(tmp,"dy:%5.2f", y);
	//tex->drawText(Vector3d(0.20,0.32,-1), Vector3d(0,0,0), Vector3d(0.025,0.025,0.025), tmp);
    //sprintf(tmp,"dz:%5.2f", z);
	//tex->drawText(Vector3d(0.20,0.29,-1), Vector3d(0,0,0), Vector3d(0.025,0.025,0.025), tmp);

	//SDL_FreeSurface(screen);
}

void Game::showPosition(float x, float y, float z){
	drawMenuBackground();
    char tmp[200];
	sprintf(tmp,"dx:%5.2f", x);
	tex->drawText(Vector3d(0.20,0.35,-1), Vector3d(0,0,0), Vector3d(0.025,0.025,0.025), tmp);
	sprintf(tmp,"dy:%5.2f", y);
	tex->drawText(Vector3d(0.20,0.32,-1), Vector3d(0,0,0), Vector3d(0.025,0.025,0.025), tmp);
    sprintf(tmp,"dz:%5.2f", z);
	tex->drawText(Vector3d(0.20,0.29,-1), Vector3d(0,0,0), Vector3d(0.025,0.025,0.025), tmp);
}

void Game::drawMenu(int health, float x, float y, float z, int point){
	char tmp[200];
	sprintf(tmp,"h  %d",2);
	//tex->drawText(Vector3d(-0.5,0.35,-1), Vector3d(0,0,0), Vector3d(0.035,0.035,0.035), tmp);
	//sprintf(tmp, "%s    %d / %d", "x", x, y);
	//tex->drawText(Vector3d(-0.54,-0.39,-1), Vector3d(0,0,0), Vector3d(0.035,0.035,0.035), tmp);
	//sprintf(tmp,"Points: %d",point);
	tex->drawText(Vector3d(0.22,0.35,-1), Vector3d(0,0,0), Vector3d(0.035,0.035,0.035), tmp);
}

SDL_Surface* Game::loadImage(std::string filename){
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	// load the image
	loadedImage = IMG_Load(filename.c_str());
	if(loadedImage != NULL){
		optimizedImage = SDL_DisplayFormat(loadedImage);
		if(optimizedImage != NULL){
			//create a color key
			Uint32 colorKey = SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF);
			// set the colors of the image to appear transparent to the background
			SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorKey);
		}
		SDL_FreeSurface(loadedImage);

	}
	return optimizedImage;
}

void Game::applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination){
	SDL_Rect offset;
	// get the offsets
	offset.x = x;
	offset.y = y;
	// Blint the surfaces
	SDL_BlitSurface(source, NULL, destination, &offset);
}







