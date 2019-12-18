//
// Created by magshimim on 13.12.2019.
//

#include "Parser.h"
//parser the file txt to commands
void Parser::parser(string& fileName) {
    Lexer lexer;
    vector<string> spliteToken;
    //init the spliteToken with vector string of words from file
    lexer.lexerTheFile(&spliteToken, fileName);
   parserByTokens(spliteToken);
}
void Parser::parserByTokens(vector<string> &spliteToken) {
    int index = 0, addToCounter = 0;
    command::it = spliteToken.begin();
    command* c;
    if(spliteToken.size() > 0) {
        vector<string>::iterator copyIter = spliteToken.begin();
        while (copyIter != spliteToken.end()) {
            if(command::_commandsMap->find(*copyIter) != command::_commandsMap->end()){
                //get command
                c = command::_commandsMap->find(*copyIter)->second;
                index = c->execute();
            } else {
                //from type variable = num
                addToCounter = updateVar();
                //function call
                if (addToCounter == 0) {
                    //vector<command> commands = command::_funcsMap->find(*it)->second;
                    //for ()
                }
                index = addToCounter;
            }
            copyIter += index;
        }
    }
}





//update value of variable that exist is progMap
int Parser::updateVar() {
    vector<string>::iterator copyIt = command::it;
    unordered_map<string, variableAir>::iterator iter;
    if(*(++copyIt) != "=") {
        return 0;
    }
    string key = *command::it;
    variableAir *var;
    command::it++; //erase var
    command::it++;//erase sign
    string left = *command::it;
    command::it++;
    //update the value
    updateValueInShuntingAlgo(left, key);
    return 3;
}
//update value of variable air according shunting yard algo
void Parser::updateValueInShuntingAlgo(const string & variable,const string & key) {
    unordered_map<string, variableAir>::iterator iter;
    string message;
    variableAir *var;
    float num;
    if(iter != command::_progTable->find(key)) { // key in map
        var = &(command::_progTable->find(key)->second);
    }
    //get the result
    num = generalShuntingAlgorithem(variable);
    var->setValue(num);
    var->createMessageToSend(message);
//    std::lock_guard<std::mutex> lk(command::m);
//    command::ready = true;
    if(message.compare("") != 0){
        ConnectCommand::setMessageToSend(message);
    }

//    std::cout << "main() signals data ready for processing\n";
//    command::cv.notify_one();
//    // wait for the worker
//    {
//        std::unique_lock<std::mutex> lk(command::m);
//        command::cv.wait(lk, []{return command::processed;});
//    }
//    std::cout << "Back in main()"<<endl;
//    command::ready = false;

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


