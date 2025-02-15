#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

class Camera
{
private:

	//View Attributes
	float centerX;
	float centerY;
	sf::Vector2f viewCenter;
	sf::Vector2f viewSize;

	//Init Functions
	void initAttributes();
	void initGameView();

public:

	//Views
	sf::View gameView;
	//sf::View uiView;

	//Constructors / Destructors
	Camera();
	~Camera();

	//Update Functions
	void updateGameCenter(sf::Vector2f playerPos, sf::Vector2f playerMomentum);

};



#endif // CAMERA_HPP