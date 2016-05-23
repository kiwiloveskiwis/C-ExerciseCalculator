#include "Calculator.hpp"

#include <iostream>
#include <cctype>
#include <map>
#include <cassert>
#include <cmath>

map<const string, TNum> constNum {{"pi", M_PI}, {"e", M_E}};

using ErrorType = Calculator::ErrorType;

bool Calculator:: handleError(ErrorType type) {
    if (!type) return false;
    int pos = static_cast<int>(iss.tellg());
    if (pos < 0) pos = expr.length(); // reach the end of the expression
    cerr << "Position " << pos << ": ";
    switch (type) {
        case ErrorType::UnexpectedNumber:
            cerr << "Unexpected number";
            break;
        case ErrorType::UnknownOperator:
            cerr << "Unknown operator";
            break;
        default:
            cerr << "Unknown error";
            break;
    }
    cerr << endl;
    return true;
}

ErrorType Calculator::popOperator() {
    assert(numbers.size() >= 1);
    assert(!opStack.empty());
    const Operator *op = popTop(opStack);
    op->operate(numbers);
    return ErrorType::OK;
}

void Calculator::readInNumber() {
    TNum a;
    iss >> a;
    numbers.push(a);
}

ErrorType Calculator::readInAlpha(bool &unaryFlag) {
    unaryFlag = true;
    string word;
    char c;
    while (iss >> std::noskipws >> c && isalpha(c)) word += c;
    iss.putback(c);
    for (int i = 0; i < word.length(); i++) word[i] = tolower(word[i]);
    if (word == "ans") {
        numbers.push(previousResult);
        unaryFlag = false;
    } else if (constNum.count(word) != 0) {
        numbers.push(constNum[word]);
        unaryFlag = false;
    }
    else if (Operator1::operators.count(word) != 0) opStack.push(Operator1::operators[word]);
    else if (Operator2::operators.count(word) != 0) {
        readInNumber();
        opStack.push(Operator2::operators[word]);
    } else return ErrorType::UnknownOperator;
    return ErrorType::OK;
}

bool Calculator::calculate(TNum &result)  {
#define ERROR_HANDLER(call) if (handleError(call)) return false
    string tempNumber;
    bool unaryFlag = true;
    char c;
    while (iss >> c) {
        if (c == ' ') continue;
        if (isdigit(c) || c == '.') {
            iss.putback(c);
            readInNumber();
            unaryFlag = false;
        } else if (isalpha(c)) {
            iss.putback(c);
            ERROR_HANDLER(readInAlpha(unaryFlag));
        } else if (c == '(') {
            opStack.push(Operator::bracket);    // precedence : max()
            unaryFlag = true;
        } else if (c == ')') {
            while (opStack.top()->name != "(") ERROR_HANDLER(popOperator());
            opStack.pop(); // pop the '('
            unaryFlag = false;
        } else {
            string op(1, c);
            if (!Operator1::operators.count(op) && !Operator2::operators.count(op))
                ERROR_HANDLER(UnknownOperator);
            if (unaryFlag) {
                while (!opStack.empty() && opStack.top()->precedence < Operator1::operators[op]->precedence)
                    ERROR_HANDLER(popOperator());
                opStack.push(Operator1::operators[op]);
            } else {
                while (!opStack.empty() && opStack.top()->precedence < Operator2::operators[op]->precedence)
                    ERROR_HANDLER(popOperator());
                opStack.push(Operator2::operators[op]);
            }
            unaryFlag = true;
        }
    }
    while (!opStack.empty()) ERROR_HANDLER(popOperator());
    if (numbers.size() != 1) {
        handleError(UnexpectedNumber);
        return false;
    }
    result = popTop(numbers);
    return true;
#undef ERROR_HANDLER
}
