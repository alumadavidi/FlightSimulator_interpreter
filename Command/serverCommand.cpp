//
// Created by magshimim on 17.12.2019.
//

#include "serverCommand.h"
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
    cout<<"enter to serverRead\n"<<endl;
    string line;
    while(true){
        readLineFromClient(line);
        spliteMessageAndConvertToFloatValur(line);
//        cout<< line << std::endl;
    }
}
//read one line from the client
void OpenServerCommand::readLineFromClient(string& line) {
    string bufString;
    char buf[1024];
    int n = 0;
    while(n = read(client_socket, buf, 1024))
    {
        if(n == -1){
            cerr<<"error in read line from clinet"<<endl;
        }
        bufString = string() + buf;
        if (bufString.find("\n")){
            line += buf;
            break;
        }
        line += buf;
    }
}
void OpenServerCommand::spliteMessageAndConvertToFloatValur(string& line) {
    std::mutex mtx;
    mtx.lock();
    float varSim[24] = {0};
    string word = "";
    char* pend;
    int j = 0;
    for(int i = 0; i < line.length() && j <24; i++){
        if(line[i] == ',' || line[i] == '\n') {
            varSim[j] = std::stof(word.c_str());
            j++;
            word = "";

        } else{
            word+=line[i];
        }
    }
//    cout<<"end loop to insert to varsim" << endl;
    mtx.unlock();
    insertValueToGeneralSimVariable(varSim);

}
void OpenServerCommand::insertValueToGeneralSimVariable(const float* arrayFloat) {
    std::mutex mtx;
    unordered_map<string, float*>::iterator iter;
    mtx.lock();
    for(int index = 0; index < 24; index++) {
        switch (index) {
            case 0:
                iter = command::_generalSimVariable->find("/instrumentation/airspeed-indicator/indicated-speed-kt/airspeed-indicator_indicated-speed-kt");
                break;
            case 1:
                iter = command::_generalSimVariable->find("//instrumentation/heading-indicator/offset-deg/heading-indicator_offset-deg");
                break;
            case 2:
                iter = command::_generalSimVariable->find("/instrumentation/altimeter/indicated-altitude-ft/altimeter_indicated-altitude-ft");
                break;
            case 3:
                iter = command::_generalSimVariable->find("/instrumentation/altimeter/pressure-alt-ft/altimeter_pressure-alt-ft");
                break;
            case 4:
                iter = command::_generalSimVariable->find("/instrumentation/attitude-indicator/indicated-pitch-deg/attitude-indicator_indicated-pitch-deg");
                break;
            case 5:
                iter = command::_generalSimVariable->find("/instrumentation/attitude-indicator/indicated-roll-deg/attitude-indicator_indicated-roll-deg");
                break;
            case 6:
                iter = command::_generalSimVariable->find("/instrumentation/attitude-indicator/internal-pitch-deg/attitude-indicator_internal-pitch-deg");
                break;
            case 7:
                iter = command::_generalSimVariable->find("/instrumentation/attitude-indicator/internal-roll-deg/attitude-indicator_internal-roll-deg");
                break;
            case 8:
                iter = command::_generalSimVariable->find("/instrumentation/encoder/indicated-altitude-ft/encoder_indicated-altitude-ft");
                break;
            case 9:
                iter = command::_generalSimVariable->find("/instrumentation/encoder/pressure-alt-ft/encoder_pressure-alt-ft");
                break;
            case 10:
                iter = command::_generalSimVariable->find("/instrumentation/gps/indicated-altitude-ft/gps_indicated-altitude-ft");
                break;
            case 11:
                iter = command::_generalSimVariable->find("/instrumentation/gps/indicated-ground-speed-kt/gps_indicated-ground-speed-kt");
                break;
            case 12:
                iter = command::_generalSimVariable->find("/instrumentation/gps/indicated-vertical-speed/gps_indicated-vertical-speed");
                break;
            case 13:
                iter = command::_generalSimVariable->find("/instrumentation/heading-indicator/indicated-heading-deg/indicated-heading-deg");
                break;
            case 14:
                iter = command::_generalSimVariable->find("/instrumentation/magnetic-compass/indicated-heading-deg/magnetic-compass_indicated-heading-deg");
                break;
            case 15:
                iter = command::_generalSimVariable->find("/instrumentation/slip-skid-ball/indicated-slip-skid/slip-skid-ball_indicated-slip-skid");
                break;
            case 16:
                iter = command::_generalSimVariable->find("/instrumentation/turn-indicator/indicated-turn-rate/turn-indicator_indicated-turn-rate");
                break;
            case 17:
                iter = command::_generalSimVariable->find("/instrumentation/vertical-speed-indicator/indicated-speed-fpm/vertical-speed-indicator_indicated-speed-fpm");
                break;
            case 18:
                iter = command::_generalSimVariable->find("/controls/flight/aileron/flight_aileron");
                break;
            case 19:
                iter = command::_generalSimVariable->find("/controls/flight/elevator/flight_elevator");
                break;
            case 20:
                iter = command::_generalSimVariable->find("/controls/flight/rudder/flight_rudder");
                break;
            case 21:
                iter = command::_generalSimVariable->find("/controls/flight/flaps/flight_flaps");
                break;
            case 22:
                iter = command::_generalSimVariable->find("/controls/engines/engine/throttle/engine_throttle");
                break;
            case 23:
                iter = command::_generalSimVariable->find("/engines/engine/engine_rpm");
                break;
            default:
                break;
        }
        if(iter->second != nullptr) {
            *(iter->second) = arrayFloat[index];
        }
    }
    mtx.unlock();
//    cout<<"update variable from sim"<<endl;
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