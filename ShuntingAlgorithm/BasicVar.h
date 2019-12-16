//
// Created by magshimim on 12.12.2019.
//
#pragma once
#ifndef UNTITLED_BASICVAR_H
#define UNTITLED_BASICVAR_H

#include "Expression.h"
#include <iostream>
class Value : public Expression{
private:
    const double value;
public:
    Value(float num) : value(num){}
    virtual float calculate();
    virtual ~Value();
};

using namespace std;
class Variable : public Expression {

private:
    string name;
    float value;
public:
    Variable(string name1, float value1);
    Variable(float value, string name);
    virtual float calculate();
    Variable& operator++();
    Variable& operator--();
    Variable& operator++(int);
    Variable& operator--(int);
    Variable& operator+=(float);
    Variable& operator-=(float);
    virtual ~Variable();
    float getNum();
    void setNum(float);
    string getValue();
    void setValue(string&);
};

#endif //UNTITLED_BASICVAR_H
