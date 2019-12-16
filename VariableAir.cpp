//
// Created by magshimim on 12.12.2019.
//

#include "VariableAir.h"
variableAir::variableAir(string sim, string direction) {
    this->_direction = direction;
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
