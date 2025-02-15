#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <array>
#include <cstdint>
#include <memory>

using namespace std;

class Player
{
private:

	//Player Bounds Box
	sf::IntRect playerBoundsBox;

	//Size Attributes
	float height;
	float width;

	//Core Attributes
	uint16_t health;
	uint16_t stamina;
	uint16_t mana;

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
	void initShape();
	void initCoreAttributes();
	void initMovement();

public:

	//Player Texture
	sf::Texture playerTexture;

	//Constructors / Destructors
	Player();
	~Player();

	//Accessors
	sf::IntRect getPlayerBounds();
	const sf::Vector2f getPlayerPos();
	const sf::Vector2f getMomentum();

	//Collision Functions
	void handleEnemyCollision(optional<sf::IntRect> enemyIntersection);

	//Update Functions
	void updateBoundsBox();
	void updateSprint();
	void updatePosition();

	//Render Functions
	void render(sf::Sprite& playerSprite, sf::RenderTarget* target);

};


#endif // PLAYER_HPP