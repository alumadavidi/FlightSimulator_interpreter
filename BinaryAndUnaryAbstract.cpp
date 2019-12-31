//
// Created by magshimim on 12.12.2019.
//

#include "BinaryAndUnaryAbstract.h"
BinaryOperator::~BinaryOperator() {
    if (this->left!= nullptr){
        delete this->left;
    }
    if(this->right != nullptr){
        delete this->right;
    }
}

UnaryOperator::~UnaryOperator() {
    delete this->unaryExp;
}


Expression::~Expression() {}