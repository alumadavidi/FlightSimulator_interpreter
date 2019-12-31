//
// Created by magshimim on 13.12.2019.
//
#pragma once
#ifndef UNTITLED11_PARSER_H
#define UNTITLED11_PARSER_H
#include "Lexer.h"
#include "Command.h"
#include "CommandsClasses.h"
#include "Interpeter.h"
#include "ClientCommand.h"
#include "Data.h"
class Parser {
public:
    void parser(string&);
    void parserByTokens(vector<string>& tokens);
    int updateVar();
    static float generalShuntingAlgorithem(const string&);
    static void updateValueInShuntingAlgo(const string&, const string&);
};
#endif //UNTITLED11_PARSER_H
