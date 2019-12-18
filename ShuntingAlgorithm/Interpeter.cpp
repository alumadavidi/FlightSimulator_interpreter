//
// Created by magshimim on 12.12.2019.
//

#include "Interpeter.h"
#include "../Command/Command.h"


Interpreter::Interpreter() {
    //this->listVeriabels = new list<Variable*>;
//    this->mapVariable = (command::_progTable);
}
Interpreter::~Interpreter() {
    //free the variabels in the list
    /*if(this->listVeriabels != NULL){
        for( Variable* var: *listVeriabels){
            if (var != nullptr){
                delete var;
            }

        }
        if (listVeriabels != nullptr){
            delete listVeriabels;
        }

    }*/
}

void Interpreter::spliteToToken(string expression) {
    string newToken;
    string oneCharFromString, nextCharFromString;
    string currentToken, nextToken;
    bool insertOperator = false;
    for(unsigned int i = 0;i < expression.length(); i++) {
        if (i > 0) {
            if (expression[i - 1] == ')' && expression[i] == '(') {
                throw "Bad input";
            }
            if (expression[i - 1] == '/' && expression[i] == '-') {
                throw "Bad input";
            }
        }
        oneCharFromString = string() + expression[i];
        if(!oneCharFromString.compare(" ") == 0) {
            //add to token list
            if ((oneCharFromString).compare("(") == 0 || (oneCharFromString).compare(")") == 0
                || (oneCharFromString).compare("+") == 0 || (oneCharFromString).compare("-") == 0
                || (oneCharFromString).compare("*") == 0 || (oneCharFromString).compare("/") == 0) {
                pushNewTokenAndOperator(newToken, oneCharFromString);
            } else {
                if (i + 1 < expression.length()) {
                    nextCharFromString = string() + expression[i + 1];
                    if (((oneCharFromString).compare("!") == 0 && (nextCharFromString).compare("=") == 0)
                        || ((oneCharFromString).compare("<") == 0 && (nextCharFromString).compare("=") == 0)
                        || ((oneCharFromString).compare(">") == 0 && (nextCharFromString).compare("=") == 0)
                        || ((oneCharFromString).compare("=") == 0 && (nextCharFromString).compare("=") == 0)) {
                        i++;
                        oneCharFromString += nextCharFromString;
                        pushNewTokenAndOperator(newToken, oneCharFromString);
                        insertOperator = true;
                    }
                }
                if (!insertOperator && ((oneCharFromString).compare("<") == 0
                                        || (oneCharFromString).compare(">") == 0 ||
                                        (oneCharFromString).compare("=") == 0)) {
                    pushNewTokenAndOperator(newToken, oneCharFromString);
                } else if (!insertOperator) {
                    if (!newToken.empty()) {
                        (newToken).append(oneCharFromString);

                    } else {
                        newToken = oneCharFromString;

                    }
//                    if (i == expression.length() - 1) {
//                        this->tokens.push_back(newToken);
//                    }
                }
            }
        }
        if (i == expression.length() - 1) {
            if(newToken.length() > 0){
                this->tokens.push_back(newToken);
            }
        }

        insertOperator = false;
    }
    //replace value name in value double - map
    replaceNameInValue();
}
void Interpreter::pushNewTokenAndOperator(string & newToken, string& newOperator) {
    if (!newToken.empty()) {
        this->tokens.push_back(newToken);
        (newToken).clear();
    }
    this->tokens.push_back(newOperator);
}
void Interpreter::replaceNameInValue() {
    list<string>::iterator it;
    string token;
    bool findVeriableValue = false;

    if(!this->tokens.empty()) {
        for (it = this->tokens.begin(); it != this->tokens.end(); ++it) {
            token = *it;
            if (!isNumber(token) && !token.compare("(") == 0 && !token.compare(")") == 0
                && !token.compare("+") == 0 && !token.compare("-") == 0 && !token.compare("/") == 0
                && !token.compare("*") == 0 && !token.compare("<") == 0 && !token.compare(">") == 0
                && !token.compare("<=") == 0 && !token.compare(">=") == 0
                && !token.compare("==") == 0 && !token.compare("!=") == 0) {
                for (auto iter : *command::_progTable) {
                    if (iter.first.compare(token) == 0) {
                        // convert string to double
                        float num = iter.second.getValue();
                        std::ostringstream os;
                        os << num;
                        std::string str = os.str();
                        *it = str;
                        findVeriableValue = true;
                        break;
                    }
                    findVeriableValue = false;
                }
                if (!findVeriableValue) {
                    throw "Variable not initialized";

                }
            }
        }
    } else {
        throw "Variable not initialized - replaceNameInValue method";
    }
}
/*void Interpreter::setVariables(const string& inputString) {

    list<string>* subString = new list<string>;
    //split to one variable
    spliteByDemiliter(inputString, ";", subString);
    spliteVeriableToListVeriabels(subString);
}*/
void Interpreter::spliteByDemiliter(const string& inputString,
                                    const string& demiliter, list<string>* subString) {
    std::string stringInput = inputString;
    size_t pos = 0;
    while ((pos = stringInput.find(demiliter)) != std::string::npos) {
        (subString)->push_back(stringInput.substr(0, pos));
        stringInput.erase(0, pos + demiliter.length());
    }
    (subString)->push_back(stringInput.substr(0, pos));
}
/*void Interpreter::spliteVeriableToListVeriabels(list<string> *subString) {
    list<string>* oneVeriable;
    string::size_type sz;
    double num;
    string numStringEnd, numStringFront, firstStringFront;
    list<string>::iterator it;
    //add name value and it value to new Expression value.
    for(it = subString->begin(); it != subString->end(); ++it) {
        oneVeriable = new list<string>;
        spliteByDemiliter(*it, "=", oneVeriable);
        if(oneVeriable->size() == 2){
            numStringEnd = (oneVeriable->back());
            numStringFront = (oneVeriable->front());
            firstStringFront = numStringFront[0];
            if(isNumber(firstStringFront) || !isValidNameVariable(numStringFront)){
                throw "Invalid input 1";
            }
            if(isNumber(numStringEnd)) {
                //convert string to double
                num = std::stod(numStringEnd, &sz);
                //find if is there a Veriable with a similar name
                if(!isThereVeriableWithSameName(oneVeriable->front(), num)){
                    //add varieble to list
                    this->listVeriabels->push_back(new Variable(numStringFront, num));
                }
                if(oneVeriable != nullptr){
                    delete oneVeriable;
                }
            } else {
                throw "Invalid input 2";
            }
        } else{
            throw "Invalid input 3";
        }

    }

}*/
bool Interpreter::isValidNameVariable(const string & name) {
    bool valid = true;
    for(unsigned int i = 0; i < name.size(); i++){
        //check if A-Zaz-z and _
        if(!(isdigit(name[i]) || (name[i] <=90 && name[i] >=65)
             || (name[i] <=122 && name[i] >=97) || name[i] == 95)){
            valid = false;
            break;
        }
    }
    return valid;
}
/*bool Interpreter::isThereVeriableWithSameName(const string& name, double num) {
    //replace value in variable with same name
    bool isSameName = false;
    list<Variable*>::iterator it;
    Variable* var;

    for(it = this->listVeriabels->begin(); it != this->listVeriabels->end(); ++it) {
        var = *it;
        if(var->getValue().compare(name) == 0){
            isSameName = true;
            var->setNum(num);
            *it = var;
        }
    }
    return isSameName;
}*/
bool Interpreter::checkAndChangerightAssociativeOperator(string& token) {
    //check if the sign "+" or "-" is unary operator
    bool isAssociativeOperator = false;
    string prevToken;
    string currentOperator;
    if(!this->tokens.empty()){
        prevToken = token;
        currentOperator = this->tokens.front();
        if(!isNumber(prevToken) && prevToken.compare(")") != 0){
            if(this->tokens.front().compare("+") == 0){
                //currentOperator = ("p");
                this->tokens.front() = "p";
                isAssociativeOperator = true;
            } else if (this->tokens.front().compare("-") == 0){
                this->tokens.front() = "m";
                // currentOperator = "m";
                isAssociativeOperator = true;
            }
        }
    }

    return isAssociativeOperator;
}
void Interpreter::ShuntingAlgorithm() {
    string prevToken;
    if(!this->tokens.empty()){
        prevToken = this->tokens.front();
    }
    while(!this->tokens.empty()) {
        string oneToken = (tokens.front());
        //If it's a number add it to queue
        if(isNumber(oneToken)){
            (this->queueString).push(oneToken);

        } //If it's an operator
        else if(isOperator(oneToken)){
            //check if the operator is rightAssociative
            checkAndChangerightAssociativeOperator(prevToken);
            oneToken = (tokens.front());
            //oneToken = prevToken;
            //While there's an operator on the top of the stack with greater precedence:
            while(isOperatorOnTopSackWithGreaterPrecedence(oneToken) /*&& !rightAssociativeOperator*/){
                //Pop operators from the stack onto the output queue
                string stringFromStack = this->stackString.top();
                this->stackString.pop();
                this->queueString.push(stringFromStack);
            }
            //Push the current operator onto the stack
            this->stackString.push(oneToken);
        } //If it's a left bracket push it onto the stack
        else if(oneToken.compare("(") == 0) {
            this->stackString.push(oneToken);
            this->bracket.push(oneToken);
        } //If it's a right bracket
        else if(oneToken.compare(")") == 0){
            if (!bracket.empty()){
                bracket.pop();
            } else {
                throw "Invalid input - bracket";
            }
            //While there's not a left bracket at the top of the stack:
            while(!isThereLeftBracketOnTopStack()){
                //Pop operators from the stack onto the output queue
                popOperatorFromStackToQueue();
            }
            //Pop the left bracket from the stack and discard it
            this->stackString.pop();
        } else{
            throw "Invalid input in interpeter";
        }
        prevToken = tokens.front();
        tokens.pop_front();
    }
    if (!bracket.empty()){

        throw "Invalid input - bracket";
    }
    //While there are operators on the stack, pop them to the queue
    while(!this->stackString.empty()){
        popOperatorFromStackToQueue();
    }
    //delete bracket;
}
Expression* Interpreter::interpret(string expressionString) {
    spliteToToken(expressionString);
    ShuntingAlgorithm();
    Expression* exp = fromShuntingAlgorithmToExpression();
    return exp;
}
bool Interpreter::isNumber(const string & num) {
    //check if string is number
    bool isNum = true;
    bool isOnePoint = true;
    char charNum;
    if (num.size() == 0){
        isNum = false;
    }

    for (unsigned int i = 0; i < num.size(); i++) {
        charNum = num[i];
        if (!isdigit(charNum)) {
            if ((charNum == '-' && i != 0)) {
                isNum = false;
                break;
            } else if (charNum == '.' && (!isOnePoint || i==0)) {
                isNum = false;
                break;
            }
            if ((charNum == '.' && isOnePoint && i != 0)) {
                isOnePoint = false;
            } else if ((charNum == '.' && isOnePoint) || (charNum == '-' && i == 0)) {
                isNum = true;
            } else {
                isNum = false;
                break;
            }
        }
    }

    if(num.size() == 1){
        if(num.compare("-") == 0){
            isNum = false;
        }
    }

    return isNum;
}
bool Interpreter::isOperator(const string & token) {
    bool isTokenOperator = false;
    if(token.compare("+") == 0 || token.compare("-") == 0
       || token.compare("*") == 0|| token.compare("/") == 0
       || token.compare("<") == 0 || token.compare(">") == 0
       || token.compare("!=") == 0|| token.compare("==") == 0
       ||token.compare("<=") == 0 || token.compare(">=") == 0){
        isTokenOperator = true;
    }
    return isTokenOperator;
}
bool Interpreter::isAssociativeOperator(const string& token) {

    bool isTokenOperator = false;
    if(token.compare("m") == 0 || token.compare("p") == 0){
        isTokenOperator = true;
    }
    return isTokenOperator;
}
bool Interpreter::isOperatorOnTopSackWithGreaterPrecedence(string & token) {
    bool haveGreaterPrecedence = false;
    string stringFromStack;
    if(!stackString.empty()){
        stringFromStack = this->stackString.top();
        //when we want to insert + or -
        if((token.compare("+") == 0 || token.compare("-") == 0) &&
           (stringFromStack.compare("*") == 0 || stringFromStack.compare("/") == 0
            ||stringFromStack.compare("m") == 0
            || stringFromStack.compare("p") == 0 || stringFromStack.compare("<") == 0
            || stringFromStack.compare(">") == 0 ||stringFromStack.compare("==") == 0
            || stringFromStack.compare("<=") == 0 || stringFromStack.compare(">=") == 0
            || stringFromStack.compare("!=") == 0)){
            haveGreaterPrecedence = true;
        }
        //when we want to insert * or /
        if((token.compare("*") == 0 || token.compare("/") == 0) &&
           (stringFromStack.compare("m") == 0 || stringFromStack.compare("p") == 0
            || stringFromStack.compare("<") == 0 || stringFromStack.compare(">") == 0
            ||stringFromStack.compare("==") == 0 || stringFromStack.compare("<=") == 0
            || stringFromStack.compare(">=") == 0 || stringFromStack.compare("!=") == 0)){
            haveGreaterPrecedence = true;
        }
        if((token.compare("m") == 0 || token.compare("p") == 0) &&
           (stringFromStack.compare("<") == 0 || stringFromStack.compare(">") == 0
            ||stringFromStack.compare("==") == 0 || stringFromStack.compare("<=") == 0
            || stringFromStack.compare(">=") == 0 || stringFromStack.compare("!=") == 0)){
            haveGreaterPrecedence = true;
        }
    }
    return haveGreaterPrecedence;
}
bool Interpreter::isThereLeftBracketOnTopStack() {
    bool isThereLeftBracket = false;
    if(this->stackString.top().compare("(") == 0){
        isThereLeftBracket = true;
    }
    return isThereLeftBracket;
}
void Interpreter::popOperatorFromStackToQueue() {
    this->queueString.push(this->stackString.top());
    this->stackString.pop();
}

