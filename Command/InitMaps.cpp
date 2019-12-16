//
// Created by magshimim on 13.12.2019.
//

#include "InitMaps.h"
//initalize the map with the command object
void InitMap::initCommandsMap() {
    command::_commandsMap = new unordered_map<string, command*>();

    command::_commandsMap->insert({"openDataServer",new OpenServerCommand()});
    command::_commandsMap->insert({"connectControlClient",new ConnectCommand()});
    command::_commandsMap->insert({"var",new DefineVarCommand()});
    command::_commandsMap->insert({"if",new IfCommand()});
    command::_commandsMap->insert({"while",new LoopCommand()});
    command::_commandsMap->insert({"Print",new Print()});
    command::_commandsMap->insert({"Sleep",new Sleep()});

    //TODO FUNC??
}
void InitMap::initProgTable() {
    command::_progTable = new unordered_map<string, variableAir>();
}
void InitMap::initSimTable() {
    command::_simTable = new unordered_map<string, variableAir>();
}
void InitMap::initfuncTable() {
    command::_funcsMap = new unordered_map<string, vector<string>*>();
}
