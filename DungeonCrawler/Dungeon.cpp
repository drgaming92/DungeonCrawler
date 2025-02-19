#include "Game.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;


//=================================
/*
    ROOM CLASS
    FUNCTIONS
*/
//=================================


/*
    INIT
    FUNCTIONS
*/

void Room::initRoomType(RoomType pType)
{
    this->type = pType;
}

void Room::initPositions()
{
    this->posX = 0;
    this->posY = 0;
}

void Room::initDimensions(int pHeight, int pWidth)
{
    this->height = pHeight;
    this->width = pWidth;
}

void Room::initRoomBoundsBox()
{
    this->roomBoundsBox.position = Vector2i(this->posX, this->posY);

    this->roomBoundsBox.size = Vector2i(this->width, this->height);
}

void Room::initPointers()
{
    this->north = nullptr;
    this->east = nullptr;
    this->west = nullptr;
    this->south = nullptr;
}


/*
    CONSTRUCTORS
    DESTRUCTORS
*/

Room::Room()
{
    /*
        Initializes member attributes with random values
        - Seeds random generator
        - Gets random values for arguments
        - Initializes attributes
    */
    random_device rd;
    mt19937 gen(rd());
    discrete_distribution<> roomTypedistrib({ 0.25,0.2,0.15,0.2 }); //empty(no room), treasure, locked, danger

    RoomType randomType = static_cast<RoomType>(roomTypedistrib(gen));
    
    uniform_int_distribution<>intDistrib(500, 1000);
    int randomHeight = intDistrib(gen);
    int randomWidth = intDistrib(gen);

    this->initRoomType(randomType);
    this->initPositions();
    this->initDimensions(randomHeight, randomWidth);

    this->initRoomBoundsBox();

    this->initPointers();

}

Room::~Room()
{
    /*           
        Remove dangling pointers
        - Check if already deleted
        - Deletes
        - Sets pointer to null pointer
    */
    if (!this->north) { delete this->north; this->north = nullptr; }
    if (!this->east) { delete this->east; this->east = nullptr; }
    if (!this->west) { delete this->west; this->west = nullptr; }
    if (!this->south) { delete this->south; this->south = nullptr; }
}


/*
    ACCESSORS
*/

IntRect Room::getRoomBoundsBox() const
{
    return this->roomBoundsBox;
}


/*
    PUBLIC
    FUNCTIONS
*/

void Room::checkAdjacent()
{
    /*
        @return void

        checks adjacent rooms
        - checks if target room exists
        - checks if target room is type empty
        - if both are true then delete that room and set pointer to nullptr
    */
    if (this->north && this->north->type == RoomType::Empty) { delete this->north; }
    if (this->east && this->east->type == RoomType::Empty) { delete this->east; }
    if (this->west && this->west->type == RoomType::Empty) { delete this->west; }
    if (this->south && this->south->type == RoomType::Empty) { delete this->south; }
}



//=====================================
/*
    DUNGEON CLASS
    FUNCTIONS
*/
//=====================================


/*
    INIT
    FUNCTIONS
*/

void Dungeon::initMap()
{
    this->map.resize(this->height, vector<Room*>(this->width, nullptr));
}

void Dungeon::initCurrentRoom()
{
    this->currentRoomShape.setFillColor(Color::White);

    this->currentRoomShape.setSize(Vector2f(
        static_cast<float>(this->currentRoom->getRoomBoundsBox().size.x),
        static_cast<float>(this->currentRoom->getRoomBoundsBox().size.y)
    ));

    this->currentRoomShape.setPosition(Vector2f(
        static_cast<float>(this->currentRoom->getRoomBoundsBox().position.x),
        static_cast<float>(this->currentRoom->getRoomBoundsBox().position.y)
    ));
}


/*
    PRIVATE
    FUNCTIONS
*/

void Dungeon::allocateMemory()
{
    /*
        @return void

        Pre-allocates Memory
        - loops through each row
        - loops through each column in row
        - dynamically allocates memory for a new room
        - assigns room pointer
    */

    int idCounter = 1;
    for (auto& row : this->map)
    {
        for (auto& roomPtr : row)
        {
            roomPtr = new Room();
            roomPtr->id = idCounter;
            idCounter++;
        }
    }

}

void Dungeon::setupConnections()
{
    /*
        @return void

        Assigns pointers
        - Assigns pointers for each row
        - Assigns pointers for each column
    */

    for (short i = 0; i < height; i++)
    {
        for (short j = 0; j < width; j++)
        {
            //check if it isn't the first row
            if (i > 0) this->map[i][j]->north = this->map[i - 1][j];
            //check if it isn't the last row
            if (i < height - 1) this->map[i][j]->south = this->map[i + 1][j];
            //check if it isn't the first column
            if (j > 0) this->map[i][j]->west = this->map[i][j - 1];
            //check if it isn't the last column
            if (j < width - 1) this->map[i][j]->east = this->map[i][j + 1];
        }
    }
}

void Dungeon::setCurrentRoom()
{

    /*
        @return void

        Searches for an eligble starting room
        - Loops through each row
        - Loops through each column in row
        - Checks if the starting room has already been found and that the room type is valid
        - Sets the current room to the first room found
    */

    bool startingRoomFound = false;
    for (const auto& row : this->map)
    {
        for (const auto& room : row)
        {
            if (room)
            {
                if (!(startingRoomFound))
                {
                    this->currentRoom = room;
                    startingRoomFound = true;
                    break;
                }
            }
        }
        if (startingRoomFound)
        {
            break;
        }
    }
}

void Dungeon::removeEmptyRooms()
{
    /*
        @return void

        checks for empty rooms
        - calls the "checkAdjacent" member function of each room
    */
    for (uint8_t i = 0; i < height; i++)
    {
        for (uint8_t j = 0; j < width; j++)
        {
            this->map[i][j]->checkAdjacent();
        }
    }

}

//Constructors / Destructors
Dungeon::Dungeon(int pWidth, int pHeight)
{
    //Init map size
    this->width = pWidth;
    this->height = pHeight;
    this->initMap();


    //Init map data
    this->allocateMemory();
    this->setupConnections();
    this->setCurrentRoom();
    this->initCurrentRoom();

    //Delete Empty Rooms
    //this->removeEmptyRooms();
}

Dungeon::~Dungeon()
{
    /*
        De-allocate memory
        - loops through each row
        - loops through each column
        - checks if the given pointer exists
        - de-allocates the room and sets pointer to nullptr
    */
    for (auto& row : this->map)
    {
        for (auto& roomPtr : row)
        {
            if (roomPtr)
            {
                delete roomPtr;
                roomPtr = nullptr;
            }
        }
    }

}


/*
    UPDATE
    FUNCTIONS
*/




/*
    RENDER
    FUNCTIONS
*/
void Dungeon::renderRoom(sf::RenderTarget* target)
{
    target->draw(this->currentRoomShape);
}

