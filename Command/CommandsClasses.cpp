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
    ++it;//for command
    string key = *it;
    ++it;
    string direction = *(it);
    if(direction.compare("=") == 0){ // var x = y
       it++;
       left = *it;
       it++;
       counterFunc = 4;
    } else { //var x -> sim("")
        it += 2;
        sim = *it;
        ++it;
        counterFunc = 5;
    }

    variableAir* newVar = new variableAir(sim, direction);
    _progTable->insert({key, newVar});  ///check the map
    if(newVar->getDirection() == "<-") {
        command::_generalSimVariable->at(sim).second = newVar;
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
    vector<string>::iterator temp = command::it;
    while(getCondition(_firstExp,_op,_secondExp)){
        vector<string> copyInCommands = _inCommands;//any time init the copy
        parser.parserByTokens(copyInCommands);
    }
    command::it = temp;
    counterTemp = counter;
    counter = 0;
    return counterTemp;
}
int IfCommand::execute() {
    int counterTemp;
    Parser parser;
    init(); //shared code to loop and if
    _inCommands = getInsideCommend(); // get the inside of the loop to new vector
    vector<string>::iterator temp = command::it;
    if(getCondition(_firstExp,_op,_secondExp)){
        vector<string> copyInCommands = _inCommands;//any time init the copy
        parser.parserByTokens(copyInCommands);
    }
    command::it = temp;
    counterTemp = counter;
    counter = 0;
    return counterTemp;
}
int FuncCommand::execute() { //for funcion
    string funcName = *it;
    ++it;//func name
    ++it;//for var
    string var = *it;
    it++;
    counter = 3;
    vector<string> inCommand = getInsideCommend();
     // get the inside of the loop to new vector
    _funcsMap->insert({funcName, {var, &inCommand}});
}
int Print::execute() {
    ++it;
    string toPrint = *it;
    string name;
    unordered_map<string, variableAir*>::iterator iter;
    variableAir *var;
    if(iter != command::_progTable->find(toPrint)) { // print variable
        var = command::_progTable->find(toPrint)->second;
        name = command::_progTable->find(toPrint)->first;
        if(name.compare("alt") == 0 && var->calculate() > 995){
            cout<<"stop"<<endl;
        }
        cout << var->calculate() << endl;
    } else {
        cout << toPrint << endl;
    }
    it++;
    return 2;
}
int Sleep::execute() {
    ++it;
    string timeS = *(it);
    std::string::size_type sz;   // convert string to long
    long time = std::stol (timeS,&sz);
    std::this_thread::sleep_for(std::chrono::milliseconds(time));
//    sleep(30);
    //TODO sleep for x miliseconds
    ++it;
    return 2;
}
void ConditionParser::init() {
    it++;
    _firstExp = *it;
    it++;
    _op = *it;
    it++;
    _secondExp = *it;
    it++;
    counter += 4;
}
//the function return the inside commands and erase them from the copy (assume validness)
vector<string> holdCommands::getInsideCommend() {
    vector<string> result;
    int leftCounter = 0;
    int rightCounter = 0;
    while(it->begin()!= it->end()) {
        if ((leftCounter == rightCounter) && leftCounter != 0) {
            break;
        } else if (*it == "{") {
            leftCounter++;
            if (leftCounter == 1) {
                counter++;
                it++;
                continue;
            }
        } else if (*it == "}") {
            rightCounter++;
        }
        result.push_back(*it); //add string to the new vector
        counter++;
        it++;
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
//    if(op == ">") {
//         result = Parser::generalShuntingAlgorithem(first) > Parser::generalShuntingAlgorithem(second);
//    } else if (op == "<") {
//        result = Parser::generalShuntingAlgorithem(first) < Parser::generalShuntingAlgorithem(second);
//    } else if (op == "<=") {
//        result = Parser::generalShuntingAlgorithem(first) <= Parser::generalShuntingAlgorithem(second);
//    } else if (op == ">=") {
//        result = Parser::generalShuntingAlgorithem(first) >= Parser::generalShuntingAlgorithem(second);
//    } else if (op == "==") {
//        result = Parser::generalShuntingAlgorithem(first) == Parser::generalShuntingAlgorithem(second);
//    } else if (op == "!=") {
//        result = Parser::generalShuntingAlgorithem(first) != Parser::generalShuntingAlgorithem(second);
//    }
    return result;
}
int activateFunc::execute() {
    Parser parser;
    vector<string> inCommands = *command::_funcsMap->find(*it)->second.second;
    string key = command::_funcsMap->find(*it)->second.first;
    it++;
    variableAir* localVar = new variableAir("", "");
    string paramVal = *it;
    _progTable->insert({key, localVar});
    parser.updateValueInShuntingAlgo(key, paramVal);
    it++;
    vector<string>::iterator tempIt = it;
    parser.parserByTokens(inCommands);
    _progTable->erase(key);
    it = tempIt;
    return 2;
}
