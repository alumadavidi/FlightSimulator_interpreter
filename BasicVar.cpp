//
// Class for basic var to expression.
//

#include "BasicVar.h"

float Value::calculate() {
    return this->value;
}
Value::~Value() {}

Variable::Variable(string name1, float value1) {
    this->name = name1;
    this->value = value1;
}

Variable& Variable::operator++() {
    this->value = this->value + 1;
    return *this;

}
Variable& Variable::operator--() {
    this->value = this->value - 1;
    return *this;
}
Variable& Variable::operator+=(float num) {
    this->value = this->value + num;
    return *this;
}
Variable& Variable::operator-=(float num) {
    this->value = this->value - num;
    return *this;
}
Variable& Variable::operator++(int) {
    this->value = this->value + 1;
    return *this;
}
Variable& Variable::operator--(int) {
    this->value = this->value - 1;
    return *this;
}
float Variable::calculate() {
    return this->value;
}
float Variable::getNum() {
    return this->value;
}
string Variable::getValue() {
    return this->name;
}
void Variable::setNum(float num) {
    this->value = num;
}
void Variable::setValue(string & newName) {
    this->name = newName;
}
Variable::~Variable()  {

}