#include "Calculator.hpp"

#include <algorithm>
#include <cassert>
#include <stack>

using namespace std;

map<const string, TNum> constNum {{"pi", M_PI}, {"e", M_E}};

bool Calculator::handleError(ErrorType type, istringstream &iss, const string &expr) {
    if (type == ErrorType::OK) return false;
    error = type;
    if ((errorPos = static_cast<int>(iss.tellg())) < 0)
        errorPos = static_cast<int>(expr.length()); // reach the end of the expression
    return true;
}

inline Calculator::ErrorType popOperator(stack<const Operator*> &opStack, stack<TNum> &numbers) {
    assert(numbers.size() >= 1);
    assert(!opStack.empty());
    const Operator *op = popTop(opStack);
    op->operate(numbers);
    return Calculator::ErrorType::OK;
}

bool Calculator::calculate(const string expr)  {
    istringstream iss(expr);
    stack<const Operator*> opStack;
    stack<TNum> numbers;
    iss >> noskipws;
#define THROW(err) do if (handleError(err, iss, expr)) return false; while (false)
#define POP_OPERATOR THROW(popOperator(opStack, numbers))
    bool unaryFlag = true;
    char c;
    while (iss >> c) {
        if (c == ' ') continue;
        if (isdigit(c) || c == '.') {
            iss.putback(c);
            TNum num;
            iss >> num;
            numbers.push(num);
            unaryFlag = false;
        } else if (isalpha(c)) {
            unaryFlag = true;
            string word(1, c);
            while (iss >> c && isalpha(c)) word += c;
            iss.putback(c);
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            if (word == "ans") {
                numbers.push(result);
                unaryFlag = false;
            } else if (constNum.count(word)) {
                numbers.push(constNum[word]);
                unaryFlag = false;
            }
            else if (Operator1::operators.count(word)) opStack.push(Operator1::operators[word]);
            else if (Operator2::operators.count(word)) opStack.push(Operator2::operators[word]);
            else THROW(ErrorType::UnknownOperator);
        } else if (c == '(') {
            opStack.push(Operator::bracket);    // precedence : max()
            unaryFlag = true;
        } else if (c == ')') {
            while (opStack.top()->name != "(") POP_OPERATOR;
            opStack.pop(); // pop the '('
            unaryFlag = false;
        } else {
            string op(1, c);
            if (!Operator1::operators.count(op) && !Operator2::operators.count(op)) THROW(ErrorType::UnknownOperator);
            if (unaryFlag) {
                while (!opStack.empty() && opStack.top()->precedence < Operator1::operators[op]->precedence)
                    POP_OPERATOR;
                opStack.push(Operator1::operators[op]);
            } else {
                while (!opStack.empty() && opStack.top()->precedence < Operator2::operators[op]->precedence)
                    POP_OPERATOR;
                opStack.push(Operator2::operators[op]);
            }
            unaryFlag = true;
        }
    }
    while (!opStack.empty()) POP_OPERATOR;
    if (numbers.size() != 1) {
        THROW(ErrorType::UnexpectedNumber);
        return false;
    }
    result = popTop(numbers);
    return true;
#undef POP_OPERATOR
#undef THROW
}
