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
    command::_generalSimVariable = new unordered_map<string, float>();
    command::_generalSimVariable->insert({"airspeed-indicator_indicated-speed-kt",0});
    command::_generalSimVariable->insert({"heading-indicator_offset-deg",0});
    command::_commandsMap->insert({"altimeter_indicated-altitude-ft",0});
    command::_commandsMap->insert({"altimeter_pressure-alt-ft",0});
    command::_commandsMap->insert({"attitude-indicator_indicated-pitch-deg",0});
    command::_commandsMap->insert({"attitude-indicator_indicated-roll-deg",0});
    command::_commandsMap->insert({"attitude-indicator_internal-pitch-deg",0});
    command::_commandsMap->insert({"attitude-indicator_internal-roll-deg",0});
    command::_commandsMap->insert({"encoder_indicated-altitude-ft",0});
    command::_commandsMap->insert({"encoder_pressure-alt-ft",0});
    command::_commandsMap->insert({"gps_indicated-altitude-ft",0});
    command::_commandsMap->insert({"gps_indicated-ground-speed-kt",0});
    command::_commandsMap->insert({"gps_indicated-vertical-speed",0});
    command::_commandsMap->insert({"indicated-heading-deg",0});
    command::_commandsMap->insert({"magnetic-compass_indicated-heading-deg",0});
    command::_commandsMap->insert({"slip-skid-ball_indicated-slip-skid",0});
    command::_commandsMap->insert({"turn-indicator_indicated-turn-rate",0});
    command::_commandsMap->insert({"vertical-speed-indicator_indicated-speed-fpm",0});
    command::_commandsMap->insert({"flight_aileron",0});
    command::_commandsMap->insert({"flight_elevator",0});
    command::_commandsMap->insert({"flight_rudder",0});
    command::_commandsMap->insert({"flight_flaps",0});
    command::_commandsMap->insert({"engine_throttle",0});
    command::_commandsMap->insert({"engine_rpm",0});
}
void InitMap::initalizeAllMaps() {
    //initGeneralSimVariable();
    initfuncTable();
    initSimTable();
    initProgTable();
    initCommandsMap();
}