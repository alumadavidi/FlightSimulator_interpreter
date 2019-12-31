//
// DataBase of program
//

#include "Data.h"
bool Data::stopLoopServer = false;
bool Data::stopLoopClient = false;
bool Data::serverFinish = false;
unordered_map<string, ProgVariables*>* Data::_progTable;
unordered_map<string, command*>* Data::_commandsMap;
unordered_map<string, pair<string,vector<string>*>>* Data::_funcsMap;
unordered_map<string, pair<float,ProgVariables*>>* Data::_generalSimVariable;
vector<string>::iterator Data::it;
queue<string> Data::messageToSend;
std::mutex Data::mutexGeneralSimVariable;
