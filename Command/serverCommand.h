//
// Created by magshimim on 17.12.2019.
//
#pragma once
#ifndef EX316_12_SERVERCOMMAND_H
#define EX316_12_SERVERCOMMAND_H

#include "Command.h"
#include <thread>
#include <mutex>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <arpa/inet.h>
#include "../Data.h"
#include "../Parser.h"
class OpenServerCommand : public command {

    int _port;
    bool done;
    int client_socket;
    int socketfd;
    static string oldBuf;
    thread serverThread;
public:
    virtual int execute();
    void openSocketServer();
    void startTherad();
    void serverRead();
    void updateVariables(char[]);
    OpenServerCommand()/*: serverThread() */{};
    ~OpenServerCommand();
};
#endif //EX316_12_SERVERCOMMAND_H
