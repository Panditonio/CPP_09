/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeDeque.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoineherbet <antoineherbet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 09:31:05 by antoineherb       #+#    #+#             */
/*   Updated: 2023/08/03 19:36:05 by antoineherb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void    PmergeMe::_dInsertionSort( int lhs, int rhs ) {
    if (lhs < 0 || rhs >= static_cast<int>(_dData.size()) || lhs >= rhs)
        return;

    clock_t start = clock();
    for (int step = lhs + 1; step <= rhs; step++) {
        int key = _dData[step];
        int j = step - 1;
        while (j >= lhs && key < _dData[j]) {
            _dData[j +1 ] = _dData[j];
            j--;
        }
        _dData[j +1] = key;
    }
    clock_t end = clock();
    double duration = (static_cast<double>(end - start) / CLOCKS_PER_SEC) * 1000.0;
    std::cout << "Insertion sort took: " << duration << " milliseconds" << std::endl;
}

void    PmergeMe::_dMergeInsertionSort( int lhs, int rhs, int k ) {
    if (rhs - lhs +1 <= k)
        _dInsertionSort(lhs, rhs);
    else if (lhs < rhs) {
        int mid = lhs + (rhs - lhs) / 2;
        _dMergeInsertionSort(lhs, mid, k);
        _dMergeInsertionSort(mid +1, rhs, k);
        _dMerge(lhs, mid, rhs);
    }
}

void    PmergeMe::_dMerge(int lhs, int mid, int rhs) {
    int p1 = mid - lhs +1;
    int p2 = rhs - mid;
    std::deque<int>    left(p1), right(p2);

    clock_t start = clock();
    for (int i = 0; i < p1; i++)
        left[i] = _dData[lhs + i];
    for (int j = 0; j < p2; j++)
        right[j] = _dData[mid +1 + j];
    
    int i, j, k;
    i = j = 0;
    k = lhs;
    while (i < p1 && j < p2) {
        if (left[i] <= right[j]) {
            _dData[k] = left[i];
            i++;
        }
        else {
            _dData[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < p1) {
        _dData[k] = left[i];
        i++;
        k++;
    }
    while (j < p2) {
        _dData[k] = right[j];
        j++;
        k++;
    }
    clock_t end = clock();
    double duration = (static_cast<double>(end - start) / CLOCKS_PER_SEC) * 1000.0;
    std::cout << "Merge sort took: " << duration << " milliseconds" << std::endl;
}

void    PmergeMe::_dSort( void ) {
    int k = _lData.size() / 2;
    clock_t start = clock();
    _dMergeInsertionSort(0, _dData.size() -1, k);
    clock_t end = clock();
    std::cout << "[DEQUE] after MIS is : ";
    printContainer(_dData);
    std::cout << std::endl;
    std::cout << "[MIS] total processing time for " << _dData.size();
    std::cout << " elements with std::deque is : " << end - start << "ms" << std::endl;
    std::cout << std::endl;
}