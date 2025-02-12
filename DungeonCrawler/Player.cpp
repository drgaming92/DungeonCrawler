#include "Player.hpp"

using namespace std;


/*
	PLAYER
	FUNCTIONS
*/

//Init functions
void Player::initWindow(shared_ptr<RenderWindow> windowPtr)
{
	this->window = windowPtr;
}

void Player::initCoreAttributes()
{
	this->health = 100;
	this->stamina = 50;
	this->mana = 10;
}

void Player::initPosition()
{
	//Window relative
	this->posX = 100;
	this->posY = 100;

	//World relative
	this->worldPosX = 0;
	this->worldPosY = 0;
}

void Player::initSize()
{
	this->height = 100;
	this->width = 100;
}

void Player::initMovement()
{
	this->speed = 10.f;
}


//Constructors / Destructors
Player::Player(shared_ptr<RenderWindow> windowPtr)
{
	this->initWindow(windowPtr);

	this->initCoreAttributes();
	this->initPosition();
	this->initSize();

	this->initMovement();
}

Player::~Player()
{
	
}

//Movement Functions
void Player::getMovement()
{

	/*
		@return void

		Changes the player's position
		- Checks which key is pressed
		- Changes the player's window-relative postional value by speed
		- Changes the player's world-relative positional value by speed
	*/

	if (Keyboard::isKeyPressed(Keyboard::Key::W))
	{
		this->posY -= this->speed;
		this->worldPosY += this->speed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::S))
	{
		this->posY += this->speed;
		this->worldPosY += this->speed;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		this->posX -= this->speed;
		this->worldPosX -= this->speed;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::D))
	{
		this->posX += this->speed;
		this->worldPosX += this->speed;
	}

}




