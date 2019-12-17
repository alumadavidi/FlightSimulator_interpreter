//
// Created by magshimim on 12.12.2019.
//

#include "CommandsClasses.h"
#include <cstring>
#include "stdlib.h"

//#include "../VariableAir.h"
//#include "Command.h"
using namespace std;




int DefineVarCommand::execute(vector<string>::iterator it) {
    int counterFunc;
    string sim = "", left = "";

    ++it;//for command
    string key = *it;
    ++it;
    string direction = *(it);
    if(direction.compare("=") == 0){ // var x = y
       ++it;
       left = *it;
       counterFunc = 4;
    } else { //var x -> sim("")
        it += 2;
        sim = *it;
        counterFunc = 5;
        ++it;
    }
    variableAir newVar = variableAir(sim, direction);
    _progTable->insert({key, newVar});  ///check the map
    if(left.size() > 0) { // first opetion var x = y
        Parser::updateValueInShuntingAlgo(left, key);
    }

    return counterFunc;
}
int LoopCommand::execute(vector<string>::iterator it) {
    Parser parser;
    init(it); //shared code to loop and if
    it += counter;
    _inCommands = getInsideCommend(it); // get the inside of the loop to new vector
    while(getCondition(_firstExp,_op,_secondExp)){
        vector<string> copyInCommands = _inCommands;//any time init the copy
        parser.parserByTokens(copyInCommands);
    }
    return counter;
}
int IfCommand::execute(vector<string>::iterator it) {
    Parser parser;
    init(it); //shared code to loop and if
    it += counter;
    _inCommands = getInsideCommend(it); // get the inside of the loop to new vector
    if(getCondition(_firstExp,_op,_secondExp)){
        vector<string> copyInCommands = _inCommands;//any time init the copy
        auto iter = copyInCommands.begin();
        while(iter != copyInCommands.end()) {
            parser.parserByTokens(copyInCommands);
        }
    }
}
int FuncCommand::execute(vector<string>::iterator it) { //for funcion
    string funcName = *it;
    ++it;
    vector<string> inCommand = getInsideCommend(it);
     // get the inside of the loop to new vector
    _funcsMap->insert({funcName, &inCommand});
}
int Print::execute(vector<string>::iterator it) {
    ++it;
    string toPrint = *it;
    if(toPrint[0] == '"'){ // string
        cout << toPrint << endl;
    } else { // print variable
        unordered_map<string, variableAir>::iterator iter;
        variableAir *var;
        if(iter != command::_progTable->find(toPrint)) {
            var = &(command::_progTable->find(toPrint)->second);
            cout << var->getValue() << endl;
        }
    }
    it++;
    return 2;
}
int Sleep::execute(vector<string>::iterator it) {
    ++it;
    string timeS = *(it);
    std::string::size_type sz;   // convert string to long
    long time = std::stol (timeS,&sz);
    //TODO sleep for x miliseconds
    ++it;
    return 2;
}
void ConditionParser::init(vector<string>::iterator it) {
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
vector<string> holdCommands::getInsideCommend(vector<string>::iterator& it) {
    vector<string> result;
    int leftCounter = 0;
    int rightCounter = 0;
    auto iter = it->begin();
    while(it->begin()!= it->end()) {
        if ((leftCounter == rightCounter) && leftCounter != 0) {
            break;
        } else if (*it == "{") {
            leftCounter++;
            if (leftCounter == 1) {
                it++;
                counter++;
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
    bool result = false;
    if(op == ">") {
         result = Parser::generalShuntingAlgorithem(first) > Parser::generalShuntingAlgorithem(second);
    } else if (op == "<") {
        result = Parser::generalShuntingAlgorithem(first) < Parser::generalShuntingAlgorithem(second);
    } else if (op == "<=") {
        result = Parser::generalShuntingAlgorithem(first) <= Parser::generalShuntingAlgorithem(second);
    } else if (op == ">=") {
        result = Parser::generalShuntingAlgorithem(first) >= Parser::generalShuntingAlgorithem(second);
    } else if (op == "==") {
        result = Parser::generalShuntingAlgorithem(first) == Parser::generalShuntingAlgorithem(second);
    } else if (op == "!=") {
        result = Parser::generalShuntingAlgorithem(first) != Parser::generalShuntingAlgorithem(second);
    }
    return result;
}
int activateFunc::execute(vector<string>::iterator it) {
    vector<string>* inCommands =command::_funcsMap->find(*it)->second;
    it++;
    int var = stod(*it);
    Parser parser;
    parser.parserByTokens(*inCommands);
}
