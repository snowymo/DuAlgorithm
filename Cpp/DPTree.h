#pragma once
#include "common.h"

class DPTree {
	// 124. Binary Tree Maximum Path Sum
	// Given a non-empty binary tree, find the maximum path sum.
	int maxPathSum(TreeNode* root) {
		int res = root->val;
		maxPathSumDP(root, res);
		return res;
	}

	int maxPathSumDP(TreeNode* root, int &res) {
		if (root == NULL) return 0;
		int l = max(0, maxPathSumDP(root->left, res));
		int r = max(0, maxPathSumDP(root->right, res));
		res = max(res, l + r + root->val);
		return root->val + max(l, r);
	}
	// Mine
	int maxPathSum(TreeNode* root) {
		// with root, left[single]+root+right[single]
		// left or right
		if(root == NULL)
		    return 0;
		auto [root_single, root_max] = maxPathSumHelp(root);
		return root_max;
	    }
	    pair<int,int> maxPathSumHelp(TreeNode* root){
		if(root == NULL)
		    return {INT_MIN,INT_MIN};
		// return (single, max)
		auto [left_single, left_max] = maxPathSumHelp(root->left);
		auto [right_single, right_max] = maxPathSumHelp(root->right);
		//cout << root->val << "\t";
		//cout << "le " << left_single << " " << left_max << " ri " << right_single << " " << right_max << "\n";
		int root_single = root->val;
		if(root->left)
		    root_single = max(root_single,max(root->val, root->val+left_single));
		if(root->right)
		    root_single = max(root_single, max(root->val, root->val+right_single));

		int root_max = root->val;
		if(root->left)
		    root_max = max(root_max, root_max + left_single);
		if(root->right)
		    root_max = max(root_max, root_max + right_single);
		root_max = max(root_max, max(left_max, right_max));
		//cout << "ro s " << root_single << " ro m " << root_max << "\n";
		return {root_single, root_max};
	    }

	// 112. Path Sum
	// Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.
	bool hasPathSum(TreeNode* root, int sum) {
		typedef pair<TreeNode*, int> NodeSum;
		stack<NodeSum> s;
		if (root == nullptr) return false;
		s.push(NodeSum(root, root->val));
		while (!s.empty()) {
			NodeSum t = s.top();
			s.pop();
			TreeNode* node = t.first;
			int cur_sum = t.second;
			if (!node->left && !node->right && cur_sum == sum) return true;
			if (node->left) s.push(NodeSum(node->left, cur_sum + node->left->val));
			if (node->right) s.push(NodeSum(node->right, cur_sum + node->right->val));
		}
		return false;
	}
	// Mine is in Cpp/BinaryTreeMisc.h 

	// 113. Path Sum II
	// Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
	// Non-recursive solution!
	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		using NodeSum = pair<TreeNode*, int>;

		vector<vector<int>> res;
		if (root == nullptr) return res;
		stack<NodeSum> s;
		stack<bool> rightmost;

		s.push(NodeSum(root, root->val));
		rightmost.push(false);
		vector<int> path;
		stack<bool> flags;

		while (!s.empty()) {
			NodeSum t = s.top(); 			s.pop();
			bool r = rightmost.top();		rightmost.pop();

			TreeNode* node = t.first;
			int cur_sum = t.second;

			path.push_back(node->val);
			flags.push(r);


			if (!node->left && !node->right) {
				if (cur_sum == sum) {
					vector<int> new_path(path);
					res.push_back(new_path);
				}
				path.pop_back();
				flags.pop();
				if (r && !flags.empty()) {
					r = flags.top();
					flags.pop();
					path.pop_back();
					while (r && !flags.empty()) {
						r = flags.top();
						flags.pop();
						path.pop_back();
					}
				}
				continue;
			}
			if (node->right) {
				s.push(NodeSum(node->right, cur_sum + node->right->val));
				rightmost.push(true);
			}
			if (node->left) {
				s.push(NodeSum(node->left, cur_sum + node->left->val));
				rightmost.push(node->right == nullptr);
			}
		}
		return res;
	}
	// Mine is in Cpp/BinaryTreeMisc.h 

	// 437. Path Sum III [E]
	// Time: O(N)
	// Space: O(h)
	// Insight: current sum - previous sum = sum
	// number of previous sum can be memorized in hash table
	using Dict = unordered_map<int, int>;

	int pathSumIII(TreeNode* root, int sum) {
		if (!root)
			return 0;
		Dict dict({ { 0,1 } });
		return pathSum(root, dict, 0, sum);
	}

	int pathSum(TreeNode* root, Dict& dict, int cur, int sum) {
		if (!root)
			return 0;
		cur += root->val;
		int res = dict.count(cur - sum) ? dict[cur - sum] : 0;
		++dict[cur];
		res += pathSum(root->left, dict, cur, sum) + pathSum(root->right, dict, cur, sum);
		--dict[cur];
		return res;
	}
	
	// Mine is in Cpp/BinaryTreeMisc.h 

	// 337. House Robber III [M]
	// It will automatically contact the police if two directly-linked houses were broken into on the same night. Determine the maximum amount of money the thief can rob tonight without alerting the police.
	// Tree DP
	int rob(TreeNode* root) {
		auto res = robDP(root);
		return max(res.first, res.second);
	}

	pair<int, int> robDP(TreeNode* root) {
		if (!root)
			return{ 0, 0 };

		auto l = robDP(root->left);
		auto r = robDP(root->right);
		return{ root->val + l.second + r.second,
			max(l.first, l.second) + max(r.first, r.second) };
	}
	
	// Mine
	map<TreeNode*, int> cache;
	    int rob(TreeNode* root) {
		if(root == NULL)
		    return 0;
		if(cache.find(root) != cache.end())
		    return cache[root];
		// rob root
		int ans = root->val;
		if(root->left){
		    ans += rob(root->left->left)
			+ rob(root->left->right);
		}
		if(root->right){
		    ans += rob(root->right->left)
			+ rob(root->right->right);
		}
		// skip root
		int ans2 = rob(root->left) + rob(root->right);
		cache[root] = max(ans, ans2);
		return cache[root];
	    }
};
