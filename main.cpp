#include <stdio.h>
#include "Game.h"
#include "Block.h"

int main(int argv, char** argc)
{
	Block block();

	printf("Size %d", sizeof(Block));

	Game* game = new Game();
	game->start();	
	return 0;
}