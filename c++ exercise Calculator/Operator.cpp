#include "Operator.hpp"

#include <cmath>

using namespace std;

Operator::Operator(const std::string name, int precedence) : name(name), precedence(precedence) { }
Operator1::Operator1(const string name, TNum (*const worker)(TNum)) : Operator(name, 0), worker(worker) { }
Operator2::Operator2(const string name, int precedence, TNum (*const worker)(TNum, TNum))
    : Operator(name, precedence), worker(worker) { }

void Operator::operate(stack<TNum> &numStack) const { }
void Operator1::operate(stack<TNum> &numStack) const {
  numStack.push(worker(popTop(numStack)));
}
void Operator2::operate(stack<TNum> &numStack) const {
  TNum rhs = popTop(numStack), lhs = popTop(numStack);
  numStack.push(worker(lhs, rhs));  // left & right hand side
}

const Operator *const Operator::bracket = new Operator("(");
map<const string, const Operator1*const> Operator1::operators {
#define OPERATOR1(name, result) { name, new Operator1(name, [](TNum num) { return result; }) }
    OPERATOR1("+", num),  // hey this unary operator does exactly nothing!
    OPERATOR1("-", -num),
    OPERATOR1("ln", log(num)),
    OPERATOR1("sin", sin(num)),
    OPERATOR1("cos", cos(num)),
    OPERATOR1("tan", tan(num)),
    OPERATOR1("sqrt", sqrt(num)),
    OPERATOR1("arctan", atan(num)),
    OPERATOR1("arccos", acos(num)),
    OPERATOR1("arcsin", asin(num)),
#undef OPERATOR1
};
map<const string, const Operator2*const> Operator2::operators {
#define OPERATOR2(name, precedence, result) \
         { name, new Operator2(name, precedence, [](TNum lhs, TNum rhs) { return result; }) }
    OPERATOR2("log", 1, log(rhs) / log(lhs)),
    OPERATOR2("^", 1, pow(lhs, rhs)),
    OPERATOR2("*", 2, lhs * rhs),
    OPERATOR2("/", 2, lhs / rhs),
    OPERATOR2("+", 3, lhs + rhs),
    OPERATOR2("-", 3, lhs - rhs),
    // equals to { "-", new Operator2("-", 3, [](TNum lhs, TNum rhs) { return lhs - rhs; }) }
#undef OPERATOR2
};
