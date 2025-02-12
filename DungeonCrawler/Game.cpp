#include "Game.hpp"

using namespace sf;

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
	this->window = make_shared<RenderWindow>(VideoMode({ 1280, 720 }), "Mystik", Style::Titlebar | Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initDungeon()
{
	uint8_t width = 16;
	uint8_t height = 16;
	this->dungeon = new Dungeon();
}

void Game::initCurrentRoom()
{
	this->currentRoomGame = this->dungeon->currentRoom;
}

void Game::initPlayer()
{
	this->player = new Player(this->window);
	this->playerShape = new RectangleShape({ static_cast<float>(this->player->width), static_cast<float>(this->player->height) });
	this->playerShape->setFillColor(Color::Green);
}


/*
	CONSTRUCTOR / DECONSTRUCTOR
*/
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initDungeon();
	this->initCurrentRoom();
	this->initPlayer();
}

Game::~Game()
{
	
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
		//Window closing
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

void Game::updateCurrentRoom()
{
	this->currentRoomShape = new RectangleShape({ static_cast<float>(this->currentRoomGame->width), static_cast<float>(this->currentRoomGame->height) });
	this->currentRoomShape->setPosition({
		static_cast<float>(this->dungeon->currentRoom->posX),
		static_cast<float>(this->dungeon->currentRoom->posY)
		} );
	this->currentRoomShape->setFillColor(Color::White);

}

void Game::updatePlayer()
{
	this->player->getMovement();

	this->playerShape->setPosition({
		static_cast<float>(this->player->posX),
		static_cast<float>(this->player->posY)
		});
}

//Master Update Function
void Game::update()
{
	this->updateEvents();

	this->updateMousePositions();

	this->updateCurrentRoom();

	this->updatePlayer();

}


/*
	RENDER FUNCTIONS
*/
void Game::renderCurrentRoom()
{
	this->window->draw(*this->currentRoomShape);
}

void Game::renderPlayer()
{
	this->window->draw(*this->playerShape);
}

//Master Render Function
void Game::render()
{
	this->window->clear(Color::Black);

	//draw
	this->renderCurrentRoom();
	this->renderPlayer();

	this->window->display();
}

