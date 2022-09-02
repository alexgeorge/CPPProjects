/**
 * @file GridTraveller.cpp
 * @author alexvgeorge@vaxel.com
 * @brief There is a robot on an m x n grid. The robot is initially located at the top-left corner 
 * (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). 
 * The robot can only move either down or right at any point in time. Given the two integers m and n, 
 * return the number of possible unique paths that the robot can take to reach the bottom-right corner. 
 * The test cases are generated so that the answer will be less than or equal to 2 * 109.
 * @version 0.1
 * @date 2022-08-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <map>

std::map<std::string, int64_t> memo = {{"1,1", 1}};

int64_t GridTraveller(int64_t m, int64_t n)
{
    std::cout << "Visiting [" << m << "," << n << "]" << std::endl;
    std::string strKey;
    strKey = std::to_string(m)+ "," + std::to_string(n); 
    if (m==1 && n==1) return 1;
    if (m==0 || n==0) return 0;
    if (memo.find(strKey) != memo.end()){
        return memo[strKey];
    }
    memo[strKey] = GridTraveller(m-1, n) + GridTraveller(m, n-1);
    return memo[strKey];
}

class Solution 
{
public:
    int uniquePaths(int m, int n) 
    {
        return GridTraveller(m,n);
    }
};


int main()
{
    //If we are using int then the number of ways will have truncation error
    //as the max value hold is 2^31 = 2,147,483,648 (2GB)
    //auto ways = GridTraveller(18,18); //Number of ways to traverse [2333606220]

    auto ways = GridTraveller(3,3);

    std::cout << "Number of ways to traverse [" << ways << "]" << std::endl;

    return 0;
}