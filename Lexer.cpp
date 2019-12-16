//
// Created by magshimim on 13.12.2019.
//

#include "Lexer.h"
using namespace std;
//get file name and parser it to token in vector<string>
void Lexer::lexerTheFile(vector<string>* wordsToken, string& nameOfFile) {
    //open text file
    ifstream ruleText;
    string fileName = "../" + string()+ nameOfFile;
    string lineToRead, word = "";
    ruleText.open(fileName, ios::in);
    if (!ruleText.is_open()) {
        throw "failed in open file - ruleText";
    } else {
        //parser line by line
        while (getline(ruleText, lineToRead)) {
            spliteLineToToken(wordsToken, lineToRead);
        }
    }
}
//splite line by letter
void Lexer::spliteLineToToken(vector<string>* wordsToken, string& lineToRead){
    string word = "";
    //parser letter by letter
    for (int i = 0; i < lineToRead.length(); i++) {
        if(lineToRead[i] == '('){
            addWordToVector(word, wordsToken);
            //if there "" - read until get the next ""
            if(lineToRead[i+1] == '"'){
                i++;
                word += "\"";
                i++;
                while(lineToRead[i] != '"'){
                    word += lineToRead[i];
                    i++;
                }
                i--;
            }
        }
        else if((lineToRead[i] == '{') || (lineToRead[i] == '}')) {
            addWordToVector(word, wordsToken);
            wordsToken->push_back(string()+lineToRead[i]);
        }
            // add prev word and splite by ) space and ,
        else if((lineToRead[i] == ')') || ((lineToRead[i] == ' '))
                || (lineToRead[i] == ',') || (lineToRead[i] == '\t')){
            addWordToVector(word, wordsToken);
        }
            // find -> or <- or !=
        else if(((lineToRead[i] == '-') && ((lineToRead[i+1] == '>')))
                || ((lineToRead[i] == '<') && (lineToRead[i+1] == '-'))
                || ((lineToRead[i] == '!') && (lineToRead[i+1] == '='))){
            addWordToVector(word, wordsToken);
            word = string()+lineToRead[i] + string()+lineToRead[i+1];
            wordsToken->push_back(word);
            i++;
            if(lineToRead[i] == '=') {
                if(lineToRead[i+1] == ' '){
                    i++;
                }
                //enter end of line to word
                word = lineToRead.substr(i+1, lineToRead.length());
                //check if there { at end of line
                openbracketTreatment(word, wordsToken);
                i = lineToRead.length();
            }
            word = "";
        }
        else if((lineToRead[i] == '=') || (lineToRead[i] == '<')
                || (lineToRead[i] == '>')){
            if(word.length() > 0) {
                //enter prev word to vector
                wordsToken->push_back(word);
            }
            word = lineToRead[i];
            if(lineToRead[i+1] == '='){
                i++;
                word += lineToRead[i];
            }
            //enter current word to vector : = or ==
            wordsToken->push_back(word);
            //enter end of line to word
            if(lineToRead[i+1] == ' '){
                i++;
            }
            word = lineToRead.substr(i+1, lineToRead.length());
            //check if there { at end of line
            openbracketTreatment(word, wordsToken);
            word = "";
            i = lineToRead.length();

        } else {
            word += lineToRead[i];
        }
    }
}
//add the word to vector and reset the word
void Lexer::addWordToVector(string& word , vector<string>* wordsToken) {
    if(word.length() > 0) {
        //enter new word to vector
        wordsToken->push_back(word);
        word = "";
    }
}
//check if there { at the end of line and splite by { if yes
void Lexer::openbracketTreatment(string& word, vector<string>* wordsToken) {
    if(word[word.length() - 1] == '{'){
        word = word.substr(0, word.length() - 1);
        wordsToken->push_back(word);
        wordsToken->push_back("{");

    } else{
        wordsToken->push_back(word);
    }
}