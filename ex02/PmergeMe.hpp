/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoineherbet <antoineherbet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 02:39:21 by antoineherb       #+#    #+#             */
/*   Updated: 2023/08/03 19:11:28 by antoineherb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                             P_MERGE_ME CLASS                               */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <algorithm>
#include <iostream>
#include <iterator>
#include <sstream>
#include <ctime>
#include <vector>
#include <deque>
#include <list>

class PmergeMe
{
    private:
        // private member attributes
        std::vector<int>    _vData;
        std::list<int>      _lData;
        std::deque<int>     _dData;
        // private member functions
        bool    _checkInput( std::string const &input );
        void    _getInput( std::string const &input );
        void    _vInsertionSort( int lhs, int rhs );
        void    _vMergeInsertionSort( int lhs, int rhs, int k );
        void    _vMerge( int lhs, int mid, int rhs );
        void    _vSort( void );
        void    _lInsertionSort( int lhs, int rhs );
        void    _lMergeInsertionSort( int lhs, int rhs, int k );
        void    _lMerge( int lhs, int mid, int rhs );
        void    _lSort( void );
        void    _dInsertionSort( int lhs, int rhs );
        void    _dMergeInsertionSort( int lhs, int rhs, int k );
        void    _dMerge( int lhs, int mid, int rhs );
        void    _dSort( void );
    public:
        // constructors
        PmergeMe( void );
        PmergeMe( PmergeMe const &src );
        // destructor
        ~PmergeMe( void );
        // operators overload
        PmergeMe&   operator=( PmergeMe const &src );
        // getter, setter
        const int&  getListValue( std::list<int> const &list, int idx ) const;
        void        setListValue( int idx, int value );
        // public member functions
        template<typename T>
        void    printContainer( T const &content );
        void    printBefore( void );
        void    sort( std::string const &input );
        // exception classes
        class MISException : public std::exception {
            public:
                const char* what() const throw() { 
                    return "[MIS ERROR] : ";
                }
        };
};

template<typename T>
void    PmergeMe::printContainer( T const &content ) {
    typename T::const_iterator  it;
    for (it = content.begin(); it != content.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

// std::iostream&  operator<<( std::iostream &os, PmergeMe const &is ) {
// }

#endif