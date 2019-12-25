//
// Created by magshimim on 12.12.2019.
//

#include "VariableAir.h"
#include "Command/Command.h"

variableAir::variableAir(string sim, string direction) {
    this->_direction = direction;
    this->_sim = sim;
    if(_direction== "<-") {
        _simValue = command::_generalSimVariable->find(_sim)->second.first;
    }
}
void variableAir::setProgValue(float value) {
    _progValue = value;
}
void variableAir::setSimValue(float value) {
    _simValue = value;
}
float variableAir::calculate() {
    if(_direction== "<-") {
        return _simValue;
    } else if(_direction== "->") {
        return _progValue;
    }
}
void variableAir::createMessageToSend(string& message) {
    message = "";
    if(this->_direction.compare("->") == 0){
        message = "set " + this->_sim+ " " + to_string(this->calculate()) + "\r\n";
    }
}
string variableAir::getDirection() {
    return this->_direction;
}
string variableAir::getSim() {
    return this->_sim;
}
variableAir::~variableAir() {

}