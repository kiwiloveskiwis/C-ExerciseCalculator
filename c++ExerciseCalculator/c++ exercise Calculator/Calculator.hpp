//
//  Calculator.h
//  算法练习2
//
//  Created by 卢以宁 on 5/14/16.
//  Copyright © 2016 卢以宁. All rights reserved.
//

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
//#include "Operator.hpp"

using namespace std;

class Calculator {
private:
    stack<char> operators;
    stack<TNum> numbers;
    string expr;
    istringstream iss;
public:
    TNum preresult;
    Calculator(string s) : expr(s), iss(expr) { }
    enum ErrorType {OK, DivisionByZero, UnknownOperator, UnexpectedNumber };
    bool handleError(ErrorType type) ;
    ErrorType popOperator() ;
    ErrorType UnaryCalculateOnce(TNum a, char operatorName,TNum &result) ;
    ErrorType binaryCalculateOnce(TNum a, TNum b, char operatorName, TNum &result);
    int getWeight(char op) ;
    void readInNumber();
    ErrorType readInAlpha() ;    bool calculate(TNum &result);
};


#endif /* Calculator_hpp */
