#include "Robot.h"

Robot::Robot(int xc, int yc, FACE_DIRECTION dir) : x(xc), y(yc), direction(dir)
{
    printf(">>>>> Initial value : %d, %d, %d\n", x,  y, static_cast<int>(dir));
}

void Robot::MoveUp()
{
    y += 1;
}

void Robot::MoveDown()
{
    y -= 1;
}

void Robot::MoveLeft()
{

    x -= 1;
}

void Robot::MoveRight()
{
    x += 1;
}

void Robot::Move()
{
    switch(direction)
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
    return x;
}

int  Robot::GetCoordinateY() const
{
    return y;
}

FACE_DIRECTION Robot::GetFacingDirection() const
{
    return direction;
}

void Robot::SetCoordinateX(int xVal)
{
    x = xVal;
}

void Robot::SetCoordinateY(int yVal)
{
    y = yVal;
}

void Robot::SetFacingDirection(FACE_DIRECTION dir)
{
    direction = dir;
}
