//
// Created by magshimim on 12.12.2019.
//
#pragma once
#ifndef UNTITLED_INTERPETER_H
#define UNTITLED_INTERPETER_H
#include <sstream>
#include <algorithm>
#include <list>
#include <stack>
#include <queue>
#include <string>
#include "map"
#include "iostream"
#include "Expression.h"
#include "BasicVar.h"
#include "BinaryOperators.h"
#include "UnaryOperators.h"
#include "ProgVariables.h"
#include <unordered_map>
using namespace std;

class Interpreter {
private:
    list<string> tokens;
    stack <string> stackString;
    stack<Expression*> stackExpression;
    stack<string> bracket;
    queue<string> queueString;
    //list<ProgVariables*>* listVeriabels;

public:
    Interpreter();
    ~Interpreter();
    void setListVeriabels(list<ProgVariables *> *listVeriabels);
    void spliteToToken(string);
    //void spliteSetVeriable(const string&);
    void spliteByDemiliter(const string& inputString,
                           const string&, list<string>* subString);
    void spliteVeriableToListVeriabels(list<string>* subString);
    Expression* interpret(string);
    bool isNumber(const string&);
    bool isOperator(const string&);
    bool isOperatorOnTopSackWithGreaterPrecedence(string & token);
    bool isThereLeftBracketOnTopStack();
    void popOperatorFromStackToQueue();
    void ShuntingAlgorithm();
    void popExpFromQueueToStack();
    Expression* fromShuntingAlgorithmToExpression();
    Expression* buildExpAcorrdingOperator(const string&);
    string popAndReturnElementFromQueue();
    string topAndPopStack();
    Expression* topAndPopStackExpression();
    void printQueue();
    void setVariables(const string&);
    bool isThereVeriableWithSameName(const string&, double num);
    void replaceNameInValue();
    bool checkAndChangerightAssociativeOperator(string&);
    bool isAssociativeOperator(const string&);
    bool isValidNameVariable(const string&);
    void pushNewTokenAndOperator(string&, string&);
};
#endif //UNTITLED_INTERPETER_H
