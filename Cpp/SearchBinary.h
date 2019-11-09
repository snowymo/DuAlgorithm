#pragma once
#include "common.h"

// lower_bound: returns an iterator pointing to the first element in the range [first, last), which is greater or equal to) val, in log2(last - first)
// upper_bound: returns an iterator pointing to the first element in the range [first,last) which compares greater than val.
class BinarySearch {
	// Search key, return the first value >= key [E]
	int binarySearch(vector<int>& A, int l, int r, int key) {
		while (l <= r) {
			int p = (l + r) >> 1;
			if (key == A[p])
				return p;
			if (key > A[p]) {
				l = p + 1;
			}
			else {
				r = p - 1;
			}
		}
		return l;
	}

	// 35. Search Insert Position
	int searchInsert(vector<int>& nums, int target) {
		int l = 0, r = (int)nums.size() - 1;
		while (l <= r) {
			int id = (l + r) >> 1;
			int x = nums[id];
			if (x == target) {
				return id;
			}
			if (x > target) {
				r = id - 1;
			}
			else {
				l = id + 1;
			}
		}
		return l;
	}
	// Mine
	int searchInsert(vector<int>& nums, int target) {
		int left = 0, right = nums.size()-1;
		while(right > left){
		    //cout << left << ":"<< right << "\n";
		    int pos = (left+right) >> 1;
		    if(target == nums[pos])
			return pos;
		    if(target > nums[pos])
			left = pos+1;
		    else
			right = pos - 1;
		}
		return (target > nums[left]) ? left+1 : left;
	    }

	// 33. Search in Rotated Sorted Array
	// Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
	// (i.e., [0, 1, 2, 4, 5, 6, 7] might become[4, 5, 6, 7, 0, 1, 2]).
	/*
	Input: nums = [4,5,6,7,0,1,2], target = 0
	Output: 4
	*/
	int search(vector<int>& nums, int target) {
		int first = 0, last = (int)nums.size();
		while (first != last) {
			const int mid = first + (last - first) / 2;
			if (nums[mid] == target) return mid;
			if (nums[first] <= nums[mid]) {
				if (nums[first] <= target && target < nums[mid]) {
					last = mid;
				}
				else {
					first = mid + 1;
				}
			}
			else {
				if (nums[mid] < target && target <= nums[last - 1]) {
					first = mid + 1;
				}
				else {
					last = mid;
				}
			}
		}
		return -1;
	}
	// Mine
	int search(vector<int>& nums, int target) {
		if(nums.size() == 0)
		    return -1;
		float delta = nums[0]-0.5;
		int left = 0, right = nums.size()-1;
		while(left <= right){
		    int pos = (left+right) >> 1;
		    if(nums[pos] == target)
			return pos;

		    float multiply = ((float)nums[pos]-delta) * ((float)target - delta);
		    //cout << nums[pos] << " " << multiply << "\n";
		    if(multiply > 0){
			// same side
			if(nums[pos] > target)
			    right = pos-1;
			if(nums[pos] < target)
			    left = pos+1;
		    }else if(multiply < 0){
			// different side
			if(nums[pos] < delta)
			    right = pos-1;
			if(nums[pos] > delta)
			    left = pos+1;
		    }else{
			if(target == delta)
			    return 0;
			return -1;
		    }
		}
		return -1;
	    }

