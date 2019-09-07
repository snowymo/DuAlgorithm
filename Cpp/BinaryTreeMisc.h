#pragma once
#include "common.h"

class BinaryTreeMisc {
	// 101. Symmetric Tree E]
	// Given a binary tree, check whether it is a mirror of itself (ie, symmetric around its center).
	bool isSymmetric(TreeNode* root) {
		if (root == nullptr) return true;
		stack<TreeNode*> s;
		s.push(root->left);
		s.push(root->right);

		while (!s.empty()) {
			TreeNode* p = s.top(); s.pop();
			TreeNode* q = s.top(); s.pop();
			if (p == nullptr && q != nullptr) return false;
			if (q == nullptr && p != nullptr) return false;
			if (p == nullptr && q == nullptr) continue;
			if (p->val != q->val) return false;
			s.push(p->left);
			s.push(q->right);

			s.push(p->right);
			s.push(q->left);
		}
		return true;
	}

	// 104. Maximum Depth of Binary Tree
	// Given a binary tree, find its maximum depth.
	// The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
	int maxDepth(TreeNode* root) {
		typedef pair<TreeNode*, int> Nodep;
		stack<Nodep> s;
		if (root == nullptr) return 0;
		s.push(Nodep(root, 1));
		int ans = 1;
		while (!s.empty()) {
			Nodep t = s.top();
			s.pop();
			TreeNode* node = t.first;
			int depth = t.second;
			if (depth > ans) ans = depth;
			if (node->left != nullptr) s.push(Nodep(node->left, depth + 1));
			if (node->right != nullptr) s.push(Nodep(node->right, depth + 1));
		}
		return ans;
	}

	// 111. Minimum Depth of Binary Tree
	// Given a binary tree, find its minimum depth.
	// The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node.
	int minDepth(TreeNode* root) {
		using Level = pair<TreeNode*, int>;
		stack<Level> s;
		if (root == nullptr) return 0;
		s.push(Level(root, 1));
		int ans = INT_MAX;
		while (!s.empty()) {
			Level t = s.top();
			s.pop();
			TreeNode* node = t.first;
			int depth = t.second;
			if (node->left == nullptr && node->right == nullptr) {
				ans = min(ans, depth);
				continue;
			}
			if (node->left != nullptr) s.push(Level(node->left, depth + 1));
			if (node->right != nullptr) s.push(Level(node->right, depth + 1));
		}
		return ans;
	}

