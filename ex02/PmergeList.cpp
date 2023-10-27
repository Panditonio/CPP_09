/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeList.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoineherbet <antoineherbet@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 09:26:45 by antoineherb       #+#    #+#             */
/*   Updated: 2023/08/03 19:36:04 by antoineherb      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

const int&  PmergeMe::getListValue( std::list<int> const &list, int idx ) const {
    std::list<int>::const_iterator  it = list.begin();
    // while (idx--) ++it;
    std::advance(it, idx);
    return (*it);
}

void    PmergeMe::setListValue( int idx, int value ) {
    std::list<int>::iterator  it = _lData.begin();
    // while (idx--) ++it;
    std::advance(it, idx);
    *it = value;
}

void    PmergeMe::_lInsertionSort( int lhs, int rhs ) {
    if (lhs < 0 || rhs >= static_cast<int>(_lData.size()) || lhs >= rhs)
        return;

    clock_t start = clock();
    for (int step = lhs + 1; step <= rhs; step++) {
        int key = getListValue(_lData, step);
        int j = step - 1;
        while (j >= lhs && key < getListValue(_lData, j)) {
            setListValue(j +1, getListValue(_lData, j));
            j--;
        }
        setListValue(j + 1, key);
    }
    clock_t end = clock();
    double duration = (static_cast<double>(end - start) / CLOCKS_PER_SEC) * 1000.0;
    std::cout << "Insertion sort took: " << duration << " milliseconds" << std::endl;
}

void    PmergeMe::_lMergeInsertionSort( int lhs, int rhs, int k ) {
    if (rhs - lhs + 1 <= k)
        _lInsertionSort(lhs, rhs);
    else if (lhs < rhs) {
        int mid = lhs + (rhs - lhs) / 2;
        _lMergeInsertionSort(lhs, mid, k);
        _lMergeInsertionSort(mid + 1, rhs, k);
        _lMerge(lhs, mid, rhs);
    }
}

void    PmergeMe::_lMerge(int lhs, int mid, int rhs) {
    // int p1 = mid - lhs +1;
    // int p2 = rhs - mid;
    std::list<int>    left, right;

    clock_t start = clock();
    for (int i = 0; i < (mid - lhs + 1); i++)
        left.push_back(getListValue(_lData, lhs + i));
    for (int j = 0; j < (rhs - mid); j++)
        right.push_back(getListValue(_lData, mid + 1 + j));
    
    int i, j, k;
    i = j = 0;
    k = lhs;
    while (i < (mid - lhs + 1) && j < (rhs - mid)) {
        if (getListValue(left, i) <= getListValue(right, j)) {
            setListValue(k, getListValue(left, i));
            i++;
        }
        else {
            setListValue(k, getListValue(right, j));
            j++;
        }
        k++;
    }
    while (i < (mid - lhs + 1)) {
        setListValue(k, getListValue(left, i));
        i++;
        k++;
    }
    while (j < (rhs - mid)) {
        setListValue(k, getListValue(right, j));
        j++;
        k++;
    }
    clock_t end = clock();
    double duration = (static_cast<double>(end - start) / CLOCKS_PER_SEC) * 1000.0;
    std::cout << "Merge sort took: " << duration << " milliseconds" << std::endl;
}

void    PmergeMe::_lSort( void ) {
    int k = (_lData.size() / 2);
    clock_t start = clock();
    _lMergeInsertionSort(0, _lData.size() - 1, k);
    clock_t end = clock();
    std::cout << "[LIST] after MIS is : ";
    printContainer(_lData);
    std::cout << std::endl;
    std::cout << "[MIS] total processing time for " << _lData.size();
    std::cout << " elements with std::list is : " << end - start << "ms" << std::endl;
    std::cout << std::endl;
}