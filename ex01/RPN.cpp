/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoineherbet <antoineherbet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 06:10:37 by antoineherb       #+#    #+#             */
/*   Updated: 2023/07/25 02:33:06 by antoineherb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN( void ) {
    return;
}

RPN::RPN( RPN const &src ) {
    *this = src;
    return;
}

RPN::~RPN( void ) {
    return;
}

RPN&    RPN::operator=( RPN const &src ) {
    if (this != &src)
        *this = src;
    return (*this);
}

bool    RPN::_isOperand( char c ) {
    return (isdigit(c));
}

bool    RPN::_isOperator( char c ) {
    return (c == '+' || c == '-' || c == '/' || c == '*');
}

bool    RPN::_isSpace( char c ) {
    return (isspace(c));
}

int  RPN::_calculator( double a, double b, char c) {
    try {
        switch (c) {
            case '+':
                return (a + b);
            case '-':
                return (a - b);
            case '*':
                return (a * b);
            case '/':
                return (a / b);
            default:
                throw RPNException();
        }
    }
    catch (RPNException &e) {
        std::cout << e.what() << "invalid calculation" << std::endl;
        return (EXIT_FAILURE);
    }
}

bool    RPN::_checkInput( std::string const &input ) {
    try {
        size_t  i, oc, sc, spc;
        i = oc = sc = spc = 0;
        while (i < input.length()) {
            if (_isOperand(input[i])) oc++;
            if (_isOperator(input[i])) sc++;
            if (!_isOperand(input[i]) && !_isOperator(input[i])
            && !_isSpace(input[i]))
                throw RPNException();
            i++;
        }
        spc = static_cast<size_t>(std::count(input.begin(), input.end(), ' '));
        // std::cout << "Number of Operands : " << oc << std::endl;
        // std::cout << "Number of Operators : " << sc << std::endl;
        // std::cout << "Number of Spaces : " << spc << std::endl;
        if (spc != ((oc + sc) -1))
            throw RPNException();
    }
    catch (RPNException &e) {
        return (false);
    }
    return (true);
}

void    RPN::convertRPN( std::string const &input ) {
    try {
        if (!_checkInput(input))
            throw RPNException();
        else {
            std::string exp = "";
            double      a, b;
            size_t      i = 0;
            a = b = 0.0;

            while (i < input.length()) {
                while (_isSpace(input[i]))
                    i++;
                if (_isOperand(input[i]) || input[i] == '.') {
                    while (_isOperand(input[i]) || input[i] == '.') {
                        exp += input[i];
                        i++;
                    }
                    _infix.push(atof(exp.c_str()));
                    // std::cout << "Current top is : " << _infix.top() << std::endl;
                    exp = "";
                }
                else if (_isOperator(input[i])) {
                    b = _infix.top();
                    _infix.pop();
                    a = _infix.top();
                    _infix.pop();
                    _infix.push(_calculator(a, b, input[i]));
                    // std::cout << "Current top is : " << _infix.top() << std::endl;
                    i++;
                }
                else {
                    throw RPNException();
                    break;
                }
            }
            std::cout << "Result is : " << _infix.top() << std::endl;
        }
    }
    catch (RPNException &e) {
        std::cout << e.what() << "invalid RPN" << std::endl;
    }
}