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
	int health;

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

class Enemy : public Entity, public sf::Drawable, sf::Transformable
{
private:

	//Enemy Bound Box
	sf::IntRect enemyBoundsBox;

	//Shape
	sf::VertexArray enemyShape;

	//Patrol/Movement Attributes
	sf::Clock patrolToggleClock;
	vector<sf::Vector2f> stopPoints;
	short currentStop;
	float speed;

	//Core Attributes

	//Init Functions
	void initAttributes();
	void initTexture();
	void initPos(sf::Vector2f position);
	void initEnemyShape();
	void initPatrol(short numOfStops);

public:

	//Enemy Sprite Attributes
	sf::Texture enemyTexture;
	sf::Vector2f enemyPosition;

	//Constructors / Destructors
	Enemy();
	~Enemy();

	//Accessors
	sf::IntRect getCollisionBox();

	//Collision Functions
	optional<sf::IntRect> checkCollisionWith(sf::IntRect otherBoundsBox);
	void handleCollisionWith(optional<sf::IntRect> intersection);

	//Movement Functions
	void moveTowardsStop();

	//Update Functions
	void updateBoundsBox();
	void updateEnemyShape();

	//Public Functions
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

//================================================

class Goblin : public Enemy, public sf::Drawable, public sf::Transformable
{
private:

	//Bounds Box
	sf::IntRect boundsBox;

	//Shape
	sf::VertexArray goblinShape;

	//Core Attributes
	int health;
	int stamina;

	//Init Functions
	void initVertexArray();
	void initCoreAttributes();

public:

	//Constructors / Destructors
	Goblin();
	~Goblin();

	//Public Functions
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};


#endif // ENTITIES_HPP