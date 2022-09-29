#pragma once
#include <iostream>
#include <memory>
#include <string>


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

    CommandInfo()
    {
        act = ACTION::UNKNOWN;
        x = 0;
        y = 0;
        dir = FACE_DIRECTION::NORTH;
    }
};
