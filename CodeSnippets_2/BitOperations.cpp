/**
 * @file BitOperations.cpp
 * @author alexvgeorge@vaxel.com)
 * @brief 
 * @version 0.1
 * @date 2022-09-08
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <vector>

/**
 * @brief Compute the number of 1s in the given number
 * The logic has a complexity of O(n). How can we
 * reduce it to O(1), provided you have enough memory
 * in the system? The solution fo O(1) will always be
 * a look up table. So a lookup table matching all the 
 * entries will take only O(1) for the solution
 * 
 */
int FindNumberOfOnes(int number)
{
    int count = 0;
    int size = sizeof(int) * 8;
    for (int i = 0; i< size; ++i){
        number = number >> 1;
        if (number & 1) ++count; //important
        std::cout << number << std::endl;
        if (!number) break; 
    }
    return count;
}

int main()
{
    int input = 8;
    auto out = FindNumberOfOnes(input); 
    std::cout << "Number of 1s in [" << input << "] is [" << out << "]\n"; 
    return 0;
}