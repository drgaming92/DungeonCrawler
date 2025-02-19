
#include <cstdint>
#include <vector>

#ifndef DUNGEON_HPP
#define DUNGEON_HPP

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;

//====================================================================

enum class RoomType
{
    //Room Types

    //Null room, should be de-allocated after init
    Empty,
    
    //Good rooms
    Treasure,

    //Puzzle rooms
    Locked,

    //Bad rooms
    Danger,
};

//====================================================================

class Room
{
private:

    //Room Bounds Box
    sf::IntRect roomBoundsBox;
    
    //Room init functions
    void initRoomType(RoomType pType);
    void initPositions();
    void initDimensions(int x, int y);
    void initRoomBoundsBox();
    void initPointers();

public:

    //ID Number
    int id;

    //Room gameplay properties
    RoomType type;

    //Room logic properties
    bool visited;

    //Room Positional Properties
    int posX;
    int posY;

    //Room physical properties
    int height;
    int width;

    //Adjacent room pointers
    Room* north;
    Room* east;
    Room* west;
    Room* south;

    //Constructors / Destructors
    Room();
    ~Room();

    //Accessors
    sf::IntRect getRoomBoundsBox() const;

    //Public Functions
    void checkAdjacent();

};

//========================================================

class Dungeon
{
private:

    //Current Room
    sf::RectangleShape currentRoomShape;

    //Map Dimensions
    int width;
    int height;

    //Init functions
    void initCurrentRoom();
    void initMap();

    //Private Functions
    void allocateMemory();
    void setupConnections();
    void setCurrentRoom();
    void removeEmptyRooms();

public:

    //Game state variables
    vector<vector<Room*>> map;
    Room* currentRoom;

    //Constuctor / Destructor
    Dungeon(int width=8, int height=8);
    ~Dungeon();

    //Update Functions

    //Render Functions
    void renderRoom(sf::RenderTarget* target);

};

//=================================================================

#endif // DUNGEON_HPP