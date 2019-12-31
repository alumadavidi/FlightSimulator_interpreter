//
// Created by magshimim on 12.12.2019.
//
#pragma once
#ifndef UNTITLED11_VARIABLEAIR_H
#define UNTITLED11_VARIABLEAIR_H

#include "Expression.h"
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;
//Pattern of variable in program
class ProgVariables : Expression {
private:
    float _progValue;
    float _simValue;
    string _sim;
    string _direction;
public:
    ProgVariables(string sim, string direction);
    void setProgValue(float value);
    void setSimValue(float value);
    void createMessageToSend(string&);
    virtual float calculate();
    string getDirection();
    string getSim();
    ~ProgVariables();

};
#endif //UNTITLED11_VARIABLEAIR_H
