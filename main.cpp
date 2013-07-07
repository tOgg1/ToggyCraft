#include <stdio.h>
#include "Game.h"
#include "Chunk.h"
#include "Block.h"
#include <GL/glfw3.h>

int main(int argv, char** argc)
{
	Game* game = new Game();
	game->start();	
	return 0;
}