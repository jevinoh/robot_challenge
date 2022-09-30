#pragma once

#include "Utils.h"
#include "Robot.h"

#include <map>

class TableController
{
public:
    TableController(int xM, int yM);

    void CheckCommandInfo(CommandInfo info);

    bool IsRobotInitialized();
    CoordinateAndDirection getRobotCoordinateAndDirection() const;

private:
    int xMax = 0;
    int yMax = 0;

    std::unique_ptr<Robot> robot = nullptr;
};
