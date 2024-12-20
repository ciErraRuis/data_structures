#include <iostream>
#include <string>
#include <vector>
#include <utility> // for std::pair
#include <cmath>   // for std::abs
#include <cstdlib>
#include "expression_evaluator.h"

// 定义一个误差允许范围（用于浮点数比较）
const double EPSILON = 1e-9;

// long double random_double(long double min=0.0, long double max=1.0) {
//     std::random_device rd;  // 用于生成种子
//     std::mt19937 gen(rd()); // 随机数引擎，使用 Mersenne Twister 算法
//     std::uniform_real_distribution<double> dis(min, max); // [0.0, 1.0] 范围内的均匀分布
//
//     // 生成随机 double 数
//     double randomValue = dis(gen);
//     return randomValue;
// }

// 测试函数
void testLegal() {
    // 测试用例列表，包含表达式和预期结果
    std::vector<std::pair<std::string, double>> testCases = {
        // 单数字
        {"1*--2", 2},
        {"-3", -3},

        // 基本运算符 + 负号合法
        {"7+2", 9},
        {"15-6", 9},
        {"8*3", 24},
        {"20/4", 5},
        {"5 + -2", 3},
        {"-5 - 3", -8},
        {"4*-2", -8},
        {"9/-3", -3},
        {"---2", -2},
        {"1----2", 3},
        {"1 * --2", 2},
        // 括号
        {"(2+3)*4", 20},
        {"(7-2)/(3+2)", 1},
        {"10/(2+3)", 2},
        {"(4+6)*(3-1)", 20},
        {"(5-3)*2+1", 5},
        {"((-2+3)*4)/2", 2},

        // 浮点数
        {"3.5 + 2.1", 5.6},
        {"7.2 - 5.1", 2.1},
        {"1.5 * 4.0", 6.0},
        {"8.4 / 2.0", 4.2},
        {"(3.1+2.9)*2.0", 12.0},
        {"((2.5-1.5)+3.0)/2.0", 2.0},

        // 科学计数法
        {"1e3", 1000},
        {"5e-2", 0.05},
        {"2.5e1", 25},
        {"1.2e3+1e2", 1300},
        {"1e-3-5e-4", 0.0005},
        {"2.5e2 * 4e-1", 100},
        {"1e2 / 2.5e1", 4},

        // 综合测试
        {"3+4*2/(1-5)", 1},
        {"(3+4)*(2-5)/2", -10.5},
        {"((2.6+3.4)*2.0)/(5-3)", 6.0},
        {"1.1e3 + (2.5e1 * 4e-1)", 1100 + 10},
        {"((3.6 / 1.24) + 0.123) * 3213.1", 9723.566138709679},
    };


    int passed = 0;
    int failed = 0;

    for (const auto& testCase : testCases) {
        const std::string& expression = testCase.first;
        Expression exp(expression);
        try {
            if (exp.eval()) {
                double result = exp.get_result();
                double expected = testCase.second;
                if (std::abs(result - expected) < EPSILON) {
                    ++passed;
                } else {
                    std::cout << "FAIL: " << expression << " (Expected: " << expected << ", Got: " << result << ")" << std::endl;
                    ++failed;
                }
            } else {
                std::cout << "FAIL: " << expression << " is legal but is deemed illegal."<< std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "ERROR: " << expression << " threw an exception: " << e.what() << std::endl;
            ++failed;
        } catch (...) {
            std::cout << "ERROR: " << expression << " threw an unknown exception." << std::endl;
            ++failed;
        }
    }

    std::cout << "\nSummary: " << passed << " passed, " << failed << " failed." << std::endl;
}

void testIllegal() {
    std::vector<std::string> testCases = {
        //连续符号
        {"2 ++ 3"},
        {"2+*3"},
        //符号在开头
        {"+2+1"},
        {"*2"},
        {"/2+1"},
        //括号不匹配
        {"((2)"},
        {"2 + (1 - 3))"},
        {"2 (+1 / 2))"},
        {"2 + ((1 ) / 2"},
        {"2 + )(2)"},
        {"2(3 + 1)"},
        //非法科学计数
        {"11e2"},
        {"1e-2.2"}

    };

    int passed = 0;
    int failed = 0;

    for (const auto& testCase : testCases) {
        const std::string& expression = testCase;
        Expression exp(expression);
        try {
            if (!exp.eval()) {
                // std::cout << "PASS: " << expression << " is illegal." << std::endl;
                ++passed;
            } else {
                    std::cout << "FAIL: " << expression << " is illegal but get " << exp.get_result() << std::endl;
                    ++failed;
            }
        } catch (const std::exception& e) {
            std::cout << "ERROR: " << expression << " threw an exception: " << e.what() << std::endl;
            ++failed;
        } catch (...) {
            std::cout << "ERROR: " << expression << " threw an unknown exception." << std::endl;
            ++failed;
        }
    }

    std::cout << "\nSummary: " << passed << " passed, " << failed << " failed." << std::endl;
}

void  runTests() {
    std::cout << "Testing legal expressions..." << std::endl;
    testLegal();
    std::cout << "Testing illegal expressions..." << std::endl;
    testIllegal();
}

int main() {
    runTests();
    return 0;
}
