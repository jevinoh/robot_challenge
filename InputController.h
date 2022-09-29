#pragma once

#include "Utils.h"
#include <map>

class InputController
{
public:
    InputController();

    CommandInfo Parse(std::string input);

private:
    bool isNumber(std::string s);
    std::string removeSpaces(std::string str);

    static const std::map<std::string, ACTION> input_actions;
    static const std::map<std::string, FACE_DIRECTION> input_direction;

};
