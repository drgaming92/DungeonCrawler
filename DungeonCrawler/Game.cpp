#include "Game.hpp"

using namespace sf;

/*
	INIT
	FUNCTIONS
*/
void Game::initWindow()
{
	this->window = new RenderWindow(VideoMode({ 1280, 720 }), "Mystik", Style::Titlebar | Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initCamera()
{
	this->camera = Camera();
}

void Game::initDungeon()
{
	uint8_t width = 16;
	uint8_t height = 16;
	this->dungeon = Dungeon();
}

void Game::initPlayer()
{
	this->player = Player();
}

void Game::initEnemies(uint16_t numOfEnemies)
{
	this->enemies.reserve(static_cast<int>(this->maxSprites));
	if (numOfEnemies > this->maxSprites)
	{
		this->enemies.resize(static_cast<int>(this->maxSprites));
	}
	else
	{
		this->enemies.resize(static_cast<int>(numOfEnemies));
	}
	for (auto& enemy : this->enemies)
	{
		enemy = new Enemy();
	}
}

/*
	PRIVATE
	FUNCTIONS
*/


/*
	CONSTRUCTORS
	DECONSTRUCTORS
*/
Game::Game()
{
	this->initWindow();
	this->initDungeon();
	this->initPlayer();

	uint16_t numOfEnemies = 28;
	this->initEnemies(numOfEnemies);
}

Game::~Game()
{
	delete this->window;
	for (auto& enemy : this->enemies)
	{
		delete enemy;
	}
}


/*
	ACCESSORS
*/
const bool Game::isRunning()
{
	return this->window->isOpen();
}


/*
	UPDATE
	FUNCTIONS
*/
void Game::updateGameView()
{
	/*
		@return void

		Sets the view to the player
		see "Camera.cpp > Public Functions > updateGameCenter" for information
	*/
	this->camera.updateGameCenter(this->player.getPlayerPos(), this->player.getMomentum());
}

void Game::updatePlayer()
{
	/*
		@return void

		Sets new position based on input from player
		see "Player.cpp > Update Functions > updatePosition" for information
	*/
	this->player.updatePosition();
}

void Game::updateEnemies()
{
	for (auto& enemy : this->enemies)
	{
		enemy->moveTowardsStop();
	}
}

void Game::updateEvents()
{
	/*
		@return void

		Handles incoming events
		NOTE: all input for the player character is handled in "Player.cpp > Update Functions"
	*/

	while (const std::optional event = this->window->pollEvent())
	{
		//Window closed
		if (event->is<Event::Closed>())
		{
			this->window->close();
		}

	}
}

void Game::updateMousePositions()
{

	/*
		@return void

		Gets mouse position
		- Get mouse position from the window
		- Get mouse position from the view
	*/

	this->mousePosWindow = Mouse::getPosition(*this->window);

	this->mousPosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

//Master Update Function
void Game::update()
{

	//Update views
	this->updateGameView();

	//Update game objects
	this->updatePlayer();
	this->updateEnemies();

	//Update Collisions
	this->handleCollisions();

	//Update mouse positions
	this->updateMousePositions();

	//Update events
	this->updateEvents();
}


/*
	COLLISION
	FUNCTIONS
*/

void Game::handlePlayerEnemyCollisions()
{
	optional<IntRect> intersection;
	for (auto& enemy : this->enemies)
	{
		intersection = enemy->checkCollisionWith(this->player.getPlayerBounds());
		if (intersection.has_value())
		{
			this->player.handleCollisionWith(intersection);
		}
	}
}

void Game::handleEnemyEnemyCollisions()
{

	/*
		@return void

		checks for collisions between each enemy
		- Iterate over each enemy
		- For each enemy check collisions with other enemies
		- Ensure that the otherEnemy is not the same as the enemy that is checking
	*/

	optional<IntRect> intersection;
	for (auto& enemy : this->enemies)
	{
		for (auto& otherEnemy : this->enemies)
		{
			if (otherEnemy->enemyPosition == enemy->enemyPosition)
			{
				continue;
			}
			else
			{
				intersection = enemy->checkCollisionWith(otherEnemy->getCollisionBox());
				enemy->handleCollisionWith(intersection);
			}
		}
	}
}

void Game::handlePlayerWorldCollisions()
{
	optional<IntRect> intersection = this->dungeon.currentRoom->getRoomBoundsBox().findIntersection(this->player.getPlayerBounds());

	if (intersection.has_value())
	{
		this->player.handleWorldCollision(intersection);
	}
}

//Master collision function
void Game::handleCollisions()
{
	//Entity-Entity Collisions
	this->handlePlayerEnemyCollisions();
	this->handleEnemyEnemyCollisions();

	//Entity-World Collisions
	this->handlePlayerWorldCollisions();

	//Update Collision Vectors
	this->player.updateCollisionVector();
}


/*
	RENDER
	FUNCTIONS
*/
void Game::renderCurrentRoom()
{
	/*
		@return void

		renders the current room
		see "Dungeon.cpp > Render Functions > renderRoom"
	*/

	this->dungeon.renderRoom(this->window);
}

void Game::renderPlayer()
{
	Sprite playerSprite(this->player.playerTexture);
	this->player.render(playerSprite, this->window);
}

void Game::renderEnemies()
{
	for (auto& enemy : this->enemies)
	{
		Texture enemyTexture = enemy->enemyTexture;
		Sprite enemySprite(enemyTexture);
		enemy->render(enemySprite, this->window);
	}
}

//Master Render Function
void Game::render()
{
	//Clear the old frame
	this->window->clear(Color::Black);

	//Render Game Objects
	this->window->setView(this->camera.gameView);

	this->renderCurrentRoom();
	this->renderEnemies();
	this->renderPlayer();

	//Render ui (coming soon)

	//Display
	this->window->display();
}

