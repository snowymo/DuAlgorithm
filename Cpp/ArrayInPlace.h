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
	
	// 283. Move Zeroes (Mine)
	// Given an array nums, write a function to move all 0's to the end of it while maintaining the relative order of the non-zero elements.
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
	// 203. Remove Linked List Elements (Mine)
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
	// 237. Delete Node in a Linked List (Mine)
	// Write a function to delete a node (except the tail) in a singly linked list, given only access to that node.
	void deleteNode(ListNode* node) {
		node->val = node->next->val;
		node->next = node->next->next;        
	    }
	
	// 268. Missing Number (Mine)
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
	// mine
	void assignInPlace(vector<int>& nums, int pos, int val){
		int temp = nums[val-1];
		if(temp < 0){
		    // already set
		    if(nums[pos] > 0)
			nums[pos] = 0;
		    return;
		}
		if(temp == val || temp == 0){
		    nums[val-1] = -val;
		    if(nums[pos] > 0)
			nums[pos] = 0;
		    return;
		}
		nums[val-1] = -val;
		assignInPlace(nums, pos, temp);
	    }
	    int firstMissingPositive(vector<int>& nums) {
		int len = nums.size();
		for(int i = 0; i < len; i++){
		    if(nums[i] < 0 || nums[i] > len){
			nums[i] = 0;
		    }
		}
		for(int i = 0; i < len; i++){
		    if(nums[i] > 0){
			assignInPlace(nums,i,nums[i]);
		    }
		}
		int ans = nums.size()+1;
		for(int i = 0; i < len; i++){
		    if(nums[i] == 0){
			ans = i+1;
			break;
		    }
		}
		return ans;
	    }
	// No.448. Find All Numbers Disappeared in an Array
	// Given an array of integers where 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.
	// Find all the elements of [1, n] inclusive that do not appear in this array.
	// Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.
	// mine
	void assignInPlace(vector<int>& nums, int pos, int val){
		if(val <= 0)
		    return;

		int temp = nums[val-1];        
		if(temp == val){
		    nums[val-1] = -val;
		    if(nums[pos] > 0)
			nums[pos] = 0;
		    return;   
		}
		if(temp < 0){
		    //already assigned
		    if(nums[pos] > 0)
			nums[pos] = 0; 
		    return;
		}

		nums[val-1] = -val;
		if(nums[pos] > 0)
		    nums[pos] = 0; 
		assignInPlace(nums, pos, temp);
	    }

	    vector<int> findDisappearedNumbers(vector<int>& nums) {
		vector<int> ret;
		for(int i = 0; i < nums.size(); i++){
		    assignInPlace(nums, i, nums[i]);
		}
		for(int i = 0; i < nums.size(); i++){
		    if(nums[i] == 0){
			ret.push_back(i+1);
		    }
		}
		return ret;
	    }
	
	// No.442. Find All Duplicates in an Array (Mine)
	// Given an array of integers, 1 ≤ a[i] ≤ n (n = size of array), some elements appear twice and others appear once.
	// Find all the elements that appear twice in this array.
	// Could you do it without extra space and in O(n) runtime?
	vector<int> findDuplicates(vector<int>& nums) {
		vector<int> ret;
		for(int i = 0; i < nums.size(); i++){
		    nums[abs(nums[i])-1] *= -1;
		    if(nums[abs(nums[i])-1] > 0)
			ret.push_back(abs(nums[i]));
		}
		return ret;
	    }
	
	// No.287. Find the Duplicate Number (Mine)
	// Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), 
	// prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one.
	// You must not modify the array (assume the array is read only).
	// You must use only constant, O(1) extra space.
	// Your runtime complexity should be less than O(n2).
	// There is only one duplicate number in the array, but it could be repeated more than once.
	int findDuplicate(vector<int>& nums) {
		int len = nums.size();
		for(int i = 0; i < len; i++){
		    for(int j = i+1; j < len; j++){
			if(nums[i] == nums[j])
			    return nums[i];
		    }
		}
		return 0;
	    }
	
	// No.765. Couples Holding Hands
	// N couples sit in 2N seats arranged in a row and want to hold hands. We want to know the minimum number of swaps so that every couple is sitting side by side. A swap consists of choosing any two people, then they stand up and switch seats.
	// The people and seats are represented by an integer from 0 to 2N-1, the couples are numbered in order, the first couple being (0, 1), the second couple being (2, 3), and so on with the last couple being (2N-2, 2N-1).
	// The couples' initial seating is given by row[i] being the value of the person who is initially sitting in the i-th seat.
	int minSwapsCouples(vector<int>& row) {
		int count = 0;
		// check how many couples are not together
		//bool flag = true;
		//while(flag){
		    //flag = false;
		    for(int i = 0; i < row.size(); i++){
			int delta = row[i] % 2 == 0 ? 1 : -1;
			int neighbour1 = i % 2 == 0 ? i+1 : i-1;
			if((row[neighbour1]-row[i] == delta)){
			    // they are couples already
			    continue;
			}
			//flag = true;
			// the other half is not by side
			for(int j = 0; j < row.size(); j++){
			    if(row[j] - row[i] == delta){
				swap(row[j], row[neighbour1]);
				++count;
				    ++i;
				break;
			    }
			}
		    }    
		//}        
		return count;
	    }
	// use map
	int minSwapsCouples(vector<int>& row) {
		int count = 0;
		std::map<int,int> mapValueIndex;
		for(int i = 0; i < row.size(); i++){
		    mapValueIndex[row[i]] = i;
		}
		for(int i = 0; i < row.size(); i++){
		    int delta = row[i] % 2 == 0 ? 1 : -1;
		    int neighbour1 = i % 2 == 0 ? i+1 : i-1;
		    if((row[neighbour1]-row[i] == delta)){
			// they are couples already
			continue;
		    }

		    // the other half is not by side
		    swap(row[neighbour1], row[mapValueIndex[row[i]+delta]]);
		    ++count;
		    mapValueIndex[row[mapValueIndex[row[i]+delta]]] = mapValueIndex[row[i]+delta];
		    mapValueIndex[row[neighbour1]] = neighbour1;//won't be visited anymore            
		}    

		return count;
	    }
	
 	// No.1 Two Sum (Mine)
	// Given an array of integers, return indices of the two numbers such that they add up to a specific target.
	// You may assume that each input would have exactly one solution, and you may not use the same element twice.

	// Example:
	// Given nums = [2, 7, 11, 15], target = 9,
	// Because nums[0] + nums[1] = 2 + 7 = 9,
	// return [0, 1].
	vector<int> twoSum2(vector<int>& nums, int target) {
		vector<int> ret(2);
		for(int i = 0; i < nums.size()-1; i++){
		    ret[0] = i;
		    for(int j = i+1; j < nums.size(); j++){
			if(nums[i] + nums[j] == target){
			    ret[1] = j;
			    return ret;
			}
		    }
		}
		return ret;
	    }
	    vector<int> twoSum(vector<int>& nums, int target) {
		map<int,int> mymap;
		for(int i = 0; i < nums.size(); i++)
		    mymap[nums[i]] = i;
		vector<int> ret(2);
		for(int i = 0; i < nums.size()-1; i++){
		    //cout << "check " << i << " want to find " << target-nums[i] << "\n";
		    if(mymap.find(target-nums[i]) != mymap.end()
		      && mymap[target-nums[i]] != i ){
			ret[0] = i;
			ret[1] = mymap[target-nums[i]];
			return ret;
		    }
		}
		return ret;
	    }
	// No.189[E] Rotate Array (Mine)
