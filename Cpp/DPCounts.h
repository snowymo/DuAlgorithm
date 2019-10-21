#pragma once
#include "common.h"

namespace DPCounts {
	// 70. Climbing Stairs
	// Distinct ways to climb the top of n stairs, with one or two each time.
	// Space: O(1)
	// Time: O(N)
	int climbStairs(int n) {
		if (n <= 0)
			return 0;
		vector<int> f(3, 1);
		for (int i = 2; i <= n; ++i)
			f[i % 3] = f[(i - 1) % 3] + f[(i - 2) % 3];
		return f[n % 3];
	}
	
	// Mine
	int climbStairs(int n) {
        // a[n] = a[n-1] + a[n-2]
		int ans1 = INT_MIN, ans2 = INT_MIN;
		int temp;
		for(int i = 1; i <= n; i ++){
		    if(i == 1)
			ans2 = 1;
		    else if(i == 2){
			ans1 = ans2;
			ans2 = 2;
		    }else{
			temp = ans1;
			ans1 = ans2;
			ans2 = temp + ans1;
		    }
		}
		return ans2;
	    }

	// 91. Decode Ways [M]
	// Ways to decode a string of numbers to A-Z: 1 -> 'A' || 26 -> 'Z'
	int numDecodings(string s) {
		const int n = (int)s.size();
		if (n == 0)
			return 0;
		vector<int> f(n + 1, 0);
		f[0] = 1;
		f[1] = (s[0] != '0');
		for (int i = 2; i <= n; ++i) {
			// illegal string
			if (s[i - 1] == '0' && (s[i - 2] == '0' || s[i - 2] > '2'))
				return 0;

			// case 1: 0 before
			if (s[i - 1] == '0') {
				f[i] = f[i - 2];
			}
			else
			// case 2: 1 or 2 two chars before 
			if (s[i - 2] == '1' || (s[i - 2] == '2' && s[i - 1] <= '6')) {
				f[i] = f[i - 1] + f[i - 2];
			}
			// case 3: single number
			else {
				f[i] = f[i - 1];
			}
		}
		return f[n];
	}
	// Mine
	int numDecodings(string s) {
		// a[n] = a[n-1] + a[n-1:n] <= 26 ? a[n-2] : 0
		int ans0 = INT_MIN;
		int ans1 = INT_MIN;
		int ans2 = INT_MIN;
		int temp;
		for(int i = 0; i < s.size(); i++){
		    if(i == 0){
			if(s[i] == '0')
			    ans2 = 0;
			else
			    ans2 = 1;
		    }
		    else if(i == 1){
			// both 0, one 0
			int digit0 = stoi(s.substr(i-1,1)),
			digit1 = stoi(s.substr(i,1)),
			digit2 = stoi(s.substr(i-1,2));
			ans1 = ans2;
			ans2 = 0;
			if(ans1 > 0 && digit1 <= 26 && digit1 > 0)
			    ans2 += 1;
			if(digit2 <= 26 && digit2 > 9)
			    ans2 += 1;

		    }
		    else{
			temp = ans1;
			ans1 = ans2;
			ans2 = 0;
			if(temp != 0){
			    int digit1 = stoi(s.substr(i-1,2));
			    if(digit1 <= 26 && digit1 > 9){
				ans2 += temp;
			    }
			}
			if(ans1 != 0){
			    int digit1 = stoi(s.substr(i,1));
			    if(digit1 <= 26 && digit1 > 0){
				ans2 += ans1;
			    }
			}
		    }
		    //cout << ans2 << "\n";
		}
		return ans2;
	    }

	// 96. Unique Binary Search Trees
	// Given n, how many structurally unique BST's (binary search trees) that store values 1 ... n?
	int numTrees(int n) {
		vector<int> f(n + 2, 0);
		f[0] = 1;
		f[1] = 1;
		for (int i = 2; i <= n; ++i) {
			for (int k = 1; k <= i; ++k) {
				f[i] += f[k - 1] * f[i - k];
			}
		}
		return f[n];
	}
	// Mine
	// Finish after read Du's
	int numTrees(int n) {
        // a[n] = a[n-1] * 2 + 1
        // 1 1-1 1
        // 2 2-2 2
        // a[3] = a[0]*a[2] + a[1]*a[1] + a[2]*a[0]=2+1+2
        // a[4] = a[0]*a[3]
        vector<int> answers(n+1, 0);
		answers[0] = 1;
		answers[1] = 1;
		for(int i = 2; i <= n; i++){
		    for(int j = 1; j <= i; j++){
			answers[i] += answers[j-1] * answers[i-j];
		    }
		}
		return answers[n];
	    }

	// 115. Distinct Subsequences
	// Given a string S and a string T, count the number of distinct subsequences of S which equals T.
	// A subsequence of a string is a new string which is formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (ie, "ACE" is a subsequence of "ABCDE" while "AEC" is not).
	int numDistinct(string s, string t) {
		const int n = (int)s.size(), m = (int)t.size();
		if (n < m || n < 1 || m < 1)
			return 0;
		vector<vector<int>> f(n + 1, vector<int>(m + 1, 0));

		f[0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			f[i][0] = 1;
			for (int j = 1; j <= min(i, m); ++j) {
				f[i][j] = f[i - 1][j];
				if (s[i - 1] == t[j - 1]) {
					f[i][j] += f[i - 1][j - 1];
				}
			}
		}
		return f[n][m];
	}

	// 629. K Inverse Pairs Array [H]
	// Given two integers n and k, find how many different arrays consist of numbers from 1 to n such that there are exactly k inverse pairs. Since the answer may be very large, the answer should be modulo 10^9 + 7.
	int kInversePairs(int n, int k) {
		static const int M = 1000000007;
		vector<vector<int>> f(2, vector<int>(k + 1));
		f[0][0] = 1;
		for (int i = 1; i <= n; ++i) {
			f[i % 2][0] = 1;
			for (int j = 1; j <= k; ++j) {
				f[i % 2][j] = (f[i % 2][j - 1] + f[(i - 1) % 2][j]) % M;
				if (j - i >= 0) {
					f[i % 2][j] = (f[i % 2][j] - f[(i - 1) % 2][j - i] + M) % M;
				}
			}
		}
		return f[n % 2][k];
	}
}
