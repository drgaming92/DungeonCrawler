#include "Player.hpp"

#include <array>
#include <iostream>

using namespace sf;


/*
	PLAYER
	FUNCTIONS
*/

//Init functions

void Player::initTexture()
{
	if (!this->playerTexture.loadFromFile("./Textures/PlayerTextures/DefaultPlayer.png"))
	{
		cout << "Error::Player::initTexture::Could not load texture" << endl;
	}
}

void Player::initShape()
{
	this->height = 30.f;
	this->width = 30.f;	
}

void Player::initCoreAttributes()
{
	this->health = 100;
	this->stamina = 50;
	this->mana = 10;
}

void Player::initMovement()
{
	this->momentumX = 0.f;
	this->momentumY = 0.f;

	this->posX = 200.f;
	this->posY = 200.f;

	this->sprinting = false;
}


//Constructors / Destructors
Player::Player()
{
	this->initTexture();
	this->initShape();
	this->initCoreAttributes();
	this->initMovement();
}

Player::~Player()
{
	
}


/*
	ACESSORS
*/

IntRect Player::getPlayerBounds()
{
	this->updateBoundsBox();
	return this->playerBoundsBox;
}

const Vector2f Player::getPlayerPos()
{
	return Vector2f(this->posX, this->posY);
}

const Vector2f Player::getMomentum()
{
	return Vector2f(this->momentumX, this->momentumY);
}


/*
	COLLISION
	FUNCTIONS
*/

void Player::handleCollisionWith(optional<IntRect> intersection)
{

	/*
		@return void

		Deters player collision with enemy
		- Resolve x collision
		- Resolve y collision
	*/

	if (intersection.has_value())
	{
		if (intersection.value().size.x < intersection.value().size.y)
		{
			//If intersection is on right side of player
			if (intersection.value().position.x > this->playerBoundsBox.getCenter().x)
			{
				this->collisionCorrection.x -= intersection.value().size.x;
				this->momentumX = 0.f;
			}
			//If intersection is on left side of player
			else
			{
				this->collisionCorrection.x += intersection.value().size.x;
				this->momentumX = 0.f;
			}
		}
		else
		{
			//If collision is above the player
			if (intersection.value().position.y < this->playerBoundsBox.getCenter().y)
			{
				this->collisionCorrection.y += intersection.value().size.y;
				this->momentumY = 0.f;
			}
			//If collision is below the player
			else
			{
				this->collisionCorrection.y -= intersection.value().size.y;
				this->momentumY = 0.f;
			}
		}
	}	
}

void Player::handleWorldCollision(optional<IntRect> worldIntersection)
{
	if (worldIntersection.value().size.x < worldIntersection.value().size.y)
	{
		//If intersection is on right side of player
		if (worldIntersection.value().position.x > this->playerBoundsBox.getCenter().x)
		{
			this->collisionCorrection.x += worldIntersection.value().size.x;
			this->momentumX = 0.f;
		}
		//If intersection is on left side of player
		else
		{
			this->collisionCorrection.x -= worldIntersection.value().size.x;
			this->momentumX = 0.f;
		}
	}
	else
	{
		//If collision is above the player
		if (worldIntersection.value().position.y < this->playerBoundsBox.getCenter().y)
		{
			this->collisionCorrection.y -= worldIntersection.value().size.y;
			this->momentumY = 0.f;
		}
		//If collision is below the player
		else
		{
			this->collisionCorrection.y += worldIntersection.value().size.y;
			this->momentumY = 0.f;
		}
	}
}

void Player::updateCollisionVector()
{
	this->posX += this->collisionCorrection.x;
	this->posY += this->collisionCorrection.y;
	this->collisionCorrection = Vector2f(0.f, 0.f);
}


/*
	UPDATE
	FUNCTIONS
*/

void Player::updateBoundsBox()
{
	this->playerBoundsBox.position.x = static_cast<int>(this->posX);
	this->playerBoundsBox.position.y = static_cast<int>(this->posY);
	this->playerBoundsBox.size.x = this->width;
	this->playerBoundsBox.size.y = this->width;
}

void Player::updateSprint()
{
	/*
		@return void

		Checks if sprinting
		- Checks if left shift is being held down
		- If it is then toggle sprint
	*/

	float sprintToggleDelay = 0.2f;
	if (Keyboard::isKeyPressed(Keyboard::Key::LShift))
	{
		if (this->sprintToggleClock.getElapsedTime().asSeconds() >= sprintToggleDelay)
		{
			this->sprinting = !this->sprinting;
			this->sprintToggleClock.restart();
		}
		
	}

}

void Player::updatePosition()
{

	/*
		@return void

		Changes the player's position
		- Checks if sprinting
		- Increases momentum to the direction of the key press
		- Decreases momentum a little bit
		- Change player position by momentum
	*/

	this->updateSprint();
	
	if (Keyboard::isKeyPressed(Keyboard::Key::W))
	{
		this->momentumY -= 2.f;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::S))
	{
		this->momentumY += 2.f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::A))
	{
		this->momentumX -= 2.f;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::D))
	{
		this->momentumX += 2.f;
	}

	if (this->sprinting)
	{
		this->momentumX = this->momentumX * 0.72f;
		this->momentumY = this->momentumY * 0.72f;
	}
	else
	{
		this->momentumX = this->momentumX * 0.65f;
		this->momentumY = this->momentumY * 0.65f;
	}
	this->posX += momentumX;
	this->posY += momentumY;

}


/*
	RENDER
	FUNCTIONS
*/
void Player::render(Sprite& playerSprite, RenderTarget* target)
{
	playerSprite.setTexture(this->playerTexture);
	playerSprite.setScale(Vector2f(1.875, 1.875));
	playerSprite.setPosition(Vector2f(this->getPlayerPos()));

	target->draw(playerSprite);
}

