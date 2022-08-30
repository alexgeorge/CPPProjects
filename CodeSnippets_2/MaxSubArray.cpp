#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <map>
#include <algorithm>

/**
 * @brief Given An Array Of N integers and a Number K return max sum of subarray of size k 
 * that has K Distinct Elements. if it does not exist return -1.
 * Test Case:
[1,2,3,4,4,3,2,1],k=3
Output:
9
[1,2,3],[2,3,4],[4,3,2],[3,2,1] are valid subarrays as they have k distinct elements.max sum among them is 9

Test Case:
[1,2,2] k=3
Output:
-1
No valid subarray of length k exist that has all k elements unique.

Constrainst:
1<=n<=1e5
k<=n
1<=arr[i]<=1e9
 */

auto SortMap(const std::map<int, int> &inMap)
{
    std::vector<std::pair<int, int>> vecPairs;
    for (auto elem : inMap){
        vecPairs.push_back(elem);
    }
    std::sort(vecPairs.begin(), vecPairs.end(), [=](std::pair<int, int> &a, std::pair<int, int> &b) {return a.second > b.second;});

    for (auto subsum : vecPairs){
        std::cout << "subarray sum [" << subsum.first << "] is [" << subsum.second << "]" << std::endl;
    }

    bool ret = false;
    return ret;
}

int ComputeMaxSubarray(int *arr, const int size, const int windowSize )
{
    auto ret = 0;
    bool bFinished = false;
    std::map<int, int> idxMap; //hold the start index and sum of window
    for (int i=0; i<size; ++i){
        int subArrSum = 0;
        for (int j = 0; j<windowSize; ++j)
        {
            if ( i+j < size ){
                subArrSum += arr[i+j];
            }
            else{
                std::cout << "Reached the end!" << std::endl;
                bFinished = true;
                break;    
            }
        }
        if (!bFinished){
            idxMap[i] = subArrSum;
        }
    }
    SortMap(idxMap);
    return ret;
}

/**
 * @brief Use moving window to compute the max sub array
 * First calculate the sum for window size, then move the index
 * by one; remove the first element and add the last element.
 * Continue till the window covers the last element in array 
 *
 * @param arr 
 * @param size 
 * @param window 
 */
void ComputeSubArrayMovingWindow(const int *arr, const int size, const int window)
{
    auto subSum = 0;
    auto firstSum = 0;
    auto maxSum = 0;
    if (size<window){
        std::cout << "Window size more than array size" << std::endl;
    }

    for (int j=0; j<window; ++j){
        firstSum += arr[j];
        maxSum = firstSum;
    }

    //Now the first sum is to be manipulated using this moving
    //window. Remove the first element each time and add the next
    //element till we reach the end
    for (int i=0; i<size; ++i){
        if (window+i >= size){
            std::cout << "Reached limit! " << std::endl;
            break;
        }
        subSum = firstSum - arr[i] + arr[i+window];
        maxSum =  subSum > maxSum ? subSum : maxSum;
        firstSum = subSum;
    }

    std::cout << "Max sum using moving window [" << maxSum << "]" << std::endl;

    return;

}

int maxSubarrayKardane(const int *arr, const int size, const int window)
{
    //Find the largest sum of any contiguous subarray.
    int best_sum = 0;
    int current_sum = 0;
    for (int i=0; i<size; ++i) {
        current_sum = std::max(0, current_sum + arr[i]);
        best_sum = std::max(best_sum, current_sum);
    }
    return best_sum;
}

int main()
{
    int arr[] = {1,4,2,10,23,3, 1,0,20};
    
    //int arr[] = {100,200,300,400};

    int size = sizeof (arr) / sizeof(int);
    int window = 4;

    ComputeMaxSubarray(arr, size, window);

    ComputeSubArrayMovingWindow(arr, size, window);

    //maxSubarrayKardane(arr, size, window);

    return 0;
}
