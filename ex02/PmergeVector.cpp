/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeVector.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoineherbet <antoineherbet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 09:19:24 by antoineherb       #+#    #+#             */
/*   Updated: 2023/08/03 19:26:03 by antoineherb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

void    PmergeMe::_vInsertionSort( int lhs, int rhs ) {
    if (lhs < 0 || rhs >= static_cast<int>(_vData.size()) || lhs >= rhs)
        return;

    clock_t start = clock();
    for (int step = lhs +1; step <= rhs; step++) {
        int key = _vData[step];
        int j = step - 1;
        while (j >= lhs && key < _vData[j]) {
            _vData[j +1] = _vData[j];
            j--;
        }
        _vData[j +1] = key;
    }
    clock_t end = clock();
    double duration = (static_cast<double>(end - start) / CLOCKS_PER_SEC) * 1000.0;
    std::cout << "Insertion sort took: " << duration << " milliseconds" << std::endl;
}

void    PmergeMe::_vMergeInsertionSort( int lhs, int rhs, int k ) {
    if (rhs - lhs +1 <= k)
        _vInsertionSort(lhs, rhs);
    else if (lhs < rhs) {
        int mid = lhs + (rhs - lhs) / 2;
        _vMergeInsertionSort(lhs, mid, k);
        _vMergeInsertionSort(mid +1, rhs, k);
        _vMerge(lhs, mid, rhs);
    }
}

void    PmergeMe::_vMerge(int lhs, int mid, int rhs) {
    int p1 = mid - lhs +1;
    int p2 = rhs - mid;
    std::vector<int>    left(p1), right(p2);

    clock_t start = clock();
    for (int i = 0; i < p1; i++)
        left[i] = _vData[lhs + i];
    for (int j = 0; j < p2; j++)
        right[j] = _vData[mid +1 + j];
    
    int i, j, k;
    i = j = 0;
    k = lhs;
    while (i < p1 && j < p2) {
        if (left[i] <= right[j]) {
            _vData[k] = left[i];
            i++;
        }
        else {
            _vData[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < p1) {
        _vData[k] = left[i];
        i++;
        k++;
    }
    while (j < p2) {
        _vData[k] = right[j];
        j++;
        k++;
    }
    clock_t end = clock();
    double duration = (static_cast<double>(end - start) / CLOCKS_PER_SEC) * 1000.0;
    std::cout << "Merge sort took: " << duration << " milliseconds" << std::endl;
}

void    PmergeMe::_vSort( void ) {
    int k = _lData.size() / 2;
    clock_t start = clock();
    _vMergeInsertionSort(0, _vData.size() -1, k);
    clock_t end = clock();
    double duration = (static_cast<double>(end - start) / CLOCKS_PER_SEC) * 1000.0;
    std::cout << "[VECTOR] after MIS is : ";
    printContainer(_vData);
    std::cout << std::endl;
    std::cout << "[MIS] total processing time for " << _vData.size();
    std::cout << " elements with std::vector is : " << duration << "milliseconds" << std::endl;
    std::cout << std::endl;
}