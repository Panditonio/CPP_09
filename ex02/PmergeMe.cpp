/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoineherbet <antoineherbet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 02:39:01 by antoineherb       #+#    #+#             */
/*   Updated: 2023/07/25 23:23:25 by antoineherb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe( void ) {
    return;
}

PmergeMe::PmergeMe( PmergeMe const &src ) {
    *this = src;
    return;
}

PmergeMe::~PmergeMe( void ) {
    return;
}

PmergeMe&   PmergeMe::operator=( PmergeMe const &src ) {
    if (this != &src)
        *this = src;
    return (*this);
}

bool    PmergeMe::_checkInput( std::string const &input ) {
    try {
        size_t  i = 0;
        while (i < input.length()) {
            if (!isdigit(input[i]) && !isspace(input[i]))
                throw MISException();
            i++;
        }
    }
    catch (MISException &e) {
        return (false);
    }
    return (true);
}

void    PmergeMe::_getInput( std::string const &input ) {
    std::istringstream          sInput(input);
    std::string                 tmp;
    while (std::getline(sInput, tmp, ' ')) {
        if (tmp.empty())
            continue;
        _vData.push_back(atoi(tmp.c_str()));
        _lData.push_back(atoi(tmp.c_str()));
        _dData.push_back(atoi(tmp.c_str()));
    }
}

void    PmergeMe::printBefore( void ) {
    std::cout << "[VECTOR] before MIS is : ";
    printContainer(_vData);
    std::cout << "[LIST] before MIS is : ";
    printContainer(_lData);
    std::cout << "[DEQUE] before MIS is : ";
    printContainer(_dData);
    std::cout << std::endl;
}

void    PmergeMe::sort( std::string const &input) {
    try {
        if (!_checkInput(input))
            throw MISException();
        else {
            _getInput(input);
            printBefore();
            _vSort();
            _lSort();
            _dSort();
        }
    }
    catch (MISException &e) {
        std::cout << e.what() << "invalid input" << std::endl;
    }
}