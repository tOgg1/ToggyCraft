#include <stdio.h>
#include "Game.h"

int main(int argv, char** argc)
{
	Game* game = new Game();
	game->start();	
	return 0;
}