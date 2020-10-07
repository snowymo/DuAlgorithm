#pragma once
#include "common.h"

class BinarySearchMisc {
  // No.69 Sqrt(x)
//   Implement int sqrt(int x).

// Compute and return the square root of x, where x is guaranteed to be a non-negative integer.

// Since the return type is an integer, the decimal digits are truncated and only the integer part of the result is returned.
  int mySqrt(int x) {
        long left = 0, right = x;
        while(left <= right){
            long pos = (left+right) >> 1;
            long cur = pos * pos;
            if(cur == x)
                return (int)pos;
            if(cur > x){
                right = pos - 1;
            }else if(cur < x){
                left = pos + 1;
            }
        }
        return (int)right;
    }
  // No.167  Two Sum II - Input array is sorted
// Given an array of integers that is already sorted in ascending order, find two numbers such that they add up to a specific target number.

// The function twoSum should return indices of the two numbers such that they add up to the target, where index1 must be less than index2.

// Note:

// Your returned answers (both index1 and index2) are not zero-based.
// You may assume that each input would have exactly one solution and you may not use the same element twice.
// Example:

// Input: numbers = [2,7,11,15], target = 9
// Output: [1,2]
// Explanation: The sum of 2 and 7 is 9. Therefore index1 = 1, index2 = 2.
  vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> ret;
        for(int i = 0; i < numbers.size()-1; i++){
            int substract = target - numbers[i];
            int left = i+1, right = numbers.size()-1;
            while(left <= right){
                int pos = (left+right) >> 1;
                if(numbers[pos] == substract){
                    ret.push_back(i+1);
                    ret.push_back(pos+1);
                    return ret;
                }
                if(numbers[pos] < substract){
                    left = pos+1;
                }else{
                    right = pos-1;
                }
            }
        }
        return ret;
    }
  // No.278 First Bad Version
// You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.

// Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.

// You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

// Example:

// Given n = 5, and version = 4 is the first bad version.

// call isBadVersion(3) -> false
// call isBadVersion(5) -> true
// call isBadVersion(4) -> true

// Then 4 is the first bad version. 
  int firstBadVersion(int n) {
        long left = 0, right = n;
        while(left < right){
            long pos = (left+right) >> 1;
            if(isBadVersion(pos)){
                right = pos;
            }else{
                left = pos+1;
            }
        }
        return (int)left;
    }
  // No.350 Intersection of Two Arrays II
// Given two arrays, write a function to compute their intersection.

// Example 1:

// Input: nums1 = [1,2,2,1], nums2 = [2,2]
// Output: [2,2]
// Example 2:

// Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
// Output: [4,9]
// Note:

// Each element in the result should appear as many times as it shows in both arrays.
// The result can be in any order.
// Follow up:

// What if the given array is already sorted? How would you optimize your algorithm?
// What if nums1's size is small compared to nums2's size? Which algorithm is better?
// What if elements of nums2 are stored on disk, and the memory is limited such that you cannot load all elements into the memory at once?
  vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
        // using map
        unordered_map<int, int> count;
        vector<int> ans;
        for(int i = 0; i < nums1.size(); i++){
            ++count[nums1[i]];
        }
        for(int i = 0; i < nums2.size(); i++){
            if(count.find(nums2[i]) != count.end()){
                if(count[nums2[i]] > 0){
                    --count[nums2[i]];
                    ans.push_back(nums2[i]);
                }
            }
        }
        return ans;
    }
    // if nums1 and nums2 are sorted, we can have two indices to scan them together
    // if nums1.size() < nums2.size(), sort nums2 and do binary search for nums2
    // if nums2 has too many elements, ... do it batchly
  
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
  
//   15. 3Sum
//   Given an array nums of n integers, are there elements a, b, c in nums such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero.

// Notice that the solution set must not contain duplicate triplets.
  bool binarySearch(vector<int>& num, int start, int end, int v){
        bool ret = false;
        
        while(true){
            if(start >= end)
                return false;
            if(num[start] == v)
                return true;
            if(num[end-1] == v)
                return true;
                
            int mid = (start + end) >> 1;
            if(num[mid] == v){
                return true;
            }
            if(num[mid] > v){
                end = mid;
            }else{
                start = mid+1;
            }
        }
        return false;
    }
    
    vector<vector<int>> threeSum1(vector<int>& numbers) {
        vector<vector<int>> ret;
        // first sort
        int len = numbers.size();
        sort(numbers.begin(), numbers.end());
        // iterate with binary search
        std::unordered_map<int,bool> mymap0;
        for(int i = 0; i < len-2; i++){
            if(numbers[i] > 0)
                break;
            // cout << "i " << i << ":" << numbers[i] << "\n";
            if(i > 0 && numbers[i] == numbers[i-1])
                continue;
            
            for(int j = i+1; j < len-1; j++){
                if(j > (i+1) && numbers[j] == numbers[j-1])
                    continue;
                
                int v = -numbers[i]-numbers[j];
                if(v < 0)
                    break;
                // cout << "\tj " << j << ":" << numbers[j] << "\n";                
                // find if we have value v

                bool findV = binarySearch(numbers,  j+1,  len,  v);
                if(findV){
                    ret.push_back(vector<int>{numbers[i], numbers[j], v});
                }
                // cout << "\t\tfind " << v << ":" << findV << "\n";
                
            }
            
        }
        return ret;
    }
    
    vector<vector<int>> threeSum(vector<int>& numbers) {
        vector<vector<int>> ret;
        // first sort
        int len = numbers.size();
        sort(numbers.begin(), numbers.end());
        // iterate with binary search
        std::unordered_map<int,bool> mymap0;
        for(int i = 0; i < len-2; i++){
            if(numbers[i] > 0)
                break;
            // cout << "i " << i << ":" << numbers[i] << "\n";
            if(i > 0 && numbers[i] == numbers[i-1])
                continue;
            
//             two pointer
            int v = -numbers[i];
            int start = i+1;
            int end = len-1;
            while(start < end){                
                if(numbers[start] + numbers[end] == v){
                    ret.push_back(vector<int>{numbers[i], numbers[start], numbers[end]});
                    while((start < len-1) && numbers[start] == numbers[start+1])
                        ++start;
                    while((end > i+1) && numbers[end] == numbers[end-1])
                        --end;
                    
                    ++start;
                    --end;
                }
                else if(numbers[start] + numbers[end] < v){
                    ++start;
                }else{
                    --end;
                }
            }
            
        }
        return ret;
    }
}
