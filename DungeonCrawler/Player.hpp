#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <cstdint>
#include <memory>

using namespace sf;

class Player
{
private:

	//Window
	std::shared_ptr<RenderWindow> window;

	//Core Attributes
	uint16_t health;
	uint16_t stamina;
	uint16_t mana;

	//Movement Attributes
	float speed;

	//Survival Attributes (Not yet implemented)

	//Init functions
	void initWindow(std::shared_ptr<RenderWindow> windowPtr);
	void initCoreAttributes();
	void initPosition();
	void initSize();
	void initMovement();

public:

	//Positional Variables
	uint16_t posX;
	uint16_t posY;
	float worldPosX;
	float worldPosY;

	//Size Variables
	uint16_t height;
	uint16_t width;

	//Constructors / Destructors
	Player(std::shared_ptr<RenderWindow> windowPtr);
	~Player();

	//Movement Functions
	void getMovement();

};


#endif // PLAYER_HPP