// Given an array, rotate the array to the right by k steps, where k is non-negative.

// Example 1:

// Input: [1,2,3,4,5,6,7] and k = 3
// Output: [5,6,7,1,2,3,4]
// Explanation:
// rotate 1 steps to the right: [7,1,2,3,4,5,6]
// rotate 2 steps to the right: [6,7,1,2,3,4,5]
// rotate 3 steps to the right: [5,6,7,1,2,3,4]
	void rotate(vector<int>& nums, int k) {
		int len = nums.size();
		int temp, temp2;
		k = k % len;
		int times = 0;
		for(int i = 0; i < k; i++){
		    int stop = 0;    
		    int oldIndex = i;
		    temp = nums[oldIndex];
		    while(stop < 2 && times < k){
			// cout << oldIndex << "\t";
			if(oldIndex == i){
			    ++stop;
			}
			int newIndex = oldIndex + k;
			if(newIndex >= len){
			    ++times;
			    newIndex -= len; 
			}
			// cout << i << "\t";
			temp2 = nums[newIndex];
			// cout << "stop" << stop << "\t";
			// cout << "nums[" << newIndex <<"]:" << nums[newIndex] << "\t";
			// cout << "nums[" << oldIndex <<"]:" << nums[oldIndex] << "\t";
			nums[newIndex] = temp;
			// cout << "nums[" << newIndex <<"]:" << nums[newIndex] << "\n\n";
			temp = temp2;
			oldIndex = newIndex;
		    }
		}
	    }
}
