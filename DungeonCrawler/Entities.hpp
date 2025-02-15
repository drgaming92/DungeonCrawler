#ifndef ENTITIES_HPP
#define ENTITES_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <array>
#include <vector>

using namespace std;

//============================================

class Entity
{
private:

	//Entity Shape
	sf::RectangleShape entityShape;

	//Init Functions
	void initAttributes();
	void initShape();
	void initPos(sf::Vector2f position);

protected:

	//Core Attributes
	uint16_t health;

	//Size Attributes
	float height;
	float width;
	
	//Protected Functions
	sf::Vector2f getRandomPos();

	//Render Functions
	void renderEntity(sf::RenderTarget* target);

public:

	//Constructors / Destructors
	Entity();
	~Entity();

};

//==============================================

class Enemy : public Entity
{
private:

	//Enemy Bound Box
	sf::IntRect enemyBoundsBox;

	//Patrol/Movement Attributes
	sf::Clock patrolToggleClock;
	vector<sf::Vector2f> stopPoints;
	uint8_t currentStop;
	float speed;

	//Core Attributes

	//Init Functions
	void initAttributes();
	void initTexture();
	void initPos(sf::Vector2f position);
	void initPatrol(uint8_t numOfStops);

public:


	//Enemy Sprite Attributes
	sf::Texture enemyTexture;
	sf::Vector2f enemyPosition;

	//Constructors / Destructors
	Enemy();
	~Enemy();

	//Public Functions
	optional<sf::IntRect> checkCollisionWith(sf::IntRect otherBoundsBox);

	//Movement Functions
	void moveTowardsStop();

	//Update Functions
	void updateBoundsBox();

	//Render Functions
	void render(sf::Sprite& enemySprite, sf::RenderTarget* target);

};

//================================================


#endif // ENTITIES_HPP