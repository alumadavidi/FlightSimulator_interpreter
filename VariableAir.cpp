//
// Created by magshimim on 12.12.2019.
//

#include "VariableAir.h"
variableAir::variableAir(string sim, string direction) {
    if(direction.compare("->") == 0) {
        this->_direction = "progToSim";
    } else if( direction.compare("<-") == 0 ){          //if(direction == "<-")
        this->_direction = "simToProg";
    } else { // direction == "="
        this->_direction = "progToProg";
    }
//    this->_direction = direction;
    this->_sim = sim;
}
void variableAir::setValue(float value) {
    this->_value = value;
}

float variableAir::getValue() const {
    return _value;
}
float variableAir::calculate() {
    return this->_value;
}
