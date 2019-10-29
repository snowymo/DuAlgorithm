#pragma once
#include "common.h"

class DP1D {
	// 42. Trapping Rain Water
	// Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining.
	int trap(vector<int>& height) {
		const int n = (int)height.size();
		if (n < 3) return 0;
		vector<int> lmax(n, 0), rmax(n, 0);
		lmax[0] = height[0];
		rmax[n - 1] = height[n - 1];
		for (int i = 0; i < n - 1; ++i) {
			lmax[i + 1] = max(lmax[i], height[i + 1]);
			rmax[n - 2 - i] = max(rmax[n - 1 - i], height[n - 2 - i]);
		}
		int ans = 0;
		for (int i = 1; i < n - 1; ++i) {
			ans += min(lmax[i], rmax[i]) - height[i];
		}
		return ans;
	}
	// Mine, after read the solution
	int trap(vector<int>& height) {
		if(height.empty() || height.size()<3)
		    return 0;

		vector<int> maxleft(height.size(),-1);
		vector<int> maxright(height.size(),-1);

		for(int i=1;i<maxleft.size();i++)
		{
		    maxleft[i] = max(height[i-1], maxleft[i-1]);
		}

		for(int i=maxright.size()-2;i>=0;i--)
		{
		    maxright[i]=max(maxright[i+1],height[i+1]);
		}
		int units = 0;
		for(int i=1;i<height.size()-1;i++)
		{
		    int val = min(maxleft[i],maxright[i])-height[i];
		    if(val>0)
			units+=val;
		}

		return units;

	    }

