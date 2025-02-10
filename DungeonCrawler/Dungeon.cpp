#include "Game.hpp"

using namespace std;
/*
    ROOM CLASS
    FUNCTIONS
*/
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

uint16_t Room::getRoomX()
{
    return this->x;
}

uint16_t Room::getRoomY()
{
    return this->y;
}


/*
    DUNGEON CLASS
    FUNCTIONS
*/
Dungeon::Dungeon(uint8_t pWidth, uint8_t pHeight)
{

    allocateMemory();

    setupConnections();

    generateRooms();

}

Dungeon::~Dungeon()
{
    /*
        De-allocate memory
        - Deletes each row in the vector
        - Deltes the vector
    */
    for (uint8_t i = 0; i < height; i++)
    {
        delete[] this->map[i];
    }
    delete[] this->map;
}

void Dungeon::allocateMemory()
{
    /*
        @return void

        Pre-allocates Memory
        - Allocate memory for each row
        - Allocate memory for each column in each row
    */

    this->map = new Room * [height];

    for (uint8_t i = 0; i < height; i++)
    {
        this->map[i] = new Room[width];
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
            if (i > 0) this->map[i][j].north = &this->map[i - 1][j];
            //check if it isn't the last row
            if (1 < height - 1) this->map[i][j].south = &this->map[i + 1][j];
            //check if it isn't the first column
            if (j > 0) this->map[i][j].west = &this->map[i][j - 1];
            //check if it isn't the last column
            if (j < width - 1) this->map[i][j].east = &this->map[i][j + 1];
        }
    }
}

void Dungeon::generateRooms()
{
    /*
        @return void

        Randomly assigns properties for each room
        - Seeds random generator
        - Randomly chooses random room type
        - Randomly chooses random room size (coming soon)
    */

    random_device rd;
    mt19937 gen(rd());
    discrete_distribution<> distrib({0.25,0.2,0.15,0.2}); //empty(no room), treasure, locked, danger

    for (short i = 0; i < height; i++)
    {
        for (short j = 0; j < width; j++)
        {
            RoomType type = static_cast<RoomType>(distrib(gen));
            this->map[i][j].type = type;

            this->map[i][j].height = 127;
            this->map[i][j].width = 127;
            
        }
    }
}



