#include "Parser.h"

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