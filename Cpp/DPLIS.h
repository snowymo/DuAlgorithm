#pragma once
#include "common.h"

// Longest Increasing Subsequence (LIS)
class LISProblems {
	// 300. Longest Increasing Subsequence
	// Given an unsorted array of integers, find the length of longest increasing subsequence.
	// f[i] = max{ f[j] } + 1, a[j] < a[i], f[i] ascending, lower_bound
	// Time: O(n log n)
	int lengthOfLIS(vector<int>& nums) {
		vector<int> f;
		const int n = (int)nums.size();
		for (int x : nums) {
			int l = 0, r = (int)f.size();
			// find the first element in f, that is not greater than x
			// 4, 2, 4, 5, 3, 7
			// 4
			// 2
			// 2, 4
			// 2, 4, 5
			// 2, 3, 5
			// 2, 3, 5, 7
			while (l < r) {
				int mid = (l + r) >> 1;
				if (f[mid] < x) l = mid + 1;
				else r = mid;
			}
			if (r >= f.size())
				f.push_back(x);
			else
				f[r] = x;
		}
		return (int)f.size();
	}

	// Using STL
	int lengthOfLIS_STL(vector<int>& nums) {
		vector<int> f;
		for (auto x : nums) {
			auto it = lower_bound(f.begin(), f.end(), x);
			if (it == f.end())
				f.emplace_back(x);
			else
				*it = x;
		}
		return (int)f.size();
	}

	// Backup: O(n^2)
	int lengthOfLISN2(vector<int>& nums) {
		const auto n = nums.size();
		if (n == 0) return 0;
		vector<int> f(n + 1);
		f[0] = 1;
		int ans = 1;
		for (size_t i = 1; i < n; ++i) {
			f[i] = 1;
			for (size_t j = 0; j < i; ++j) if (nums[i] > nums[j]) {
				f[i] = max(f[i], f[j] + 1);
				ans = max(ans, f[i]);
			}
		}
		return ans;
	}

	// 675. Longest Continuous Increasing Subsequence [H]
	// Given an unsorted array of integers, find the length of longest continuous increasing subsequence (subarray).
	// Time: O(NM)
	int findLengthOfLCIS(vector<int>& nums) {
		int res = 0, cnt = 0, n = (int)nums.size();
		for (int i = 0; i < n; ++i) {
			if (i == 0 || nums[i - 1] < nums[i]) {
				cnt += 1;
				res = max(res, cnt);
			}
			else {
				cnt = 1;
			}
		}
		return res;
	}

	// 329. Longest Increasing Path in a Matrix [H]
	int longestIncreasingPath(vector<vector<int>>& matrix) {
		if (matrix.empty() || matrix[0].empty())
			return 0;
		const int n = (int)matrix.size(), m = (int)matrix[0].size();
		int ans = 1;

		// f[i][j] indicates the longest path starting from (i, j)
		vector<vector<int>> f(n, vector<int>(m, 0));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				ans = max(ans, dfs(matrix, f, i, j));
			}
		}
		return ans;
	}

	int dfs(vector<vector<int>>& matrix, vector<vector<int>> &f, int i, int j) {
		//cout << i << " " << j << endl; 
		if (f[i][j])
			return f[i][j];
		vector<vector<int>> dirs = { { 0, -1 },{ -1, 0 },{ 0, 1 },{ 1, 0 } };
		int cur_max = 1;
		const int n = (int)matrix.size(), m = (int)matrix[0].size();
		for (auto d : dirs) {
			int y = i + d[0], x = j + d[1];
			if (y < 0 || y >= n || x < 0 || x >= m || matrix[y][x] <= matrix[i][j])
				continue;
			//cout << "=> " << y << ' ' << x << ' ' << endl;
			int val = dfs(matrix, f, y, x);
			cur_max = max(cur_max, 1 + val);
		}
		f[i][j] = cur_max;
		return cur_max;
	}
	// Mine is in BinaryTreeMisc.h
};
