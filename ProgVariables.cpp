//
// Created by magshimim on 12.12.2019.
//
#include "ProgVariables.h"
#include "Command/Command.h"
#include "Data.h"

ProgVariables::ProgVariables(string sim, string direction) {
    this->_direction = direction;
    this->_sim = sim;
    if(_direction== "<-") {
        _simValue = Data::_generalSimVariable->find(_sim)->second.first;
    }
}
void ProgVariables::setProgValue(float value) {
    _progValue = value;
}
void ProgVariables::setSimValue(float value) {
    _simValue = value;
}
float ProgVariables::calculate() {
    if(_direction== "<-") {
        return _simValue;
    } else {
        return _progValue;
    }
}
void ProgVariables::createMessageToSend(string& message) {
    message = "";
    if(this->_direction.compare("->") == 0){
        message = "set " + this->_sim+ " " + to_string(this->calculate()) + "\r\n";
    }
}
string ProgVariables::getDirection() {
    return this->_direction;
}
string ProgVariables::getSim() {
    return this->_sim;
}
ProgVariables::~ProgVariables() {

}