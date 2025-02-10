#include "Game.hpp"


/*
	INIT
	FUNCTIONS
*/
void Game::initVariables()
{
	this->window = nullptr;
}

void Game::initWindow()
{
	this->window = new RenderWindow(VideoMode({ 1280, 720 }), "Mystik", Style::Titlebar | Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initDungeon()
{
	uint8_t width = 16;
	uint8_t height = 16;
	this->dungeon = &Dungeon(width, height);
}


/*
	CONSTRUCTOR / DECONSTRUCTOR
*/
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initDungeon();
}

Game::~Game()
{
	delete this->window;
}


/*
	ACCESSORS
*/
const bool Game::isRunning()
{
	return this->window->isOpen();
}


/*
	UPDATE FUNCTIONS
*/
void Game::updateEvents()
{
	while (const std::optional event = this->window->pollEvent())
	{
		if (event->is<Event::Closed>())
		{
			this->window->close();
		}
	}
}

void Game::updateMousePositions()
{
	this->mousePosWindow = Mouse::getPosition(*this->window);

	this->mousPosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateRoomPositions()
{
	
}

//Master Update Function
void Game::update()
{
	this->updateEvents();

	this->updateMousePositions();

}


/*
	RENDER FUNCTIONS
*/
void Game::renderRooms()
{

}

//Master Render Function
void Game::render()
{
	this->window->clear();

	//draw

	this->window->display();
}

