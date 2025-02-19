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
	uniform_real_distribution<>floatDristib(-100.0f, 1000.0f);

	return Vector2f(static_cast<float>(floatDristib(gen)), static_cast<float>(floatDristib(gen)));
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

	this->height = 16;
	this->width = 16;
}

void Enemy::initTexture()
{
	Texture texture;
	if (!texture.loadFromFile("./Textures/EnemyTextures/defaultEnemy.png"))
	{
		cout << "Error::Enemy::initTexture::Could not load file" << endl;
	}
	this->enemyTexture = texture;
}

void Enemy::initEnemyShape()
{
	this->enemyShape.setPrimitiveType(PrimitiveType::TriangleStrip);
	this->enemyShape.resize(4);

	//Vertice Positions
	this->enemyShape[0].position = Vector2f(this->enemyPosition.x, this->enemyPosition.y);
	this->enemyShape[1].position = Vector2f(this->enemyPosition.x + this->width, this->enemyPosition.y);
	this->enemyShape[2].position = Vector2f(this->enemyPosition.x, this->enemyPosition.y + this->height);
	this->enemyShape[3].position = Vector2f(this->enemyPosition.x + this->width, this->enemyPosition.y + this->height);

	//Texture Positions
	this->enemyShape[0].texCoords = Vector2f(0.f, 0.f);
	this->enemyShape[1].texCoords = Vector2f(this->width, 0.f);
	this->enemyShape[2].texCoords = Vector2f(0.f, this->height);
	this->enemyShape[3].texCoords = Vector2f(this->width, this->height);
}

void Enemy::initPos(Vector2f position)
{
	this->enemyPosition = position;
}

void Enemy::initPatrol(short numOfStops=2)
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
	this->initAttributes();
	this->initTexture();
	this->initPos(this->getRandomPos());
	this->initEnemyShape();
	this->initPatrol();
}

Enemy::~Enemy()
{

}


/*
	ACCESSORS
*/

IntRect Enemy::getCollisionBox()
{
	this->updateBoundsBox();
	return this->enemyBoundsBox;
}


/*
	COLLISION
	FUNCTIONS
*/

optional<IntRect> Enemy::checkCollisionWith(IntRect otherBoundsBox)
{
	this->updateBoundsBox();

	optional<IntRect> intersection = this->enemyBoundsBox.findIntersection(otherBoundsBox);
	return intersection;
}

void Enemy::handleCollisionWith(optional<IntRect> intersection)
{

	/*
		@return void

		Resolves collisions
		- Resolve x collision
		- Resolve y collision
	*/

	if (intersection.has_value())
	{
		if (intersection.value().size.x < intersection.value().size.y)
		{
			//If intersection is on right side of player
			if (intersection.value().position.x > this->enemyBoundsBox.getCenter().x)
			{
				this->enemyPosition.x -= intersection.value().size.x;
			}
			//If intersection is on left side of player
			else
			{
				this->enemyPosition.x += intersection.value().size.x;
			}
		}
		else
		{
			//If collision is above the player
			if (intersection.value().position.y < this->enemyBoundsBox.getCenter().y)
			{
				this->enemyPosition.y += intersection.value().size.y;
			}
			//If collision is below the player
			else
			{
				this->enemyPosition.y -= intersection.value().size.y;
			}
		}
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

void Enemy::updateEnemyShape()
{
	//Update the enemy shape position
	this->enemyShape[0].position = Vector2f(this->enemyPosition.x, this->enemyPosition.y);
	this->enemyShape[1].position = Vector2f(this->enemyPosition.x + this->width, this->enemyPosition.y);
	this->enemyShape[2].position = Vector2f(this->enemyPosition.x, this->enemyPosition.y + this->height);
	this->enemyShape[3].position = Vector2f(this->enemyPosition.x + this->width, this->enemyPosition.y + this->height);

	//Update the texture vertices
	this->enemyShape[0].texCoords = Vector2f(0.f, 0.f);
	this->enemyShape[1].texCoords = Vector2f(this->width, 0.f);
	this->enemyShape[2].texCoords = Vector2f(0.f, this->height);
	this->enemyShape[3].texCoords = Vector2f(this->width, this->height);
}


/*
	PUBLIC
	FUNCTIONS
*/

void Enemy::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= Transformable::getTransform();
	states.texture = &this->enemyTexture;
	states.blendMode = BlendAlpha;

	target.draw(this->enemyShape, states);
}



//==================================================
/*
	GOBLIN
	CLASS
	FUNCTIONS
*/
//==================================================


/*
	INIT
	FUNCTIONS
*/

void Goblin::initVertexArray()
{
	this->goblinShape.setPrimitiveType(PrimitiveType::Triangles);
	this->goblinShape.resize(3);

	//Vertice Positions
	this->goblinShape[0].position = Vector2f(10.f, 10.f);
	this->goblinShape[1].position = Vector2f(10.f, 100.f);
	this->goblinShape[2].position = Vector2f(100.f, 100.f);
}

void Goblin::initCoreAttributes()
{
	this->health = 100;
	this->stamina = 100;
}


/*
	CONSTRUCTORS
	DESTRUCTORS
*/

Goblin::Goblin()
{
	this->initVertexArray();
	this->initCoreAttributes();
}

Goblin::~Goblin()
{

}


/*
	PUBLIC FUNCTIONS
*/

void Goblin::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= Transformable::getTransform();
	target.draw(this->goblinShape);
}

