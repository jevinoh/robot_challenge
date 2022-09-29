#include "InputController.h"

#include <vector>
#include <algorithm>

const std::map<std::string, ACTION> InputController::input_actions = {
    { "PLACE",  ACTION::PLACE  },
    { "MOVE",   ACTION::MOVE   },
    { "LEFT",   ACTION::LEFT   },
    { "RIGHT",  ACTION::RIGHT  },
    { "REPORT", ACTION::REPORT }
};

const std::map<std::string, FACE_DIRECTION> InputController::input_direction = {
    { "NORTH",  FACE_DIRECTION::NORTH  },
    { "EAST",   FACE_DIRECTION::EAST   },
    { "SOUTH",  FACE_DIRECTION::SOUTH  },
    { "WEST",   FACE_DIRECTION::WEST   },
};

// set of characters that would separate the input parameters, esp. for PLACE command
static const std::vector<std::string> delimiter = { " ", ",", ","};


InputController::InputController()
{
}

bool InputController::isNumber(std::string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        if (isdigit(s[i]) == false)
        {
            return false;
        }
    }
    return true;
}

std::string InputController::removeSpaces(std::string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

CommandInfo InputController::Parse(std::string input)
{
    CommandInfo info;
    size_t pos = 0;
    std::string token;
    int input_counter = 0;

    // Ignore if first character is '#' . Input might be from a test file and it's a comment section
    if(input.length() > 0 && input.at(0) == '#')
    {
        return info;
    }

    // Check if the input follows PLACE command pattern
    while ((pos = input.find(delimiter.at(input_counter))) != std::string::npos) {
        token = input.substr(0, pos);

        // Do some space cleanup just in case user added space character
        token = removeSpaces(token);

        // Check for primary command
        if(input_counter == 0)
        {
            auto it = input_actions.find(token);
            if(it != input_actions.end())
            {
                info.act = input_actions.at(token);
            }
            else
            {
                std::cerr << "[ERROR] Command not found, invalid input string" << std::endl;
                return info;
            }
        }
        // Check for coordinate value in case command is PLACE
        else if((info.act == ACTION::PLACE) && (input_counter == 1 || input_counter == 2))
        {
            if(isNumber(token))
            {
                input_counter == 1? info.x = stoi(token) : info.y = stoi(token);
            }
            else
            {
                info.act = ACTION::UNKNOWN;
                std::cerr << "[ERROR] coordinate input is not a number" << std::endl;
                return info;
            }
        }
        else
        {
            std::cerr << "[ERROR] Extra strings were added: " + input << std::endl;
            info.act = ACTION::UNKNOWN;
            return info;
        }

        input.erase(0, pos + delimiter.at(input_counter).length());
        if(input_counter < 2)
        {
            input_counter++;
        }
    }

    token = removeSpaces(input);
    auto it = input_direction.find(token);

    // Check for direction parameter if PLACE command or single COMMAND parameter
    if(it != input_direction.end())
    {
        info.dir = input_direction.at(token);
    }
    else
    {
        auto iter = input_actions.find(token);
        if(iter != input_actions.end())
        {
            info.act = input_actions.at(token);
            if((info.act == ACTION::PLACE))
            {
                std::cerr << "[ERROR] Needs additional parameters for: " +  token << std::endl;
                info.act = ACTION::UNKNOWN;
            }
        }
        else
        {
            std::cerr << "[ERROR] invalid input string: " +  token<< std::endl;
            info.act = ACTION::UNKNOWN;
            return info;
        }
    }

    return info;
}
