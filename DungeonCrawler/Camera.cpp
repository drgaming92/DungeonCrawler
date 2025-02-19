#include "Camera.hpp"

using namespace sf;


/*
	INIT
	FUNCTIONS
*/
void Camera::initAttributes()
{
	this->centerX = 200.f;
	this->centerY = 200.f;
	this->viewCenter = { this->centerX, this->centerY };

	this->viewSize = { 320.f, 180.f };
}

void Camera::initGameView()
{
	this->gameView = View(this->viewCenter, this->viewSize);
}


/*
	CONSTRUCTORS
	DESTRUCTORS
*/
Camera::Camera()
{
	this->initAttributes();
	this->initGameView();
}

Camera::~Camera()
{
	
}


/*
	PUBLIC
	FUNCTIONS
*/
void Camera::updateGameCenter(Vector2f playerPos, Vector2f playerMomentum)
{
	/*
		@return void

		Sets the center of the view to the player with an offset
		- Creates an updated center position for the view from player position and momentum
		- Sets the updated center position
	*/
	Vector2f newCenter = playerPos;
	newCenter.x -= playerMomentum.x - 15.f;
	newCenter.y -= playerMomentum.y - 15.f;
	this->gameView.setCenter(newCenter);

}

