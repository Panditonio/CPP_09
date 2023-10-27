/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoineherbet <antoineherbet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 06:10:41 by antoineherb       #+#    #+#             */
/*   Updated: 2023/07/26 04:42:53 by antoineherb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                 RPN CLASS                                  */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <string>
#include <cctype>
#include <stack>

class RPN
{
    private:
        // private member attributes
        std::stack<double>      _infix;
        // private member functions
        bool    _checkInput( std::string const &input );
        bool    _isOperand( char c );
        bool    _isOperator( char c );
        bool    _isSpace( char c );
        int     _calculator( double a, double b, char c);
    public:
        // constructors
        RPN( void );
        RPN( RPN const &src );
        // destructor
        ~RPN( void );
        // operators overload
        RPN&    operator=( RPN const &src );
        // getter, setter
        // public member functions
        void    convertRPN( std::string const &input );
        // exception classes
        class RPNException : public std::exception {
            public:
                const char* what() const throw() { 
                    return "[RPN ERROR] : ";
                }
        };
};

// std::iostream&  operator<<( std::iostream &os, RPN const &is) {
// }

#endif