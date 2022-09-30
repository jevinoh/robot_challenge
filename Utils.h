#pragma once
#include <iostream>
#include <memory>
#include <string>
#include <map>

// Increment value based on clockwise direction
enum class FACE_DIRECTION
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

enum class ACTION
{
    PLACE,
    MOVE,
    LEFT,
    RIGHT,
    REPORT,
    UNKNOWN
};

struct CommandInfo
{
    ACTION act;
    int x;
    int y;
    FACE_DIRECTION dir;

    CommandInfo(ACTION initAct, int initX, int initY, FACE_DIRECTION initDir):
     act(initAct), x(initX), y(initY), dir(initDir)
    {
    }

    CommandInfo()
    {
        act = ACTION::UNKNOWN;
        x = 0;
        y = 0;
        dir = FACE_DIRECTION::NORTH;
    }

    void reset()
    {
        act = ACTION::UNKNOWN;
        x = 0;
        y = 0;
        dir = FACE_DIRECTION::NORTH;
    }

    bool operator==(const CommandInfo &rOther) const
    {
        return (act == rOther.act) && (x == rOther.x) && (y == rOther.y) && (dir == rOther.dir);
    }

    bool operator!=(const CommandInfo &rOther) const
    {
        return (act != rOther.act) || (x != rOther.x) || (y != rOther.y) || (dir != rOther.dir);
    }
};

struct CoordinateAndDirection
{
    int x;
    int y;
    FACE_DIRECTION dir;

    CoordinateAndDirection()
    {
        x = 0;
        y = 0;
        dir = FACE_DIRECTION::NORTH;
    }
};


static const std::map<FACE_DIRECTION, std::string> directionsToString = {
    { FACE_DIRECTION::NORTH , "NORTH"},
    { FACE_DIRECTION::EAST  , "EAST" },
    { FACE_DIRECTION::SOUTH , "SOUTH"},
    { FACE_DIRECTION::WEST  , "WEST" },
};

static const std::map<ACTION, std::string> actionsToString = {
    { ACTION::PLACE,   "PLACE"  },
    { ACTION::MOVE,    "MOVE"  },
    { ACTION::LEFT,    "LEFT" },
    { ACTION::RIGHT,   "RIGHT"},
    { ACTION::REPORT , "REPORT" }
};

