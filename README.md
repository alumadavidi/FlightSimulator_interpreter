## FlightSimulator_interpreter
Interpreter flight simulator coding language, CPP.

### General Description:
In this task we were asked to deal with communication to FlightGear simulator (https://www.flightgear.org/) in order to activate it by code only. The program gets "fly.txt" file (given as an argument) that contain high language command to the simulator and interprets those command to code that get/sent data/instructions from/to the simulator. The program connect to the simulator both as client and as server.

### Features:
The program reads the file line by line and translate it into flight instructions. One of the command in the file is connect as server command that means the simulator connect as a client to program in order to get live data from it. (The program support getting 36 variables from the simulator). Another command is connect as client command that means to connect the program as a client to the simulator in order to sent flight instructions to the it by changes in the program made from interprets the script file (fly.txt). The program manage both connections in parallel by using threads. Arithmetic expressions, function definition, usage of functions and Nested loops and if statements are supported.

### Program structure:
The code can be divide to parts:

#### 1. Data section:
this section contain data that common to all the program, it's contain define of consts and static members that can be access from anywhere in the program, we choose that way to implement the sharing data because it's simple to read and understanding and allows quick and easy access to the required objects all over the program.

#### 2. Command section:
we created class to each command, all those classes are implement the class command that has an execute function that execute the command. all the simple commands are located in CommandsClasses file and the complex command that uses threads and server-client activity located in separated files (ClientCaommand, ServerCommand - will be clarified later). All command gets data from Data class that has static members that initialize at the beginning of the program.

#### 3. shunting yard algorithm:
we uses the code from the previous task to deal with complex mathematical expressions (we added the operators ==,>=,<=,!=,>,<).

#### 4. Lexer section:
The lexer read the file line by line by commands name and get values that required to execute it. the lexer keep mathematical expressions as they are (those are interpreted by shunting yard algorithm). in cases of loop, if statements or function definition it keeps brackets. It also removes Unnecessary spaces and tubs.

#### 5. Parser section:
The parser activate the appropriate execute function to each command. This class has static function that links between the shunting yard algorithem to the command in order to interprets complex arguments of the commands.

#### 6. server-client connection section:
We created two synced maps one get live data from simulator and the other get data from the script file. The program using the maps in order to sent updates to simulator and updated it's variables.

### Compile and Run
First download the simulator from the above address. Insert the file generic_small.xml (repository) to "[FlightGear installation path]/‫‪data/protocol". add both lines into the setting in FlightGear: --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small --telnet=socket,in,10,127.0.0.1,5402,tcp In order to compile the code use the following command: g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread Make sure you have a fly.txt script file (can be taken from repository). Run a.out with the relative path this file. Open the simulator after running the program. Enjoy :)

### Developers
This program developed by Efrat Luzzun and Aluma Davidi, CS students from Bar-Ilan university, Israel.
