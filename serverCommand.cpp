//
// Created by magshimim on 17.12.2019.
//

#include "serverCommand.h"

int OpenServerCommand::execute() {
    ++Data::it;
    int numPort = Parser::generalShuntingAlgorithem(*Data::it);
    _port = (int)numPort;
    ++Data::it;
    //bind the socket
    openSocketServer();
    //open thread in background that read from the client
    startTherad();
    return 2;
}
//open thread to read Data from client in server
void OpenServerCommand::startTherad() {
    serverThread = thread(&OpenServerCommand::serverRead, this);
}
//Read from the simulator and update the variable
void OpenServerCommand::serverRead() {
    cout<<"enter to serverRead"<<endl;
    while(!Data::stopLoopServer){
        if(!Data::serverFinish) {
            Data::mutexGeneralSimVariable.lock();
            char buf[1024] = {0};
            int n = read(client_socket, buf, 1024);
            if (n == -1) {
                cerr << "error in read line from clinet" << endl;
            }
            updateVariables(buf);
            Data::serverFinish = true;
            Data::mutexGeneralSimVariable.unlock();
        }
    }
    close(socketfd);
    cout<<"endLoopServer"<<endl;
    Data::stopLoopServer = false;

}

//read one line from the client
void OpenServerCommand::updateVariables(char buf[]) {
    string bufString = buf;
    int startOfLine = 0;
    int endOfLine = bufString.find('\n');
    int j = bufString.find('\n',endOfLine + 1);
    if ((unsigned int) j < bufString.length()){
        startOfLine = endOfLine + 1;
        endOfLine = j;
    }
    string word = "";
    string line = bufString.substr(startOfLine, endOfLine - startOfLine + 1);
    int k = 0;
    unordered_map<string, pair<float,ProgVariables*>>::iterator iter;
    for(int i = 0; (unsigned int)i < line.length(); i++) {
        char c = line[i];
        if(c != ',' && c != '\n') {
            word += c;
        } else {
            switch (k) {
                case 0:
                    iter = Data::_generalSimVariable->find(V1);
                    break;
                case 1:
                    iter = Data::_generalSimVariable->find(V2);
                    break;
                case 2:
                    iter = Data::_generalSimVariable->find(V3);
                    break;
                case 3:
                    iter = Data::_generalSimVariable->find(V4);
                    break;
                case 4:
                    iter = Data::_generalSimVariable->find(V5);
                    break;
                case 5:
                    iter = Data::_generalSimVariable->find(V6);
                    break;
                case 6:
                    iter = Data::_generalSimVariable->find(V7);
                    break;
                case 7:
                    iter = Data::_generalSimVariable->find(V8);
                    break;
                case 8:
                    iter = Data::_generalSimVariable->find(V9);
                    break;
                case 9:
                    iter = Data::_generalSimVariable->find(V10);
                    break;
                case 10:
                    iter = Data::_generalSimVariable->find(V11);
                    break;
                case 11:
                    iter = Data::_generalSimVariable->find(V12);
                    break;
                case 12:
                    iter = Data::_generalSimVariable->find(V13);
                    break;
                case 13:
                    iter = Data::_generalSimVariable->find(V14);
                    break;
                case 14:
                    iter = Data::_generalSimVariable->find(V15);
                    break;
                case 15:
                    iter = Data::_generalSimVariable->find(V16);
                    break;
                case 16:
                    iter = Data::_generalSimVariable->find(V17);
                    break;
                case 17:
                    iter = Data::_generalSimVariable->find(V18);
                    break;
                case 18:
                    iter = Data::_generalSimVariable->find(V19);
                    break;
                case 19:
                    iter = Data::_generalSimVariable->find(V20);
                    break;
                case 20:
                    iter = Data::_generalSimVariable->find(V21);
                    break;
                case 21:
                    iter = Data::_generalSimVariable->find(V22);
                    break;
                case 22:
                    iter = Data::_generalSimVariable->find(V23);
                    break;
                case 23:
                    iter = Data::_generalSimVariable->find(V24);
                    break;
                case 24:
                    iter = Data::_generalSimVariable->find(V25);
                    break;
                case 25:
                    iter = Data::_generalSimVariable->find(V26);
                    break;
                case 26:
                    iter = Data::_generalSimVariable->find(V27);
                    break;
                case 27:
                    iter = Data::_generalSimVariable->find(V28);
                    break;
                case 28:
                    iter = Data::_generalSimVariable->find(V29);
                    break;
                case 29:
                    iter = Data::_generalSimVariable->find(V30);
                    break;
                case 30:
                    iter = Data::_generalSimVariable->find(V31);
                    break;
                case 31:
                    iter = Data::_generalSimVariable->find(V32);
                    break;
                case 32:
                    iter = Data::_generalSimVariable->find(V33);
                    break;
                case 33:
                    iter = Data::_generalSimVariable->find(V34);
                    break;
                case 34:
                    iter = Data::_generalSimVariable->find(V35);
                    break;
                case 35:
                    iter = Data::_generalSimVariable->find(V36);;
                    break;
                default:
                    break;
            }
            float val = stof(word);
            iter->second.first = val;
            if(iter->second.second != nullptr) {
                iter->second.second->setSimValue(val);
            }
            word = "";
            k++;
        }
    }
}
//Open socket for the server
void OpenServerCommand::openSocketServer() {
    //create socket
    int socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        throw "Could not create a socket";
    }
    this->socketfd = socketFd;
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
    int clientSocket = accept(socketfd, (struct sockaddr *)&address,
                               (socklen_t*)&address);
    if (clientSocket == -1) {
        throw "Error accepting client";
    }

    this->client_socket = clientSocket;
}
OpenServerCommand::~OpenServerCommand() {
    cout<<"enter to disServer"<<endl;
//    done = true;
    if(serverThread.joinable()){
        serverThread.join();
    }
    close(socketfd);
    cout<<"end disServer"<<endl;

}