#include <stdlib.h>
#include "Game.h"

int main(){
	Game* pGame = Game::getInstance();

	pGame->init();
	pGame->run();

	return 0;
};