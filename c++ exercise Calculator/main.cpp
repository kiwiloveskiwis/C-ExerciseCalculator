#include <cmath>
#include <iostream>

#include "Calculator.hpp"

using namespace std;

int main() {
    string s;
    TNum previousResult = 0;
    while (getline(cin, s)) {
        long double result;
        Calculator calculator(s);
        calculator.previousResult = previousResult;
        if (calculator.calculate(result)) {
            cout << "Result: " ;
            if (abs(result - round(result)) < 1e-8) cout << round(result) << endl;
            else cout << result << endl;
        }
        previousResult = result;
    }
    return 0;
}
