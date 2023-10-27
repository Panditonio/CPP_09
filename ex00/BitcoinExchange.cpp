/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoineherbet <antoineherbet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 05:58:31 by antoineherb       #+#    #+#             */
/*   Updated: 2023/07/27 07:29:41 by antoineherb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange( void ) {
    return;
}

BitcoinExchange::~BitcoinExchange( void ) {
    return;
}

BitcoinExchange::BitcoinExchange( BitcoinExchange const &src ) {
    *this = src;
    return;
}

BitcoinExchange&    BitcoinExchange::operator=( BitcoinExchange const &src ) {
    if (this != &src) {
        this->_btcData = src._btcData;
        // this->_inputData = src._inputData;
    }
    return (*this);
}

void    BitcoinExchange::_formatOutput( std::string const &date, float const &value ) {
    float   result = 0;
    std::map<std::string, float>::const_iterator    it = _btcData.find(date);

    if (it != _btcData.end())
        result = (it->second) * value;
    else {
        it = _btcData.lower_bound(date);
        if (it == _btcData.begin()) {
            std::cout << "Error : no data available" << std::endl;
            return;
        }
        --it;
        result = (it->second) * value;
    }
    (value == static_cast<int>(value)) ?
        std::cout << date << " => " << static_cast<int>(value) << " = " << result << std::endl :
        std::cout << date << " => " << value << " = " << result << std::endl;
    // std::map<std::string, float>::const_iterator    iti;

    // try {
    //     for (iti = _inputData.begin(); iti != _inputData.end(); iti++) {
    //         it = _btcData.find(iti->first);
    //         if (it != _btcData.end())
    //             result = (it->second) * (iti->second);
    //         else {
    //             it = _btcData.lower_bound(iti->first);
    //             if (it == _btcData.begin())
    //                 throw BitcoinException();
    //             --it;
    //             result = (it->second) * (iti->second);
    //         }
    //         std::cout << iti->first << " => " << iti->second << " = " << result << std::endl;
    //     }
    // }
    // catch (BitcoinException &e) {
    //     std::cout << e.what() << "no data available" << std::endl;
    //     return;
    // }
}

void    BitcoinExchange::exchange( char* input ) {
    try {
        _validDataFile();
        _checkInputFile(input);
    }
    catch (BitcoinException &e) {
        return;
    }
    return;
}