	// 81. Search in Rotated Sorted Array II
	// Suppose an array sorted in ascending order is rotated at some pivot unknown to you beforehand.
	// (i.e., [0, 0, 1, 2, 2, 5, 6] might become[2, 5, 6, 0, 0, 1, 2]).
	// You are given a target value to search.If found in the array return true, otherwise return false.
	bool search2(vector<int>& nums, int target) {
		int l = 0, r = (int)nums.size() - 1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (nums[mid] == target) return true;
			if (nums[l] < nums[mid]) {
				if (nums[l] <= target && target < nums[mid]) {
					r = mid - 1;
				}
				else {
					l = mid + 1;
				}
			}
			else
				if (nums[l] > nums[mid]) {
					if (nums[mid] < target && target <= nums[r]) {
						l = mid + 1;
					}
					else {
						r = mid - 1;
					}
				}
				else {
					// duplicated
					++l;
				}
		}
		return false;
	}
	// Mine
	bool search(vector<int>& nums, int target) {
		if(nums.size() == 0)
		    return false;

		int delta = nums[0];
		if(target == delta)
		    return true;

		int left = 0;
		while(left < nums.size()-1){
		    if(nums[++left] != delta)
			break;
		}
		if(left >= nums.size())
		    return false;

		float fdelta = nums[left]-0.5;
		int right = nums.size()-1;
		while(left <= right){
			    int pos = (left+right) >> 1;
			    if(nums[pos] == target)
				    return true;

			    float multiply = ((float)nums[pos]-fdelta) * ((float)target - fdelta);
			    //cout << nums[pos] << " " << multiply << "\n";
			    if(multiply > 0){
				// same side
			if(nums[pos] > target)
			    right = pos-1;
			if(nums[pos] < target)
			    left = pos+1;
		    }else if(multiply < 0){
		    // different side
			if(nums[pos] < fdelta)
			    right = pos-1;
			if(nums[pos] > fdelta)
			    left = pos+1;
		    }else{
			if(target == fdelta)
			    return true;
			return false;
		    }
		}
		return false;
	    }

	// 153. Find Minimum in Rotated Sorted Array
	// no duplicates
	int findMinNoDuplicates(vector<int>& nums) {
		int l = 0, r = (int)nums.size() - 1;
		while (l < r) {
			int p = (l + r) >> 1;
			if (nums[p] > nums[r])
				l = p + 1;
			else
				if (nums[p] < nums[p - 1])
					return nums[p];
				else
					r = p - 1;
		}
		return nums[l];
	}
	// Mine
	int findMin(vector<int>& nums) {
		if(nums.size() == 0)
		    return -1;
		int start = nums[0];
		int ret = start;
		int left = 0, right = nums.size()-1;
		while(left < right){
		    int pos = (left+right)>>1;
		    ret = min(ret,nums[pos]);

		    if(nums[pos] >= start)
			left = pos+1;
		    else{
			right = pos-1;
		    }
		    //cout << pos << " " << left << " " << right << "\n";
		}
		return min(ret,nums[left]);
	    }

	// 154. Find Minimum in Rotated Sorted Array II [H]
	// with duplicates
private:
	int findMin(vector<int>& nums, int l, int r) {
		while (l < r) {
			int p = (l + r) >> 1;
			if (nums[p] > nums[r])
				l = p + 1;
			else if (nums[p] < nums[p - 1])
				return nums[p];
			else if (nums[p] < nums[r])
				r = p - 1;
			else
				return min(min(findMin(nums, l, p - 1), findMin(nums, p + 1, r)), nums[p]);
		}
		return nums[l];
	}
