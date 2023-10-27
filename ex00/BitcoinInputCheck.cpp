/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinInputCheck.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbet <aherbet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 07:38:48 by antoineherb       #+#    #+#             */
/*   Updated: 2023/08/09 18:02:21 by aherbet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool    BitcoinExchange::_checkDate( std::string const &date ) {
    std::istringstream  sDate(date);
    std::string         format;
    int                 year, month, day;
    int                 read = 0;

    if (date.length() != 10 || date.find('-', date.length() -1) != std::string::npos) {
        std::cout << "Error : invalid date format" << date << std::endl;
        return (false);
    }
    while (std::getline(sDate, format, '-')) {
        if (read == 0) {
            std::istringstream(format) >> year;
            time_t  now = time(0);
            tm  *ltm = localtime(&now);
            if (year < 2000 || year > 1900 + ltm->tm_year) {
                std::cout << "Error : invalid year => " << date << std::endl;
                return (false);
            }
        }
        if (read == 1) {
            std::istringstream(format) >> month;
            if (month < 1 || month > 12) {
                std::cout << "Error : invalid month => " << date << std::endl;
                return (false);
            }
        }
        if (read == 2) {
            std::istringstream(format) >> day;
            if (day < 1 || day > 31) {
                std::cout << "Error : bad input => " << date << std::endl;
                return (false);
            }
            if (day == 31 && (month == 4 || month == 6 || month == 9 || month == 11)) {
                std::cout << "Error : invalid day => " << date << std::endl;
                return (false);
            }
            if (month == 2) {
                if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                    if (day > 29) {
                        std::cout << "Error : invalid day => " << date << std::endl;
                        return (false);
                    }
                }
                else if (day > 28) {
                    std::cout << "Error : invalid day => " << date << std::endl;
                    return (false);
                }
            }
        }
        read++;
    }
    if (read != 3) {
        std::cout << "Error : wrong input" << date << std::endl;
        return (false);
    }
    return (true);
}

bool    BitcoinExchange::_checkValue( std::string const &value ) {
    // try {
    //     double  dValue = stod(value);
    //     if (dValue) {
    //         // std::cout << "dValue is : " << dValue << std::endl;
    //         return (true);
    //     }
    //     else
    //         return (false);
    // }
    // catch (std::invalid_argument &e) {
    //     return (false);
    // }
    // catch (std::out_of_range &e) {
    //     return (false);
    // }
    // -- or --
    // try {
    size_t dotCount = 0;
    for (size_t i = 0; i < value.length(); ++i) {
        if (value[i] == '.')
            dotCount++;
    }
    if (value[0] == '.' || dotCount > 1) {
        std::cout << "Error : not a valid number" << std::endl;
        return (false);            
    }
    double  dValue = std::strtod(value.c_str(), NULL);
    if (dValue == 0.0 && !std::isdigit(value[0])) {
        std::cout << "Error : value processing failed" << std::endl;
        return (false);
    }
    // if (pos != nullptr && *pos != 'f')
        // std::cout << "Error : not a valid number" << std::endl;
        // return (false);
    if (dValue < 0) {
        std::cout << "Error : not a positive number" << std::endl;
        return (false);
    }
    if (value.length() > 10 || (value.length() == 10 && dValue > INT_MAX)) {
        std::cout << "Error : too large a number" << std::endl;
        return (false);
    }
    // }
    // catch (std::exception &e) {
        // std::cout << "[BTC ERROR] : " << e.what() << std::endl;
    // }
    return (true);
}

void    BitcoinExchange::_checkInfo( std::string const &data ) {
    std::istringstream  sFormat(data);
    std::string         read, date;
    float               value;
    int                 idx = 0;

    while (std::getline(sFormat, read, ' ')) {
        if (idx == 0) {
            if (!_checkDate(read))
                return;
            date = read;
        }
        if (idx == 1 && read != "|") {
            std::cout << "Error : bad input => " << data << std::endl;
            return;
        }
        if (idx == 2) {
            if (!_checkValue(read))
                return;
            value = strtod(read.c_str(), NULL);
            if (value > 10000) {
                std::cout << "Error : too large a number" << std::endl;
                return;
            }
        }
        idx++;
    }
    // _inputData.insert(std::pair<std::string, float>(date, value));
    if (idx != 3) {
        std::cout << "Error : bad input => " << data << std::endl;
        return;
    }
    _formatOutput(date, value);
}

void    BitcoinExchange::_checkInputFile( char* input ) {
    std::ifstream   sInput(input);
    std::string     read/*, date*/;
    // size_t          date_size;
    // float           value;

    try {
        if (!sInput)
            throw BitcoinException();
    }
    catch (BitcoinException &e) {
        std::cout << e.what() << "could not open input file" << std::endl;
    }
    try {
        if (sInput.peek() == EOF)
            throw BitcoinException();
    }
    catch (BitcoinException &e) {
        std::cout << e.what() << "empty input file" << std::endl;
    }
    try {
        std::getline(sInput, read);
        if (read != "date | value")
            throw BitcoinException();
    }
    catch (BitcoinException &e) {
        std::cout << e.what() << "input format error" << std::endl;
    }
    // try {
    while (std::getline(sInput, read)) {
        _checkInfo(read);
    }
    // printContainer(_inputData);
    //     if (read != "date | value") {
    //         date_size = read.find(" | ");
    //         if (!_checkDate(read.substr(0, date_size)))
    //             std::cout << "[WARNING] : include invalid date" << std::endl;
    //             // throw BitcoinException();
    //         if (read.substr(date_size, 3) != " | ")
    //             std::cout << "[WARNING] : include invalid input format" << std::endl;
    //             // throw BitcoinException();
    //         if (!_checkValue(read.substr(date_size +3)))
    //             std::cout << "[WARNING] : include invalid value" << std::endl;
    //             // throw BitcoinException();
    //         date = read.substr(0, date_size);
    //         std::istringstream(read.substr(date_size +3)) >> value;
    //         _inputData.insert(std::pair<std::string, float>(date, value));
    //     }
    // }
    // printContainer(_inputData);
    // }
    // catch (BitcoinException &e) {
        // std::cout << e.what() << "invalid input format" << std::endl;
    // }
}