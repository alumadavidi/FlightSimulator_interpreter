//
// Created by magshimim on 12.12.2019.
//
#pragma once
#ifndef UNTITLED11_COMMANDSCLASSES_H
#define UNTITLED11_COMMANDSCLASSES_H
#include <vector>
#include <iostream>
#include "Command.h"
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <thread>
#include <string>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include "../Parser.h"
class holdCommands : public command { //should to be abstract?
protected:
    vector<string> _inCommands;
    vector<string> getInsideCommend(vector<string>::iterator it);
};
class OpenServerCommand : public command {
    thread serverThread;
    int _port;
    int client_socket;
    int socketfd;
public:
    virtual int execute(vector<string>::iterator);
    void openSocketServer();
    void startTherad();
    void serverRead();
    OpenServerCommand(): serverThread() {};
    ~OpenServerCommand();
};


class ConnectCommand : public command {
    thread clientThread;
    int _port;
    const char *_ip;
    int clientSocket;
public:
    virtual int execute(vector<string>::iterator);
    void openSocketClient();
    void writeClient();
    void startTherad();
    ConnectCommand(): clientThread(){};
    ~ConnectCommand();

};

class DefineVarCommand : public command {
public:
    virtual int execute(vector<string>::iterator);
};

class ConditionParser : public holdCommands {
protected:
    string _firstExp;
    string _op;
    string _secondExp;
    void init(vector<string>::iterator);
    bool getCondition(string first, string op, string second);
/*public:
    virtual int execute();*/
};

class IfCommand : public ConditionParser {
public:
    virtual int execute(vector<string>::iterator);
};

class LoopCommand : public ConditionParser {
public:
    virtual int execute(vector<string>::iterator);
};

class FuncCommand : public holdCommands {
    vector<string> params;
public:
    virtual int execute(vector<string>::iterator);
};

class Print : public command {
public:
    virtual int execute(vector<string>::iterator);
};

class Sleep : public command {
public:
    virtual int execute(vector<string>::iterator);
};
#endif //UNTITLED11_COMMANDSCLASSES_H
