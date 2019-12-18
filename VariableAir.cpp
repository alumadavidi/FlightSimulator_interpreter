//
// Created by magshimim on 12.12.2019.
//

#include "VariableAir.h"
#include "Command/Command.h"

variableAir::variableAir(string sim, string direction) {
    std::mutex mutex;
    mutex.lock();
    this->_direction = direction;
    this->_sim = sim;
    unordered_map<string, float>::iterator iter;
    if(direction.compare("<-") == 0){
        ///engines/engine/rpm/engine_rpm
        if(iter != command::_generalSimVariable->find(sim)) { // key in map
            this->_value = &command::_generalSimVariable->find(sim)->second;
        }
    }
    mutex.unlock();
}
void variableAir::setValue(float value) {
    this->_value = &value;
}

float variableAir::getValue() const {
    return *_value;
}
float variableAir::calculate() {
    return *(this->_value);
}
void variableAir::createMessageToSend(string& message) {
    message = "";
    if(this->_direction.compare("->") == 0){
        message = "set " + this->_sim+ " " + to_string(*this->_value) + "\r\n";
    }
}