string Interpreter::popAndReturnElementFromQueue() {
    string frontElementInQueue;
    frontElementInQueue = this->queueString.front();
    this->queueString.pop();
    return frontElementInQueue;

}
void Interpreter::popExpFromQueueToStack() {
    string queueFront;
    while(!this->queueString.empty()){
        queueFront = (this->queueString.front());
        this->queueString.pop();
        this->stackString.push(queueFront);
    }
}
Expression* Interpreter::fromShuntingAlgorithmToExpression() {
    Expression* afterBuild;
    string frontElementInQueue;
    string::size_type sz;
    float num;
    if(this->queueString.size() == 1) { // one number at queue without operators
        num = stof(queueString.front());
        afterBuild = new Value(num);
        return afterBuild;
    }
    while(!this->queueString.empty()){
        while (isNumber(this->queueString.front())){
            frontElementInQueue = popAndReturnElementFromQueue();
            //convert string to float
            num = std::stof(frontElementInQueue.c_str());
            this->stackExpression.push((new Value(num)));
        }
        if (this->queueString.empty()){
            throw "Invalid input operator";
        }
        frontElementInQueue = popAndReturnElementFromQueue();
        if(isOperator(frontElementInQueue) || isAssociativeOperator(frontElementInQueue)){
            afterBuild = buildExpAcorrdingOperator(frontElementInQueue);
            this->stackExpression.push(afterBuild);
        }
    }
    return afterBuild;
}

