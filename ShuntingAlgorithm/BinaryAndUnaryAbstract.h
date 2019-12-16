//
// Created by magshimim on 12.12.2019.
//
#pragma once
#ifndef UNTITLED_BINARYANDUNARYABSTRACT_H
#define UNTITLED_BINARYANDUNARYABSTRACT_H
#include "Expression.h"

class BinaryOperator: public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    virtual ~BinaryOperator();
};

class UnaryOperator : public Expression {
protected:
    Expression* unaryExp;
public:
    virtual ~UnaryOperator();
};
#endif //UNTITLED_BINARYANDUNARYABSTRACT_H
