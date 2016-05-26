#ifndef Operator_hpp
#define Operator_hpp

#include <limits>
#include <map>
#include <string>

#include "utils.hpp"

class Operator {
protected:
    Operator(std::string name, int precedence = std::numeric_limits<int>::max());
public:
    const std::string name;
    const int precedence;
    virtual void operate(std::stack<TNum> &numStack) const;
    
    static const Operator *const bracket;
};

class Operator1 : public Operator {
private:
    TNum (*const worker)(TNum);
protected:
    Operator1(std::string name, TNum (*worker)(TNum));
public:
    virtual void operate(std::stack<TNum> &numStack) const;
    static std::map<std::string, const Operator1*> operators;
};

class Operator2 : public Operator {
private:
    TNum (*const worker)(TNum, TNum);
protected:
    Operator2(std::string name, int precedence, TNum (*worker)(TNum, TNum));
public:
    virtual void operate(std::stack<TNum> &numStack) const;
    static std::map<std::string, const Operator2*> operators;
};

#endif /* Operator_hpp */
