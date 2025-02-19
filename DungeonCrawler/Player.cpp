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

void Player::initSize()
{
	this->height = 16;
	this->width = 16;
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

void Player::initPlayerShape()
{
	this->playerShape.setPrimitiveType(PrimitiveType::TriangleStrip);
	this->playerShape.resize(4);

	//Set Vertex Positions
	this->playerShape[0].position = Vector2f(this->posX, this->posY);
	this->playerShape[1].position = Vector2f(this->posX + this->width, this->posY);
	this->playerShape[2].position = Vector2f(this->posX, this->posY + this->height);
	this->playerShape[3].position = Vector2f(this->posX + this->width, this->posY + this->height);

	//Set Texture Points
	this->playerShape[0].texCoords = Vector2f(0.f, 0.f);
	this->playerShape[1].texCoords = Vector2f(this->width, 0.f);
	this->playerShape[2].texCoords = Vector2f(0.f, this->height);
	this->playerShape[3].texCoords = Vector2f(this->width, this->height);
}


/*
	CONSTRUCTORS
	DESTRUCTORS
*/

Player::Player()
{
	this->initTexture();
	this->initSize();
	this->initCoreAttributes();
	this->initMovement();
	this->initPlayerShape();
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
	if (worldIntersection.value().position == this->playerBoundsBox.position
	 && worldIntersection.value().size	   == this->playerBoundsBox.size)
	{
		return;
	}

	if (worldIntersection.value().size.x < worldIntersection.value().size.y)
	{
		//If intersection is on right side of player
		if (worldIntersection.value().position.x > this->playerBoundsBox.getCenter().x)
		{
			this->collisionCorrection.x += this->momentumX;
			this->momentumX = 0.f;
		}
		//If intersection is on left side of player
		else
		{
			this->collisionCorrection.x -= this->momentumX;
			this->momentumX = 0.f;
		}
	}
	else
	{
		//If collision is above the player
		if (worldIntersection.value().position.y < this->playerBoundsBox.getCenter().y)
		{
			this->collisionCorrection.y -= this->momentumY;
			this->momentumY = 0.f;
		}
		//If collision is below the player
		else
		{
			this->collisionCorrection.y += this->momentumY;
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

	const float sprintToggleDelay = 0.2f;
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
		@return voidssss

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
		this->momentumX *= 0.65f;
		this->momentumY *= 0.65f;
	}
	else
	{
		this->momentumX *= 0.52f;
		this->momentumY *= 0.52f;
	}

	this->posX += this->momentumX;
	this->posY += this->momentumY;

}

void Player::updatePlayerShape()
{
	//Set Vertex Positions
	this->playerShape[0].position = Vector2f(this->posX, this->posY);
	this->playerShape[1].position = Vector2f(this->posX + this->width, this->posY);
	this->playerShape[2].position = Vector2f(this->posX, this->posY + this->height);
	this->playerShape[3].position = Vector2f(this->posX + this->width, this->posY + this->height);

	//Set Texture Points
	this->playerShape[0].texCoords = Vector2f(0.f, 0.f);
	this->playerShape[1].texCoords = Vector2f(this->width, 0.f);
	this->playerShape[2].texCoords = Vector2f(0.f, this->height);
	this->playerShape[3].texCoords = Vector2f(this->width, this->height);

}


/*
	RENDER
	FUNCTIONS
*/

void Player::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= Transformable::getTransform();
	states.texture = &this->playerTexture;
	states.blendMode = BlendAlpha;

	target.draw(this->playerShape, states);
}

