//
// Interface command
//
#ifndef UNTITLED11_COMMAND_H
#define UNTITLED11_COMMAND_H

using namespace std;

class command {

public:
    //run the method of the simulator
    virtual int execute() = 0;
    virtual ~command() {}
};
#endif //UNTITLED11_COMMAND_H
