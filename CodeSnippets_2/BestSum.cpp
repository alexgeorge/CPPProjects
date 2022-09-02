/**
 * @file BestSum.cpp
 * @author alexvgeorge@vaxel.com
 * @brief Problem is similar to Cansum.cpp, but here the function should return
 * an array contianing shortest combination that adds up exactly to the
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
std::vector<int> shortestElems;

//since this is an optimization problem, we have to keep track of 
//minimum element vector through out

bool HowSum(const int targetSum, const std::vector<int> &vecIn, std::vector<int> &vecOut)
{
    if (memo.find(targetSum) != memo.end()){
        vecOut = memo[1].vecElems;
        return memo[1].bRet;
    }

    if (targetSum == 0) return true;

    bool bRet = false;
    static int counter = 0;
    for (auto elem : vecIn){
        auto remainder = 0;     
        if (targetSum >= elem){
            remainder = targetSum - elem;
            
            if (HowSum(remainder, vecIn, vecOut)){
                vecOut.push_back(elem);            
                bRet = true;
                std::cout << "calling [" << ++counter << "] times ts [" << targetSum << "] ele [" << elem << "]\n";
                std::cout << "Completed [" << vecOut.size() << "]\n";
                if (shortestElems.empty() || shortestElems.size() > vecOut.size()){
                    shortestElems = vecOut;
                }                           
            }
        }
    }
    stMemo temp;
    temp.bRet = bRet;
    temp.vecElems = shortestElems;
    memo[targetSum] = temp;
    return bRet;
}

void StackOverFlow(int &n)
{
    //the stack grows to the input size n
    //so the space complexity of this recursion 
    //will be O(n)
    //Time complexioty also will be O(n) as there
    //Will be n operations happening

    //base case condition which prevents the recursion from
    //Running indefinitely.  
    if (n == 0) return; 
    printf ("%d\n", --n);     
    StackOverFlow(n);

}

int main()
{
    //checking recursion 
    //int inp = 100;
    //StackOverFlow(inp);

    for (int n=100; n>0; --n){
        printf("%d\n", n);
    }

    std::map<int, std::vector<int>> inputMap;
    //inputMap[7] = {5,3,4,7}; // [7]
    inputMap[8] = {1,4,5}; // [4,4]
    //inputMap[8] = {2,3,5}; // [3,5]
    //inputMap[100] = {1,2,5,25}; // [25,25,25,25]
  
    std::vector<int> vecOut; //holds the elements adding up to targetsum
    auto it = inputMap.begin();
    if (HowSum(it->first, it->second, vecOut)){
        //print the elements in vecOut
        std::cout << "Sum possible. Shortest number of elements used [" ;
        for (auto el : vecOut) {std::cout << el << ",";}
        std::cout << "]\n";   
    }else{
        std::cout << "Sum not possible" << std::endl;
    }

}