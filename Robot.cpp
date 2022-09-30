#include "Robot.h"

Robot::Robot(int xc, int yc, FACE_DIRECTION dir)
{
    info.x = xc;
    info.y = yc;
    info.dir = dir;
}

void Robot::MoveUp()
{
    info.y += 1;
}

void Robot::MoveDown()
{
    info.y -= 1;
}

void Robot::MoveLeft()
{
    info.x -= 1;
}

void Robot::MoveRight()
{
    info.x += 1;
}

void Robot::Move()
{
    switch(info.dir)
    {
        case FACE_DIRECTION::NORTH:
            MoveUp();
            break;
        case FACE_DIRECTION::SOUTH:
            MoveDown();
            break;
        case FACE_DIRECTION::EAST:
            MoveRight();
            break;
        case FACE_DIRECTION::WEST:
            MoveLeft();
            break;
        default:
            break;
    }
}

int  Robot::GetCoordinateX() const
{
    return info.x;
}

int  Robot::GetCoordinateY() const
{
    return info.y;
}

FACE_DIRECTION Robot::GetFacingDirection() const
{
    return info.dir;
}

CoordinateAndDirection Robot::GetRobotCoordinateAndDirection() const
{
    return info;
}

void Robot::SetCoordinateX(int xVal)
{
    info.x = xVal;
}

void Robot::SetCoordinateY(int yVal)
{
    info.y = yVal;
}

void Robot::SetFacingDirection(FACE_DIRECTION dir)
{
    info.dir = dir;
}
