#include "MainMenu.h"

// constructor
MainMenu::MainMenu(){

}
//destructor
MainMenu::~MainMenu(){
    delete labels;
    delete selected;
    delete color;
    for(int i = 0; i < NUM_MENU_ITEMS; i++){
         SDL_FreeSurface(menus[i]);
    }
	SDL_FreeSurface(screen);
	SDL_FreeSurface(image);
	SDL_FreeSurface(logo);
    SDL_FreeSurface(alpha);
    SDL_FreeSurface(screen);
    TTF_CloseFont(font);
	Mix_FreeMusic(music);
	Mix_CloseAudio();
    TTF_Quit();
}
// display the main menu with its own loop
int MainMenu::showMainMenu(){
	SDL_Init(SDL_INIT_EVERYTHING);
	js = SDL_JoystickOpen(0);
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
    Uint32 time = 0;
    int x = 0;
    int y = 0;
    int dy = 0;
    const char* labels[NUM_MENU_ITEMS] = {"START","EXIT"};
    bool selected[NUM_MENU_ITEMS] = {0,0};
    SDL_Color color[2] = {{255,255,255},{255,0,0}};
    this->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE | SDL_FULLSCREEN);
    this->screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
    TTF_Init();
    this->font = TTF_OpenFont("font/spaceAge.ttf",50);
    menus[0] = TTF_RenderText_Solid(font,labels[0],color[0]);
    menus[1] = TTF_RenderText_Solid(font,labels[1],color[0]);
    SDL_Rect pos[NUM_MENU_ITEMS];
    pos[0].x = screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
    pos[0].y = screen->clip_rect.h/2 - menus[0]->clip_rect.h;
    pos[1].x = screen->clip_rect.w/2 - menus[0]->clip_rect.w/2;
    pos[1].y = screen->clip_rect.h/2 + menus[0]->clip_rect.h;


    this->image = loadImage("data/spaceopera.png");
    applySurface(0, 0, image, screen);

    //this->logo = loadImage("data/gamelogo.png");
    //applySurface(0, 0, logo, screen);


    //SDL_Surface* alpha = SDL_LoadBMP("data/mm.bmp");
    SDL_Surface* alpha = SDL_CreateRGBSurface(SDL_SWSURFACE, screen->w, screen->h, 32, screen->format->Rmask, screen->format->Gmask, screen->format->Bmask, screen->format->Amask);

    SDL_FillRect(alpha,&screen->clip_rect,SDL_MapRGB(screen->format,0x00,0x00,0x00)); // if you use a image...this will need to be commented out

    SDL_SetAlpha(alpha, SDL_SRCALPHA, 129); // 129 software accelerated // 128 hardware
    SDL_BlitSurface(alpha, NULL, screen, NULL);
    //SDL_FillRect(screen,&screen->clip_rect,SDL_MapRGB(screen->format,0x00,0x00,0x00));
	music = Mix_LoadMUS("data/sound/Five Armies.mp3");
	//music = Mix_LoadMUS("data/sound/Legend.mp3");
	Mix_PlayMusic(music,-1);

    int MENU_FLAG = 0;

    SDL_Event event;
        while(1){
            time = SDL_GetTicks();
            while(SDL_PollEvent(&event)){
                switch(event.type){
                    case SDL_QUIT:
                        SDL_FreeSurface(menus[0]);
                        SDL_FreeSurface(menus[1]);
                        return 1;
                    case SDL_MOUSEMOTION:
                        x = event.motion.x;
                        y = event.motion.y;
                        for(int i = 0; i < NUM_MENU_ITEMS; i += 1){
                            if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h){
                                if(!selected[i]){
                                    selected[i] = 1;
                                    SDL_FreeSurface(menus[i]);
                                    menus[i] = TTF_RenderText_Solid(font,labels[i],color[1]);
                                }
                            }else{
                                if(selected[i]){
                                    selected[i] = 0;
                                    SDL_FreeSurface(menus[i]);
                                    menus[i] = TTF_RenderText_Solid(font,labels[i],color[0]);
                                }
                            }
                        }
                        break;
                        case SDL_MOUSEBUTTONDOWN:
                            x = event.button.x;
                            y = event.button.y;
                            for(int i = 0; i < NUM_MENU_ITEMS; i += 1){
                                if(x>=pos[i].x && x<=pos[i].x+pos[i].w && y>=pos[i].y && y<=pos[i].y+pos[i].h){
                                    SDL_FreeSurface(menus[0]);
                                    SDL_FreeSurface(menus[1]);
                                    return i;
                                }
                            }
                        break;
                        case SDL_KEYDOWN:
                            if(event.key.keysym.sym == SDLK_ESCAPE){
                                SDL_FreeSurface(menus[0]);
                                SDL_FreeSurface(menus[1]);
                                return 0;
                            }
                       break;
                       // Joystick Axis
                       case SDL_JOYAXISMOTION:
                    		x = SDL_JoystickGetAxis(js, 0);
                    		//y = SDL_JoystickGetAxis(js, 1) + pos[0].y;
                    		dy = SDL_JoystickGetAxis(js, 1);
                    		//y = pos[1].y;
                    	   if(event.jaxis.value < -3200 || event.jaxis.value > 3200){
                        	   if(event.jaxis.axis == 1){
                        		   if(dy <= 1)
                        			   y = pos[0].y;
                        		   else
                        			   y = pos[1].y;
                                   for(int i = 0; i < NUM_MENU_ITEMS; i += 1){
                                       if(y >= pos[i].y && y <= pos[i].y + pos[i].h){
                                           if(!selected[i]){
                                               selected[i] = 1;
                                               SDL_FreeSurface(menus[i]);
                                               menus[i] = TTF_RenderText_Solid(font,labels[i],color[1]);
                                               MENU_FLAG = i;
                                           }
                                       }else{
                                           if(selected[i]){
                                               selected[i] = 0;
                                               SDL_FreeSurface(menus[i]);
                                               menus[i] = TTF_RenderText_Solid(font,labels[i],color[0]);
                                           }
                                       }
                                   }
                               }
                    	   }
                       break;
                       case SDL_JOYBUTTONDOWN:
                     	   if (event.jbutton.button == 0){
                                SDL_FreeSurface(menus[0]);
                                SDL_FreeSurface(menus[1]);
                                return MENU_FLAG;
                     	   }
                       break;
                   }
            }
            for(int i = 0; i < NUM_MENU_ITEMS; i += 1){
                SDL_BlitSurface(menus[i],NULL,screen,&pos[i]);
            }
            SDL_Flip(screen);
                if(1000/30 > (SDL_GetTicks()-time))
                    SDL_Delay(1000/30 - (SDL_GetTicks()-time));
        }
        SDL_FreeSurface(alpha);
        SDL_JoystickClose(js);
        TTF_Quit();
}
// Used to load image files for the menu items
SDL_Surface* MainMenu::loadImage(std::string fname){
	SDL_Surface* loadedImage = NULL;
	SDL_Surface* optimizedImage = NULL;
	// load the image
	loadedImage = IMG_Load(fname.c_str());
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
// used to place the image on the screen
void MainMenu::applySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination){
	SDL_Rect offset;
	// get the offsets
	offset.x = x;
	offset.y = y;
	// Blint the surfaces
	SDL_BlitSurface(source, NULL, destination, &offset);
}








