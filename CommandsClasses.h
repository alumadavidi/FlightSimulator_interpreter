//
// Created by magshimim on 12.12.2019.
//
#pragma once
#ifndef UNTITLED11_COMMANDSCLASSES_H
#define UNTITLED11_COMMANDSCLASSES_H
#include <vector>
#include <iostream>
#include "Command.h"
#include <arpa/inet.h>
#include <thread>
#include <string>
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include "Parser.h"
#include "Data.h"
class holdCommands : public command { //should to be abstract?
protected:
    int counter;
    vector<string> _inCommands;
    vector<string> getInsideCommend();
};

class DefineVarCommand : public command {
public:
    virtual int execute();
    virtual ~DefineVarCommand(){}
};

class ConditionParser : public holdCommands {
protected:
    string _firstExp;
    string _op;
    string _secondExp;
    void init();
    bool getCondition(string first, string op, string second);

};

class IfCommand : public ConditionParser {
public:
    virtual int execute();
};

class LoopCommand : public ConditionParser {
public:
    virtual int execute();
    virtual ~LoopCommand(){}
};

class FuncCommand : public holdCommands {
protected:
    string _localVar;
    vector<string> params;
public:
    virtual int execute();
    void activateFunc(string);
    virtual ~FuncCommand(){}
};

class Print : public command {
public:
    virtual int execute();
    virtual ~Print(){}
};

class Sleep : public command {
public:
    virtual int execute();
    virtual ~Sleep(){}
};
#endif //UNTITLED11_COMMANDSCLASSES_H
