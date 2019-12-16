#include "ProgramInclude.h"
vector<string>* command::_copyInput = 0;
unordered_map<string, variableAir>* command::_progTable = 0;
unordered_map<string, variableAir>* command::_simTable;
unordered_map<string, command*>* command::_commandsMap;
unordered_map<string, vector<string>*>* command::_funcsMap;


int main(int argc, char **argv) {
    Parser parser;
    vector<string> wordsToken = {"openDataServer", "5400", "connectControlClient","\"127.0.0.1\""};
    if(argc > 1){
        string fileName = argv[1];
        InitMap initalizeMap;
        initalizeMap.initCommandsMap();
        initalizeMap.initProgTable();
        initalizeMap.initSimTable();
        try {
            parser.parser(fileName);
        } catch (const char* e) {
            cout<<e<<endl;
        }
    } else {
        cout<<"error - no file"<<endl;
    }


    //vector<string> v = wordsToken;
    //command::_copyInput = &v;

    return 0;
}