/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoineherbet <antoineherbet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 02:36:30 by antoineherb       #+#    #+#             */
/*   Updated: 2023/07/25 23:34:22 by antoineherb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main( int argc, char** argv ) {
    if (argc < 2) {
        std::cout << "[MIS ERROR] Syntax is : ./PmergeMe <int values separated";
        std::cout << " by space>" << std::endl;
        return (1);
    }
    else {
        std::string input = "";
        PmergeMe    m_i_s;
        for (int i = 1; i < argc; i++)
            input.append(argv[i]).append(" ");
        m_i_s.sort(input);
    }
    return (0);
}