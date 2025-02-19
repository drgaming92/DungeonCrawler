#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;


//============================================
/*
	CAMERA
	CLASS
*/
//============================================

class Camera
{
private:

	//Game View Attributes
	sf::Vector2f gameViewCenter;
	sf::Vector2f gameViewSize;

	//UI View Attributes
	sf::Vector2f uiViewCenter;
	sf::Vector2f uiViewSize;

	//Init Functions
	void initGameViewAttributes();
	void initUI_ViewAttributes();
	void initGameView();

public:

	//Views
	sf::View gameView;
	sf::View uiView;

	//Constructors / Destructors
	Camera();
	~Camera();

	//Update Functions
	void updateGameCenter(sf::Vector2f playerPos, sf::Vector2f playerMomentum);

};


//=====================================================
/*
	BUTTON
	CLASS
*/
//=====================================================

class Button : public sf::Drawable, public sf::Transformable
{
private:

	//Button Vertex Array
	sf::VertexArray buttonVertexArray;

	//Init Functions
	void initVertexArray();

public:

	//Constructors / Destructors
	Button();
	~Button();

	//Render Functions
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};


//=====================================================
/*
	USER INTERFACE
	CLASS
*/
//=====================================================

class UI
{
private:

	//Status Bars
	sf::RectangleShape barBacking;
	sf::RectangleShape playerHealthBar;

	//Init Functions
	void initButtons();

public:

	//Constructors / Destructors
	UI();
	~UI();

};


#endif // CAMERA_HPP