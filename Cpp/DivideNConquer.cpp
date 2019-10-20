#pragma once
#include "common.h"

namespace DivideNConquer {//Mine
  // No.53 Maximum Subarray
  // Given an integer array nums, find the contiguous subarray (containing at least one number) which has the largest sum and return its sum.
  int maxSubArray(vector<int>& nums) {
        int curMax = nums[0];
        int allMax = curMax;
        for(int i = 1; i < nums.size(); i++){
            curMax = max(curMax+nums[i], nums[i]);
            if(curMax > allMax)
                allMax = curMax;
        }
        return allMax;
    }
  
  // No.169 Majority Element
  // Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.
  // You may assume that the array is non-empty and the majority element always exist in the array.
  int majorityElement(vector<int>& nums) {
        int count = nums.size()/2;
        map<int,int> mymap;
        for(int i = 0; i < nums.size(); i++){
           if(++mymap[nums[i]] > count)
               return nums[i];
        }
        return 0;
    }
}