Expression* Interpreter::topAndPopStackExpression() {
    Expression* topStack = (this->stackExpression.top());
    this->stackExpression.pop();
    return topStack;
}
Expression* Interpreter::buildExpAcorrdingOperator(const string& topStack) {
    if(!this->stackExpression.empty()) {
        Expression *exp;
        Expression *first = (topAndPopStackExpression());
        Expression *second;
        if (topStack.compare("+") == 0 || topStack.compare("-") == 0 ||
            topStack.compare("*") == 0 || topStack.compare("/") == 0
            ||topStack.compare("<") == 0 || topStack.compare(">") == 0
            ||topStack.compare("==") == 0 || topStack.compare("<=") == 0
            || topStack.compare(">=") == 0 || topStack.compare("!=") == 0) {
            if(!this->stackExpression.empty()) {
                second = (topAndPopStackExpression());
                if ((topStack).compare("+") == 0) {
                    exp = new Plus(second, first);
                } else if (topStack.compare("-") == 0) {
                    exp = new Minus(second, first);
                } else if (topStack.compare("*") == 0) {
                    exp = new Mul(second, first);
                } else if (topStack.compare("/") == 0) {
                    exp = new Div(second, first);
                } else if (topStack.compare("<") == 0) {
                    exp = new Smaller(second, first);
                } else if (topStack.compare(">") == 0) {
                    exp = new Bigger(second, first);
                } else if (topStack.compare("<=") == 0) {
                    exp = new SmallEqually(second, first);
                } else if (topStack.compare(">=") == 0) {
                    exp = new BigEqually(second, first);
                } else if (topStack.compare("==") == 0) {
                    exp = new Equal(second, first);
                } else if (topStack.compare("!=") == 0) {
                    exp = new Different(second, first);
                }
            } else {
                throw "Invalid input operator";
            }
        } else if(topStack.compare("m") == 0){
            exp = new UMinus(first);
        } else if(topStack.compare("p") == 0){
            exp = new UPlus(first);
        }
        return exp;
    } else {
        throw "Invalid operator input";
    }

}
string Interpreter::topAndPopStack() {
    string topStack = (this->stackString.top());
    this->stackString.pop();
    return topStack;
}
void Interpreter::printQueue() {
    while(!this->queueString.empty()){
        cout<<" "<<this->queueString.front();
        this->queueString.pop();
    }
    cout<<endl;
}


