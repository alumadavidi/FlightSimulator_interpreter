#include "ProgramInclude.h"
unordered_map<string, variableAir*>* command::_progTable;
unordered_map<string, variableAir>* command::_simTable;
unordered_map<string, command*>* command::_commandsMap;
unordered_map<string, pair<string,vector<string>*>>* command::_funcsMap;
unordered_map<string, pair<float,variableAir*>>* command::_generalSimVariable;
vector<string>::iterator command::it;
queue<string> command::messageToSend;
std::mutex command::mutexGeneralSimVariable;
bool command::serverFinish = false;
int main(int argc, char **argv) {
    Parser parser;
    if(argc > 1){
        InitMap initalizeMap;
        try {
            string fileName = argv[1];
            initalizeMap.initalizeAllMaps();
            //unordered_map<string, float>::iterator iter;
            //iter = command::_generalSimVariable->find("/engines/engine/rpm");
            parser.parser(fileName);
            initalizeMap.eraseMap();
        } catch (const char* e) {
            cout<<e<<endl;
        }
    } else {
        cout<<"error - no file"<<endl;
    }

    cout<<"end"<<endl;

    return 0;
}