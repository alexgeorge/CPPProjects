/**
 * @file HowSum.cpp
 * @author alexvgeorge@vaxel.com
 * @brief Problem is similar to Cansum.cpp, but here the function should return
 * an array contianing any combination of the elements that adds up exactly to the
 * targetSum. If there are no combinations then return null
 * This variant is addressing the 
 * @version 0.1
 * @date 2022-08-31
 * 
 * @copyright Copyright (c) 2022
 * time complexity: O(n^m) Without memoize (brut force)
 * Number of times the operation is executed
 * time complexity: O(n*m) with memoize
 * space complexity: O(m) Stack space
 */

#include <iostream>
#include <map>
#include <vector>

struct stMemo{
    bool bRet;
    std::vector<int> vecElems;
};

//without memo the operation for 300 (7,4) will not be finished
std::map<int, stMemo> memo;

bool HowSum(const int targetSum, const std::vector<int> &vecIn, std::vector<int> &vecOut)
{
    if (memo.find(targetSum) != memo.end()){
        vecOut = memo[1].vecElems;
        return memo[1].bRet;
    }

    if (targetSum == 0) return true;
    bool bRet = false;
    for (auto elem : vecIn){
        auto remainder = 0;
        if (targetSum >= elem){
            remainder = targetSum - elem;
            if (HowSum(remainder, vecIn, vecOut)){
                vecOut.push_back(elem);
                bRet = true;
                break;
            }
        }else{
            continue;
        }
    }
    stMemo temp;
    temp.bRet = bRet;
    temp.vecElems = vecOut;
    memo[targetSum] = temp;
    return bRet;
}

int main()
{
    std::map<int, std::vector<int>> inputMap;
    //inputMap[7] = {2,3}; // [3,2,2]
    //inputMap[7] = {5,3,4,7}; // [4,3]
    //inputMap[7] = {2,4}; //null
    inputMap[8] = {2,3,5}; // [2,2,2,2]
    //inputMap[300] = {7,14}; // null
  
    std::vector<int> vecOut; //holds the elements adding up to targetsum
    auto it = inputMap.begin();
    if (HowSum(it->first, it->second, vecOut)){
        //print the elements in vecOut
        std::cout << "Sum possible. Elements used [" ;
        for (auto el : vecOut) {std::cout << el << ",";}
        std::cout << "]\n";   
    }else{
        std::cout << "Sum not possible" << std::endl;
    }

}