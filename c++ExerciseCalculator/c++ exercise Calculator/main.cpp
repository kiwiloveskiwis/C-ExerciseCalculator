#include <iostream>
#include <string>
#include "Calculator.hpp"
#include "Operator.hpp"
using namespace std;

int main() {
    string s;
    long double preresult = 0;
    while (getline(cin, s)) {
        long double result;
        Calculator calculator(s);
        calculator.preresult = preresult;
        if (calculator.calculate(result)) cout << "Result: " << result << endl;
        preresult = result;
    }
    return 0;
}
