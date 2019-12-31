//
// Created by magshimim on 17.12.2019.
//

#include "ClientCommand.h"

ConnectCommand::~ConnectCommand() {
    close(clientSocket);
    clientThread.join();
}
void ConnectCommand::startTherad() {
    clientThread = thread(&ConnectCommand::writeClient, this);
}
int ConnectCommand::execute() {
    cout<<"enter to connect client\n"<<endl;
    ++Data::it;
    _ip = (*Data::it).c_str();
    ++Data::it;
    try {
        int numPort = Parser::generalShuntingAlgorithem(*Data::it);
        _port = ((int)numPort);
        ++Data::it;
        //bind socket client
        openSocketClient();
        //send to server
        startTherad();
        return 3;
    } catch (const char* e){
        throw "failed in parser algo in ConnectCommand::execute";
    }

}
void ConnectCommand::writeClient() {
    string thisMessage;
    while(!Data::stopLoopClient) {
        if(Data::serverFinish) {
            Data::mutexGeneralSimVariable.lock();
            while (!Data::messageToSend.empty()) {
                thisMessage = Data::messageToSend.front();
                Data::messageToSend.pop();
                int is_sent = send(clientSocket, thisMessage.c_str(), thisMessage.length(), 0);
                if (is_sent == -1) {
                    std::cout << "Error sending message" << std::endl;
                } else {
                    std::cout << "send: " << thisMessage << std::endl;
                }
            }
            Data::serverFinish = false;
            Data::mutexGeneralSimVariable.unlock();
        }
    }
    Data::stopLoopClient = false;

}
void ConnectCommand::setMessageToSend(string message) {
    Data::messageToSend.push(message);
}
void ConnectCommand::openSocketClient() {
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        throw "Could not create a socket";
    }
    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4
    address.sin_addr.s_addr = inet_addr(_ip);  //the localhost address
    address.sin_port = htons(_port);
    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *)&address, sizeof(address));
    if (is_connect == -1) {
        throw "Could not connect to host server";
    } else {
        std::cout<<"Client is now connected to server" <<std::endl;
    }
    this->clientSocket = client_socket;
}

