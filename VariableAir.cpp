//
// Created by magshimim on 12.12.2019.
//

#include "VariableAir.h"
#include "Command/Command.h"

variableAir::variableAir(string sim, string direction) {
    this->_direction = direction;
    this->_sim = sim;
}
void variableAir::setValue(float value) {
    _value = value;
}
float variableAir::calculate() {
    if(_direction== "<-") {
        _value = command::_generalSimVariable->find(_sim)->second;
    }
    return _value;
}
void variableAir::createMessageToSend(string& message) {
    message = "";
    if(this->_direction.compare("->") == 0){
        message = "set " + this->_sim+ " " + to_string(_value) + "\r\n";
    }
}
string variableAir::getDirection() {
    return this->_direction;
}
string variableAir::getSim() {
    return this->_sim;
}