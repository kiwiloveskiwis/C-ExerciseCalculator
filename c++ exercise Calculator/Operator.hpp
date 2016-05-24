#ifndef Operator_hpp
#define Operator_hpp

#include <limits>
#include <map>
#include <string>

#include "utils.hpp"

class Operator {
protected:
    Operator(const std::string name, int precedence = std::numeric_limits<int>::max());
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
    Operator1(const std::string name, TNum (*const worker)(TNum));
public:
    virtual void operate(std::stack<TNum> &numStack) const;
    static std::map<const std::string, const Operator1* const> operators;
};

class Operator2 : public Operator {
private:
    TNum (*const worker)(TNum, TNum);
protected:
    Operator2(const std::string name, int precedence, TNum (*const worker)(TNum, TNum));
public:
    virtual void operate(std::stack<TNum> &numStack) const;
    static std::map<const std::string, const Operator2* const> operators;
};

#endif /* Operator_hpp */