public:
	int findMin(vector<int>& nums) {
		return findMin(nums, 0, (int)nums.size() - 1);
	}
	// Mine 
	int findMin(vector<int>& nums) {
		if(nums.size() == 0)
			    return -1;
		if(nums.size() == 1)
		    return nums[0];
			int left = 0, right = nums.size()-1;
		while(left < nums.size()-1){
		    if(nums[++left] != nums[0])
			break;
		}
		int start = nums[left];
			int ret = min(start, nums[0]);

		while(left < right){
			    int pos = (left+right)>>1;
			    ret = min(ret,nums[pos]);

			    if(nums[pos] >= start)
				left = pos+1;
			    else{
				right = pos-1;
			    }
			    //cout << pos << " " << left << " " << right << "\n";
			}
			return min(ret,nums[left]);
	    }

	// 34. Find First and Last Position of Element in Sorted Array
	// Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.
	/*
	Input: nums = [5,7,7,8,8,10], target = 8
	Output: [3,4]
	*/
	vector<int> searchRange(vector<int>& nums, int target) {
		int first = 0, last = (int)nums.size();
		const int l = (int)distance(nums.begin(), lower_bound(nums.begin(), nums.end(), target));
		const int u = (int)distance(nums.begin(), prev(upper_bound(nums.begin(), nums.end(), target)));

		if (nums[l] != target) return vector<int>{-1, -1};
		return vector<int> {l, u};
	}
	// Mine
	vector<int> searchRange(vector<int>& nums, int target) {
		vector<int> ret(2, -1);
		if(nums.size() < 1)
		    return ret;
		int left = 0, right = nums.size()-1;
		while(left <= right){
		    int pos = (left+right) >> 1;
		    if(nums[pos] > target){
			right = pos - 1;
		    }else if(nums[pos] < target){
			left = pos + 1;
		    }else{
					   // find the left
			ret[0] = searchLeft(nums, target, left, pos, true);
			ret[1] = searchLeft(nums, target, pos, right, false);
		       return ret; 
		    }
		}
		return ret;
	    }

	    int searchLeft(vector<int>& nums, int target, int left, int right, bool isLeft){
		while(left <= right){
		    int pos = (left+right) >> 1;
		    if(isLeft){
			if(nums[pos] == target){
			    right = pos-1;
			}else{
			    left = pos+1;
			}    
		    }
		    else{
			if(nums[pos] == target){
			    left = pos+1;                    
			}else{
			    right = pos-1;
			}
		    }
		}
		return isLeft ? right+1 : left-1;
	    }

	// 74. Search a 2D Matrix [M]
	// Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
	// Integers in each row are sorted from left to right.
	// The first integer of each row is greater than the last integer of the previous row.
	bool searchMatrix(vector<vector<int>> &matrix, int target) {
		auto n = (int)matrix.size();
		auto m = (int)matrix[0].size();
		int l = 0, r = n * m - 1;
		while (l <= r) {
			int p = (l + r) >> 1;
			int mid = matrix[p / m][p % m];
			if (mid < target) {
				l = p + 1;
			}
			else
				if (mid > target) {
					r = p - 1;
				}
				else {
					return true;
				}
		}
		return false;
	}
	// Mine
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		// binary search the first column
		// binary search the specific row
		if(matrix.size() == 0)
		    return false;
		if(matrix[0].size() == 0)
		    return false;
		int left = 0, right = matrix.size()-1;
		while(left <= right){
		    int pos = (left+right) >> 1;
		    if(matrix[pos][0] < target){
			left = pos+1;
		    }else if(matrix[pos][0] > target){
			right = pos - 1;
		    }else
			return true;
		}
		int row = left-1;
		if(row < 0)
		    return false;
		left = 0; right = matrix[row].size()-1;
		while(left <= right){
		    int pos = (left+right) >> 1;
		    if(matrix[row][pos] < target){
			left = pos+1;
		    }else if(matrix[row][pos] > target){
			right = pos - 1;
		    }else
			return true;
		}
		return false;
	    }


	// 162. Find peak element in an array [E]
	int findPeakElement(vector<int>& nums) {
		int n = (int)nums.size();
		if (n <= 1) return 0;
		int l = 0, r = n - 1;
		while (l < r) {
			int mid = (l + r) >> 1;
			if (nums[mid] < nums[mid + 1]) {
				l = mid + 1;
			}
			else {
				r = mid;
			}
		}
		return r;
	}
	// Mine
	int findPeakElement(vector<int>& nums) {
		if(nums.size() == 0)
		    return -1;
		if(nums.size() == 1)
		    return 0;
		if(nums.size() == 2)
		    return (nums[0] > nums[1]) ? 0 : 1;

		int step = 0;
		for(int i = 0; i < nums.size(); i++){
		    if(step == 0 && nums[i] >= 0){
			step = 1;
		    }
		    else if(step == 1 && nums[i] < nums[i-1]){
			return i-1;
		    }
		}
		return nums.size()-1;
	    }

	// 852. Peak Index in a Mountain Array [E]
	int peakIndexInMountainArray(vector<int>& A) {
		int l = 0, r = (int)A.size();
		while (l < r) {
			int p = (l + r) >> 1;
			if (A[p] > A[p + 1]) {
				r = p;
			}
			else {
				l = p + 1;
			}
		}
		return l;
	}
	// Mine
	int peakIndexInMountainArray(vector<int>& A) {
		return std::max_element(A.begin(),A.end()) - A.begin();
	    }
	// Not using STL. After reading Du's
	int peakIndexInMountainArray(vector<int>& A) {
		int left = 0, right = A.size()-1;
		while(left <= right){
		    int pos = (left+right) >> 1;
		    if(A[pos] < A[pos+1]){
			left = pos+1;
		    }
		    else if(A[pos] < A[pos-1]){
			right = pos-1;
		    }else
			return pos;
		}
		return left;
	    }

	// 719. Find K-th Smallest Pair Distance [H]
	// Given an integer array, return the k-th smallest distance among all the pairs. The distance of a pair (A, B) is defined as the absolute difference between A and B.
	// O(N log N)
	// http://blog.ruofeidu.com/719-find-k-th-smallest-pair-distance/
	int smallestDistancePair(vector<int>& nums, int k) {
		sort(nums.begin(), nums.end());
		int l = 0, r = nums[nums.size() - 1] - nums[0];
		while (r > l) {
			int mid = (l + r) >> 1;
			if (count(nums, mid) < k) {
				l = mid + 1;
			}
			else {
				r = mid;
			}
		}
		return r;
	}

	int count(vector<int>& nums, int mid) {
		int ans = 0, j = 0;
		for (int i = 1; i < nums.size(); ++i) {
			while (j < i && nums[i] - nums[j] > mid) ++j;
			ans += i - j;
		}
		return ans;
	}

	// 349. Intersection of Two Arrays
	// Given two arrays, write a function to compute their intersection.
	// Time:  O(max(m, n) * log(max(m, n)))
	// Space: O(1)
	// See hash map for linear time solution 
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		// Time:  O(max(m, n) * log(max(m, n)))
		// Space: O(1)
		// Binary search solution.

		if (nums1.size() > nums2.size()) {
			return intersection(nums2, nums1);
		}

		sort(nums1.begin(), nums1.end());
		sort(nums2.begin(), nums2.end());

		vector<int> result;
		auto it = nums2.cbegin();
		for (const auto& x : nums1) {
			it = lower_bound(it, nums2.cend(), x);
			if (it != nums2.end() && *it == x) {
				result.emplace_back(*it);
				it = upper_bound(it, nums2.cend(), x);
			}
		}

		return result;
	}
	// Mine
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		vector<int> ans;
		for(int i = 0; i < nums1.size(); i++){
		    if(searchInAns(nums1[i], ans))
			continue;
		    for(int j = 0; j < nums2.size(); j++){
			if(nums1[i] == nums2[j]){
			    insertIntoAns(nums1[i], ans);
			    break;
			}                    
		    }
		}
		return ans;
	    }
	    bool searchInAns(int target, vector<int>& ans){
		int left = 0, right = ans.size()-1;
		while(left <= right){
		    int pos = (left+right) >> 1;
		    if(ans[pos] == target){
			return true;
		    }else if(ans[pos] < target){
			left = pos + 1;
		    }else if(ans[pos] > target){
			right = pos - 1;
		    }
		}
		return false;
	    }
	    void insertIntoAns(int target, vector<int>& ans){
		int left = 0, right = ans.size()-1;
		while(left <= right){
		    int pos = (left+right) >> 1;
		    if(ans[pos] == target){
			return ;
		    }else if(ans[pos] < target){
			left = pos + 1;
		    }else if(ans[pos] > target){
			right = pos - 1;
		    }
		}
		//cout << "insert at " << left << "\n";
		ans.insert(ans.begin()+left, target);
	    }

	// 129. Sum Root to Leaf Numbers
	// Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number. An example is the root - to - leaf path 1->2->3 which represents the number 123. Find the total sum of all root - to - leaf numbers.
	int sumNumbers(TreeNode *root) {
		return sumNumbersDFS(root, 0);
	}

	int sumNumbersDFS(TreeNode *root, int sum) {
		if (!root) return 0;
		int cursum = 10 * sum + root->val;
		if (!root->left && !root->right) return cursum;
		return sumNumbersDFS(root->left, cursum) + sumNumbersDFS(root->right, cursum);
	}
	// Mine is in BinaryTreeMisc.h

	// 315. Count of Smaller Numbers After Self
	// You are given an integer array nums and you have to return a new counts array. The counts array has the property where counts[i] is the number of smaller elements to the right of nums[i].
	// Time:  O(nlogn)
	// Space: O(n)
	vector<int> countSmaller(vector<int>& nums) {
		const int n = (int)nums.size();
		vector<int> ans(n);
		vector<int> low;
		for (int i = n - 1; i >= 0; --i) {
			int d = (int)distance(low.begin(), lower_bound(low.begin(), low.end(), nums[i]));
			ans[i] = d;
			low.insert(low.begin() + d, nums[i]);
		}
		return ans;
	}
	// Mine
	vector<int> countSmaller(vector<int>& nums) {
		if(nums.size() == 0)
		    return vector<int>();
		vector<int> ans(1);
		vector<int> process(1, nums.back());
		for(int i = nums.size()-2; i >= 0; i--){
		    // binary search and insert it into process
		    //cout << "processing " << i << " " << nums[i] << "\n";
		    ans.push_back( binaryInsert(nums[i], process));
		}
		reverse(ans.begin(), ans.end());
		return ans;
	    }

	    int binaryInsert(int element, vector<int> & process){
		int left = 0;
		int right = process.size()-1;
		while(left <= right){

		    int mid = (left+right) >> 1;
		    //cout << "l " << left << " r " << right << " m " << mid << "\n";
		    if(element <= process[mid]){
			right = mid-1;
		    }else if(element > process[mid]){
			left = mid+1;
		    }
		}
		//cout << "left " << left << "\n";
		if(left == process.size())
		    process.push_back(element);
		else
		    process.insert(process.begin()+left, element);
		return left;
	    }
};
