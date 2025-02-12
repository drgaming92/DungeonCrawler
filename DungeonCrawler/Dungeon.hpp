
#include <cstdint>
#include <vector>

#ifndef DUNGEON_HPP
#define DUNGEON_HPP

using namespace std;

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

class Room
{
private:
    
    //Room init functions
    void initRoomType(RoomType pType);
    void initPositions();
    void initDimensions(float x, float y);
    void initPointers();

public:

    //Room gameplay properties
    RoomType type;

    //Room logic properties
    bool visited;

    //Room Positional Properties
    int posX;
    int posY;

    //Room physical properties
    uint16_t height;
    uint16_t width;

    //Adjacent room pointers
    Room* north;
    Room* east;
    Room* west;
    Room* south;

    //Constructors / Destructors
    Room();
    ~Room();

    //Functions
    void checkAdjacent();

};

class Dungeon
{
private:

    //Dimensions
    uint8_t width;
    uint8_t height;

    //Init functions
    void initMap();
public:

    //Game state variables
    vector<vector<Room*>> map;
    Room* currentRoom;

    //Constuctor / Destructor
    Dungeon();
    ~Dungeon();

    //Functions
    void allocateMemory();
    void setupConnections();
    void initCurrentRoom();
    void removeEmptyRooms();

};


#endif // DUNGEON_HPP