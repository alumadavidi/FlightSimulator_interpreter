//
// Created by magshimim on 12.12.2019.
//

#include "CommandsClasses.h"


using namespace std;
//Add new var to progTable map
int DefineVarCommand::execute() {
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
    //create new var
    ProgVariables* newVar = new ProgVariables(sim, direction);
    Data::_progTable->insert({key, newVar});  ///check the map
    if(newVar->getDirection() == "<-") {
        Data::_generalSimVariable->at(sim).second = newVar;
    }
    if (left.size() > 0) { // first opetion var x = y
        try {
            Parser::updateValueInShuntingAlgo(left, key);
        } catch (const char* e){
            throw "failed in parser of DefineVarCommand::execute";
        }



    }

    return counterFunc;
}
//Loop of methods by conditation
int LoopCommand::execute() {
    int counterTemp = 0;
    Parser parser;
    //shared code to loop and if
    init();
    // get the inside of the loop to new vector
    _inCommands = getInsideCommend();
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
//Do the method if the condition is true
int IfCommand::execute() {
    int counterTemp;
    Parser parser;
    //shared code to loop and if
    init();
    // get the inside of the loop to new vector
    _inCommands = getInsideCommend();
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
//initalize func and play func
int FuncCommand::execute() {
    string funcName = *Data::it;
    ++Data::it;//func name
    counter++;
    string tempString = *Data::it;
    //the func is exist in map
    if(tempString.substr(0,3)!= "var") {
        activateFunc(funcName);
    } else {
        //initalize new func and add to funcMap
        string var = tempString.substr(4, tempString.length() - 4);
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
//play the func
void FuncCommand::activateFunc(string funcName) {
    Parser parser;
    //find the func in map
    vector<string> inCommands = *Data::_funcsMap->find(funcName)->second.second;
    string key = Data::_funcsMap->find(funcName)->second.first;
    ProgVariables* localVar = new ProgVariables("", "");
    string paramVal = *Data::it;
    Data::it++;
    counter++;
    Data::_progTable->insert({key, localVar});
    try {
        parser.updateValueInShuntingAlgo(paramVal, key);
    } catch (const char* e){
        throw "failed in activateFunc in algo";
    }
    vector<string>::iterator tempIt = Data::it;
    parser.parserByTokens(inCommands);
    delete localVar;
    //ersase local var
    Data::_progTable->erase(key);
    Data::it = tempIt;
}
//print to console
int Print::execute() {
    ++Data::it;
    string toPrint = *Data::it;
    string name;
    float varPrint;
    unordered_map<string, ProgVariables*>::iterator iter;
    ProgVariables *var;
    if(iter != Data::_progTable->find(toPrint)) { // print variable
        var = Data::_progTable->find(toPrint)->second;
        cout << var->calculate() << endl;
    } else {
        try {
            varPrint = Parser::generalShuntingAlgorithem(toPrint);
            cout<<varPrint<<endl;
        } catch(const char* e){
            cout << toPrint << endl;
        }

    }
    Data::it++;
    return 2;
}
//sleep the main thead for x miliseconds
int Sleep::execute() {
    float time;
    ++Data::it;
    string timeS = *(Data::it);
    try {
        time = Parser::generalShuntingAlgorithem(timeS);
        // convert string to long
        std::string::size_type sz;
        std::this_thread::sleep_for(std::chrono::milliseconds((long)time));
        ++Data::it;
        return 2;
    } catch (const char* e){
        throw "failed in algo of Sleep::execute";
    }

}
//initalize the condition for loop and if command
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
//return true or false of condition
bool ConditionParser::getCondition(string first, string op, string second) {
    bool result;
    try {
        int resultNum = Parser::generalShuntingAlgorithem(first + op + second);
        if (resultNum == 0) {
            result = false;
        } else {
            result = true;
        }
        return result;
    }  catch (const char* e){
        throw "failed in parser algo in ConditionParser::getCondition";
    }
}
