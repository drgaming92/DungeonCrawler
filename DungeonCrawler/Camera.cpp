#include "Camera.hpp"

using namespace sf;


//====================================================
/*
	CAMERA
	CLASS
	FUNCTIONS
*/
//====================================================


/*
	INIT
	FUNCTIONS
*/

void Camera::initGameViewAttributes()
{
	this->gameViewCenter = { 200.f, 200.f };
	this->gameViewSize = { 320.f, 180.f };
}

void Camera::initUI_ViewAttributes()
{
	this->uiViewCenter = this->gameViewCenter;
	this->uiViewSize = this->gameViewSize;
}

void Camera::initGameView()
{
	this->gameView = View(this->gameViewCenter, this->gameViewSize);
}


/*
	CONSTRUCTORS
	DESTRUCTORS
*/

Camera::Camera()
{
	this->initGameViewAttributes();
	this->initUI_ViewAttributes();
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


//=============================================
/*
	BUTTON
	CLASS
*/
//==============================================


/*
	INIT
	FUNCTIONS
*/

void Button::initVertexArray()
{

}


/*
	CONSTRUCTORS
	DESTRUCTORS
*/

Button::Button()
{
	this->initVertexArray();
}

Button::~Button()
{

}


/*
	RENDER
	FUNCTIONS
*/

void Button::draw(RenderTarget& target, RenderStates states) const
{
	
}


//=============================================
/*
	USER INTERFACE
	CLASS
	FUNCTIONS
*/
//=============================================

/*
	INIT
	FUNCTIONS
*/

void UI::initButtons()
{
	
}


/*
	CONSTRUCTORS
	DESTRUCTORS
*/

UI::UI()
{
	this->initButtons();
}

UI::~UI()
{

}

