#include <cmath>
#include <iostream>

#include "Calculator.hpp"

using namespace std;

int main() {
    string s;
    Calculator calculator;
    while (getline(cin, s)) {
        if (calculator.calculate(s)) {
            TNum roundedResult = round(calculator.result);
            cout << "Result: "
                 << (abs(calculator.result - roundedResult) < 1e-8 ? roundedResult : calculator.result) << endl;
        } else {
            cerr << "Position " << calculator.errorPos << ": ";
            switch (calculator.error) {
                case Calculator::ErrorType::UnexpectedNumber:
                    cerr << "Unexpected number";
                    break;
                case Calculator::ErrorType::UnknownOperator:
                    cerr << "Unknown operator";
                    break;
                default:
                    cerr << "Unknown error";
                    break;
            }
            cerr << endl;
        }
    }
    return 0;
}
