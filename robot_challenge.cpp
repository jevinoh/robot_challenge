#include "InputParser.h"
#include "TableController.h"
#include "Robot.h"
#include "Utils.h"

int main(int argc, char **argv) {
    std::unique_ptr<InputParser> inputParser = std::make_unique<InputParser>();

    // 5x5 dimension, starts at coordinate 0,0
    std::unique_ptr<TableController> tableCtrl = std::make_unique<TableController>(4,4);
    for (std::string line; std::getline(std::cin, line);) {
        CommandInfo parsedInput = inputParser->Parse(line);
        tableCtrl->CheckCommandInfo(parsedInput);
    }
    return 0;
}
