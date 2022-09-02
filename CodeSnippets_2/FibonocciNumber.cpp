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
 * of O(2^n) (recursive method) and space complexity of O(n). 
 * Time complexity indicate the  number of times
 * a compute operation is called and space complexity indicate the level of stack 
 * build up while running the algorithm. This can be explained representing this 
 * problem as a binary tree. More details - 
 * Optimizing using map which holds the key and value for memoization
 * Dynamic programming (DP) means solving problems recursively by combining 
 * the solutions to similar smaller overlapping subproblems.
 * memoization technique is a routine trick applied in dynamic programming (DP)
 * this eliminate repetation of same computation by storing the result for 
 * easy reference
 * 2^n time complexity for the binary tree parse
 * 
 * Theme:- Compare recursive and iterative methods:-
 * Time Complexity
 * There are O(N) recursive calls in our recursive approach, 
 * and each call uses O(1) operations. Thus, the time complexity 
 * of factorial using recursion is O(N)
 * There are O(N) iterations of the loop in our iterative approach, 
 * so its time complexity is also O(N).
 * Though both the programs’ theoretical time complexity is the same, 
 * a recursive program will take more time to execute due to the overhead of function calls, 
 * which is much higher than that of iteration.
 * 
 * Space Complexity:-
 * In the recursive program, due to each recursive call, some memory gets allocated in the stack 
 * to store parameters and local variables. As there are O(N) recursive calls, 
 * the space complexity using recursion is O(N).
 * No extra memory gets allocated in the iterative program, 
 * so its space complexity is O(1).
 * 
 * @param n 
 */


void RecursiveStackOverFlow(int &n)
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
    RecursiveStackOverFlow(n);

}

void IterativeLoop()
{

    //There are O(N) iterations of the loop in our iterative approach, 
    //so its time complexity is also O(N).    
    //No extra memory gets allocated in the iterative program, 
    //so its space complexity is O(1).
    for (int n=100; n>0; --n){
        printf("%d\n", n);
    }
}


std::map<int64_t, int64_t> memo = {{0,1}, {1,1}};

int64_t Fibo(int64_t n)
{
    if (memo.find(n) != memo.end()){
        return memo[n];
    }
    //To check the timecomplexity reduction by using the memo
    //comment out the memo portion and test
    memo[n] = Fibo(n-1) + Fibo(n-2);
    return memo[n];
    //return Fibo(n-1) + Fibo(n-2);
}

int main ()
{

    //checking recursion 
    //int inp = 100;
    //RecursiveStackOverFlow(inp);

    for (int i=0; i<50; ++i){
        auto n = static_cast<int64_t>(i);
        std::cout << "Fibo [" << i << "] = [" << Fibo(i) << "]" << std::endl;
    }
    return 0;
}


