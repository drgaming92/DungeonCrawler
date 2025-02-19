#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <array>
#include <cstdint>
#include <memory>

using namespace std;

class Player : public sf::Drawable, public sf::Transformable
{
private:

	//Player Bounds Box
	sf::IntRect playerBoundsBox;
	sf::Vector2f collisionCorrection;

	//Player Vertex Array
	sf::VertexArray playerShape;
	sf::Texture playerTexture;

	//Size Attributes
	int height;
	int width;

	//Core Attributes
	int health;
	int stamina;
	int mana;

	//Clocks
	sf::Clock sprintToggleClock;

	//Movement Attributes
	float momentumX;
	float momentumY;
	float posX;
	float posY;
	bool sprinting;

	//Survival Attributes (Not yet implemented)

	//Init functions
	void initTexture();
	void initSize();
	void initCoreAttributes();
	void initMovement();
	void initPlayerShape();

public:

	//Constructors / Destructors
	Player();
	~Player();

	//Accessors
	sf::IntRect getPlayerBounds();
	const sf::Vector2f getPlayerPos();
	const sf::Vector2f getMomentum();

	//Collision Functions
	void handleCollisionWith(optional<sf::IntRect> enemyIntersection);
	void handleWorldCollision(optional<sf::IntRect> worldIntersection);
	void updateCollisionVector();

	//Update Functions
	void updateBoundsBox();
	void updateSprint();
	void updatePosition();
	void updatePlayerShape();

	//Render Functions
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};


#endif // PLAYER_HPP