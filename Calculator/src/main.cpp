//
// Created by cierra on 2024/12/20.
//
#include <string>
#include <iostream>
#include "expression_evaluator.h"

int main() {
    while (1) {
        std::string expr;
        std::cout << "Enter expression: ";
        std::getline(std::cin, expr);
        Expression calculator(expr);
        if (calculator.eval()) {
            std::cout << "Result: " << calculator.get_result() << std::endl;
        } else {
            std::cout << "Illegal" << std::endl;
        }
    }
}