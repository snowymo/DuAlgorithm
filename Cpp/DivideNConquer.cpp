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
  
  // No.215 Kth Largest Element in an Array
  // Find the kth largest element in an unsorted array. Note that it is the kth largest element in the sorted order, not the kth distinct element.
  // the below is an unoptimized solution. Quicksort/quickselection should be the ideal way
  int findKthLargest(vector<int>& nums, int k) {
        // insert the element into a sorted array
        // discard the k+1 largest one to save time of insertion
        vector<int> sortedNums;
        for(int i = 0; i < nums.size(); i++){
            int j = 0;
            for(; j < sortedNums.size(); j++){
                if(nums[i] >= sortedNums[j]){
                     break;
                }
            }
            cout << ":" << j << "\n";
            if(j!=-1)
                sortedNums.insert(sortedNums.begin()+j, nums[i]);
            //print(sortedNums);
            int size = sortedNums.size();
            while(size-- > k)
                sortedNums.pop_back();
            //print(sortedNums);
        }
        return sortedNums[k-1];
    }
}
