# robot_challenge

This is an application that simulate a toy robot moving on a square table top, of dimensions 5 units x 5 units. There are no
other obstructions on the table surface. The robot is free to roam around the surface of the table, and is prevented
from falling to destruction.

## Prerequisite
- `CMake version 2.6 and later version`
- `C++14 and later version`

## How to Run the Application

1. Clone this repository, in the terminal
```bash
git clone https://github.com/jevinoh/robot_challenge.git
```


2. In the terminal, walk to the project root folder and then build the project using these commands
```bash
cmake .
make
```


3. Once the build is completed, a binary named `robot_challenge` should be created on the root folder. Execute this command to run the binary

For Linux or MacOS:
```bash
./robot_challenge
```

For Windows:
```bash
.\robot_challenge
```


## How to Run Unit and Integration test of the project
1. From the root directory, navigate to `test` folder
```bash
cd test
```


2. Build the test application using these commands
```bash
cmake .
make
```


3. Once the build is completed, a binary named `test_robot_challenge` should be created on the root folder. Note that to run an integration test,
a separate file that contains commands should be created and should be supplied as an argument to the test binary.
`test/testCommand.txt` is created for this purpose

Execute this command to run tests:

For Linux or MacOS:
```bash
./test_robot_challenge testCommand.txt
```

For Windows:
```bash
.\test_robot_challenge testCommand.txt
```

