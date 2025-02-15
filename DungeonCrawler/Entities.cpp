#include "Entities.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <cmath>
#include <iostream>
#include <optional>
#include <random>

using namespace sf;

//==============================
/*
	ENTITY
	CLASS
	FUNCTIONS
*/
//===============================

/*
	INIT
	FUNCTIONS
*/
void Entity::initAttributes()
{
	this->health = 100;

	this->height = 20;
	this->width = 20;
}

void Entity::initShape()
{
	this->entityShape = RectangleShape({ this->width, this->height });
	this->entityShape.setFillColor(Color::Red);
}

void Entity::initPos(Vector2f position)
{
	this->entityShape.setPosition(position);
}

Vector2f Entity::getRandomPos()
{
	random_device rd;
	mt19937 gen(rd());
	uniform_real_distribution<>floatDistrib(-100.f, 1000.f);

	return Vector2f(static_cast<int>(floatDistrib(gen)), static_cast<int>(floatDistrib(gen)));
}


/*
	CONSTRUCTORS
	DESTRUCTORS
*/
Entity::Entity()
{
	this->initAttributes();
	this->initShape();
	this->initPos(this->getRandomPos());
}

Entity::~Entity()
{

}


/*
	RENDER
	FUNCTIONS
*/

void Entity::renderEntity(RenderTarget* target)
{
	target->draw(this->entityShape);
}


//==================================
/*
	ENEMY
	CLASS
	FUNCTIONS
*/
//===================================

/*
	INIT
	FUNCTIONS
*/

void Enemy::initAttributes()
{
	this->health = 200;

	this->speed = 2.f;

	this->height = 30;
	this->width = 30;
}

void Enemy::initTexture()
{
	if (!this->enemyTexture.loadFromFile("./Textures/EnemyTextures/defaultEnemy.png"))
	{
		cout << "Error::Enemy::initTexture::Could not load file" << endl;
	}
}

void Enemy::initPos(Vector2f position)
{
	this->enemyPosition = position;
}

void Enemy::initPatrol(uint8_t numOfStops=2)
{

	/*
		@return void

		Makes new positions for stops
		- Resize the stops vector
		- Assign random positions for each stop
		- Store each position in the stops vector
		- Assign the current position to the stop vector
	*/

	this->stopPoints.reserve(numOfStops + 1);
	this->stopPoints.resize(numOfStops + 1);

	for (auto& stop : this->stopPoints)
	{
		stop = this->getRandomPos();
	}

	this->stopPoints.insert(this->stopPoints.begin(), this->enemyPosition);
	this->currentStop = 1;
	this->patrolToggleClock.start();

}


/*
	CONSTRUCTORS
	DESTRUCTORS
*/

Enemy::Enemy()
{
	//Init Functions
	this->initTexture();
	this->initAttributes();
	this->initPos(this->getRandomPos());
	this->initPatrol();
}

Enemy::~Enemy()
{

}


/*
	PUBLIC
	FUNCTIONS
*/

optional<IntRect> Enemy::checkCollisionWith(IntRect otherBoundsBox)
{
	this->updateBoundsBox();

	optional<IntRect> intersection = this->enemyBoundsBox.findIntersection(otherBoundsBox);

	if (intersection.has_value())
	{
		return intersection;
	}
	else
	{
		return intersection;
	}
}


/*
	MOVEMENT
	FUNCTIONS
*/
void Enemy::moveTowardsStop()
{

	/*
		@return void

		Move the enemy to each stop position
		- Checks if the enemy is already at the next stop and has waited long enough to start mooving again
		- Sets the direction that the enemy must move in
		- Gets total distance to the next stop
		- Makes the necessary movement to the next stop
	*/

	float patrolStop = 0.5f;

	Vector2f currentPosition = this->enemyPosition;
	Vector2f target = this->stopPoints[currentStop];

	if (currentPosition == target)
	{
		if (this->patrolToggleClock.getElapsedTime().asSeconds() >= patrolStop)
		{
			this->currentStop = (currentStop + 1) % this->stopPoints.size();
			target = this->stopPoints[currentStop];
		}
		else
		{
			return;
		}
	}
	else
	{
		Vector2f direction = target - currentPosition;
		float distance = sqrt((direction.x * direction.x) + (direction.y * direction.y));

		if (distance > 1.f)
		{
			if (distance > 0.f)
			{
				//Normalize vector
				direction /= distance;
				float moveX = direction.x * this->speed;
				float moveY = direction.y * this->speed;

				//Correct movement
				float totalMovement = sqrt(moveX * moveX + moveY * moveY);
				float correctionFactor = this->speed / totalMovement;
				moveX *= correctionFactor;
				moveY *= correctionFactor;

				//Apply corrected movement
				currentPosition.x += moveX;
				currentPosition.y += moveY;
				this->enemyPosition = currentPosition;
			}
			else
			{
				currentPosition = target;
				this->enemyPosition = currentPosition;
			}
			
		}
		else
		{ 
			currentPosition = target;
			this->enemyPosition = currentPosition;
			
		}

		if (currentPosition == target)
		{
			this->patrolToggleClock.restart();
		}
	}

}


/*
	UPDATE
	FUNCTIONS
*/

void Enemy::updateBoundsBox()
{
	this->enemyBoundsBox.position.x = static_cast<int>(this->enemyPosition.x);
	this->enemyBoundsBox.position.y = static_cast<int>(this->enemyPosition.y);
	this->enemyBoundsBox.size.x = static_cast<int>(this->width);
	this->enemyBoundsBox.size.y = static_cast<int>(this->height);
}


/*
	RENDER
	FUNCTIONS
*/

void Enemy::render(Sprite& enemySprite, RenderTarget* target)
{
	//Set sprite attributes
	enemySprite.setScale(Vector2f(1.875f, 1.875f));
	enemySprite.setPosition(this->enemyPosition);
	enemySprite.setTexture(this->enemyTexture);

	target->draw(enemySprite);
}

