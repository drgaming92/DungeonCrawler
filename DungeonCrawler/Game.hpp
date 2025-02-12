#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <memory>
#include <optional>
#include <random>
#include <string>
#include <vector>

#include "Dungeon.hpp"
#include "Player.hpp"

using namespace sf;

class Game
{
private:
	//Variables
	uint8_t maxSprites = 127;

	//Window
	shared_ptr<RenderWindow> window;

	//Mouse Positions
	Vector2i mousePosWindow;
	Vector2f mousPosView;

	//Game Object Pointers
	Dungeon* dungeon;
	Room* currentRoomGame;
	Player* player;

	//Game Object Shape Pointers
	RectangleShape* currentRoomShape;
	RectangleShape* playerShape;

	//Init functions
	void initVariables();
	void initWindow();
	void initDungeon();
	void initCurrentRoom();
	void initPlayer();

public:

	//constructors / destructors
	Game();
	~Game();

	//Accessors
	const bool isRunning();

	//Update functions
	void updateEvents();
	void updateMousePositions();
	void updateCurrentRoom();
	void updatePlayer();
	void update();

	//Render Functions
	void renderCurrentRoom();
	void renderPlayer();
	void render();

};


#endif //GAME_H