//
// Created by magshimim on 12.12.2019.
//

#include "UnaryOperators.h"

UMinus::UMinus(Expression *expression1) {
    this->unaryExp = expression1;
}

float UMinus::calculate() {
    return -(this->unaryExp->calculate());
}
UMinus::~UMinus() {}

UPlus::UPlus(Expression *expression1) {
    this->unaryExp = expression1;
}

float UPlus::calculate() {
    return this->unaryExp->calculate();
}
UPlus::~UPlus() {}
