#ifndef Calculator_hpp
#define Calculator_hpp

#include <sstream>
#include <stack>
#include <string>

#include "Operator.hpp"

class Calculator {
public:
    enum class ErrorType { OK, UnknownOperator, UnexpectedNumber };
private:
    std::stack<const Operator*> opStack;
    std::stack<TNum> numbers;
    std::string expr;
    std::istringstream iss;
    bool handleError(ErrorType type);
    ErrorType popOperator();
    void readInNumber();
    ErrorType readInAlpha(bool &unaryFlag);
public:
    TNum previousResult;
    Calculator(std::string s) : expr(s), iss(expr) { }
    bool calculate(TNum &result);
};

#endif /* Calculator_hpp */
