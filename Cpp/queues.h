#pragma once
#include "common.h"

namespace Queues {
	// 239. Sliding Window Maximum [H]
	// Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position. Return the max sliding window.
	// every element enque once and deque once
	/*
		[1,3,-1,-3,5,3,6,7]
		3
		0
		1
		1	2
		1	2	3
		4
		4	5
		6
		7
	*/
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		vector<int> res;
		deque<int> q;
		const int n = (int)nums.size();
		for (int i = 0; i < n; ++i) {
			if (!q.empty() && q.front() == i - k) q.pop_front();
			while (!q.empty() && nums[q.back()] < nums[i]) q.pop_back();
			q.emplace_back(i);
			if (i >= k - 1) res.emplace_back(nums[q.front()]);
		}
		return res;
	}

	class MovingAverage {
	public:
		MovingAverage(int size) {
			this->size = size;
			sum = 0;
		}

		double next(int val) {
			if (q.size() >= size) {
				sum -= q.front();
				q.pop();
			}
			q.push(val);
			sum += val;
			return sum / q.size();
		}

	private:
		queue<int> q;
		int size;
		double sum;
	};

	// 225. Implement Stack using Queues
	// See Python
	
// 	Mine No.378 [M] Find Minimum in Rotated Sorted Array
// 	Given a n x n matrix where each of the rows and columns are sorted in ascending order, find the kth smallest element in the matrix.

// Note that it is the kth smallest element in the sorted order, not the kth distinct element.

// Example:

// matrix = [
//    [ 1,  5,  9],
//    [10, 11, 13],
//    [12, 13, 15]
// ],
// k = 8,

// return 13.
// Note:
// You may assume k is always valid, 1 ≤ k ≤ n2.
	int kthSmallest(vector<vector<int>>& matrix, int k) {
		int len = matrix.size();
		bool small = true;
		if(k > len*len/2){
		    k = len*len-k+1;
		    small = false;
		}
		if(small){
		    priority_queue<int> potential;
		    for(int i = 0, j = len-1; i < len && j >= 0;){
			if((i+1) * (j+1) > k){
			    --j;
			    // cout << "move to left " << j << "\n";
			}else{
			    // move to next row
			    for(int rowi = 0; rowi <=j; rowi++){
				// cout << "add " << matrix[i][rowi] << "\n";
				potential.push(matrix[i][rowi]);
				if(potential.size() > k){
				    potential.pop();
				}
			    }

			    ++i;
			    // cout << "move down " << i << "\n";
			}
		    }   
		    return potential.top();
		}else{
		    priority_queue<int, vector<int>, greater<int>> potential;
		    cout << "find the " << k << "th from the end\n";
		    for(int i = 0, j = len-1; i < len && j >= 0;){
			cout << "cal " << len-i << "*" << len-j << "\n";
			if((len-i) * (len-j) <= k){
			    // move to left
			    for(int coli = i; coli < len; coli++){
				// cout << "add " << matrix[coli][j] << "\n";
				potential.push(matrix[coli][j]);
				if(potential.size() > k){
				    potential.pop();
				}
			    }                    
			    --j;
			    // cout << "move to left " << j << "\n";
			}else{
			    ++i;
			    // cout << "move down " << i << "\n";
			}
		    }
		    return potential.top();
		}
	    }
};
