#include "Game.hpp"

using namespace sf;

int main()
{
	//Init game engine
	Game game{};

	//Game Loop
	while (game.isRunning())
	{
		
		//Update
		game.update();

		//Render
		game.render();

	}

	//End of application
	return 0;
}