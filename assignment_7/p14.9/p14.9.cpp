/**
 * Assignment 7 - 14.9
 *
 * This program converts standard math expressions to Reverse Polish Notation (RPN).
 *
 * @author JJ Hoffmann
 * @version 2024-05-08
*/

#include <iostream>
#include <stack>
#include <string>
#include <sstream>

/**
 * Checks if a character is an operator.
 * 
 * @param c The character to check.
 * @return True if the character is an operator, false otherwise.
 */
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

/**
 * Gets the precedence of an operator.
 * 
 * @param op The operator to check.
 * @return The precedence of the operator.
 */
int getPrecedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

/**
 * Converts a standard math expression to Reverse Polish Notation (RPN).
 * 
 * @param expression The math expression to convert.
 * @return The expression in RPN.
 */
std::string convertToRPN(const std::string& expression) {
    std::stack<char> operators;
    std::stringstream rpn;
    std::stringstream numberBuffer;

    for (char c : expression) {
        if (std::isdigit(c)) {
            numberBuffer << c;
        } else {
            if (!numberBuffer.str().empty()) {
                rpn << numberBuffer.str() << " ";
                numberBuffer.str("");
            }

            if (isOperator(c)) {
                while (!operators.empty() && operators.top() != '(' && getPrecedence(operators.top()) >= getPrecedence(c)) {
                    rpn << operators.top() << " ";
                    operators.pop();
                }
                operators.push(c);
            } else if (c == '(') {
                operators.push(c);
            } else if (c == ')') {
                while (!operators.empty() && operators.top() != '(') {
                    rpn << operators.top() << " ";
                    operators.pop();
                }
                operators.pop(); // Throw away the '('
            }
        }
    }

    if (!numberBuffer.str().empty()) {
        rpn << numberBuffer.str() << " ";
    }

    while (!operators.empty()) {
        rpn << operators.top() << " ";
        operators.pop();
    }

    return rpn.str();
}

int main() {
    std::string expression;
    std::cout << "Enter a standard expression: ";
    std::getline(std::cin, expression);

    std::string rpn = convertToRPN(expression);
    std::cout << "Reverse Polish Notation: " << rpn << std::endl;

    return 0;
}