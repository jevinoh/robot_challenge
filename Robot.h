#pragma once

#include "Utils.h"

class Robot
{
public:
    Robot(int xc, int yc, FACE_DIRECTION dir);

    void MoveUp();
    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void Move();

    int  GetCoordinateX() const;
    int  GetCoordinateY() const;
    FACE_DIRECTION GetFacingDirection() const;

    void SetCoordinateX(int xVal);
    void SetCoordinateY(int yVal);
    void SetFacingDirection(FACE_DIRECTION dir);

private:
    int x, y;
    FACE_DIRECTION direction = FACE_DIRECTION::NORTH;
};
