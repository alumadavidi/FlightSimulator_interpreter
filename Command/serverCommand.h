//
// Created by magshimim on 17.12.2019.
//
#pragma once
#ifndef EX316_12_SERVERCOMMAND_H
#define EX316_12_SERVERCOMMAND_H

#include "Command.h"
#include <thread>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <arpa/inet.h>
class OpenServerCommand : public command {
    thread serverThread;
    int _port;
    int client_socket;
    int socketfd;
public:
    virtual int execute();
    void openSocketServer();
    void startTherad();
    void serverRead();
    void readLineFromClient(string &);
    OpenServerCommand(): serverThread() {};
    ~OpenServerCommand();
};
#endif //EX316_12_SERVERCOMMAND_H
