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
};
