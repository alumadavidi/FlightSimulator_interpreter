
#include "ProgramInclude.h"
//vector<string>* command::_copyInput = 0;
unordered_map<string, variableAir>* command::_progTable;
unordered_map<string, variableAir>* command::_simTable;
unordered_map<string, command*>* command::_commandsMap;
unordered_map<string, pair<string,vector<string>*>>* command::_funcsMap;
map<string, float>* command::_generalSimVariable;
vector<string>::iterator command::it;
queue<string> command::messageToSend;
std::mutex command::mutexGeneralSimVariable;
bool command::serverFinish = false;
//std::mutexGeneralSimVariable command::m;
std::condition_variable command::cv;
//std::string command::data;
//bool command::processed = false;
int main(int argc, char **argv) {
    Parser parser;
    if(argc > 1){

        string fileName = argv[1];
        InitMap initalizeMap;
        initalizeMap.initalizeAllMaps();
        try {
            map<string, float>::iterator iter;
            iter = command::_generalSimVariable->find("/engines/engine/rpm");


            parser.parser(fileName);
        } catch (const char* e) {
            cout<<e<<endl;
        }
    } else {
        cout<<"error - no file"<<endl;
    }
    return 0;
}