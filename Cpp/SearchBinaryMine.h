#pragma once
#include "common.h"

class BinarySearchMisc {
  // No.367 Valid Perfect Square
// Given a positive integer num, write a function which returns True if num is a perfect square else False.
// Note: Do not use any built-in library function such as sqrt.
  bool isPerfectSquare(int num) {
        // start from n/2, --, 
        int left = 0, right = num;
        while(left <= right){
            long pos = (left+right) >> 1;
            long ans = pos * pos;
            if(ans == num)
                return true;
            if(ans < num){
                left = pos + 1;
            }else{
                right = pos - 1;
            }
        }
        return false;
    }
  // No.374 Guess Number Higher or Lower
// We are playing the Guess Game. The game is as follows:
// I pick a number from 1 to n. You have to guess which number I picked.
// Every time you guess wrong, I'll tell you whether the number is higher or lower.
// You call a pre-defined API guess(int num) which returns 3 possible results (-1, 1, or 0):
// -1 : My number is lower
//  1 : My number is higher
//  0 : Congrats! You got it!
  int guessNumber(int n) {
        long left = 1, right = n;
        while(left <= right){
            long pos = (left+right) >> 1;
            int ans = guess((int)pos);
            //cout << pos << ":" << ans << "\n";
            if(ans == 0)
                return (int)pos;
            if(ans == -1){
                // higher
                right = pos-1;
            }else
                // lower
                left = pos+1;
        }
        return -1;
    }
  // No.441 Arranging Coins
  // You have a total of n coins that you want to form in a staircase shape, where every k-th row must have exactly k coins.
  // Given n, find the total number of full staircase rows that can be formed.
  // n is a non-negative integer and fits within the range of a 32-bit signed integer.
  // Example 1:
  // n = 5
  // The coins can form the following rows:
  // ¤
  // ¤ ¤
  // ¤ ¤

Because the 3rd row is incomplete, we return 2.
  int arrangeCoins(int n) {
        // (1+k)*k/2 < n, find largest k
        // k*k + k < 2n < k*k + 3k + 2
        // k < sqrt(2n)
        long helper = sqrt(2 * (long)n);
        while(helper > 0){
            if(helper * (helper+1L) <= (long)n*2)
                return (int)helper;
            --helper;
        }
        return 0;
    }
  // No.475 Heaters
  // Winter is coming! Your first job during the contest is to design a standard heater with fixed warm radius to warm all the houses.
  // Now, you are given positions of houses and heaters on a horizontal line, find out minimum radius of heaters so that all houses could be covered by those heaters.
  // So, your input will be the positions of houses and heaters seperately, and your expected output will be the minimum radius standard of heaters.
  // Note:
  // Numbers of houses and heaters you are given are non-negative and will not exceed 25000.
  // Positions of houses and heaters you are given are non-negative and will not exceed 10^9.
  // As long as a house is in the heaters' warm radius range, it can be warmed.
  // All the heaters follow your radius standard and the warm radius will the same.
  // Example 1:
  // Input: [1,2,3],[2]
  // Output: 1
  // Explanation: The only heater was placed in the position 2, and if we use the radius 1 standard, then all the houses can be warmed.
  // Example 2:
  // Input: [1,2,3,4],[1,4]
  // Output: 1
  // Explanation: The two heater was placed in the position 1 and 4. We need to use radius 1 standard, then all the houses can be warmed.
    int findRadius(vector<int>& houses, vector<int>& heaters) {
        int ans = 0;
        sort(houses.begin(), houses.end());
        sort(heaters.begin(), heaters.end());
        if(houses[0] >= heaters.back()){
            // all the houses are largers than heaters
            ans = houses.back() - heaters.back();
        }else if(heaters.size() == 1){
            ans = max(abs(houses.back()-heaters[0]), abs(houses.front()-heaters[0]));
        }else{
            int i,j;
            for(i = 0, j = 0; i < houses.size() && j < heaters.size()-1;){
                if(houses[i] > heaters[j+1])
                    ++j;
                else{
                    int cur = min(abs(houses[i] - heaters[j]), abs(houses[i] - heaters[j+1]));
                    ans = max(cur, ans);
                    ++i;
                }
            }
            for(; i < houses.size(); i++){
                int cur = abs(houses[i] - heaters.back());
                    ans = max(cur, ans);
            }
        }
        return ans;
    }
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
