//
// Created by magshimim on 13.12.2019.
//

#include "InitMaps.h"
#include "serverCommand.h"
#include "ClientCommand.h"

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
    command::_funcsMap = new unordered_map<string, pair<string,vector<string>*>>();
}
void InitMap::initGeneralSimVariable() {
    command::_generalSimVariable = new unordered_map<string,float>();
    command::_generalSimVariable->insert({"/instrumentation/airspeed-indicator/indicated-speed-kt",0});
    command::_generalSimVariable->insert({"/sim/time/warp",0});
    command::_generalSimVariable->insert({"/controls/switches/magnetos",0});
    command::_generalSimVariable->insert({"//instrumentation/heading-indicator/offset-deg",0});
    command::_generalSimVariable->insert({"/instrumentation/altimeter/indicated-altitude-ft",0});
    command::_generalSimVariable->insert({"/instrumentation/altimeter/pressure-alt-ft",0});
    command::_generalSimVariable->insert({"/instrumentation/attitude-indicator/indicated-pitch-deg",0});
    command::_generalSimVariable->insert({"/instrumentation/attitude-indicator/indicated-roll-deg",0});
    command::_generalSimVariable->insert({"/instrumentation/attitude-indicator/internal-pitch-deg",0});
    command::_generalSimVariable->insert({"/instrumentation/attitude-indicator/internal-roll-deg",0});
    command::_generalSimVariable->insert({"/instrumentation/encoder/indicated-altitude-ft",0});
    command::_generalSimVariable->insert({"/instrumentation/encoder/pressure-alt-ft",0});
    command::_generalSimVariable->insert({"/instrumentation/gps/indicated-altitude-ft",0});
    command::_generalSimVariable->insert({"/instrumentation/gps/indicated-ground-speed-kt",0});
    command::_generalSimVariable->insert({"/instrumentation/gps/indicated-vertical-speed",0});
    command::_generalSimVariable->insert({"/instrumentation/heading-indicator/indicated-heading-deg",0});
    command::_generalSimVariable->insert({"/instrumentation/magnetic-compass/indicated-heading-deg",0});
    command::_generalSimVariable->insert({"/instrumentation/slip-skid-ball/indicated-slip-skid",0});
    command::_generalSimVariable->insert({"/instrumentation/turn-indicator/indicated-turn-rate",0});
    command::_generalSimVariable->insert({"/instrumentation/vertical-speed-indicator/indicated-speed-fpm",0});
    command::_generalSimVariable->insert({"/controls/flight/aileron",0});
    command::_generalSimVariable->insert({"/controls/flight/elevator",0});
    command::_generalSimVariable->insert({"/controls/flight/rudder",0});
    command::_generalSimVariable->insert({"/controls/flight/flaps",0});
    command::_generalSimVariable->insert({"/controls/engines/engine/throttle",0});
    command::_generalSimVariable->insert({"/controls/engines/current-engine/throttle",0});
    command::_generalSimVariable->insert({"/controls/switches/master-avionics",0});
    command::_generalSimVariable->insert({"/controls/switches/starter",0});
    command::_generalSimVariable->insert({"/engines/active-engine/auto-start",0});
    command::_generalSimVariable->insert({"/controls/flight/speedbrake",0});
    command::_generalSimVariable->insert({"/sim/model/c172p/brake-parking",0});
    command::_generalSimVariable->insert({"/controls/engines/engine/primer",0});
    command::_generalSimVariable->insert({"/controls/engines/current-engine/mixture",0});
    command::_generalSimVariable->insert({"/controls/switches/master-bat",0});
    command::_generalSimVariable->insert({"/controls/switches/master-alt",0});
    command::_generalSimVariable->insert({"/engines/engine/rpm",0});

}
void InitMap::initalizeAllMaps() {
    initGeneralSimVariable();
    initfuncTable();
    initSimTable();
    initProgTable();
    initCommandsMap();
}