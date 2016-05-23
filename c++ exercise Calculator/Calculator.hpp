#ifndef Calculator_hpp
#define Calculator_hpp

#include <stack>
#include <sstream>
#include <string>

#include "Operator.hpp"

using namespace std;

class Calculator {
public:
    enum ErrorType { OK, DivisionByZero, UnknownOperator, UnexpectedNumber };
private:
    stack<const Operator*> opStack;
    stack<TNum> numbers;
    string expr;
    istringstream iss;
    bool handleError(ErrorType type);
    ErrorType popOperator();
    int getWeight(char op);
    void readInNumber();
    ErrorType readInAlpha(bool &unaryFlag);
public:
    TNum previousResult;
    Calculator(string s) : expr(s), iss(expr) { }
    bool calculate(TNum &result);
};

#endif /* Calculator_hpp */
