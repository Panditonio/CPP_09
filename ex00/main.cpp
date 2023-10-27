/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoineherbet <antoineherbet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 05:58:42 by antoineherb       #+#    #+#             */
/*   Updated: 2023/07/23 05:32:37 by antoineherb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main( int argc, char** argv ) {
    if (argc != 2) {
        std::cout << "[BTC ERROR] Syntax is : ./btc <input_file>" << std::endl;
        return (1);
    }
    else {
        BitcoinExchange     bitcoin;
        bitcoin.exchange(argv[1]);
    }
    return (0);
}