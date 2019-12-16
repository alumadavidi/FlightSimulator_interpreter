//
// Created by magshimim on 13.12.2019.
//
#pragma once
#ifndef UNTITLED11_LEXER_H
#define UNTITLED11_LEXER_H
#include <vector>
#include <string>
#include <fstream>
using namespace std;
class Lexer{
public:
    void lexerTheFile(vector<string>*, string&);
    void addWordToVector(string&, vector<string>*);
    void spliteLineToToken(vector<string>*, string&);
    void openbracketTreatment(string&, vector<string>*);

};
#endif //UNTITLED11_LEXER_H
