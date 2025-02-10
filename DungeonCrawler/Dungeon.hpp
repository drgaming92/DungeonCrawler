#ifndef DUNGEON_H
#define DUNGEON_H

#include "Game.hpp"

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
public:

    //Room gameplay properties
    RoomType type;

    //Room logic properties
    bool visited;

    //Room Positional Properties
    uint16_t x;
    uint16_t y;

    //Room physical properties
    uint8_t height;
    uint8_t width;

    //Adjacent room pointers
    Room* north;
    Room* east;
    Room* west;
    Room* south;

    //Constructors / Destructors
    Room() : type(RoomType::Empty), visited(false), north(nullptr), east(nullptr), west(nullptr), south(nullptr), x(0), y(0) {}
    ~Room();

    uint16_t getRoomX();
    uint16_t getRoomY();
};


class Dungeon
{
private:

    //Dimensions
    uint8_t width;
    uint8_t height;

public:
    //2D map vector
    Room** map;

    //Constuctor / Destructor
    Dungeon(uint8_t pWidth, uint8_t pHeight);
    ~Dungeon();

    //Functions
    void allocateMemory();
    void setupConnections();
    void generateRooms();
    void setCurrentRoom();

};


#endif // DUNGEON_H
