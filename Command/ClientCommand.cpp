//
// Created by magshimim on 17.12.2019.
//

#include "ClientCommand.h"
queue<string> ConnectCommand::messageToSend;
ConnectCommand::~ConnectCommand() {
    if(clientThread.joinable()){
        clientThread.join();
    }
    close(clientSocket);
}

void ConnectCommand::startTherad() {
    clientThread = thread(&ConnectCommand::writeClient, this);
}
int ConnectCommand::execute() {
    cout<<"enter to connect client"<<endl;
    ++it;
    _ip = (*it).c_str();
    ++it;
    _port = stoi(*it);
    ++it;
    //bind socket client
    openSocketClient();
    //send to server
    startTherad();
    return 3;
}
void ConnectCommand::writeClient() {
    std::mutex mutex;
    string thisMessage;
    while(true) {

        // Wait until main() sends data
//        std::unique_lock<std::mutex> lk(command::m);
//        cout<<"beforewait"<<endl;
//        command::cv.wait(lk, []{return command::ready;});

        // after the wait, we own the lock.
//        std::cout << "Worker thread is processing data\n";
        mutex.lock();
        if(!messageToSend.empty()) {
            thisMessage = messageToSend.front();
            messageToSend.pop();
            int is_sent = send(clientSocket, thisMessage.c_str(), thisMessage.length(), 0);
            if (is_sent == -1) {
                std::cout << "Error sending message" << std::endl;
            } else {
                std::cout << "send: " << thisMessage << std::endl;
            }
        }
        mutex.unlock();
//        lk.unlock();
//        // Send data back to main()
//        command::processed = true;
//        std::cout << "Worker thread signals data processing completed\n";

        // Manual unlocking is done before notifying, to avoid waking up
        // the waiting thread only to block again (see notify_one for details)

//        command::cv.notify_one();
//        command::processed = false;
    }

}
void ConnectCommand::setMessageToSend(string& message) {
    std::mutex mutex;
    mutex.lock();
    messageToSend.push(message);
    mutex.unlock();
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
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  //the localhost address
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