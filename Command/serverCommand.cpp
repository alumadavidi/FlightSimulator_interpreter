//
// Created by magshimim on 17.12.2019.
//

#include "serverCommand.h"
#include "../data.h"
string OpenServerCommand::oldBuf;
int OpenServerCommand::execute() {
    ++it;
    _port = stoi(*it);
    ++it;
    //bind the socket
    openSocketServer();
    //open thread in background that read from the client
    startTherad();
    return 2;
}
//open thread to read data from client in server
void OpenServerCommand::startTherad() {
    serverThread = thread(&OpenServerCommand::serverRead, this);
}
void OpenServerCommand::serverRead() {
    cout<<"enter to serverRead"<<endl;
    while(true){
        if(!serverFinish) {
            mutexGeneralSimVariable.lock();
            char buf[1024] = {0};
            int n = read(client_socket, buf, 1024);
            if (n == -1) {
                cerr << "error in read line from clinet" << endl;
            }
            updateVariables(buf);
            serverFinish = true;
            mutexGeneralSimVariable.unlock();
        }
    }
}

//read one line from the client
void OpenServerCommand::updateVariables(char buf[]) {
    //cout<<"enter update\n"<<endl;
    sleep(3);
    string bufString = buf;
    int startOfLine = 0;
    int endOfLine = bufString.find('\n');
    int j = bufString.find('\n',endOfLine);
    if (j < bufString.length()){
        startOfLine = endOfLine + 1;
        endOfLine = j - 1;
    }
    string word = "";
    string line = bufString.substr(startOfLine, endOfLine - startOfLine);
    cout<<line<<endl;
    //update sim map
    map<string, float>::iterator mapIt = _generalSimVariable->begin();
    for(char c: line) {
        if(c != ',') {
            word += c;
        } else {
            int val = stof(word);
            mapIt->second = val;
            mapIt++;
            word = "";
        }
    }

}

void OpenServerCommand::openSocketServer() {
    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        throw "Could not create a socket";
    }
    this->socketfd = socketfd;
    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(_port);
    //the actual bind command

    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        // throw "Could not bind the socket to an IP";
        throw "Could not bind the socket to an IP";
    }
    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        throw "Error during listening command";
    } else {
        std::cout<<"Server is now listening ..."<<std::endl;
    }
    // accepting a client
    int client_socket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t*)&address);
    if (client_socket == -1) {
        throw "Error accepting client";
    }

    this->client_socket = client_socket;
}
OpenServerCommand::~OpenServerCommand() {
    if(serverThread.joinable()){
        serverThread.join();
    }
    close(socketfd);

}