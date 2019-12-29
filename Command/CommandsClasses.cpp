//
// Created by magshimim on 12.12.2019.
//

#include "CommandsClasses.h"
#include <cstring>
#include "stdlib.h"

using namespace std;
int DefineVarCommand::execute() {
//    std::mutexGeneralSimVariable mutexGeneralSimVariable;
    int counterFunc;
    string sim = "", left = "";
    ++Data::it;//for command
    string key = *Data::it;
    ++Data::it;
    string direction = *(Data::it);
    if(direction.compare("=") == 0){ // var x = y
        Data::it++;
       left = *Data::it;
        Data::it++;
       counterFunc = 4;
    } else { //var x -> sim("")
        Data::it += 2;
        sim = *Data::it;
        ++Data::it;
        counterFunc = 5;
    }

    ProgVariables* newVar = new ProgVariables(sim, direction);
    Data::_progTable->insert({key, newVar});  ///check the map
    if(newVar->getDirection() == "<-") {
        Data::_generalSimVariable->at(sim).second = newVar;
    }
    if (left.size() > 0) { // first opetion var x = y
        Parser::updateValueInShuntingAlgo(left, key);
    }

    return counterFunc;
}
int LoopCommand::execute() {
    int counterTemp = 0;
    Parser parser;
    init(); //shared code to loop and if
    _inCommands = getInsideCommend(); // get the inside of the loop to new vector
    vector<string>::iterator temp = Data::it;
    while(getCondition(_firstExp,_op,_secondExp)){
        vector<string> copyInCommands = _inCommands;//any time init the copy
        parser.parserByTokens(copyInCommands);
    }
    Data::it = temp;
    counterTemp = counter;
    counter = 0;
    return counterTemp;
}
int IfCommand::execute() {
    int counterTemp;
    Parser parser;
    init(); //shared code to loop and if
    _inCommands = getInsideCommend(); // get the inside of the loop to new vector
    vector<string>::iterator temp = Data::it;
    if(getCondition(_firstExp,_op,_secondExp)){
        vector<string> copyInCommands = _inCommands;//any time init the copy
        parser.parserByTokens(copyInCommands);
    }
    Data::it = temp;
    counterTemp = counter;
    counter = 0;
    return counterTemp;
}
int FuncCommand::execute() { //for funcion
    string funcName = *Data::it;
    ++Data::it;//func name
    counter++;
    string temp = *Data::it;
    if(temp.substr(0,3)!= "var") {
        activateFunc(funcName);
    } else {
        string var = temp.substr(4, temp.length() - 4);
        Data::it++;
        counter ++;
        vector<string>* inCommand = new vector<string>();
        vector<string> temp = getInsideCommend();
        for (string s: temp) {
            inCommand->push_back(s);
        }
        // get the inside of the loop to new vector
        Data::_funcsMap->insert({funcName, {var, inCommand}});
    }
    int counterTemp = counter;
    counter = 0;
    return counterTemp;
}
void FuncCommand::activateFunc(string funcName) {
    Parser parser;
    vector<string> inCommands = *Data::_funcsMap->find(funcName)->second.second;
    string key = Data::_funcsMap->find(funcName)->second.first;
    ProgVariables* localVar = new ProgVariables("", "");
    string paramVal = *Data::it;
    Data::it++;
    counter++;
    Data::_progTable->insert({key, localVar});
    parser.updateValueInShuntingAlgo(paramVal, key);
    vector<string>::iterator tempIt = Data::it;
    parser.parserByTokens(inCommands);
    delete localVar;
    Data::_progTable->erase(key);
    Data::it = tempIt;
}
int Print::execute() {
    ++Data::it;
    string toPrint = *Data::it;
    string name;
    unordered_map<string, ProgVariables*>::iterator iter;
    ProgVariables *var;
    if(iter != Data::_progTable->find(toPrint)) { // print variable
        var = Data::_progTable->find(toPrint)->second;
        cout << var->calculate() << endl;
    } else {
        cout << toPrint << endl;
    }
    Data::it++;
    return 2;
}
int Sleep::execute() {
    ++Data::it;
    string timeS = *(Data::it);
    std::string::size_type sz;   // convert string to long
    long time = std::stol (timeS,&sz);
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
    ++Data::it;
    return 2;
}
void ConditionParser::init() {
    Data::it++;
    _firstExp = *Data::it;
    Data::it++;
    _op = *Data::it;
    Data::it++;
    _secondExp = *Data::it;
    Data::it++;
    counter += 4;
}
//the function return the inside commands and erase them from the copy (assume validness)
vector<string> holdCommands::getInsideCommend() {
    //TODO change
    vector<string> result;
    int leftCounter = 0;
    int rightCounter = 0;
    while((leftCounter != rightCounter) || leftCounter == 0) {
        if (*Data::it == "{") {
            leftCounter++;
            if (leftCounter == 1) {
                counter++;
                Data::it++;
                continue;
            }
        } else if (*Data::it == "}") {
            rightCounter++;
        }
        result.push_back(*Data::it); //add string to the new vector
        counter++;
        Data::it++;
    }
    if(!result.empty())
        result.pop_back(); //for "}"
    return result;
}
bool ConditionParser::getCondition(string first, string op, string second) {
    bool result;
    int resultNum = Parser::generalShuntingAlgorithem(first + op + second);
    if(resultNum == 0){
        result = false;
    } else{
        result = true;
    }
    return result;
}
