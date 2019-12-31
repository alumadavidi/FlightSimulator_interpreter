//
// Created by magshimim on 12.12.2019.
//
#pragma once
#ifndef UNTITLED_BINARYOPERATORS_H
#define UNTITLED_BINARYOPERATORS_H
#include "Expression.h"
#include "BinaryAndUnaryAbstract.h"

class Div : public BinaryOperator{
public:
    Div(Expression* left1, Expression* right2);
    virtual float calculate();
    virtual ~Div();
};

class Minus : public BinaryOperator {
public:
    Minus(Expression* left1, Expression* right1);
    virtual float calculate();
    virtual ~Minus();
};

class Mul : public BinaryOperator{
public:
    Mul(Expression* left1, Expression* right2);
    virtual float calculate();
    virtual ~Mul();
};

class Plus: public BinaryOperator{
public:
    Plus(Expression* left1, Expression* right2);
    virtual float calculate();
    virtual ~Plus();
};

class Smaller : public BinaryOperator {
public:
    Smaller(Expression* left1, Expression* right1);
    virtual float calculate();
    virtual ~Smaller();
};

class Bigger : public BinaryOperator {
public:
    Bigger(Expression* left1, Expression* right1);
    virtual float calculate();
    virtual ~Bigger();
};

class SmallEqually : public BinaryOperator {
public:
    SmallEqually(Expression* left1, Expression* right1);
    virtual float calculate();
    virtual ~SmallEqually();
};

class BigEqually : public BinaryOperator {
public:
    BigEqually(Expression* left1, Expression* right1);
    virtual float calculate();
    virtual ~BigEqually();
};

class Equal : public BinaryOperator {
public:
    Equal(Expression* left1, Expression* right1);
    virtual float calculate();
    virtual ~Equal();
};

class Different : public BinaryOperator {
public:
    Different(Expression* left1, Expression* right1);
    virtual float calculate();
    virtual ~Different();
};
#endif //UNTITLED_BINARYOPERATORS_H
