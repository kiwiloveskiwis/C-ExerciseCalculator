#include <iostream>
#include <string>
#include "Calculator.hpp"

using namespace std;

int main() {
    string s;
    long double preresult = 0;
    while (getline(cin, s)) {
        long double result;
        Calculator calculator(s);
        calculator.preresult = preresult;
        if (calculator.calculate(result)) {
            cout << "Result: " ;
            if (result - (long int)result < 1e-8) cout<< (long int)result<<endl;
            else cout << result << endl;
        }
        preresult = result;
    }
    return 0;
}
