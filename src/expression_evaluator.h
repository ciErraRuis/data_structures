//
// Created by cierra on 2024/12/18.
//

#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include <stack>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <utility>
#include <map>

bool LOG = false;

void Log(std::string msg) {
    if (!LOG)
        return;
    std::cout << msg << std::endl;
}

inline void remove_space(std::string& str) {
    std::string::iterator end_pos = std::remove(str.begin(), str.end(), ' ');
    str.erase(end_pos, str.end());
}

class Expression {
public:
    Expression();
    Expression(std::string str);
    ~Expression() {};
    bool eval();
    long double get_result();
protected:
    long double result;
    std::string expression;
    std::map<char, int> level;
    std::stack<char> ops;
    std::stack<long double> nums;
    int curr_idx;
    bool isDigit(char c);
    bool isOperator(char c);
    bool _is_valid_index(int i);
    bool _get_int(int& i, int& ret);
    bool _get_float(int& i, long double& ret);
    bool _get_scientific_exp(int& i, int& ret);
    int _compose_num(int& i, long double& result);
    void _calc();
};

inline bool Expression::isDigit(char c) {
    return c >= '0' && c <= '9';
}

inline bool Expression::isOperator(char c) {
    return level.count(c);
}
//remove all spaces first for convenience
Expression::Expression(std::string str) {
    //add rules to level
    level['+'] = 1;
    level['-'] = 1;
    level['*'] = 2;
    level['/'] = 2;

    //initialize stack
    ops = std::stack<char>();
    nums = std::stack<long double>();
    curr_idx = 0;

    //preprocess the expression
    this->expression = std::move(str);
    remove_space(expression);
}

Expression::Expression():Expression("") {}


bool Expression::_is_valid_index(int i) {
    return !(i < 0 || i >= expression.size() || !isDigit(expression[i]));
}

bool Expression::_get_int(int& i, int& ret) {
    if (!_is_valid_index(i)) {
        Log("get_int: invalid index");
        return false;
    }
    char c = expression[i];
    ret = c - '0';
    while (i + 1 < expression.size() && isDigit(expression[i + 1])) {
        ret = ret * 10 + (expression[++i] - '0');
    }
    return true;
}

bool Expression::_get_float(int& i, long double& ret) {
    ret = 0.0;
    if (!_is_valid_index(i)) {
        i--;
        ret = 0.0;
        return true;
    }
    int exp = 1;
    while (i < expression.size()) {
        //the next is operator
        if (!isDigit(expression[i])) {
            i--;
            break;
        }
        ret += (expression[i] - '0') * std::pow(10, -(exp++));
        i += 1;
    }
    return true;
}

bool Expression::_get_scientific_exp(int& i, int& ret) {
    if (expression[i-1] != 'e') {
        Log("get_float: invalid index");
        return false;
    }
    int sci_exp = 0;
    int sign = 1;
    if (expression[i] == '-' && isDigit(expression[i+1])) {
        sign = -1;
        i = i + 1;
    } else if (isDigit(expression[i])) {
       i = i;
    } else {
        Log("compose_num: invalid scientific notation: char(s) right after 'e' is invalid");
        return false;
    }

    if (!_get_int(i, sci_exp)) {
        Log("Scientific notation: fail to get exp.");
        return false;
    }
    ret = sign * sci_exp;
    return true;
}

// return the valid number or raise an error. Move the index passed in as well.
int Expression::_compose_num(int& i, long double& result) {
    //assure start with a digit
    long double dtemp = 0.0;
    int itemp = 0;
    if (!_is_valid_index(i)) {
        Log("compose_num: get invalid index");
        return -1;
    }
    // start from the given index, get the
    result = 0.0;
    if (isDigit(expression[i])) {
        if (!_get_int(i, itemp)) {
            Log("compose_num: negative number got. Please check.");
            return false;
        }
        result += itemp;
    }

    //<num>.<num> -> float
    if (expression[i+1] == '.') {
        i += 2;
        //add the float part
        if (!_get_float(i, dtemp)) {
            Log("Something is wrong with _get_float.");
            return false;
        }
        result = result + dtemp;
    }
    //scientific. <num>e<int>
    if (expression[i+1] == 'e') {
        i += 2;
        if (result >= 10) {
            Log("invalid scientific notation: base part >= 10.");
            return false;
        }
        if (!_get_scientific_exp(i, itemp)) {
            Log("Something is wrong with _get_scientific.");
            return false;
        }
        result = result * std::pow(10, itemp);
        if (i < expression.size() && expression[i] == '.') {
            Log("invalid scientific notation: number after e with decimal");
            return false;
        }
    }

    return true;
}

void Expression::_calc() {
    if (nums.empty() || nums.size() < 2) return;
    if (ops.empty()) return;
    long double b = nums.top();
    nums.pop();
    long double a = nums.top();
    nums.pop();
    char op = ops.top();
    ops.pop();
    long double ans = 0;
    if (op == '+') ans = a + b;
    else if (op == '-') ans = a - b;
    else if (op == '*') ans = a * b;
    else if (op == '/')  ans = a / b;
    nums.push(ans);
}

bool Expression::eval() {
    if (expression.empty()) {
        std::cout << "Empty expression." << std::endl;
        return false;
    }
    if (isOperator(expression[0])) {
        if (expression[0] != '-') {
            Log("Operator can't be placed the first.");
            return false;
        } else {
            nums.push(0);
            ops.push('+');
        }
    }
    int brac_cnt = 0;
    nums.push(0);
    int sign = 1;
    for (int i = 0; i < expression.size(); i++) {
        char c = expression[i];
        if (c == '(') {
            ops.push(c);
            brac_cnt++;
        } else if (c == ')') {
            if (brac_cnt == 0) {
                Log("eval: bracket not match (')' appears before a '(')");
                return false;
            }
            brac_cnt--;
            while (!ops.empty()) {
                if (ops.top() != '(') {
                    _calc();
                } else {
                    ops.pop();
                    break;
                }
            }
        } else if (isDigit(c)) {
            long double temp;
            if (!_compose_num(i, temp)) {
                Log("eval: something wrong when reading nums. Stop at " + c);
                return false;
            }
            if (i + 1 < expression.size() && brac_cnt <= 0 && !isOperator(expression[i+1])) {
                Log("_compose_num: must a operator after the operand.");
                return false;
            }
            nums.push(temp * sign);
            sign = 1;
        } else if (isOperator(c)){
            //valid operators which are defined when initialize.
            //add  one '0' first if at the front of (
            if (isOperator(expression[i-1])) {
                if (c != '-') {
                    Log("consecutive operators not allowed.");
                    return false;
                } else {
                    sign *= -1;
                    continue;
                }
            } else if (i > 0 && (expression[i-1] == '('))
                nums.push(0);
            while (!ops.empty() && ops.top() != '(') {
                char prev = ops.top();
                if (level[prev] >= level[c]) _calc();
                else break;
            }
            ops.push(c);
        } else {
            Log("Invalid operator: " + expression[i]);
            return false;
        }
    }
    if  (brac_cnt != 0) {
        return false;
    }
    while (!ops.empty())
        _calc();
    result = nums.top();
    return true;
}

long double Expression::get_result() {
    return result;
}
#endif //EXPRESSION_EVALUATOR_H
