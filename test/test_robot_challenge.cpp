#include "InputParser.h"
#include "TableController.h"
#include "Robot.h"
#include "Utils.h"

#include <iostream>
#include <fstream>

int m_num_test  = 0;
int m_num_error = 0;

void evaluateRobotCoordinateAndDirection(int xResult, int yResult, FACE_DIRECTION dirResult, int xExpected, int yExpected, FACE_DIRECTION dirExpected, const std::string &description, int &num_test, int &num_error)
{
    num_test++;
    if((xResult != xExpected) || (yResult != yExpected) || (dirResult != dirExpected))
    {
        printf("[TEST-ERROR] Test #%d '%s' doesn't match the expected result\n", num_test, description.c_str());
        printf("                actual value: x[%d] y[%d] direction[%s]\n", xResult, yResult, directionsToString.at(dirResult).c_str());
        printf("              expected value: x[%d] y[%d] direction[%s]\n", xExpected, yExpected, directionsToString.at(dirExpected).c_str());
        num_error++;
    }
    else
    {
        printf("[TEST-OK] Test #%d '%s' passed\n", num_test, description.c_str());
    }
}


void evaluateParseInfo(const CommandInfo resultInfo, const CommandInfo expectedInfo, const std::string &description, int &num_test, int &num_error)
{
    num_test++;
    if(resultInfo != expectedInfo)
    {
        printf("[TEST-ERROR] Test #%d '%s' doesn't match the expected result\n", num_test, description.c_str());
        printf("                actual value: command[%s] x[%d] y[%d] direction[%s]\n", actionsToString.at(resultInfo.act).c_str(), resultInfo.x, resultInfo.y, directionsToString.at(resultInfo.dir).c_str());
        printf("              expected value: command[%s] x[%d] y[%d] direction[%s]\n", actionsToString.at(expectedInfo.act).c_str(), expectedInfo.x, expectedInfo.y, directionsToString.at(expectedInfo.dir).c_str());
        num_error++;
    }
    else
    {
        printf("[TEST-OK] Test #%d '%s' passed\n", num_test, description.c_str());
    }
}

void test_robot(int &num_test, int &num_error)
{
    printf("[TEST-INFO] ============== Testing Robot ==============\n");

    std::unique_ptr<Robot> testRobot = std::make_unique<Robot>(1,1, FACE_DIRECTION::NORTH);

    testRobot->Move();
    evaluateRobotCoordinateAndDirection(testRobot->GetCoordinateX(), testRobot->GetCoordinateY(), testRobot->GetFacingDirection(), 1 , 2 , FACE_DIRECTION::NORTH, "Moving Up", m_num_test, m_num_error);

    testRobot->SetFacingDirection(FACE_DIRECTION::EAST);
    testRobot->Move();
    evaluateRobotCoordinateAndDirection(testRobot->GetCoordinateX(), testRobot->GetCoordinateY(), testRobot->GetFacingDirection(), 2 , 2, FACE_DIRECTION::EAST, "Moving Right", m_num_test, m_num_error);

    testRobot->SetFacingDirection(FACE_DIRECTION::SOUTH);
    testRobot->Move();
    evaluateRobotCoordinateAndDirection(testRobot->GetCoordinateX(), testRobot->GetCoordinateY(), testRobot->GetFacingDirection(), 2 , 1, FACE_DIRECTION::SOUTH, "Moving Down", m_num_test, m_num_error);

    testRobot->SetFacingDirection(FACE_DIRECTION::WEST);
    testRobot->Move();
    evaluateRobotCoordinateAndDirection(testRobot->GetCoordinateX(), testRobot->GetCoordinateY(), testRobot->GetFacingDirection(), 1 , 1, FACE_DIRECTION::WEST, "Moving Left", m_num_test, m_num_error);
}


