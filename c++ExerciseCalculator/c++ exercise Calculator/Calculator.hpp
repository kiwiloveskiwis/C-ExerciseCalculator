#ifndef Calculator_hpp
#define Calculator_hpp
#define TNum long double

#include <cctype>
#include <iostream>
#include <map>
#include <stack>
#include <cassert>
#include <cmath>
#include <string>
#include <sstream>
#include "Operator.hpp"

using namespace std;

class Calculator {
private:
    stack<const Operator*> opStack;
    stack<TNum> numbers;
    string expr;
    istringstream iss;
public:
    TNum preresult;
    Calculator(string s) : expr(s), iss(expr) { }
    enum ErrorType {OK, DivisionByZero, UnknownOperator, UnexpectedNumber };
    bool handleError(ErrorType type) ;
    ErrorType popOperator() ;
    int getWeight(char op) ;
    void readInNumber();
    ErrorType readInAlpha(bool &unaryFlag) ;
    bool calculate(TNum &result);
};

#endif /* Calculator_hpp */
