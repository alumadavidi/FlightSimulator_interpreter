//
// Created by magshimim on 17.12.2019.
//

#include "serverCommand.h"


thread OpenServerCommand::serverThread;
string OpenServerCommand::oldBuf;
int OpenServerCommand::execute() {
    ++it;
    int numPort = Parser::generalShuntingAlgorithem(*it);
    _port = (int)numPort;
    ++it;
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
void OpenServerCommand::serverRead() {
    cout<<"enter to serverRead"<<endl;
    while(!Data::stopLoopServer){
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
    close(socketfd);
    cout<<"endLoopServer"<<endl;
    Data::stopLoopServer = false;

}

//read one line from the client
void OpenServerCommand::updateVariables(char buf[]) {
    //cout<<"enter update\n"<<endl;
    string bufString = buf;
    int startOfLine = 0;
    int endOfLine = bufString.find('\n');
    int j = bufString.find('\n',endOfLine + 1);
    if (j < bufString.length()){
        startOfLine = endOfLine + 1;
        endOfLine = j;
    }
    string word = "";
    string line = bufString.substr(startOfLine, endOfLine - startOfLine + 1);
//    cout<<line<<endl;
    int k = 0;
    //update sim map
    //map<string, float>::iterator mapIt = _generalSimVariable->begin();
    unordered_map<string, pair<float,variableAir*>>::iterator iter;
    for(int i = 0; i < line.length(); i++) {
        char c = line[i];
        if(c != ',' && c != '\n') {
            word += c;
        } else {
            switch (k) {
                case 0:
                    iter = command::_generalSimVariable->find("/instrumentation/airspeed-indicator/indicated-speed-kt");
                    break;
                case 1:
                    iter = command::_generalSimVariable->find("/sim/time/warp");
                    break;
                case 2:
                    iter = command::_generalSimVariable->find("/controls/switches/magnetos");
                    break;
                case 3:
                    iter = command::_generalSimVariable->find("/instrumentation/heading-indicator/offset-deg");
                    break;
                case 4:
                    iter = command::_generalSimVariable->find("/instrumentation/altimeter/indicated-altitude-ft");
                    break;
                case 5:
                    iter = command::_generalSimVariable->find("/instrumentation/altimeter/pressure-alt-ft");
                    break;
                case 6:
                    iter = command::_generalSimVariable->find("/instrumentation/attitude-indicator/indicated-pitch-deg");
                    break;
                case 7:
                    iter = command::_generalSimVariable->find("/instrumentation/attitude-indicator/indicated-roll-deg");
                    break;
                case 8:
                    iter = command::_generalSimVariable->find("/instrumentation/attitude-indicator/internal-pitch-deg");
                    break;
                case 9:
                    iter = command::_generalSimVariable->find("/instrumentation/attitude-indicator/internal-roll-deg");
                    break;
                case 10:
                    iter = command::_generalSimVariable->find("/instrumentation/encoder/indicated-altitude-ft");
                    break;
                case 11:
                    iter = command::_generalSimVariable->find("/instrumentation/encoder/pressure-alt-ft");
                    break;
                case 12:
                    iter = command::_generalSimVariable->find("/instrumentation/gps/indicated-altitude-ft");
                    break;
                case 13:
                    iter = command::_generalSimVariable->find("/instrumentation/gps/indicated-ground-speed-kt");
                    break;
                case 14:
                    iter = command::_generalSimVariable->find("/instrumentation/gps/indicated-vertical-speed");
                    break;
                case 15:
                    iter = command::_generalSimVariable->find("/instrumentation/heading-indicator/indicated-heading-deg");
                    break;
                case 16:
                    iter = command::_generalSimVariable->find("/instrumentation/magnetic-compass/indicated-heading-deg");
                    break;
                case 17:
                    iter = command::_generalSimVariable->find("/instrumentation/slip-skid-ball/indicated-slip-skid");
                    break;
                case 18:
                    iter = command::_generalSimVariable->find("/instrumentation/turn-indicator/indicated-turn-rate");
                    break;
                case 19:
                    iter = command::_generalSimVariable->find("/instrumentation/vertical-speed-indicator/indicated-speed-fpm");
                    break;
                case 20:
                    iter = command::_generalSimVariable->find("/controls/flight/aileron");
                    break;
                case 21:
                    iter = command::_generalSimVariable->find("/controls/flight/elevator");
                    break;
                case 22:
                    iter = command::_generalSimVariable->find("/controls/flight/rudder");
                    break;
                case 23:
                    iter = command::_generalSimVariable->find("/controls/flight/flaps");
                    break;
                case 24:
                    iter = command::_generalSimVariable->find("/controls/engines/engine/throttle");
                    break;
                case 25:
                    iter = command::_generalSimVariable->find("/controls/engines/current-engine/throttle");
                    break;
                case 26:
                    iter = command::_generalSimVariable->find("/controls/switches/master-avionics");
                    break;
                case 27:
                    iter = command::_generalSimVariable->find("/controls/switches/starter");
                    break;
                case 28:
                    iter = command::_generalSimVariable->find("/engines/active-engine/auto-start");
                    break;
                case 29:
                    iter = command::_generalSimVariable->find("/controls/flight/speedbrake");
                    break;
                case 30:
                    iter = command::_generalSimVariable->find("/sim/model/c172p/brake-parking");
                    break;
                case 31:
                    iter = command::_generalSimVariable->find("/controls/engines/engine/primer");
                    break;
                case 32:
                    iter = command::_generalSimVariable->find("/controls/engines/current-engine/mixture");
                    break;
                case 33:
                    iter = command::_generalSimVariable->find("/controls/switches/master-bat");
                    break;
                case 34:
                    iter = command::_generalSimVariable->find("/controls/switches/master-alt");
//                    cout<<word<<"rmp!!"<<endl;
                    break;
                case 35:
                    iter = command::_generalSimVariable->find("/engines/engine/rpm");
//                    cout<<word<<"rmp!!"<<endl;
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
    cout<<"enter to disServer"<<endl;
//    done = true;
//    if(serverThread.joinable()){
//        serverThread.join();
//    }
//    close(socketfd);
    cout<<"end disServer"<<endl;

}