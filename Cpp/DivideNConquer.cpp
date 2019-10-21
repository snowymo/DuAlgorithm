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
  
  // No.241 Different Ways to Add Parentheses
  // Given a string of numbers and operators, 
  // return all possible results from computing all the different possible ways to group numbers and operators. 
  // The valid operators are +, - and *.
  // Finish after read the discussion
  map<pair<int,int>, vector<int>> cache;
    
    vector<int> diffWaysHelper(string input, int start, int end){
        pair<int,int> curPair = make_pair(start, end);
        if(cache.find(curPair) != cache.end())
            return cache[curPair];
        
        // for through the operators one by one
        vector<int> left, right, ans;
        
        bool isOp = false;
        for(int i = start; i <= end; i++){
            if(!isdigit(input[i])){
                isOp = true;
                //cout << start << "," << i-1 << "\n";
                //cout << i+1 << "," << end << "\n\n";
                left = diffWaysHelper(input, start, i-1);
                right = diffWaysHelper(input, i+1, end);

                for(int lefti = 0; lefti < left.size(); lefti++){
                    for(int rightj = 0; rightj < right.size(); rightj++){
                        if(input[i] == '+')
                            ans.push_back(left[lefti] + right[rightj]);
                        else if(input[i] == '-')
                            ans.push_back(left[lefti] - right[rightj]);
                        else if(input[i] == '*')
                            ans.push_back(left[lefti] * right[rightj]);
                    }
                }    
            }
        }    
        if(!isOp)
            ans.push_back(stoi(input.substr(start, end-start+1)));

        cache[curPair] = ans;
        return ans;
    }
    vector<int> diffWaysToCompute(string input) {
        return diffWaysHelper(input, 0, input.size()-1);
    }
  
  // No.932 Beautiful Array
  // For some fixed N, an array A is beautiful if it is a permutation of the integers 1, 2, ..., N, such that:
  // For every i < j, there is no k with i < k < j such that A[k] * 2 = A[i] + A[j].
  // Given N, return any beautiful array A.  (It is guaranteed that one exists.)
  // Finish after read the solution
  map<int, vector<int>> ans;
    vector<int> beautifulArray(int N) {
        // it is not a medium
        // solve this problem linearly
        // let's say we have solution for two arrays, we concatenate them as [a,b] and this new array fit the requirement too
        // if x meets the condition, ax+b meets too
        if(N == 1){
            ans[N] = vector<int>(1,1);
        }            
        else{
            vector<int> cur;
            // construct the vector with [left,right]
            vector<int> odd = beautifulArray((N+1)/2);
            for(int i = 0; i < odd.size(); i++)
                cur.push_back(odd[i]*2-1);
            vector<int> even = beautifulArray((N)/2);
            for(int i = 0; i < even.size(); i++)
                cur.push_back(even[i]*2);
            ans[N] = cur;
        }        
        return ans[N];
    }
  // optimized: instead of calculating each value, we only calculate the odd now, and use the odd result for even
  // remember to get rid of the number which is larger than N
  vector<int> beautifulArray(int N) {
        vector<int> cur;
        if(N == 1){
            cur = vector<int>(1,1);
        }            
        else{
            // construct the vector with [left,right]
            vector<int> odd = beautifulArray((N+1)/2);
            int evensize = odd.size();
            
            for(int i = 0; i <  odd.size(); i++)
                cur.push_back(odd[i]*2-1);
            //vector<int> even = beautifulArray((N)/2);
            for(int i = 0; i < odd.size(); i++)
                if(odd[i]*2 <= N)
                    cur.push_back(odd[i]*2);
        }        
        return cur;
    }

  // No.4 Median of Two Sorted Arrays
  // There are two sorted arrays nums1 and nums2 of size m and n respectively.
  // Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
  // You may assume nums1 and nums2 cannot be both empty.
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        
        vector<int> ans;
        int n = nums1.size();
        int m = nums2.size();
        int ideal = (n+m+1)/2;
        int ideal2 = ideal;
        if((n+m) % 2 == 0)
            ++ideal2;
        
        
        int count = 0;
        int large = 0, preLarge = 0;
        
        int mIndex = 0;
        int nIndex = 0;
        double left = INT_MIN;
        double right = INT_MIN;
        
        
        while(nIndex < n && mIndex < m){
            if(nums1[nIndex] > nums2[mIndex]){
                ++count;
                preLarge = large;
                large = nums2[mIndex];
                cout << "add " << nums2[mIndex] << "\n";
                ++mIndex;
            }else{
                ++count;
                preLarge = large;
                large = nums1[nIndex];
                cout << "add " << nums1[nIndex] << "\n";
                ++nIndex;
            }
            if(count == ideal){
                left = large;
                cout << "left = " << left << "\n";
            }
            if(count == ideal2){
                right = large;
                cout << "return " << (left+right)/2 << "\n";
                return (left+right)/2;
            }
        }
        
        if(nIndex >= n){
            if(left == INT_MIN)
                left = nums2[mIndex+ideal-1-count];
            return double(left+ nums2[mIndex+ideal2-1-count])/2;
        }
        if(mIndex >= m){
            if(left == INT_MIN)
                left = nums1[nIndex+ideal-1-count];
            return double(left + nums1[nIndex+ideal2-1-count])/2;
        }
        return 0;
    }
