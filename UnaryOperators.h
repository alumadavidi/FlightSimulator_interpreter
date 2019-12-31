//
// Created by magshimim on 12.12.2019.
//
#pragma once
#ifndef UNTITLED_UNARYOPERATORS_H
#define UNTITLED_UNARYOPERATORS_H
#include "Expression.h"
#include "BinaryAndUnaryAbstract.h"

class UMinus : public UnaryOperator {

public:
    UMinus(Expression* expression1);
    virtual float calculate();
    virtual ~UMinus();
};

class UPlus : public UnaryOperator {

public:
    UPlus(Expression* expression1);
    virtual float calculate();
    virtual ~UPlus();
};
#endif //UNTITLED_UNARYOPERATORS_H
