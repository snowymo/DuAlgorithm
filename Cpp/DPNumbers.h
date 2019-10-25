#pragma once
#include "common.h"

class DPMath {
public:
	// 343. Integer Break
	// Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the maximum product you can get.
	/**
	 * 2, 1
	 * 3, 2
	 * 4, 4
	 * 5, 3+2, 6
	 * 6, 3+3, 9
	 * 7, 3+4
	 * 8, 3+3+2
	 * 9, 3+3+3
	 * 10, 3+3+4
	 **/
	int integerBreak(int n) {
		vector<int> f{ 0, 0, 1, 2, 4, 6, 9 };
		for (int i = 7; i <= n; ++i) {
			f.push_back(3 * f[i - 3]);
		}
		return f[n];
	}
	// Mine
	int integerBreak(int n) {
		if(n == 2)
		    return 1;
		if(n == 3)
		    return 2;

		int reminder = n % 3;
		if(reminder == 1){
		    return pow(3, n/3-1) * 4;
		}
		if( reminder == 0)
		    return pow(3, n/3);
		return pow(3, n/3) * 2;            
	    }

	// 413. Arithmetic Slices
	int numberOfArithmeticSlices(vector<int>& A) {
		int res = 0, len = 2;
		const auto n = A.size();
		for (size_t i = 2; i < n; ++i) {
			if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
				++len;
			}
			else {
				if (len > 2) res += (len - 1) * (len - 2) / 2;
				len = 2;
			}
		}
		if (len > 2) res += (len - 1) * (len - 2) / 2;
		return res;
	}
	// Mine
	int numberOfArithmeticSlices(vector<int>& A) {
		int ans = 0;
		int diff = INT_MIN;
		int count = 0;
		for(int i = 1; i < A.size(); i++){
		    if(diff == A[i] - A[i-1]){
			++count;
		    }else{
			ans += (count+1) * count/2;
			diff = A[i] - A[i-1];
			count = 0;
		    }
		}
		ans += (count+1) * count/2;
		return ans;
	    }
	
	// No.446 Arithmetic Slices II - Subsequence(Mine)
	// A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
	// For example, these are arithmetic sequences:
	// 1, 3, 5, 7, 9
	// 7, 7, 7, 7
	// 3, -1, -5, -9
	// The following sequence is not arithmetic.
	// 1, 1, 2, 5, 7

	// A zero-indexed array A consisting of N numbers is given. A subsequence slice of that array is any sequence of integers (P0, P1, ..., Pk) such that 0 ≤ P0 < P1 < ... < Pk < N.
	// A subsequence slice (P0, P1, ..., Pk) of array A is called arithmetic if the sequence A[P0], A[P1], ..., A[Pk-1], A[Pk] is arithmetic. In particular, this means that k ≥ 2.
	// The function should return the number of arithmetic subsequence slices in the array A.
	// The input contains N integers. Every integer is in the range of -231 and 231-1 and 0 ≤ N ≤ 1000. The output is guaranteed to be less than 231-1.
	 // Example:
	// Input: [2, 4, 6, 8, 10]
	// Output: 7

	// Explanation:
	// All arithmetic subsequence slices are:
	// [2,4,6]
	// [4,6,8]
	// [6,8,10]
	// [2,4,6,8]
	// [4,6,8,10]
	// [2,4,6,8,10]
	// [2,6,10]
	int numberOfArithmeticSlices(vector<int>& A) {
		vector<map<long long, int>> memos (A.size());
		long long ans = 0;
		for(int i = 1; i < A.size(); i++){
		    for(int j = 0; j < i; j++){
			long long diff = (long long)A[i]-(long long)A[j];
			long long cur = 0;
			if(memos[j].find(diff) != memos[j].end())
			    cur = memos[j][diff];
			memos[i][diff] += cur + 1;
			ans += cur;
		    }
		}
		return (int)ans;
	    }
};
