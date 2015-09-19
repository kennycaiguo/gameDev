#include "MainMenu.h"
#include "Game.h"
#include <cstdlib>

int main(int argc, char* argv[]){
    MainMenu mm;
    int mmFlag = mm.showMainMenu();
    if(mmFlag == START){
    	Game g;
    	g.start();
    }
    else if(mmFlag == EXIT){
    	return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}
