/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbet <aherbet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 05:58:39 by antoineherb       #+#    #+#             */
/*   Updated: 2023/08/09 17:59:14 by aherbet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                          BITCOIN EXCHANGE CLASS                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <climits>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

class BitcoinExchange
{
    private:
        // private member attributes
        std::map<std::string, float>     _btcData;
        // std::map<std::string, float>     _inputData;
        // private member functions
        bool    _validDate( std::string date );
        bool    _validRate( std::string rate );
        void    _validDataFile( void );
        void    _checkInfo( std::string const &data );
        bool    _checkDate( std::string const &date );
        bool    _checkValue( std::string const &value );
        void    _checkInputFile( char* input );
        void    _formatOutput( std::string const &date, float const &value );
    public:
        // constructors
        BitcoinExchange( void );
        BitcoinExchange( BitcoinExchange const &src );
        // destructor
        ~BitcoinExchange( void );
        // operators overload
        BitcoinExchange&    operator=( BitcoinExchange const &src );
        // getter, setter
        // public member functions
        // template<typename T>
        // void    printContainer( T const &content );
        void    exchange( char* input );
        // exception classes
        class BitcoinException : public std::exception {
            public:
                const char* what() const throw() { 
                    return "[BTC ERROR] : ";
                }
        };
};

// template<typename T>
// void    BitcoinExchange::printContainer( T const &content ) {
//     typename T::const_iterator  it;
//     for (it = content.begin(); it != content.end(); it++)
//         std::cout << it->first << " | " << std::fixed << std::setprecision(2) << it->second << "\n";
//     std::cout << std::endl;
// }

#endif