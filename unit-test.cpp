#include <cassert>
#include <cmath>
#include <iostream>
#include <string>

#include "Calculator.hpp"

using namespace std;

Calculator calc;

void test(string expr, TNum val, int line) {
    if (!calc.calculate(expr)) {
        cerr << "Test line #" << line << " has failed with error #" << static_cast<int>(calc.error) << " at column " << calc.errorPos << endl;
        exit(1);
    }
    if (abs(calc.result - val) > 1e-8) {
        cerr << "Test line #" << line << " has failed with unexpected result " << calc.result << ". Expected output: " << val << endl;
        exit(1);
    }
}
void testFail(string expr, Calculator::ErrorType err, int column, int line) {
    if (calc.calculate(expr)) {
        cerr << "TestFail line #" << line << " has failed with result " << calc.result << endl;
        exit(1);
    }
    if (calc.error != err || calc.errorPos != column) {
        cerr << "TestFail line #" << line << " has failed with error #" << static_cast<int>(calc.error) << " at column " << calc.errorPos
             << ". Expected error #" << static_cast<int>(err) << " at column " << column << endl;
        exit(1);
    }
}

#define TEST(expr, val) test(expr, val, __LINE__)
#define TEST_FAIL(expr, val, column) testFail(expr, val, column, __LINE__)

int main() {
    TEST("3+3", 6);
    TEST("sin(pi)", 0);
    TEST("ans", 0);
    TEST_FAIL("1%3", Calculator::ErrorType::UnknownOperator, 2);
    cout << "Unit test has passed. :-)" << endl;
    return 0;
}

