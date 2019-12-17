//
// Created by magshimim on 17.12.2019.
//
#pragma once
#ifndef EX316_12_CLIENTCOMMAND_H
#define EX316_12_CLIENTCOMMAND_H
#include <iostream>
#include "Command.h"
#include <arpa/inet.h>
#include <thread>
#include <sys/socket.h>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
using namespace std;
class ConnectCommand : public command {
    thread clientThread;
    int _port;
    const char *_ip;
    int clientSocket;
public:
    virtual int execute();
    void openSocketClient();
    void writeClient();
    void startTherad();
    ConnectCommand(): clientThread(){};
    ~ConnectCommand();

};
#endif //EX316_12_CLIENTCOMMAND_H