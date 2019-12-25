//
// Created by magshimim on 12.12.2019.
//
#pragma once
#ifndef UNTITLED11_VARIABLEAIR_H
#define UNTITLED11_VARIABLEAIR_H

#include "ShuntingAlgorithm/Expression.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include "Data.h"
using namespace std;

class variableAir :Expression {
private:
    float _progValue;
    float _simValue;
    string _sim;
    string _direction;
public:
    variableAir(string sim, string direction);
    void setProgValue(float value);
    void setSimValue(float value);
    void createMessageToSend(string&);
    virtual float calculate();
    string getDirection();
    string getSim();
    ~variableAir();

};
#endif //UNTITLED11_VARIABLEAIR_H
