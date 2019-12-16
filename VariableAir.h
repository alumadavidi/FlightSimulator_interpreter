//
// Created by magshimim on 12.12.2019.
//
#pragma once
#ifndef UNTITLED11_VARIABLEAIR_H
#define UNTITLED11_VARIABLEAIR_H

#include "ShuntingAlgorithm/Expression.h"
#include <iostream>
#include <string>
using namespace std;

class variableAir :Expression{
private:
    float _value;
    string _sim;
    string _direction;
public:
    variableAir(string sim, string direction);
    void setValue(float value);
    float getValue() const;
    virtual float calculate();
};
#endif //UNTITLED11_VARIABLEAIR_H