void test_input_parser(std::unique_ptr<InputParser> &inputParser, int &num_test, int &num_error)
{
    printf("[TEST-INFO] ============== Testing InputParser ==============\n");
    evaluateParseInfo(inputParser->Parse("PLACE 1,3, NORTH"), {ACTION::PLACE, 1, 3, FACE_DIRECTION::NORTH}, "Proper PLACE command", m_num_test, m_num_error);
    evaluateParseInfo(inputParser->Parse("PLACE 13, NORTH"), {ACTION::UNKNOWN, 0, 0, FACE_DIRECTION::NORTH}, "Improper coordinate parameter of PLACE command", m_num_test, m_num_error);
    evaluateParseInfo(inputParser->Parse("PLACE 1,2 NORTH1232"), {ACTION::UNKNOWN, 0, 0, FACE_DIRECTION::NORTH}, "Invalid direction parameter of PLACE command", m_num_test, m_num_error);
    evaluateParseInfo(inputParser->Parse("MOVE"), {ACTION::MOVE, 0, 0, FACE_DIRECTION::NORTH}, "Proper MOVE command", m_num_test, m_num_error);
    evaluateParseInfo(inputParser->Parse("LEFT"), {ACTION::LEFT, 0, 0, FACE_DIRECTION::NORTH}, "Proper LEFT command", m_num_test, m_num_error);
    evaluateParseInfo(inputParser->Parse("RIGHT"), {ACTION::RIGHT, 0, 0, FACE_DIRECTION::NORTH}, "Proper RIGHT command", m_num_test, m_num_error);
    evaluateParseInfo(inputParser->Parse("REPORT"), {ACTION::REPORT, 0, 0, FACE_DIRECTION::NORTH}, "Proper REPORT command", m_num_test, m_num_error);
    evaluateParseInfo(inputParser->Parse("MOVE 1,2, NORTH"), {ACTION::UNKNOWN, 0, 0, FACE_DIRECTION::NORTH}, "Invalid MOVE command, too many parameter", m_num_test, m_num_error);
    evaluateParseInfo(inputParser->Parse("REPORT123123123"), {ACTION::UNKNOWN, 0, 0, FACE_DIRECTION::NORTH}, "Invalid REPORT command, extra characters detected", m_num_test, m_num_error);
}

int main(int argc, char **argv) {

    std::unique_ptr<InputParser> inputParser = std::make_unique<InputParser>();

    printf("[TEST-INFO] ============== UNIT TEST STARTS ==============\n");
    test_input_parser(inputParser, m_num_test, m_num_error);
    test_robot(m_num_test, m_num_error);

    printf("[TEST-INFO] ============== INTEGRATION TEST STARTS ==============\n");
    if(argc == 2)
    {
        std::ifstream testFile;
        testFile.open(argv[1]);
        std::string line;
        if (testFile.is_open())
        {
            // 5x5 dimension, starts at coordinate 0,0
            std::unique_ptr<TableController> tableCtrl = std::make_unique<TableController>(4,4);
            while (testFile)
            {
                std::getline (testFile, line);
                CommandInfo parsedInput = inputParser->Parse(line);
                tableCtrl->CheckCommandInfo(parsedInput);
            }

            if(tableCtrl->IsRobotInitialized())
            {
                CoordinateAndDirection info = tableCtrl->getRobotCoordinateAndDirection();
                evaluateRobotCoordinateAndDirection(info.x, info.y, info.dir, 4 , 0 , FACE_DIRECTION::SOUTH, "Integration test", m_num_test, m_num_error);
            }
            else
            {
                printf("[TEST-ERROR] Integration test fails. Robot not yet initialized\n");
                m_num_test++;
                m_num_error++;
            }
        }
        else {
            printf("[TEST-ERROR] Won't run integration test. Unable to open attached file: %s\n", argv[1]);
        }
    }
    else
    {
        printf("[TEST-ERROR] Won't run integration test. No test file attached\n");
    }


    printf("[TEST-RESULT] Detected %d error(s) out of %d test(s)\n", m_num_error, m_num_test);
    return 0;
}
