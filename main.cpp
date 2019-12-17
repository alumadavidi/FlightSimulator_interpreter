#include "ProgramInclude.h"
//vector<string>* command::_copyInput = 0;
unordered_map<string, variableAir>* command::_progTable;
unordered_map<string, variableAir>* command::_simTable;
unordered_map<string, command*>* command::_commandsMap;
unordered_map<string, pair<string,vector<string>*>>* command::_funcsMap;
unordered_map<string,float>* command::_generalSimVariable;
vector<string>::iterator command::it;

int main(int argc, char **argv) {
    Parser parser;
    if(argc > 1){
        string fileName = argv[1];
        InitMap initalizeMap;
        initalizeMap.initalizeAllMaps();
        try {
            parser.parser(fileName);
        } catch (const char* e) {
            cout<<e<<endl;
        }
    } else {
        cout<<"error - no file"<<endl;
    }
    return 0;
}