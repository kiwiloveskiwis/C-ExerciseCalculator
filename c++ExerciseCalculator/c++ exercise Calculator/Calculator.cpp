//
//  Calculator.cpp
//  算法练习2
//
//  Created by 卢以宁 on 5/21/16.
//  Copyright © 2016 卢以宁. All rights reserved.
//

#include "Calculator.hpp"
using ErrorType = Calculator::ErrorType;

template <typename T>
inline T popTop(stack<T> &stack) {
    T result = stack.top();
    stack.pop();
    return result;
}

bool Calculator:: handleError(ErrorType type) {
    if (!type) return false;
    int pos = static_cast<int>(iss.tellg());
    if (pos < 0) pos = expr.length(); // reach the end of the expression
    cerr << "Position " << pos << ": ";
    switch (type) {
        case ErrorType::DivisionByZero:
            cerr << "Division by zero";
            break;
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
    assert(!operators.empty());
    TNum result;
    char op = popTop(operators);
    if (op == 's' || op =='c' || op == 't' || op == 'l') {
        TNum a = popTop(numbers);
        ErrorType err = UnaryCalculateOnce(a, op, result);
    }
    else {
        assert(numbers.size() >= 2);
        TNum b = popTop(numbers), a = popTop(numbers);
        ErrorType err = binaryCalculateOnce(a, b, op, result);
        if (err) return err;
    }
    numbers.push(result);
    return ErrorType::OK;
}

ErrorType Calculator:: UnaryCalculateOnce(TNum a, char operatorName,TNum &result) {
    switch (operatorName) {
        case 's':
            result = sin(a);
            return ErrorType::OK;
        case 'c':
            result = cos(a);
            return ErrorType::OK;
        case 't':
            result = tan(a);
            return ErrorType::OK;
        case 'l': // natural logarithm
            result = log(a);
            return ErrorType::OK;
            
        default: return ErrorType::UnknownOperator;
    }
}

ErrorType Calculator:: binaryCalculateOnce(TNum a, TNum b, char operatorName, TNum &result) {
    
    switch (operatorName) {
        case '*':
            result = a * b;
            return ErrorType::OK;
        case '+':
            result = a + b;
            return ErrorType::OK;
        case '-':
            result = a - b;
            return ErrorType::OK;
        case '/':
            if (b == 0) return ErrorType::DivisionByZero;
            result = a / b;
            return ErrorType::OK;
        case '^':
            result = pow(a, b);
            return ErrorType::OK;
        case 'L':
            result = log(b) / log(a);
            return ErrorType::OK;
            
        default: return ErrorType::UnknownOperator;
    }
}

int Calculator::getWeight(char op) {
    switch (op) {
        case '*': case '/' : return 2;
        case '+': case '-' : return 1;
        case 's': case 'c' : case 't' :case 'l':case 'L':return 4;
        case '^': return 3;
        case '(': return 0;
        default: return -1; // Unknown operator
    }
}

void Calculator::readInNumber() {
    TNum a;
    iss >> a;
    numbers.push(a);
}

ErrorType Calculator::readInAlpha() {
    string word;
    char c;
    while (iss >>std::noskipws >> c && isalpha(c)) word += c;
    iss.putback(c);
    for (int i = 0;i < word.length(); i++)word[i] = tolower(word[i]);
    if (word == "pi") numbers.push(M_PI);
    else if (word == "e") numbers.push(M_E);
    else if (word == "ans") numbers.push(preresult);
    else if (word == "sin") operators.push('s');
    else if (word == "cos") operators.push('c');
    else if (word == "tan") operators.push('t');
    else if (word == "ln") operators.push('l');
    else if (word == "log" && isdigit(c)) {
        readInNumber();
        operators.push('L');
    } else {
        cout << word << ' ';
        return ErrorType::UnknownOperator;
    }
    return OK;
}


bool Calculator::calculate(TNum &result)  {
#define ERROR_HANDLER(call) if (handleError(call)) return false
    string tempNumber;
    bool firstMinusFlag = true;
    char c;
    while (iss >> c) {
        if (c == ' ') continue;
        // TODO: Remove the hack!!!1!!!! ARRRGHHGHGHGH IT'S UUNBEARRABLE!!!11 IT'S FRICKING KILLING MEEE ;_;
        // Awww ;_;
        if (c == '-' && firstMinusFlag) numbers.push(0); // Handle the case where '-' comes first
        firstMinusFlag = false;
        if (isdigit(c) || c == '.') {
            iss.putback(c);
            readInNumber();
        } else if (c == '(') {
            operators.push(c);
            firstMinusFlag = true;
        } else if (c == ')') {
            while (operators.top() != '(') ERROR_HANDLER(popOperator());
            operators.pop(); // pop the '('
        } else if (isalpha(c)) {
            iss.putback(c);
            ERROR_HANDLER(readInAlpha());
        } else {
            if (getWeight(c) == -1) ERROR_HANDLER(UnknownOperator);
            while (!operators.empty() && getWeight(operators.top()) >= getWeight(c))
                ERROR_HANDLER(popOperator());
            operators.push(c);
        }
    }
    while (!operators.empty()) ERROR_HANDLER(popOperator());
    assert(numbers.size() == 1);
    result = popTop(numbers);
    return true;
#undef ERROR_HANDLER
}
