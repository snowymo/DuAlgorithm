#pragma once
#include "common.h"

namespace ArrayInPlace {
	// 26. Remove Duplicates from Sorted Array [E]
	// Given a sorted array nums, remove the duplicates in-place such that each element appear only once and return the new length.
	int removeDuplicates(vector<int>& nums) {
		if (nums.empty())
			return 0;
		int index = 0;
		for (int i = 0; i < (int)nums.size(); ++i) {
			if (nums[index] != nums[i])
				nums[++index] = nums[i];
		}
		return index + 1;
	}
	// mine
	int removeDuplicates(vector<int>& nums) {
		int len = nums.size();
		if(len < 1)
		    return len;

		int curValue = nums[0];
		int curIndex = 1;
		for(int startIndex = 0; startIndex < len-1; startIndex++){
		    if(nums[startIndex+1] > curValue){
			//curValue = nums[startIndex+1];
			nums[curIndex++] = curValue= nums[startIndex+1];
			//++curIndex;
		    }
		}
		return curIndex;
	    }

	// 80. Remove Duplicates from Sorted Array II
	// Given a sorted array nums, remove the duplicates in-place such that duplicates appeared at most twice and return the new length.
	// Do not allocate extra space for another array, you must do this by modifying the input array in - place with O(1) extra memory.
	int removeDuplicates2(vector<int>& nums) {
		auto n = (int)nums.size();
		if (n <= 2) return n;
		int index = 2;

		for (size_t i = index; i < n; ++i) {
			if (nums[i] != nums[index - 2]) nums[index++] = nums[i];
		}
		return index;
	}
	// mine
	int removeDuplicates(vector<int>& nums) {
		if(nums.size() < 2)
		    return nums.size();

		int dupCount = 0;
		int curIndex = 0;
		int curValue = nums[curIndex];
		for(int nextIndex = 0; nextIndex < nums.size(); nextIndex++){
		    if(curValue == nums[nextIndex]){
			++dupCount;
			if(dupCount >= 3){
			    continue;
			}
			//curValue = nums[curIndex];
		    }else{
			// new value
			dupCount = 1;
			curValue = nums[nextIndex];
		    }    
		    nums[curIndex] = curValue;
		    ++curIndex;
		}
		return curIndex;
	    }

	// 27. Remove Element [E]
	// Given an array nums and a value val, remove all instances of that value in-place and return the new length.
	int removeElement(vector<int>& nums, int val) {
		if (nums.empty())
			return 0;
		int index = 0;
		for (int i = 0; i < nums.size(); ++i) {
			if (nums[i] != val)
				nums[index++] = nums[i];
		}
		return index;
	}
	// mine
	int removeElement(vector<int>& nums, int val) {
		int curIndex = 0;
		int nextIndex = 0;
		for(;nextIndex < nums.size(); nextIndex++){
		    if(nums[nextIndex] != val){
			nums[curIndex++] = nums[nextIndex];                
		    }
		}
		return curIndex;
	    }
	
	// 283. Move Zeroes
	// Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.
	// mine
	void moveZeroes(vector<int>& nums) {
		int firstZeroIndex = 0;
		int nextNonZeroIndex = firstZeroIndex+1;
		int len = nums.size();
		while(nextNonZeroIndex < len){
		    // find zero
		    for(; firstZeroIndex < len; firstZeroIndex++){
			if(nums[firstZeroIndex] == 0)
			    break;
		    }
		    if(firstZeroIndex >= len)
			break;
		    // find non-zero
		    for(nextNonZeroIndex = firstZeroIndex+1; nextNonZeroIndex < len; nextNonZeroIndex++){
			if(nums[nextNonZeroIndex] != 0)
			    break;
		    }            
		    if(nextNonZeroIndex >= len)
			break;
		    // swap
		    nums[firstZeroIndex] = nums[nextNonZeroIndex];
		    nums[nextNonZeroIndex] = 0;
		    ++firstZeroIndex;
		    ++nextNonZeroIndex;
		}
	    }
	// better
	void moveZeroes(vector<int>& nums) {
		int lastNonZeroFoundAt = 0;
		int len = nums.size();
		// If the current element is not 0, then we need to
		// append it just in front of last non 0 element we found. 
		for (int i = 0; i < len; i++) {
		    if (nums[i] != 0) {
			nums[lastNonZeroFoundAt++] = nums[i];
		    }
		}
		// After we have finished processing new elements,
		// all the non-zero elements are already at beginning of array.
		// We just need to fill remaining array with 0's.
		for (; lastNonZeroFoundAt < len; lastNonZeroFoundAt++) {
		    nums[lastNonZeroFoundAt] = 0;
		}
	    }
	// 203. Remove Linked List Elements
	// Remove all elements from a linked list of integers that have value val.
	ListNode* removeElements(ListNode* head, int val) {
		ListNode* headhead = new ListNode(val-1);
		headhead->next = head;
		ListNode* lastPtr = headhead, *curPtr = head;
		while(curPtr){
		    if(curPtr->val == val){
			lastPtr->next = curPtr->next;
		    }else
			lastPtr = lastPtr->next;
		    curPtr = curPtr->next;            
		}
		return headhead->next;
	    }
	// 237. Delete Node in a Linked List
	// Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.
	void deleteNode(ListNode* node) {
		node->val = node->next->val;
		node->next = node->next->next;        
	    }
	
	// 268. Missing Number
	// Given an array containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array.
	int missingNumber(vector<int>& nums) {
		int len = nums.size();
		int sum = (0+len)*(len+1)/2;
		for(int i = 0; i < len; i++){
		    sum -= nums[i];
		}
		return sum;
	    }

	// 41. First Missing Positive [H]
	// Given an unsorted integer array, find the smallest missing positive integer.
	/*
	Input: [7,8,9,11,12]
	Output: 1

	Input: [1,2,0]
	Output: 3

	Input: [3,4,-1,1]
	Output: 2
	*/
	// Time: O(N)
	int firstMissingPositive(vector<int>& nums) {
		const int n = (int)nums.size();
		for (int i = 0; i < n; ++i) {
			while (nums[i] != i + 1) {
				if (nums[i] <= 0 || nums[i] > n || nums[i] == nums[nums[i] - 1])
					break;
				swap(nums[i], nums[nums[i] - 1]);
			}
		}

		for (int i = 0; i < n; ++i)
			if (nums[i] != (i + 1))
				return i + 1;
		return n + 1;
	}
}
