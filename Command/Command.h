//
// Created by magshimim on 12.12.2019.
//
#ifndef UNTITLED11_COMMAND_H
#define UNTITLED11_COMMAND_H

using namespace std;

class command {

public:
    virtual int execute() = 0;
    virtual ~command() {}
};
#endif //UNTITLED11_COMMAND_H