	// 106. Construct Binary Tree from Inorder and Postorder Traversal
	// Given inorder and postorder traversal of a tree, construct the binary tree.
	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		return buildTree(inorder, 0, (int)inorder.size() - 1, postorder, 0, (int)postorder.size() - 1);
	}

	TreeNode* buildTree(vector<int>& inorder, int il, int ir, vector<int>& postorder, int pl, int pr) {
		if (ir - il != pr - pl || pl > pr || il > ir) return nullptr;
		int val = postorder[pr];
		TreeNode* root = new TreeNode(val);

		if (pl == pr) return root;
		int j = -1;
		for (int i = il; i <= ir; ++i) if (inorder[i] == val) {
			j = i;
			break;
		}
		// check if finds or not
		root->left = buildTree(inorder, il, j - 1, postorder, pl, pl + j - 1 - il);
		root->right = buildTree(inorder, j + 1, ir, postorder, pr - 1 - (ir - j - 1), pr - 1);
		return root;
	}

	// 114. Flatten Binary Tree to Linked List
	// Given a binary tree, flatten it to a linked list in-place.
	// O(n) Time, O(log n) Space
	void flatten(TreeNode* root) {
		if (root == nullptr) return;
		stack<TreeNode*> s;
		s.push(root);

		while (!s.empty()) {
			auto p = s.top();
			s.pop();

			if (p->right) s.push(p->right);
			if (p->left) s.push(p->left);

			p->left = nullptr;
			if (!s.empty()) p->right = s.top();
		}
	}

	// 100. Same Tree [E]
	// Given two binary trees, write a function to check if they are the same or not.
	bool isSameTree(TreeNode* p, TreeNode* q) {
		if (p == nullptr && q == nullptr) return true;
		if ((p == nullptr && q != nullptr) || (q == nullptr && p != nullptr)) return false;
		if (p->val != q->val) return false;
		return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
	}

	// 116. Populating Next Right Pointers in Each Node
	// Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
	// Initially, all next pointers are set to NULL.
	// You may only use constant extra space.
	// Recursive approach is fine, implicit stack space does not count as extra space for this problem.
	// You may assume that it is a perfect binary tree (ie, all leaves are at the same level, and every parent has two children).
	void connect(TreeLinkNode *root) {
		if (root == nullptr) return;
		TreeLinkNode level(0);
		for (auto node = root, prev = &level; node; node = node->next) {
			if (node->left) {
				prev->next = node->left;
				prev = prev->next;
			}
			if (node->right) {
				prev->next = node->right;
				prev = prev->next;
			}
		}
		connect(level.next);
	}

	// 117. Populating Next Right Pointers in Each Node II
	// Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.
	// You may only use constant extra space.
	void connect2(TreeLinkNode *root) {
		if (root == nullptr) return;
		TreeLinkNode level(0);
		for (auto node = root, prev = &level; node; node = node->next) {
			if (node->left) {
				prev->next = node->left;
				prev = prev->next;
			}
			if (node->right) {
				prev->next = node->right;
				prev = prev->next;
			}
		}
		connect(level.next);
	}

	// 226. Invert Binary Tree [E]
	TreeNode* invertTree(TreeNode* root) {
		if (!root)
			return nullptr;
		auto t = invertTree(root->left);
		root->left = invertTree(root->right);
		root->right = t;
		return root;
	}

	// 257. Binary Tree Paths [E]
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> res;
		if (root) binaryTreePathsDFS(root, "", res);
		return res;
	}

	void binaryTreePathsDFS(TreeNode *root, string out, vector<string> &res) {
		out += to_string(root->val);
		if (!root->left && !root->right) res.push_back(out);
		else {
			if (root->left) binaryTreePathsDFS(root->left, out + "->", res);
			if (root->right) binaryTreePathsDFS(root->right, out + "->", res);
		}
	}
	
	// 501. Find Mode in Binary Search Tree
	// Given a binary search tree (BST) with duplicates, find all the mode(s) (the most frequently occurred element) in the given BST.
	// Assume a BST is defined as follows:
	// The left subtree of a node contains only nodes with keys less than or equal to the node's key.
	// The right subtree of a node contains only nodes with keys greater than or equal to the node's key.
	// Both the left and right subtrees must also be binary search trees.
	void findMode(TreeNode* node, map<int, int>& ret, int& maxCount){
		if(!node)
		    return;
		findMode(node->left, ret, maxCount);
		findMode(node->right, ret, maxCount);
		if(ret.find(node->val) == ret.end()){
		    ret[node->val] = 1;
		    cout << "first time:" << node->val << "\t1\n";
		}            
		else{
		    ++ret[node->val];
		    cout << "find again:" << node->val << "\t" << ret[node->val] << "\n";
		}   
		maxCount = max(maxCount, ret[node->val]);
		cout << "maxCount:" << maxCount << "\n";
	    }

	    vector<int> findMode(TreeNode* root) {
		// the point is, if the node is different from the child's value, then the child's value reaches its max value.
		map<int,int> ret;
		int count = 0;
		vector<int> ans;
		findMode(root, ret, count);
		for(auto start = ret.begin(); start != ret.end(); start++){
		    if(start->second == count)
			ans.push_back(start->first);
		}
		return ans;
	    }
	// not using hashmap
	void findMode(TreeNode* node, int & curValue, int & curCount, int& maxCount, vector<int>& ans){
		if(!node)
		    return;
		findMode(node->left, curValue, curCount, maxCount, ans);

		if(curCount == 0){
		    // first time
		    curCount = 1;
		    curValue = node->val;
		}
		else if(curValue == node->val){
		    ++curCount;
		}else{
		    //reaches the top
		    if(curCount == maxCount){
			ans.push_back(curValue);
		    }else if(curCount > maxCount){
			ans.clear();
			ans.push_back(curValue);
			maxCount = curCount;
		    }
		    curValue = node->val;
		    curCount = 1;
		}

		findMode(node->right, curValue, curCount, maxCount, ans);
	    }

	    vector<int> findMode(TreeNode* root) {
		// the point is, if the node is different from the child's value, then the child's value reaches its max value.
		int val = -1;
		int count = 0;
		int maxCount = 0;
		vector<int> ans;

		findMode(root, val, count, maxCount, ans);
		if(count > 0 && count == maxCount){
		    ans.push_back(val);
		}else if(count > maxCount){
		    ans.clear();
		    ans.push_back(val);
		    maxCount = count;
		}
		return ans;
	    }
	
	// No.543. Diameter of Binary Tree
	// Given a binary tree, you need to compute the length of the diameter of the tree. The diameter of a binary tree is the length of the longest path between any two nodes in a tree. This path may or may not pass through the root.
	void diameterOfBinaryTree(TreeNode* node, int& depth, int& maxLen){
		if(!node)
		    return;
		int curDepth = depth;
		int curLen = maxLen;
		diameterOfBinaryTree(node->left, depth, maxLen);
		diameterOfBinaryTree(node->right, curDepth, curLen);

		if(node->left || node->right){
		    if(node->left && node->right){
			maxLen = max(curLen,max(maxLen,depth + curDepth + 2));
		    }else{
			maxLen = max(curLen,max(maxLen,max(depth, curDepth)+1));
		    }

		    depth = max(curDepth, depth)+1;
		}
	    }

	    int diameterOfBinaryTree(TreeNode* root) {
		// for each node, find the furthest node from left subtree and right subtree.
		int maxLen = 0;
		int depth = 0;
		diameterOfBinaryTree(root, depth, maxLen);
		return maxLen;
	    }
};


// 297. Serialize and Deserialize Binary Tree
class Codec {
public:
	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		ostringstream out;
		serialize(root, out);
		return out.str();
	}

	void serialize(TreeNode *root, ostringstream &out) {
		if (root) {
			out << root->val << ' ';
			serialize(root->left, out);
			serialize(root->right, out);
		}
		else {
			out << "# ";
		}
	}

	TreeNode* deserialize(istringstream &in) {
		string val;
		in >> val;
		if (val == "#") return nullptr;
		TreeNode *root = new TreeNode(stoi(val));
		root->left = deserialize(in);
		root->right = deserialize(in);
		return root;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		istringstream in(data);
		return deserialize(in);
	}
};
