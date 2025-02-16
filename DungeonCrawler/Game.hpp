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

#include "Camera.hpp"
#include "Dungeon.hpp"
#include "Entities.hpp"
#include "Player.hpp"

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
	Camera camera;
	Dungeon dungeon;

	//Game Entities
	Player player;
	vector<Enemy*> enemies;

	//Init functions
	void initWindow();
	void initCamera();
	void initDungeon();
	void initPlayer();
	void initEnemies(uint16_t numOfEnemies);

	//Private Functions


public:

	//constructors / destructors
	Game();
	~Game();

	//Accessors
	const bool isRunning();

	//Update functions
	void updateGameView();
	void updatePlayer();
	void updateEnemies();
	void updateEvents();
	void updateMousePositions();
	void update(); //Master update function

	//Collision Functions
	void handlePlayerEnemyCollisions();
	void handleEnemyEnemyCollisions();
	void handlePlayerWorldCollisions();
	void handleCollisions(); //Master collision function

	//Render Functions
	void renderCurrentRoom();
	void renderEnemies();
	void renderPlayer();
	void render(); //Master render function

};


#endif //GAME_H