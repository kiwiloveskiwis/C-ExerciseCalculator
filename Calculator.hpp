#ifndef Calculator_hpp
#define Calculator_hpp

#include <sstream>
#include <string>

#include "Operator.hpp"

class Calculator {
public:
    enum class ErrorType { OK, UnknownOperator, UnexpectedNumber } error = ErrorType::OK;
    int errorPos = -1;
    TNum result;
    constexpr Calculator(TNum previousResult = 0) : result(previousResult) { }
    bool calculate(std::string expr);
private:
    bool handleError(ErrorType type, std::istringstream &iss, const std::string &expr);
};

#endif /* Calculator_hpp */
