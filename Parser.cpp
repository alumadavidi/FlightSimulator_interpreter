//
// Created by magshimim on 13.12.2019.
//

#include "Parser.h"
//parser the file txt to commands
void Parser::parser(string& fileName) {
    int index = 0, i = 0, addToCounter = 0;
    Lexer lexer;
    vector<string> spliteToken;
    //init the spliteToken with vector string of words from file
    lexer.lexerTheFile(&spliteToken, fileName);
    command* c;
    if(spliteToken.size() > 0) {
        vector<string>::iterator it = spliteToken.begin();
        while (index < spliteToken.size()) {
            if(command::_commandsMap->find(*it) != command::_commandsMap->end()){
                //get command
                c = command::_commandsMap->find(*it)->second;
                index += c->execute(it);
            } else {
                //from type variable = num
                addToCounter = updateVar(it);
                if (addToCounter == 0) {
                    //from type func
                    //TODO c is funcCommand
                }
                index += addToCounter;
            }
            for (i; i < index; i++) {
                it++;
            }
            command::counter = 0;
        }
    }
}
//update value of variable that exist is progMap
int Parser::updateVar(vector<string>::iterator it) {
    unordered_map<string, variableAir>::iterator iter;
    float num;
    string key = *it;
    variableAir *var;
    ++it; //erase var
    ++it;//erase sign
    string left = *it;
    //update the value
    updateValueInShuntingAlgo(left, key);
    return 3;
}
//update value of variable air according shunting yard algo
void Parser::updateValueInShuntingAlgo(const string & variable,const string & key) {
    unordered_map<string, variableAir>::iterator iter;
    variableAir *var;
    float num;
    if(iter != command::_progTable->find(key)) { // key in map
        var = &(command::_progTable->find(key)->second);
    }
    //get the result
    num = generalShuntingAlgorithem(variable);
    var->setValue(num);
}
//general method to get num of variables
float Parser::generalShuntingAlgorithem(const string& variable) {

    Interpreter interpreter;
    float num;
    try {
        Expression* e = interpreter.interpret(variable);
        num = e->calculate();
    } catch (const char* exc){
        throw exc;
    }
    return num;
}


