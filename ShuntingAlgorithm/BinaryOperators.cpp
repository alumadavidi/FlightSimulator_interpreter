//
// Created by magshimim on 12.12.2019.
//

#include "BinaryOperators.h"
Div::Div(Expression *left1, Expression *right2) {
    this->left = left1;
    this->right = right2;
}
float Div::calculate() {
    float num = this->right->calculate();
    if(num == 0){
        throw "Can't division by zero";
    }
    return this->left->calculate() / num;
}
Div::~Div() {}

Minus::Minus(Expression *left1, Expression *right1) {
    this->left = left1;
    this->right = right1;
}
float Minus::calculate() {
    return this->left->calculate() - this->right->calculate();
}
Minus::~Minus() {}

Mul::Mul(Expression *left1, Expression *right2) {
    this->left = left1;
    this->right = right2;
}
float Mul::calculate() {
    return this->left->calculate() * this->right->calculate();
}
Mul::~Mul() {}

Plus::Plus(Expression *left1, Expression *right2) {
    this->left = left1;
    this->right = right2;
}
float Plus::calculate() {
    return this->left->calculate() + this->right->calculate();
}
Plus::~Plus() {}

/**Smaller method**/
Smaller::Smaller(Expression *left1, Expression *right1) {
    this->left = left1;
    this->right = right1;
}
//return 0 - for false 1 - for true
float Smaller::calculate() {
    return (this->left->calculate() < this->right->calculate());
}
Smaller::~Smaller() {}

/**Bigger method**/
Bigger::Bigger(Expression *left1, Expression *right1) {
    this->left = left1;
    this->right = right1;
}
//return 0 - for false 1 - for true
float Bigger::calculate() {
    return (this->left->calculate() > this->right->calculate());
}
Bigger::~Bigger() {}

/**SmallEqually method**/
SmallEqually::SmallEqually(Expression *left1, Expression *right1) {
    this->left = left1;
    this->right = right1;
}
//return 0 - for false 1 - for true
float SmallEqually::calculate() {
    return (this->left->calculate() <= this->right->calculate());
}
SmallEqually::~SmallEqually() {}


/**BigEqually method**/
BigEqually::BigEqually(Expression *left1, Expression *right1) {
    this->left = left1;
    this->right = right1;
}
//return 0 - for false 1 - for true
float BigEqually::calculate() {
    return (this->left->calculate() >= this->right->calculate());
}
BigEqually::~BigEqually() {}


/**Equal method**/
Equal::Equal(Expression *left1, Expression *right1) {
    this->left = left1;
    this->right = right1;
}
//return 0 - for false 1 - for true
float Equal::calculate() {
    return (this->left->calculate() == this->right->calculate());
}
Equal::~Equal() {}

/**Different method**/
Different::Different(Expression *left1, Expression *right1) {
    this->left = left1;
    this->right = right1;
}
//return 0 - for false,  1 - for true
float Different::calculate() {
    return (this->left->calculate()!= this->right->calculate());
}
Different::~Different() {}