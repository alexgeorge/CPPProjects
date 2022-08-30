/**
 * @file FibonocciNumber.cpp
 * @author alexvgeorge@vaxel.com)
 * @brief Recursive and dynamic implementation of
 * Fibonocci number. Find Fibo(n) where n is the index 
 * for which the Fibonocci number to be found.
 * Fibonocci series  1,1,2,3,5,8,12,20,32,.....
 * @version 0.1
 * @date 2022-08-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <string>
#include <map>

/**
 * @brief Recursive function to find the fibonocci
 * However this function is having a time complexity 
 * of O(2^n) and space complexity of O(n). Time complexity indicate the  number of times
 * a compute operation is called and space complexity indicate the level of stack 
 * build up while running the algorithm. This can be explained representing this 
 * problem as a binary tree. More details - 
 * Optimizing using map which holds the key and value for memoization
 * Dynamic programming (DP) means solving problems recursively by combining 
 * the solutions to similar smaller overlapping subproblems.
 * memoization technique is a routine trick applied in dynamic programming (DP)
 * this eliminate repetation of same computation by storing the result for 
 * easy reference
 * @param n 
 * @return int 
 */

std::map<int64_t, int64_t> memo = {{0,1}, {1,1}};

int64_t Fibo(int64_t n)
{
    if (memo.find(n) != memo.end()){
        return memo[n];
    }
    memo[n] = Fibo(n-1) + Fibo(n-2);
    return memo[n];
}

int main ()
{
    for (int i=0; i<50; ++i){
        auto n = static_cast<int64_t>(i);
        std::cout << "Fibo [" << i << "] = [" << Fibo(i) << "]" << std::endl;
    }
    return 0;
}


