#include "TableController.h"

TableController::TableController(int xM, int yM) : xMax(xM), yMax(yM)
{
}

void TableController::CheckCommandInfo(CommandInfo info)
{
    if(info.act == ACTION::UNKNOWN)
    {
        return;
    }

    if(info.act == ACTION::PLACE)
    {
        if(info.x > xMax || info.y > yMax)
        {
            printf("[ERROR] Robot will fall using input coordinates: inputX[%d] inputY[%d] xMax[%d] yMax[%d]\n", info.x, info.y, xMax, yMax);
            return;
        }

        if(robot == nullptr)
        {
            robot = std::make_unique<Robot>(info.x, info.y, info.dir);
        }
        else
        {
            robot->SetCoordinateX(info.x);
            robot->SetCoordinateY(info.y);
            robot->SetFacingDirection(info.dir);
        }
    }
    else if(robot && info.act == ACTION::REPORT)
    {
        printf(">>>>> %d, %d, %s\n", robot->GetCoordinateX(),  robot->GetCoordinateY(), directionsToString.at(robot->GetFacingDirection()).c_str());
    }
    else if(robot && info.act == ACTION::MOVE)
    {
        int tempX = robot->GetCoordinateX();
        int tempY = robot->GetCoordinateY();

        switch(robot->GetFacingDirection())
        {
            case FACE_DIRECTION::NORTH:
                tempY++;
                break;
            case FACE_DIRECTION::SOUTH:
                tempY--;
                break;
            case FACE_DIRECTION::EAST:
                tempX++;
                break;
            case FACE_DIRECTION::WEST:
                tempX--;
                break;
            default:
                break;
        }

        if((tempX < 0) || (tempX > xMax) || (tempY < 0) || (tempY > yMax))
        {
            printf("[ERROR] Ignoring MOVE command, the Robot may fall off the table\n");
        }
        else
        {
            robot->Move();
        }

    }
    else if(robot && info.act == ACTION::LEFT)
    {
        if(robot->GetFacingDirection() == FACE_DIRECTION::NORTH)
        {
            robot->SetFacingDirection(FACE_DIRECTION::WEST);
        }
        else
        {
            FACE_DIRECTION newDir = static_cast<FACE_DIRECTION>(static_cast<int>(robot->GetFacingDirection()) - 1);
            robot->SetFacingDirection(newDir);
        }
    }
    else if(robot && info.act == ACTION::RIGHT)
    {
        if(robot->GetFacingDirection() == FACE_DIRECTION::WEST)
        {
            robot->SetFacingDirection(FACE_DIRECTION::NORTH);
        }
        else
        {
            FACE_DIRECTION newDir = static_cast<FACE_DIRECTION>(static_cast<int>(robot->GetFacingDirection()) + 1);
            robot->SetFacingDirection(newDir);
        }
    }
    else
    {
        printf("[ERROR] Robot not initialized\n");
    }
}

bool TableController::IsRobotInitialized()
{
    return robot ? true: false;
}

CoordinateAndDirection TableController::getRobotCoordinateAndDirection() const
{
    return robot->GetRobotCoordinateAndDirection();
}
