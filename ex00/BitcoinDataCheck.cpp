/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinDataCheck.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherbet <aherbet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 07:28:20 by antoineherb       #+#    #+#             */
/*   Updated: 2023/08/09 17:54:45 by aherbet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

bool    BitcoinExchange::_validDate( std::string date ) {
    std::istringstream  sDate(date);
    std::string         format;
    int                 year, month, day;
    int                 read = 0;

    if (date.length() != 10)
        return (false);
    while (std::getline(sDate, format, '-')) {
        if (read == 0) {
            std::istringstream(format) >> year;
            time_t  now = time(0);
            tm  *ltm = localtime(&now);
            if (year < 1900 || year > 1900 + ltm->tm_year)
                return (false);
        }
        else if (read == 1) {
            std::istringstream(format) >> month;
            if (month < 1 || month > 12)
                return (false);
        }
        else if (read == 2) {
            std::istringstream(format) >> day;
            if (day < 1 || day > 31)
                return (false);
            if (day == 31 && (month == 4 || month == 6 || month == 9 || month == 11))
                return (false);
            if (month == 2) {
                if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) {
                    if (day > 29)
                        return (false);
                }
                else if (day > 28)
                    return (false);
            }
        }
        read++;
    }
    if (read != 3)
        return (false);
    return (true);
}

bool    BitcoinExchange::_validRate( std::string rate ) {
    try {
        float  fRate = atof(rate.c_str());
        if (fRate >= 0) {
            // std::cout << "fRate is : " << fRate << std::endl;
            return (true);
        }
        else
            return (false);
    }
    catch (std::invalid_argument &e) {
        return (false);
    }
    catch (std::out_of_range &e) {
        return (false);
    }    
    // // try {
    // char*   pos = nullptr;
    // double  dRate = std::strtod(rate.c_str(), &pos);
    // if (dRate == 0.0 && !std::isdigit(rate[0]))
    //     return (false);
    // if (pos != nullptr && *pos != 'f')
    //     return (false);
    // if (dRate < 0)
    //     return (false);
    // // }
    // // catch (std::exception &e) {
    //     // std::cout << "[BTC ERROR] : " << e.what() << std::endl;
    // // }
    // return (true);
}

void    BitcoinExchange::_validDataFile( void ) {
    std::ifstream   data("data.csv");
    std::string     read;
    std::string     date;
    size_t          date_size;
    float           rate;

    try {
        if (!data)
            throw BitcoinException();
    }
    catch (BitcoinException &e) {
        std::cout << e.what() << "could not open data file" << std::endl;
    }
    try {
        if (data.peek() == EOF)
            throw BitcoinException();
    }
    catch (BitcoinException &e) {
        std::cout << e.what() << "empty data file" << std::endl;
    }
    // try {
    while (std::getline(data, read)) {
        if (read != "date,exchange_rate") {
            date_size = read.find(',');
            if (!_validDate(read.substr(0, date_size)))
                std::cout << "[WARNING] : include invalid date" << std::endl;
                // throw BitcoinException();
            if (!_validRate(read.substr(date_size +1)))
                std::cout << "[WARNING] : include invalid rate" << std::endl;
                // throw BitcoinException();
            date = read.substr(0, date_size);
            std::istringstream(read.substr(date_size +1)) >> rate;
            _btcData.insert(std::pair<std::string, float>(date, rate));
        }
    }
    // printContainer(_btcData);
    // }
    // catch (BitcoinException &e) {
        // std::cout << e.what() << "invalid data format" << std::endl;
    // }
}