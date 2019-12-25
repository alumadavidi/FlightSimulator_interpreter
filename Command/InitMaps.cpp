//
// Created by magshimim on 13.12.2019.
//

#include "InitMaps.h"
#include "serverCommand.h"
#include "ClientCommand.h"
#include "../Data.h"

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
    command::_progTable = new unordered_map<string, variableAir*>();
}
void InitMap::initSimTable() {
    command::_simTable = new unordered_map<string, variableAir>();
}
void InitMap::initfuncTable() {
    command::_funcsMap = new unordered_map<string, pair<string,vector<string>*>>();
}
void InitMap::initGeneralSimVariable() {
    command::_generalSimVariable = new unordered_map<string, pair<float, variableAir*>>();
    command::_generalSimVariable->insert({V1,{0, nullptr}});
    command::_generalSimVariable->insert({V2,{0, nullptr}});
    command::_generalSimVariable->insert({V3,{0, nullptr}});
    command::_generalSimVariable->insert({V4,{0, nullptr}});
    command::_generalSimVariable->insert({V5,{0, nullptr}});
    command::_generalSimVariable->insert({V6,{0, nullptr}});
    command::_generalSimVariable->insert({V7,{0, nullptr}});
    command::_generalSimVariable->insert({V8,{0, nullptr}});
    command::_generalSimVariable->insert({V9,{0, nullptr}});
    command::_generalSimVariable->insert({V10,{0, nullptr}});
    command::_generalSimVariable->insert({V11,{0, nullptr}});
    command::_generalSimVariable->insert({V12,{0, nullptr}});
    command::_generalSimVariable->insert({V13,{0, nullptr}});
    command::_generalSimVariable->insert({V14,{0, nullptr}});
    command::_generalSimVariable->insert({V15,{0, nullptr}});
    command::_generalSimVariable->insert({V16,{0, nullptr}});
    command::_generalSimVariable->insert({V17,{0, nullptr}});
    command::_generalSimVariable->insert({V18,{0, nullptr}});
    command::_generalSimVariable->insert({V19,{0, nullptr}});
    command::_generalSimVariable->insert({V20,{0, nullptr}});
    command::_generalSimVariable->insert({V21,{0, nullptr}});
    command::_generalSimVariable->insert({V22,{0, nullptr}});
    command::_generalSimVariable->insert({V23,{0, nullptr}});
    command::_generalSimVariable->insert({V24,{0, nullptr}});
    command::_generalSimVariable->insert({V25,{0, nullptr}});
    command::_generalSimVariable->insert({V26,{0, nullptr}});
    command::_generalSimVariable->insert({V27,{0, nullptr}});
    command::_generalSimVariable->insert({V28,{0, nullptr}});
    command::_generalSimVariable->insert({V29,{0, nullptr}});
    command::_generalSimVariable->insert({V30,{0, nullptr}});
    command::_generalSimVariable->insert({V31,{0, nullptr}});
    command::_generalSimVariable->insert({V32,{0, nullptr}});
    command::_generalSimVariable->insert({V33,{0, nullptr}});
    command::_generalSimVariable->insert({V34,{0, nullptr}});
    command::_generalSimVariable->insert({V35,{0, nullptr}});
    command::_generalSimVariable->insert({V36,{0, nullptr}});

}
void InitMap::initalizeAllMaps() {
    initGeneralSimVariable();
    initfuncTable();
    initSimTable();
    initProgTable();
    initCommandsMap();
}
void InitMap::eraseMap() {

    //delete progTable
    unordered_map<string, variableAir*>::iterator iterProgTable;
    unordered_map<string, pair<float, variableAir*>>::iterator iter;
    /*for (iterProgTable = command::_progTable->begin();
         iterProgTable != command::_progTable->end(); iterProgTable++){
        variableAir* var = iterProgTable->second;
        variableAir* varSim;
        if(var != nullptr){
            if (iter != command::_generalSimVariable->find(var->getSim())) { // key in map
                varSim = command::_generalSimVariable->find(var->getSim())->second.second;
                delete iter->second.second;
                iterProgTable->second = nullptr;
                iter->second.second = nullptr;
            } else {
                delete iterProgTable->second;
                iterProgTable->second = nullptr;
            }
            command::_progTable->erase(iterProgTable);
        }
    }*/
    delete command::_progTable;



    //delte generalSimVariable
    unordered_map<string, pair<float, variableAir*>>::iterator iterSimTable;
    /*for (iterSimTable = command::_generalSimVariable->begin();
    iterSimTable != command::_generalSimVariable->end(); iterSimTable++){

        variableAir* var = iterSimTable->second.second;

       if(var != nullptr) {
            delete var;
           iterSimTable->second.second = nullptr;
        }
    }*/
    delete command::_generalSimVariable;

    //delete funcTable
    unordered_map<string, pair<string,vector<string>*>>::iterator iterFuncable;
    /*for (iterFuncable = command::_funcsMap->begin();
    iterFuncable != command::_funcsMap->end(); iterFuncable++){
        vector<string>* vector = iterFuncable->second.second;
        if(vector != nullptr){
            delete vector;
            iterFuncable->second.second = nullptr;
        }
    }*/
    delete command::_funcsMap;


    //delete commandMap
    unordered_map<string, command*>::iterator iterCommandMap;
    for (iterCommandMap = command::_commandsMap->begin();
         iterCommandMap != command::_commandsMap->end(); iterCommandMap++){
        command* command = iterCommandMap->second;
        if(command != nullptr){
            delete command;
        }
    }
    delete command::_commandsMap;
}