	// 256. Paint House
	// k = 3
	// There are a row of n houses, each house can be painted with one of the k colors. 
	// The cost of painting each house with a certain color is different. 
	// You have to paint all the houses such that no two adjacent houses have the same color.
	int minCost(vector<vector<int>>& costs) {
		if (costs.empty() || costs[0].empty()) return 0;
		vector<vector<int>> dp = costs;
		for (size_t i = 1; i < dp.size(); ++i) {
			for (size_t j = 0; j < 3; ++j) {
				dp[i][j] += min(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]);
			}
		}
		return min(min(dp.back()[0], dp.back()[1]), dp.back()[2]);
	}


	// 135. Candy [H]
	// There are N children standing in a line. Each child is assigned a rating value. You are giving candies to these children subjected to the following requirements : Each child must have at least one candy. Children with a higher rating get more candies than their neighbors. What is the minimum candies you must give ?
	// 1, 2, 3, 4, 5 ==>
	// 3, 2, 1, 2, 3 ==>
	// 1, 2, 1, 2, 1
	int candy(vector<int>& ratings) {
		const int n = (int)ratings.size();
		int ans = 0;
		vector<int> f(n, 1); // longest increasing from left
		vector<int> g(n, 1); // longest increasing from right
		for (int i = 1; i < n; ++i) {
			if (ratings[i] > ratings[i - 1]) f[i] = f[i - 1] + 1;
		}
		for (int i = n - 2; i >= 0; --i) {
			if (ratings[i] > ratings[i + 1]) g[i] = g[i + 1] + 1;
		}
		for (int i = 0; i < n; ++i) {
			// cout << f[i] << "\t" << g[i] << endl; 
			ans += max(f[i], g[i]);
		}
		return ans;
	}
	// Mine, first I was confused about the problem itself. Then I read the solution... 
	// So here is one easy-understanding solution and the other is a smart one
	int candy2(vector<int>& ratings) {
		    if (ratings.size() == 0) 
			return 0;
		    int ret = 1;
		    int up = 0, down = 0, peak = 0;
		    for (int i = 1; i < ratings.size() ; i++) {
			if (ratings[i - 1] < ratings[i]) {
			    peak = ++up;
			    down = 0;
			    ret += 1 + up;
			} else if (ratings[i - 1] == ratings[i])  {
			    peak = up = down = 0;
			    ret += 1;
			} else {
			    up = 0;
			    down++;
			    ret += 1 + down + (peak >= down ? -1 : 0);
			}
		    }

		    return ret;
	    }

	    int candy(vector<int>& ratings) {
		    if (ratings.size() == 0) 
			return 0;
		int ans[ratings.size()] = {1};

		for(int i = 1; i < ratings.size(); i++){
		    ans[i] = 1;
		    if(ratings[i] > ratings[i-1]){
			ans[i] = ans[i-1]+1;
		    }
		    //cout << i << ":" << ans[i] << "\n";
		}
		for(int i = ratings.size()-2; i >= 0; i--){
		    if(ratings[i] > ratings[i+1]){
			ans[i] = max(ans[i],ans[i+1]+1);
		    }
		    //cout << i << ":" << ans[i] << "\n";
		}
		return accumulate(ans, ans+ratings.size(), 0); 

	    }

	// 139. Word Break
	// Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, determine if s can be segmented into a space-separated sequence of one or more dictionary words.
	bool wordBreak(string s, unordered_set<string>& wordDict) {
		const int n = (int)s.size(), m = (int)wordDict.size();
		if (n <= 0) return false;
		vector<bool> f(n + 1);
		f[0] = true;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= i; ++j) 
				if (f[j - 1]) {
					if (wordDict.find(s.substr(j - 1, i - j + 1)) != wordDict.end()) {
						f[i] = true;
						break;
					}
			}
		}
		return f[n];
	}
	// Mine
	map<string, int> dict;
	    map<pair<int,int>, int> dp;
	    bool wordBreak(string s, vector<string>& wordDict) {
		for(int i = 0; i < wordDict.size(); i++){
		    // find a word start from i
		    dict[wordDict[i]] = i;
		}
		return wordBreakHelp(s, 0);
	    }
	    bool wordBreakHelp(string s, int start){
		if(start == s.size())
		    return true;
		if(dp[{start, s.size()}] != 0)
		    return dp[{start, s.size()}] == 1;
		for(int i = 0; i <= s.size()-start; i++){
		    if(dict.find(s.substr(start, i)) != dict.end()){
			//cout << s.substr(start, i)<< "\n";
			// word exist
			dp[{start, start+i}] = 1;
			bool cur = wordBreakHelp(s, start+i);
			dp[{start+i, s.size()}] = cur? 1 : -1;
			if(cur)
			    return cur;
			//cout << "not find " << s.substr(start+i) << "\n";
		    }
		}
		return false;
	    }

	// 140. Word Break II
	// Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences.
	vector<string> wordBreak2(string s, unordered_set<string>& wordDict) {
		const int n = (int)s.size(), m = (int)wordDict.size();
		vector<string> ans;
		if (n <= 0) return ans;
		vector<bool> f(n + 1);
		vector<vector<int>> p(n + 1);
		f[0] = true;
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= i; ++j) if (f[j - 1]) {
				if (wordDict.find(s.substr(j - 1, i - j + 1)) != wordDict.end()) {
					f[i] = true;
					p[i].push_back(j - 1);
				}
			}
		}
		if (!f[n]) return ans;
		findWordBreak(ans, f, p, s, n, "");
		return ans;
	}


	void findWordBreak(vector<string> &ans, vector<bool> &f, vector<vector<int>> &p, string &s, int n, string path) {
		if (n <= 0) {
			ans.push_back(path);
			return;
		}
		if (!f[n]) return;
		for (int i = 0; i < p[n].size(); ++i) {
			int j = p[n][i];
			string newpath = path;
			if (newpath.empty()) {
				newpath = s.substr(j, n - j);
			}
			else {
				newpath = s.substr(j, n - j) + " " + newpath;
			}
			findWordBreak(ans, f, p, s, j, newpath);
		}
	}
	
	// Mine
	set<string> myset;
	    map<pair<int,int>, 
	    vector<vector<string>>  > dp; // indicating that start with int and end with int is a word
	    vector<string> wordBreak(string s, vector<string>& wordDict) {
		// init the set first
		for(int i = 0; i < wordDict.size(); i++){
		    myset.insert(wordDict[i]);
		}
		vector<vector<string>> answers;
		wordBreakHelp(s, 0, s.size() ,answers);

		vector<string> ret((int)answers.size(), "");
		for(int i = 0; i < answers.size(); i++){
		    string curRet = "";
		    for(int j = 0; j < answers[i].size(); j++){
			curRet += answers[i][answers[i].size()-j-1] + " ";
		    }
		    ret[i] = curRet.substr(0, (int)curRet.size()-1);
		}
		return ret;
	    }

	    bool wordBreakHelp(string s, int start, int end, vector<vector<string>> & answers){
		//cout << "processing " << s.substr(start, end-start+1) << "\n";
		// DP
		if(dp.find({start, end}) != dp.end()){
		    answers = dp[{start,end}];
		    return answers.size() > 0;
		}            

		vector<vector<string>> ret;
		for(int j = start; j < end; j++){
		    string cur = s.substr(start, j-start+1);
		    if(myset.find(cur) != myset.end()){
			//cout << "find " << cur << " " << j << " " << end << "\n";
			//
			if(j == end-1){
	//                    cout << "meet end " << cur << "\n";
			    ret.push_back(vector<string>(1, cur));
			}else{
			    vector<vector<string>> temp;
			    if(wordBreakHelp(s, j+1, end, temp)){
	  //                      cout << "push_back " << cur << "\n";
				for(int i = 0; i < temp.size(); i++){
				    temp[i].push_back(cur);
				    ret.push_back(temp[i]);                           
				}
			    }    
			}
		    }
		}
		dp[{start, end}] = ret;
		answers = ret;
	    //    cout << "dp[{" << start << ", " << end << "}] = " << ret.size() << "\n";
		return ret.size() > 0;
	    }

	// 152. Maximum Product Subarray
	// Given an integer array nums, find the contiguous subarray within an array (containing at least one number) which has the largest product.
	int maxProduct(vector<int>& nums) {
		if (nums.empty()) return 0;
		int res = nums[0], mn = nums[0], mx = nums[0];
		for (int i = 1; i < nums.size(); ++i) {
			int tmax = mx, tmin = mn;
			mx = max(max(nums[i], tmax * nums[i]), tmin * nums[i]);
			mn = min(min(nums[i], tmax * nums[i]), tmin * nums[i]);
			res = max(res, mx);
		}
		return res;
	}
	// Mine
	int maxProduct(vector<int>& nums) {
		if(nums.size() == 0)
		    return 0;

		vector<int> dpMax(nums.size());
		vector<int> dpMin(nums.size());
		dpMax[0] = nums[0];
		dpMin[0] = nums[0];

		for(int i = 1; i < nums.size(); i++){
		    //cout << nums[i] << "\t";
		    if(nums[i] == 0)
			dpMax[i] = dpMin[i] = 0;
		    else if(nums[i] > 0){
			dpMax[i] = max(nums[i], dpMax[i-1] * nums[i]);
			dpMin[i] = min(nums[i], dpMin[i-1] * nums[i]);
		    }
		    else if(nums[i] < 0){
			dpMax[i] = max(nums[i], dpMin[i-1] * nums[i]);
			dpMin[i] = min(nums[i], dpMax[i-1] * nums[i]);
		    }
		}
		return *max_element(dpMax.begin(), dpMax.end());
	    }

	// 198. House Robber [E]
	// You are a professional robber planning to rob houses along a street. Each house has a certain amount of money stashed, the only constraint stopping you from robbing each of them is that adjacent houses have security system connected and it will automatically contact the police if two adjacent houses were broken into on the same night. Max.
	int rob(vector<int>& nums) {
		const int n = (int)nums.size();
		if (n == 0) return 0;
		vector<int> f(3); // f[i] = maximum from 0 .. i - 1
		f[1] = nums[0];

		for (int i = 2; i <= n; ++i) {
			f[i % 3] = max(f[(i - 1) % 3], f[(i - 2) % 3] + nums[i - 1]);
		}

		return f[n % 3];
	}
	// Mine
	int rob(vector<int>& nums) {
		if(nums.size() == 0)
		    return 0;

		vector<int> money(nums.size()+1, 0);
		money[1] = nums[0];
		for(int i = 2; i <= nums.size(); i++){
		    money[i] = max(money[i-1], money[i-2] + nums[i-1]);
		}
		return money.back();
	    }

	// 213. House Robber II [M]
	// All houses at this place are arranged in a circle.
	int rob2(vector<int>& nums) {
		const int n = (int)nums.size();
		if (n <= 1)
			return nums.empty() ? 0 : nums[0];
		return max(rob2(nums, 0, n - 1), rob2(nums, 1, n));
	}

	int rob2(vector<int> &nums, int l, int r) {
		if (r - l <= 1)
			return nums[l];
		vector<int> f(r, 0);
		f[l] = nums[l];
		f[l + 1] = max(nums[l], nums[l + 1]);
		for (int i = l + 2; i < r; ++i) {
			f[i] = max(nums[i] + f[i - 2], f[i - 1]);
		}
		return f.back();
	}
	// Mine
	int rob(vector<int>& nums) {
		if(nums.size() == 0)
		    return 0;
		if(nums.size() == 1)
		    return nums[0];
		if(nums.size() <= 3){
		    return *max_element(nums.begin(), nums.end());
		}
		vector<vector<int>> dp (2,vector<int>(nums.size()));
		dp[0][0] = nums[0];
		dp[0][1] = nums[0];
		dp[1][1] = nums[1];
		dp[0][2] = max(nums[0], nums[1]);
		dp[1][2] = max(nums[1], nums[2]);
		for(int i = 3; i <  nums.size(); i++){
		    dp[0][i] = max(dp[0][i-2] + nums[i-1], dp[0][i-1]);
		    dp[1][i] = max(dp[1][i-2] + nums[i], dp[1][i-1]);
		}
		return max(dp[0].back(), dp[1].back());
	    }

	// 312. Burst Balloons [H] [NOIP 2007?]
	// Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent. Find the maximum coins you can collect by bursting the balloons wisely.
	/*
		Input: [3,1,5,8]
		Output: 167 
		Explanation: nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
					 coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
	*/
	int maxCoins(vector<int>& nums) {
		const int n = (int)nums.size();
		vector<int> a;
		a.emplace_back(1);
		for (const auto& x : nums)
			a.emplace_back(x);
		a.emplace_back(1);

		vector<vector<int>> f(n + 2, vector<int>(n + 2));
		// f[i][j] indicates the maximum score we can get in [i, j]

		// k is number of bursts
		for (int k = 1; k <= n; ++k) {
			// infer [i, i + k]
			for (int i = 1; i <= n - k + 1; ++i) {
				int r = i + k - 1;
				for (int j = i; j <= r; ++j) {
					f[i][r] = max(f[i][r], f[i][j - 1] + f[j + 1][r] + a[j] * a[i - 1] * a[r + 1]);
				}
			}
		}

		return f[1][n];
	}
	// Mine, after read discussion
	int solve(vector<int>& nums, int s, int e, vector<vector<int> >& dp){
		if(dp[s][e] != -1){
		    return dp[s][e];
		}
		int l = s-1 < 0 ? 1 : nums[s-1];
		int r = e+1 >= nums.size() ? 1 : nums[e+1];
		if(s == e){
		    dp[s][e] = l*nums[s]*r;
		    return dp[s][e];
		}
		int mx = 0;
		for(int mid=s; mid<=e; mid++){
		    int left = (mid == s) ? 0 : solve(nums, s, mid-1, dp);
		    int right = (mid == e) ? 0 :solve(nums, mid+1, e, dp);    

		    int val = left + l * nums[mid] * r + right;
		    mx = max(mx, val);
		}
		dp[s][e] = mx;        
		return dp[s][e];        
	    }
	    int maxCoins2(vector<int>& nums) {
		int n = (int)nums.size();
		if(n == 0) return 0;
		vector<vector<int> > dp(n, vector<int>(n, -1));       
		int ans = solve(nums, 0, n-1, dp);

		return ans;
	    }
	    int maxCoins(vector<int>& nums){
		const int n=nums.size();
		if(n==0)
		    return 0;
		vector<vector<int> >dp(n,vector<int>(n));
		for(int L=n-1;L>=0;L--)
		{
		    for(int R=L;R<n;R++)
		    {
			for(int i=L;i<=R;i++)
			{
			    dp[L][R]=max(dp[L][R],
					  nums[i]*(L?nums[L-1]:1)*(R==n-1?1:nums[R+1])
					 + (i>0?dp[L][i-1]:0)+  (i==n-1?0:dp[i+1][R])
					);
			}
		    }
		}
		return dp[0][n-1];
	    }

	// 313. Super Ugly Number [M] [VH]
	// Super ugly numbers are positive numbers whose all prime factors are in the given prime list primes of size k. 
	/*
	Input: n = 12, primes = [2,7,13,19]
	Output: 32
	Explanation: [1,2,4,7,8,13,14,16,19,26,28,32] is the sequence of the first 12
	super ugly numbers given primes = [2,7,13,19] of size 4.
	*/
	// Solution: f[i] = min(f[i], f[inx[j]] * primes[j]);
	// Time: O(n^2)
	// Space: O(n)
	int nthSuperUglyNumberN2(int n, vector<int>& primes) {
		const int m = (int)primes.size();
		vector<int> f(n, 1), idx(n, 0);
		for (int i = 1; i < n; ++i) {
			f[i] = INT_MAX;
			for (int j = 0; j < n; ++j) {
				f[i] = min(f[i], f[idx[j]] * primes[j]);
			}
			for (int j = 0; j < m; ++j) {
				if (f[i] == f[idx[j]] * primes[j]) {
					++idx[j];
				}
			}
		}
		return f.back();
	}

	// Time:  O(n * k)
	// Space: O(n + k)
	int nthSuperUglyNumber(int n, vector<int>& primes) {
		const int m = (int)primes.size();
		// min_heap
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> heap;

		vector<int> uglies(n), idx(m), ugly_by_last_prime(n);
		uglies[0] = 1;

		for (int i = 0; i < m; ++i) {
			heap.emplace(primes[i], i);
		}
		for (int i = 1; i < n; ++i) {
			int k;
			tie(uglies[i], k) = heap.top();
			heap.pop();
			ugly_by_last_prime[i] = k;
			while (ugly_by_last_prime[++idx[k]] > k);  // average time: O(k)
			heap.emplace(uglies[idx[k]] * primes[k], k);
		}
		return uglies[n - 1];
	}
	// Mine, mine is TLE, because I caLculated too many unnecessary answers
	// Here is the optimization after reading the discussion
	int nthSuperUglyNumber(int n, vector<int>& primes) {
		if(n <= 1)
		    return n;
		int pos[primes.size()] = {0};
		int ans[n] = {1};

		for(int i =1;i<n;i++){
		    ans[i] = INT_MAX;
		    for(int j = 0; j<primes.size();j++){
			if(primes[j] * ans[pos[j]] < ans[i])
			    ans[i] = primes[j] * ans[pos[j]];
		    }

		    for(int j=0;j<primes.size();j++){
			if(primes[j] * ans[pos[j]] == ans[i])
			    ++pos[j];
		    }           
		}

		return ans[n-1];

	    }
	
	// No.303 Range Sum Query - Immutable Mine
	// Given an integer array nums, find the sum of the elements between indices i and j (i ≤ j), inclusive.
	vector<int> sums;
	    NumArray(vector<int>& nums) {
		if(nums.size() == 0)
		    return;
		sums = vector<int>(nums.size(), nums[0]);
		//sums.push_back(nums[0]);
		for(int i = 1; i < nums.size(); i++){
		    sums[i] = (sums[i-1] + nums[i]);
		    //cout << sums.back() << "\t";
		}

	    }

	    int sumRange(int i, int j) {
		if(i == 0)
		    return sums[j];
		return sums[j] - sums[i-1];
	    }
	
	// No.746 Min Cost Climbing Stairs Mine
	// On a staircase, the i-th step has some non-negative cost cost[i] assigned (0 indexed).
	// Once you pay the cost, you can either climb one or two steps. 
	// You need to find minimum cost to reach the top of the floor,
	// and you can either start from the step with index 0, or the step with index 1.
	int minCostClimbingStairs(vector<int>& cost) {
		if(cost.size() == 0)
		    return 0;
		if(cost.size() == 1)
		    return cost[0];
		// vector<int> steps(cost.size());
		// steps[0] = cost[0];
		// steps[1] = cost[1];
		int cost1 = cost[0];
		int cost2 = cost[1];
		int cost3 = min(cost1, cost2);
		for(int i = 2; i < cost.size(); i++){
		    cost3 = min(cost1+cost[i], cost2+cost[i]);
		    cost1 = cost2;
		    cost2 = cost3;
		    // steps[i] = min(steps[i-2] + cost[i], steps[i-1] + cost[i]);
		}
		// return min(steps.back(), steps[steps.size()-2]);
		return min(cost1, cost3);
	    }
};
