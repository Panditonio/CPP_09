/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoineherbet <antoineherbet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 06:10:30 by antoineherb       #+#    #+#             */
/*   Updated: 2023/07/24 06:20:35 by antoineherb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main( int argc, char** argv ) {
    if (argc != 2) {
        std::cout << "[BTC ERROR] Syntax is : ./RPN <\"RPN expression\">" << std::endl;
        return (1);
    }
    else {
        RPN con;
        con.convertRPN(argv[1]);
    }
    return (0);
}