#pragma once
#include "common.h"

class BinarySearchMisc {
  //No.744  Find Smallest Letter Greater Than Target
//   Given a list of sorted characters letters containing only lowercase letters, and given a target letter target, 
  // find the smallest element in the list that is larger than the given target.

// Letters also wrap around. For example, if the target is target = 'z' and letters = ['a', 'b'], the answer is 'a'.
  char nextGreatestLetter(vector<char>& letters, char target) {
        int left = 0, right = letters.size()-1;
        while(left <= right){
            int pos = (left+right) >> 1;
            if(letters[pos] <= target){
                left = pos+1;
            }else{
                right = pos-1;
            }
        }
        return letters[left%((int)letters.size())];
    }
  // No.704 Binary Search
// Given a sorted (in ascending order) integer array nums of n elements and a target value, write a function to search target in nums. 
  //If target exists, then return its index, otherwise return -1.
// Example 1:

// Input: nums = [-1,0,3,5,9,12], target = 9
// Output: 4
// Explanation: 9 exists in nums and its index is 4
// Example 2:

// Input: nums = [-1,0,3,5,9,12], target = 2
// Output: -1
// Explanation: 2 does not exist in nums so return -1
// Note:
// You may assume that all elements in nums are unique.
// n will be in the range [1, 10000].
// The value of each element in nums will be in the range [-9999, 9999]
  int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size()-1;
        while(left <= right){
            int pos = (left+right) >> 1;
            if(nums[pos] == target)
                return pos;
            if(nums[pos] < target){
                left = pos+1;
            }else
                right = pos-1;
        }
        return -1;
    }
  
  
  // No.1237 Find Positive Integer Solution for a Given Equation
  // Given a function  f(x, y) and a value z, return all positive integer pairs x and y where f(x,y) == z.

  // The function is constantly increasing, i.e.:

  // f(x, y) < f(x + 1, y)
  // f(x, y) < f(x, y + 1)
  // The function interface is defined like this: 

  // interface CustomFunction {
  // public:
  //   // Returns positive integer f(x, y) for any given positive integer x and y.
  //   int f(int x, int y);
  // };
  // For custom testing purposes you're given an integer function_id and a target z as input, where function_id represent one function from an secret internal list, on the examples you'll know only two functions from the list.  

  // You may return the solutions in any order.
  vector<vector<int>> findSolution(CustomFunction& customfunction, int z) {
        // min 0 max 1000
        vector<vector<int>> ans;
        // first, findthe range for me to grow x
        // int minx = 0, maxx = 1000;
        // int startx;
        // while(minx < maxx){
        //     startx = (minx+maxx) >> 1;
        //     int temp = customfunction.f(startx, 1000);
        //     cout << minx << " " << maxx << " " << startx << " " << temp << "\n";
        //     if(temp < z){
        //         minx = startx;
        //     }else if(temp > z){
        //         maxx = startx;
        //     }else
        //         break;
        // }
        // cout << startx << "\n";
        for(int i = 1000; i >= 1; i--){
            // there should be at most one answer for it
            int miny = 1, maxy = 1000;
            int starty;
            while(miny <= maxy){
                starty = (miny+maxy) >> 1;
                int temp = customfunction.f(i, starty);
                if(temp < z){
                    miny = starty+1;
                }else if(temp > z){
                    maxy = starty-1;
                }else{
                     ans.push_back(vector<int>{i, starty});
                    break;
                }
                   
            }
        }
        return ans;
    }
}
