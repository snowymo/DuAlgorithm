#pragma once
#include "common.h"

class KnapsackProblems {
public:
	// 322. Coin Change
	// Unbounded knapsack with infinite goods
	// Time: O(MN)
	// Space: O(M)
	/**
	*	Example 1:
	*	coins = [1, 2, 5], amount = 11
	*	return 3 (11 = 5 + 5 + 1)
	*/
	int coinChange(vector<int>& coins, int amount) {
		const int n = (int)coins.size(), m = amount;
		if (m < 0)
			return -1;
		vector<int> f(m + 1, m + 1);
		// f[i] indicates the min number of coins to form total amount of i
		f[0] = 0;
		for (int i = 1; i <= m; ++i)
			for (int j = 0; j < n; ++j)
				if (coins[j] <= i && f[i - coins[j]] + 1 < f[i]) {
					f[i] = f[i - coins[j]] + 1;
				}
		return f[m] > m ? -1 : f[m];
	}
	// Mine
	int coinChange(vector<int>& coins, int amount) {
		if(amount == 0)
		    return 0;

		vector<int> memo(amount, INT_MAX/2);
		for(int c : coins){
		    if(c-1 < amount)
			memo[c-1] = 1;
		}

		sort(coins.begin(), coins.end());

		for(int i = 0; i < amount; i++){
		    for(int j = 0; j < coins.size(); j++){
			//cout << "i:" << i << " i-k-1 " << i-k-1 << " k " << k << "\n";
			if(coins[j] < i+1){
			    memo[i] = min(memo[i], memo[i-coins[j]]+memo[coins[j]-1]);    
			}

		    }
		}
		return (memo.back() == INT_MAX/2) ? -1 : memo.back();
	    }
	// A faster way for top-down solution
	int minC = INT_MAX;
	    int coinChange(vector<int>& coins, int amount) {
		sort(coins.begin(), coins.end(), greater<int>());
		calc(0, amount, 0, coins);
		return minC == INT_MAX ? -1 : minC;
	    }

	    void calc(int index, int amount, int currC, const vector<int>& coins) {
		if (index == coins.size()) {
		    if (amount == 0) minC = min(minC, currC);
		    return;
		}

		// Key pruning here.
		if (amount/coins[index] + currC > minC) return;

		for (int i = amount/coins[index]; i >= 0; i--) {
		    calc(index + 1, amount - i*coins[index], currC + i, coins);
		}
	    }
	

	// 416. Partition Equal Subset Sum [M]
	// Given a non-empty array containing only positive integers, find if the array can be partitioned into two subsets such that the sum of elements in both subsets is equal.
	// 0/1 knapsack Solution, refer to Bits for more details
	// Time: O(NM), M is the sum of nums.
	// Space: O(M)
	bool canPartition(vector<int>& nums) {
		int sum = accumulate(nums.begin(), nums.end(), 0);
		if (sum & 1)
			return false;
		const int n = (int)nums.size(), m = sum >> 1;
		vector<bool> dp(m + 1, false);
		dp[0] = true;
		for (int i = 0; i < n; ++i) {
			for (int j = m; j >= nums[i]; --j) {
				dp[j] = dp[j] || dp[j - nums[i]];
			}
		}
		return dp.back();
	}
	// Mine. Finish after read Du's
	bool canPartition(vector<int>& nums) {
		// need to caclulate and sort the vector
		sort(nums.begin(), nums.end());
		int sum = 0;
		for(int n : nums){
		    sum += n;
		}
		if(sum % 2 == 1)
		    return false;
		sum = sum >> 1;
		vector<bool> memo(sum+1, false);
		memo[0] = true;

		// 0/1 knapsack problem
		//for(int j = 0; j < nums.size()+1; j++)
	//            memo[0][j] = true;
		for(int j = 0; j < nums.size(); j++){
		    for(int i = sum; i >= nums[j]; i--){            
			    memo[i] = memo[i] || memo[i-nums[j]];

		    }
		}

		return memo.back();
	    }
};
