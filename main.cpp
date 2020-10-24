#include "Game.h"
/*
	Game class creates a window with a game level loaded
*/

int main ()
{
	Game game("Test", 1280, 1024, 4, 5, false);

	while (!game.getWindowShouldClose())
	{
		game.update();
		game.render();
	}
	return 0;
}