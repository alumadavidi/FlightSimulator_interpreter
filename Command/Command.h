//
// Created by magshimim on 12.12.2019.
//
#pragma once
#ifndef UNTITLED11_COMMAND_H
#define UNTITLED11_COMMAND_H

#include <vector>
#include <unordered_map>
#include <map>
#include <mutex>
#include <condition_variable>
#include <queue>
#include "../VariableAir.h"

using namespace std;

class command {

public:
   // static vector<string>* _copyInput; //copy of the vector
    static unordered_map<string, variableAir*>* _progTable; //program vars
    static unordered_map<string, variableAir>* _simTable; //flight sim vars
    static unordered_map<string, command*>* _commandsMap;
    static unordered_map<string, pair<string,vector<string>*>>* _funcsMap;
    static vector<string>::iterator it;
    static unordered_map<string, pair<float,variableAir*>>* _generalSimVariable;
    static queue<string> messageToSend;
    static std::mutex mutexGeneralSimVariable;
    //static std::mutex mutexMessage;
    //static bool updateFinish;
    static std::condition_variable cv;
    static std::string data;
    static bool serverFinish;
    static bool processed;

    virtual int execute() = 0;
    virtual ~command() {}
};
#endif //UNTITLED11_COMMAND_H
