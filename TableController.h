#pragma once

#include "Utils.h"
#include "Robot.h"

#include <map>

class TableController
{
public:
    TableController(int xM, int yM);

    void CheckCommandInfo(CommandInfo info);

private:
    int xMax = 0;
    int yMax = 0;

    std::unique_ptr<Robot> robot = nullptr;
    static const std::map<FACE_DIRECTION, std::string> directions;
};
