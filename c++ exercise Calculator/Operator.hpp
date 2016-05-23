#ifndef Operator_hpp
#define Operator_hpp

#include <stdio.h>
#include <cassert>
#include <cmath>
#include <limits>
#include <map>
#include <stack>
#include <string>
using namespace std;
#define TNum long double

template <typename T>
inline T popTop(stack<T> &stack) {
    T result = stack.top();
    stack.pop();
    return result;
}

class Operator {
private:
protected:
    Operator(const string name, int precedence = numeric_limits<int>::max()) : name(name), precedence(precedence){ }
public:
    const string name;
    const int precedence;
    virtual void operate(stack<TNum> &numStack) const { }
    
    static const Operator *const bracket;
};

class Operator1: public Operator {
private:
    TNum(*const worker) (TNum);
protected:
    Operator1(const string name, TNum (*const worker)(TNum)):Operator(name, 0),worker(worker){ }
public:
    virtual void operate(stack<TNum> &numStack) const {
        numStack.push(worker(popTop(numStack)));
    }
    static map<const string, const Operator1* const> operators;
};


class Operator2:public Operator {
private:
    TNum(*const worker) (TNum, TNum);
protected:
    Operator2(const string name, const int precedence, TNum (*const worker)(TNum, TNum)):Operator(name, precedence), worker(worker){ }
public:
    virtual void operate(stack<TNum> &numStack) const {
        TNum rhs = popTop(numStack), lhs = popTop(numStack);
        numStack.push(worker(lhs, rhs)); //left&right hand size
    }
    static map<const string, const Operator2* const> operators;
};


#endif /* Operator_hpp */
