#ifndef GAME_H
#define GAME_H

#include "Dungeon.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cstdint>
#include <iostream>
#include <optional>
#include <random>
#include <string>
#include <vector>

using namespace sf;

class Game
{
private:
	//Variables
	uint8_t maxSprites = 127;

	//Window
	RenderWindow* window;

	//Mouse Positions
	Vector2i mousePosWindow;
	Vector2f mousPosView;

	//Game Objects
	Dungeon* dungeon;

	//Init functions
	void initVariables();
	void initWindow();
	void initDungeon();

public:

	//constructors / destructors
	Game();
	~Game();

	//Accessors
	const bool isRunning();

	//Update functions
	void updateEvents();
	void updateMousePositions();
	void updateRoomPositions();
	void update();

	//Render Functions
	void renderRooms();
	void render();

};


#endif //GAME_H