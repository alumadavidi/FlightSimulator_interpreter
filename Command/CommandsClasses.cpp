//
// Created by magshimim on 12.12.2019.
//

#include "CommandsClasses.h"
#include <cstring>
#include "stdlib.h"

//#include "../VariableAir.h"
//#include "Command.h"
using namespace std;

int OpenServerCommand::execute(vector<string>::iterator it) {
   ++it;
    _port = stoi(*it);
    ++it;
    //bind the socket
    openSocketServer();
    //open thread in background that read from the client
    startTherad();
    //TODO open thread to accept more clients
    return 2;
}
//open thread to read data from client in server
void OpenServerCommand::startTherad() {
    serverThread = thread(&OpenServerCommand::serverRead, this);
}
void OpenServerCommand::serverRead() {
    cout<<"enter to serverRead\n"<<endl;
    while(true){
        char buffer[1024] = {0};
        cout<< client_socket << std::endl;
        int valread = read(client_socket, buffer, 1024);
        cout<< buffer << std::endl;

        //TODO check the valid of read
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
        return;
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
ConnectCommand::~ConnectCommand() {
    if(clientThread.joinable()){
        clientThread.join();
    }
    close(clientSocket);
}
void ConnectCommand::startTherad() {
    clientThread = thread(&ConnectCommand::writeClient, this);
}
int ConnectCommand::execute(vector<string>::iterator it) {
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
    while(true) {
        char x[256] = {'m', 'y', ' '};
        //cin.get(x, 256);
        int is_sent = send(clientSocket, x, strlen(x), 0);
        if (is_sent == -1) {
            std::cout << "Error sending message" << std::endl;
        } else {
            std::cout << "Hello message sent to server" << std::endl;
        }
    }

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

int DefineVarCommand::execute(vector<string>::iterator it) {
    int counterFunc;
    string sim = "", left = "";

    ++it;//for command
    string key = *it;
    ++it;
    string direction = *(it);
    if(direction.compare("=") == 0){ // var x = y
       ++it;
       left = *it;
       counterFunc = 4;
    } else { //var x -> sim("")
        it += 2;
        sim = *it;
        counterFunc = 5;
        ++it;
    }
    variableAir newVar = variableAir(sim, direction);
    _progTable->insert({key, newVar});  ///check the map
    if(left.size() > 0) { // first opetion var x = y
        Parser::updateValueInShuntingAlgo(left, key);
    }

    return counterFunc;
}
int LoopCommand::execute(vector<string>::iterator it) {
    Parser parser;
    init(it); //shared code to loop and if
    it += counter;
    _inCommands = getInsideCommend(it); // get the inside of the loop to new vector
    while(getCondition(_firstExp,_op,_secondExp)){
        vector<string> copyInCommands = _inCommands;//any time init the copy
        parser.parserByTokens(copyInCommands);
    }
    return counter;
}
int IfCommand::execute(vector<string>::iterator it) {
    Parser parser;
    init(it); //shared code to loop and if
    it += counter;
    _inCommands = getInsideCommend(it); // get the inside of the loop to new vector
    if(getCondition(_firstExp,_op,_secondExp)){
        vector<string> copyInCommands = _inCommands;//any time init the copy
        auto iter = copyInCommands.begin();
        while(iter != copyInCommands.end()) {
            parser.parserByTokens(copyInCommands);
        }
    }
}
int FuncCommand::execute(vector<string>::iterator it) { //for funcion
    string funcName = *it;
    ++it;
    vector<string> inCommand = getInsideCommend(it);
     // get the inside of the loop to new vector
    _funcsMap->insert({funcName, &inCommand});
}
int Print::execute(vector<string>::iterator it) {
    ++it;
    string toPrint = *it;
    if(toPrint[0] == '"'){ // string
        cout << toPrint << endl;
    } else { // print variable
        unordered_map<string, variableAir>::iterator iter;
        variableAir *var;
        if(iter != command::_progTable->find(toPrint)) {
            var = &(command::_progTable->find(toPrint)->second);
            cout << var->getValue() << endl;
        }
    }
    it++;
    return 2;
}
int Sleep::execute(vector<string>::iterator it) {
    ++it;
    string timeS = *(it);
    std::string::size_type sz;   // convert string to long
    long time = std::stol (timeS,&sz);
    //TODO sleep for x miliseconds
    ++it;
    return 2;
}
void ConditionParser::init(vector<string>::iterator it) {
    it++;
    _firstExp = *it;
    it++;
    _op = *it;
    it++;
    _secondExp = *it;
    it++;
    counter += 4;
}
//the function return the inside commands and erase them from the copy (assume validness)
vector<string> holdCommands::getInsideCommend(vector<string>::iterator& it) {
    vector<string> result;
    int leftCounter = 0;
    int rightCounter = 0;
    auto iter = it->begin();
    while(it->begin()!= it->end()) {
        if ((leftCounter == rightCounter) && leftCounter != 0) {
            break;
        } else if (*it == "{") {
            leftCounter++;
            if (leftCounter == 1) {
                it++;
                counter++;
                continue;
            }
        } else if (*it == "}") {
            rightCounter++;
        }
        result.push_back(*it); //add string to the new vector
        counter++;
        it++;
    }
    if(!result.empty())
        result.pop_back(); //for "}"
    return result;
}
bool ConditionParser::getCondition(string first, string op, string second) {
    bool result = false;
    if(op == ">") {
         result = Parser::generalShuntingAlgorithem(first) > Parser::generalShuntingAlgorithem(second);
    } else if (op == "<") {
        result = Parser::generalShuntingAlgorithem(first) < Parser::generalShuntingAlgorithem(second);
    } else if (op == "<=") {
        result = Parser::generalShuntingAlgorithem(first) <= Parser::generalShuntingAlgorithem(second);
    } else if (op == ">=") {
        result = Parser::generalShuntingAlgorithem(first) >= Parser::generalShuntingAlgorithem(second);
    } else if (op == "==") {
        result = Parser::generalShuntingAlgorithem(first) == Parser::generalShuntingAlgorithem(second);
    } else if (op == "!=") {
        result = Parser::generalShuntingAlgorithem(first) != Parser::generalShuntingAlgorithem(second);
    }
    return result;
}
int activateFunc::execute(vector<string>::iterator it) {
    vector<string>* inCommands =command::_funcsMap->find(*it)->second;
    it++;
    int var = stod(*it);
    Parser parser;
    parser.parserByTokens(*inCommands);
}
