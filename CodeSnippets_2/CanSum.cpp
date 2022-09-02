/**
 * @file CanSum.cpp
 * @author alexvgeorge@vaxel.com
 * @type decision making problem
 * @brief CanSum(7,[5,3,4,7]) = true, Return true if the targetsum 7 can be
 * generated using the elements in the array. Answer is binary here
 * @version 0.1
 * @date 2022-08-30
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <map>
#include <vector>

std::map<int, bool> memo;

bool CanSum(int targetSum, const std::vector<int> &vecIn)
{
    std::cout << "sum [" << targetSum << "]\n";
    if (memo.find(targetSum) != memo.end()) return memo[targetSum];
    if (targetSum == 0) return true;
    if (targetSum < 0) return false;

    bool bRet = false;
    for (auto vec : vecIn)
    {
        int remainder = 0;
        if (targetSum >= vec){
            remainder = targetSum - vec;
        }else{
            continue;
        }
        //if any of the node reaches the end then finish the operation
        if (CanSum(remainder, vecIn)){
            bRet = true;
            break;
        }
    }
    memo[targetSum] = bRet;
    return bRet;
}


int main()
{
  
    //{7, {2,3}} true
    //{7,(5,3,4,7)} true
    //{7,(2,4)}  false
    //{8,(2,3,5)} true
    //{300, (7,14)}}; false

    std::map<int, std::vector<int>> inputMap;

    inputMap[300] = {7,14};
    //inputMap[8] = {2,3,5};
    //inputMap[7] = {2,4};
    //inputMap[7] = {5,3,4,7};
  
    auto it = inputMap.begin();
    if (CanSum(it->first, it->second))
    {
        std::cout << "Sum possible" << std::endl;  
    }
    else
    {
        std::cout << "No complete factors" << std::endl;   
    }

}