//
// Created by magshimim on 12.12.2019.
//
#pragma once
#ifndef UNTITLED11_COMMAND_H
#define UNTITLED11_COMMAND_H

#include <vector>
#include <unordered_map>
#include "../VariableAir.h"

using namespace std;

class command {
/*protected:
    int counter = 0;*/
public:
    static int counter;
    static vector<string>* _copyInput; //copy of the vector
    static unordered_map<string, variableAir>* _progTable; //program vars
    static unordered_map<string, variableAir>* _simTable; //flight sim vars
    static unordered_map<string, command*>* _commandsMap;

    virtual int execute(vector<string>::iterator) = 0;
    virtual ~command() {}
};
#endif //UNTITLED11_COMMAND_H
