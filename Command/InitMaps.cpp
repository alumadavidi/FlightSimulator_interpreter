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
    command::_generalSimVariable->insert({"/instrumentation/airspeed-indicator/indicated-speed-kt/airspeed-indicator_indicated-speed-kt",0});
    command::_generalSimVariable->insert({"//instrumentation/heading-indicator/offset-deg/heading-indicator_offset-deg",0});
    command::_generalSimVariable->insert({"/instrumentation/altimeter/indicated-altitude-ft/altimeter_indicated-altitude-ft",0});
    command::_generalSimVariable->insert({"/instrumentation/altimeter/pressure-alt-ft/altimeter_pressure-alt-ft",0});
    command::_generalSimVariable->insert({"/instrumentation/attitude-indicator/indicated-pitch-deg/attitude-indicator_indicated-pitch-deg",0});
    command::_generalSimVariable->insert({"/instrumentation/attitude-indicator/indicated-roll-deg/attitude-indicator_indicated-roll-deg",0});
    command::_generalSimVariable->insert({"/instrumentation/attitude-indicator/internal-pitch-deg/attitude-indicator_internal-pitch-deg",0});
    command::_generalSimVariable->insert({"/instrumentation/attitude-indicator/internal-roll-deg/attitude-indicator_internal-roll-deg",0});
    command::_generalSimVariable->insert({"/instrumentation/encoder/indicated-altitude-ft/encoder_indicated-altitude-ft",0});
    command::_generalSimVariable->insert({"/instrumentation/encoder/pressure-alt-ft/encoder_pressure-alt-ft",0});
    command::_generalSimVariable->insert({"/instrumentation/gps/indicated-altitude-ft/gps_indicated-altitude-ft",0});
    command::_generalSimVariable->insert({"/instrumentation/gps/indicated-ground-speed-kt/gps_indicated-ground-speed-kt",0});
    command::_generalSimVariable->insert({"/instrumentation/gps/indicated-vertical-speed/gps_indicated-vertical-speed",0});
    command::_generalSimVariable->insert({"/instrumentation/heading-indicator/indicated-heading-deg/indicated-heading-deg",0});
    command::_generalSimVariable->insert({"/instrumentation/magnetic-compass/indicated-heading-deg/magnetic-compass_indicated-heading-deg",0});
    command::_generalSimVariable->insert({"/instrumentation/slip-skid-ball/indicated-slip-skid/slip-skid-ball_indicated-slip-skid",0});
    command::_generalSimVariable->insert({"/instrumentation/turn-indicator/indicated-turn-rate/turn-indicator_indicated-turn-rate",0});
    command::_generalSimVariable->insert({"/instrumentation/vertical-speed-indicator/indicated-speed-fpm/vertical-speed-indicator_indicated-speed-fpm",0});
    command::_generalSimVariable->insert({"/controls/flight/aileron/flight_aileron",0});
    command::_generalSimVariable->insert({"/controls/flight/elevator/flight_elevator",0});
    command::_generalSimVariable->insert({"/controls/flight/rudder/flight_rudder",0});
    command::_generalSimVariable->insert({"/controls/flight/flaps/flight_flaps",0});
    command::_generalSimVariable->insert({"/controls/engines/engine/throttle/engine_throttle",0});
    command::_generalSimVariable->insert({"\"/engines/engine/engine_rpm\"",0});
}
void InitMap::initalizeAllMaps() {
    initGeneralSimVariable();
    initfuncTable();
    initSimTable();
    initProgTable();
    initCommandsMap();
}