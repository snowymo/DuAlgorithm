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
	// mine
	int maxDepth(TreeNode* root) {
		if(!root)
		    return 0;
		int depth = 0;
		deque<TreeNode*> mystack;
		mystack.push_back(root);
		while(!mystack.empty()){
		    int size = mystack.size();
		    while(size-- > 0){
			TreeNode* curNode = mystack.front();
			mystack.pop_front();
			if(curNode->left)
			    mystack.push_back(curNode->left);
			if(curNode->right)
			    mystack.push_back(curNode->right);         
		    }
		    ++depth;
		}
		return depth;
	}
	// optimized
	int maxDepth(TreeNode* root) {
		if (root==NULL){
		    return 0;
		}

		int left_height = 1 + maxDepth(root->left);
		int right_height = 1 + maxDepth(root->right);

		if (left_height>right_height){
		    return left_height;
		}

		return right_height;
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
	// mine
	int minDepth(TreeNode* root) {
		deque<TreeNode*> mystack;
		if(!root)
		    return 0;
		mystack.push_back(root);
		int depth = 1;
		while(!mystack.empty()){
		    int size = mystack.size();        
		    while(size-- > 0){
			TreeNode* curNode = mystack.front();
			mystack.pop_front();
			if(!curNode->left && !curNode->right)
			    return depth;
			if(curNode->left)
			    mystack.push_back(curNode->left);
			if(curNode->right)
			    mystack.push_back(curNode->right);

		    }
		    ++depth;
		}
		return depth;
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
	// mine
	Node* connect(Node* root) {
		if(!root)
		    return root;
		deque<Node*> mystack;
		mystack.push_back(root);
		while(!mystack.empty()){
		    int size = mystack.size();
		    while(size-- > 0){
			Node* curNode = mystack.front();
			mystack.pop_front();
			if(size > 0)
			    curNode->next = mystack.front();
			if(curNode->left){
			    mystack.push_back(curNode->left);
			    mystack.push_back(curNode->right);
			}

		    }
		}
		return root;
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
	// mine
	// the same as No.116
	// just slightly changed the condition for right child

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
	// mine, iterative
	vector<string> binaryTreePaths(TreeNode* root) {
		// it depends on how many leaves
		map<TreeNode*, TreeNode*> myParent;
		vector<TreeNode*> mystack;
		vector<string> ans;
		while(root || !mystack.empty()){
		    if(root){
			if(root->left){
			    myParent[root->left] = root;
			}
			if(root->right){
			    myParent[root->right] = root;
			}
			if(!root->left && !root->right){
			    //leaf
			    TreeNode* leaf = root;
			    vector<int> path;
			    path.push_back(leaf->val);
			    while(myParent[leaf]){
				leaf = myParent[leaf];
				path.push_back(leaf->val);
			    }
			    string st = std::to_string(path[path.size()-1]);
			    for(int i = 1; i < path.size(); i++){
				st += "->" + std::to_string(path[path.size()-i-1]);
			    }
			    ans.push_back(st);
			    root = NULL;
			}else{
			    mystack.push_back(root->right);
			    root = root->left;    
			}                
		    }
		    else{
			root = mystack.back();
			mystack.pop_back();
		    }
		}
		return ans;
	    }
	
	// No.98. Validate Binary Search Tree
	// Given a binary tree, determine if it is a valid binary search tree (BST).
	bool isValidTree(TreeNode* node, int* lower, int* upper){
		if(!node)
		    return true;
		bool bLeft = lower == NULL || node->val > *lower;
		bool bRight = upper == NULL || node->val < *upper;
		if(bLeft && bRight){
		    return isValidTree(node->left, lower, &(node->val))
			&& isValidTree(node->right, &(node->val), upper);
		}
		else
		    return false;
	    }
	    bool isValidBST(TreeNode* root) {
		return isValidTree(root, NULL, NULL);
	    }
	// iteration solution
	bool isValidBST(TreeNode* root) {
		vector<TreeNode*> mystack;
		vector<int*> lowers, uppers;
		mystack.push_back(root);
		lowers.push_back(NULL);
		uppers.push_back(NULL);
		int* lower, *upper;
		while(!mystack.empty()){
		    root = mystack.back();
		    lower = lowers.back();
		    upper = uppers.back();
		    mystack.pop_back();
		    lowers.pop_back();
		    uppers.pop_back();
		    if(root){
			if(lower && root->val <= *lower)
			    return false;
			if(upper && root->val >= *upper)
			    return false;
			mystack.push_back(root->left);
			lowers.push_back(lower);
			uppers.push_back(&(root->val));
			mystack.push_back(root->right);
			lowers.push_back(&(root->val));
			uppers.push_back(upper);
		    }
		}
		return true;
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
	// No. 637 Average of Levels in Binary Tree (Mine)
	// Given a non-empty binary tree, return the average value of the nodes on each level in the form of an array.
	vector<double> averageOfLevels(TreeNode* root) {
		deque<TreeNode*> mystack;
		mystack.push_back(root);
		vector<double> result;
		while(!mystack.empty()){
		    int curLevelSize = mystack.size();
		    int number = curLevelSize;
		    double sum = 0;
		    while(curLevelSize-- > 0){
			TreeNode* curNode = mystack.front();
			mystack.pop_front();
			sum += curNode->val;
			if(curNode->left)
			    mystack.push_back(curNode->left);
			if(curNode->right)
			    mystack.push_back(curNode->right);

		    }
		    result.push_back(sum / (double)number);

		}
		return result;
	    }
	// No. 559 Given a n-ary tree, find its maximum depth. (Mine)
	// The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node.
	 int maxDepth(Node* root) {
		deque<Node*> mystack;
		if(!root)
		    return 0;
		mystack.push_back(root);
		int depth = 1;
		while(!mystack.empty()){

		    int size = mystack.size();
		    bool hasChildren = false;
		    while(size -- > 0){
			Node* curNode = mystack.front();
			mystack.pop_front();
			for(int i = 0; i < curNode->children.size(); i++){
			    mystack.push_back(curNode->children[i]);
			    hasChildren = true;
			}
		    }
		    if(hasChildren)
			++depth;
		}
		return depth;
	    }
	    int maxDepth(Node* root){
		if(!root)
		    return 0;
		int depth = 1;
		for(int i = 0; i < root->children.size(); i++){
		    int curDepth = 1 + maxDepth(root->children[i]);
		    if(curDepth > depth)
			depth = curDepth;
		}
		return depth;
	    }
	// No. 110 Balanced Binary Tree(Mine)
	// Given a binary tree, determine if it is height-balanced.
	// For this problem, a height-balanced binary tree is defined as:
	// a binary tree in which the depth of the two subtrees of every node never differ by more than 1.
	bool ret = true;
	    int getDepth(TreeNode* root){
		if(!root)
		    return 0;

		int leftDepth = 0, rightDepth = 0;
		if(root->left)
		    leftDepth = 1+ getDepth(root->left);
		if(root->right)
		    rightDepth = 1 + getDepth(root->right);
		if(abs(leftDepth-rightDepth) > 1)
		    ret = false;
		return max(leftDepth, rightDepth);

	    }
	    bool isBalanced(TreeNode* root) {
		getDepth(root);
		return ret;
	    }
	// No.993 Cousins in Binary Tree(Mine
	// In a binary tree, the root node is at depth 0, and children of each depth k node are at depth k+1.
	//Two nodes of a binary tree are cousins if they have the same depth, but have different parents.
	// We are given the root of a binary tree with unique values, and the values x and y of two different nodes in the tree.
	// Return true if and only if the nodes corresponding to the values x and y are cousins
	bool isCousins(TreeNode* root, int x, int y) {
		if(!root)
		    return false;
		deque<TreeNode*> mystack;
		mystack.push_back(root);
		while(!mystack.empty()){
		    int size = mystack.size();
		    int count = 0;
		    while(size-- > 0){
			TreeNode* curNode = mystack.front();
			mystack.pop_front();

			if(curNode->val == x || curNode->val == y){
			    if(++count == 2)
			    return true;
			}
			if(curNode->left && curNode->right){
			    if(curNode->left->val == x
			      && curNode->right->val == y)
				return false;
			    if(curNode->left->val == y
			      && curNode->right->val == x)
				return false;
			}
			if(curNode->left)
			    mystack.push_back(curNode->left);
			if(curNode->right)
			    mystack.push_back(curNode->right);
		    }

		}
		return false;
	    }
	// No.687 Longest Univalue Path (Mine)
	// Given a binary tree, find the length of the longest path where each node in the path has the same value. This path may or may not pass through the root.
	// The length of path between two nodes is represented by the number of edges between the
	struct MyNode{
		int length;// the longest path may or may not include the root
		int leftLength;// the path including the root and left children
		int rightLength;// the path including th root and the right children
		int val; // the value related to the length
		MyNode(): length(0), leftLength(0), rightLength(0), val(-1234){}
	    };
	    int longestHelper(TreeNode* root, MyNode* ret){
		if(!root){
		    return 0;
		}
		//cout << "visiting " << root->val << "\n";
		MyNode* leftRet = new MyNode(), *rightRet = new MyNode();
		int leftPath = longestHelper(root->left, leftRet);
		int rightPath = longestHelper(root->right, rightRet);
		//cout << leftPath << ":" << *leftVal << "\t" << rightPath <<":" << *rightVal << "\n";
		//cout << "root->val\t" << root->val;

		ret->val = root->val;

		//ret->leftLength = 0;
		if(root->left ){
		    if(leftRet && root->val == root->left->val){        
			ret->leftLength = 1 + max(leftRet->leftLength, leftRet->rightLength);
		    }

		}
		if(root->right ){
		    if(rightRet && root->val == root->right->val){
			ret->rightLength = 1 +  max(rightRet->leftLength, rightRet->rightLength);
		    }

		}

		    ret->length = max(ret->leftLength, ret->rightLength);
		// if two children
		if(root->left && root->right){
		    if(root->val == root->left->val &&
		      root->val == root->right->val){ 
			ret->length = max(ret->length,2 + max(leftRet->leftLength, leftRet->rightLength) + max(rightRet->leftLength, rightRet->rightLength));
		    }
		}
		if(ret->length < leftPath){
		    //cout << "leftVal " << *leftVal << "\n";
		    ret->length = leftPath;
		    ret->val = leftRet->val;
		}
		if(ret->length < rightPath){
		    //cout << "rightVal " << *rightVal << "\n";
		    ret->val = rightRet->val;
		    ret->length = rightPath;
		}
		//if(ret->length > 1)
		//     cout << "leaving " << root->val << " with ";
		// if(root->left)
		//     cout << "leftchild " << root->left->val;
		// if(root->right)
		//     cout << "rightchild " << root->right->val;
		// ret->output();
		return ret->length;
	    }
	    int longestUnivaluePath(TreeNode* root) {
		MyNode* ret = new MyNode();
		return longestHelper(root, ret);
	    }
	// No.112 Path Sum I(Mine)
	//Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum.
	// Note: A leaf is a node with no children.
	bool hasPathSum(TreeNode* root, int sum) {
		if(!root)
		    return false;
		if(!root->left && !root->right){
		    if(root->val == sum)
			return true;
		    else
			    return false;
		}
		return hasPathSum(root->left, sum-root->val)
		    || hasPathSum(root->right, sum-root->val);
	    }
	// No. 113 Path Sum II(Mine)
	// Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
	vector<vector<int>> ret;
	    void pathSumHelp(TreeNode* root, int sum, vector<int> path){
		if(!root){
		    return;
		}
		if(!root->left && !root->right){
		    if(root->val == sum){
			path.push_back(root->val);
			ret.push_back(path);
			return;
		    }
		}
		path.push_back(root->val);
		pathSumHelp(root->left, sum-root->val, path);
		pathSumHelp(root->right, sum-root->val, path);
	    }
	    vector<vector<int>> pathSum(TreeNode* root, int sum) {
		vector<int>path;
		pathSumHelp(root, sum, path);
		return ret;
	    }
	// No.437 Path Sum III(Mine)
	// You are given a binary tree in which each node contains an integer value.
	// Find the number of paths that sum to a given value.
	// The path does not need to start or end at the root or a leaf, but it must go downwards (traveling only from parent nodes to child nodes).
	int pathSumHelp(TreeNode* root, deque<int> sums){
		int ret = 0;
		int size = sums.size();
		int oriSum = sums[0];
		for(int i = 0; i < size; i++){
		    if(sums[i] == root->val)
			++ret;
		    sums[i] = (sums[i] - root->val);
		}
		sums.push_front( oriSum);
		int leftRet = 0;
		int rightRet = 0;

		if(root->left)
		    leftRet = pathSumHelp(root->left, sums);
		if(root->right)
		    rightRet = pathSumHelp(root->right, sums);
		return ret + leftRet + rightRet;
	    }
	    int pathSum(TreeNode* root, int sum) {
		if(!root)
		    return 0;
		deque<int> sums;
		sums.push_back(sum);
		return pathSumHelp(root, sums);
	    }
	// No. 669 Trim Binary Search Tree(Mine)
	// Given a binary search tree and the lowest and highest boundaries as L and R, 
	// trim the tree so that all its elements lies in [L, R] (R >= L). 
	// You might need to change the root of the tree, so the result should return the new root of the trimmed binary search tree.
	TreeNode* trimBST(TreeNode* root, int L, int R) {
		if(!root)
		    return root;
		if(root->val < L){
		    return trimBST(root->right, L, R);
		}
		if(root->val > R){
		    return trimBST(root->left, L, R);
		}
		if(root->left)
		    root->left = trimBST(root->left, L, R);
		if(root->right)
		    root->right = trimBST(root->right, L, R);
		return root;
	    }
	// No. 1130 Minimun cost tree from leave values (Mine)
	// Given an array arr of positive integers, consider all binary trees such that:
	// Each node has either 0 or 2 children;
	// The values of arr correspond to the values of each leaf in an in-order traversal of the tree.  (Recall that a node is a leaf if and only if it has 0 children.)
	// The value of each non-leaf node is equal to the product of the largest leaf value in its left and right subtree respectively.
	// Among all possible binary trees considered, return the smallest possible sum of the values of each non-leaf node.  It is guaranteed this sum fits into a 32-bit integer.
	int mctFromLeafValues(vector<int>& arr) {
		int sums = 0;
		// we need to let the smallest two combine together
		while(arr.size() > 1){
		    vector<int> indices;
		    int index = 0;
		    int product = arr[0] * arr[1];
		    indices.push_back(index);
		    vector<int> temp;

		    for(int i = 1; i < arr.size()-1; i++){
			int curProduct = arr[i] * arr[i+1];
			if(curProduct == product){
			    indices.push_back(i);
			}
			if(curProduct < product){
			    product = curProduct;
			    indices.clear();
			    indices.push_back(i);
			}
		    }
		    // get rid of those indices with new values
		    for(int i = 0, j = 0; i < arr.size(); i ++){
			if(j < indices.size() && i == indices[j]){
			    sums += arr[i] * arr[i+1];
			    //cout << " " << sums;
			    temp.push_back(max(arr[i],arr[i+1]));
			    ++j;
			    ++i;
			}else{
			    temp.push_back(arr[i]);
			}
		    }
		    arr = temp;
		    //cout << "\n" << arr.size();
		}
		return sums;
	    }
	// No.515 Find Largest Value in Each Tree Row (Mine)
	// You need to find the largest value in each row of a binary tree.
	vector<int> largestValues(TreeNode* root) {
		vector<int> ret;
		if(!root)
		    return ret;
		deque<TreeNode*> mystack;
		mystack.push_back(root);

		while(!mystack.empty()){
		    int size = mystack.size();
		    int largest = mystack.front()->val;
		    while(size-- > 0){
			TreeNode* curNode = mystack.front();
			mystack.pop_front();
			if(curNode->val > largest)
			    largest = curNode->val;
			if(curNode->left)
			    mystack.push_back(curNode->left);
			if(curNode->right)
			    mystack.push_back(curNode->right);
		    }
		    ret.push_back(largest);
		}
		return ret;
	    }
	
	// No.329 Longest Increasing Path in a Matrix(Mine)
	// Given an integer matrix, find the length of the longest increasing path.
	// From each cell, you can either move to four directions: left, right, up or down. You may NOT move diagonally or move outside of the boundary (i.e. wrap-around is not allowed).
	struct MatrixNode{
		int rowIndex;
		int columnIndex;
		vector<MatrixNode*> next;
		int depth;
		bool isRoot;
		MatrixNode(int r, int c):rowIndex(r), columnIndex(c),depth(-1),isRoot(true){}
	    };
	    int nCol = 0;
	    int helper(MatrixNode* node){
		if(!node)
		    return 0;
		if(node->depth > 0)
		    return node->depth;

		int count = 0;
		for(int i = 0; i < node->next.size(); i++){
		    int temp = helper(node->next[i]);
		    if(temp > count)
			count = temp;
		}
		node->depth = count+1;
		//cout << "\t" << node->rowIndex << "," << node->columnIndex << ":"<< count+1 << "\n";
		return count+1;
	    }
	    int longestIncreasingPath(vector<vector<int>>& matrix) {
		if(matrix.empty())
		    return 0;
		nCol = matrix[0].size();
		// create the path between the matrix
		vector<MatrixNode*> matrixNode;
		for(int i = 0; i < matrix.size(); i++){
		    for(int j = 0; j < matrix[i].size(); j++){
			//cout << i << "-" << j << "\n";
			MatrixNode* curNode = new MatrixNode(i,j);
			//cout << curNode->rowIndex << "," << curNode->columnIndex << ":" << curNode->isRoot << "\n";
		       //cout << i<<","<<j<<":"<<matrix[i][j] << "\t";
			// test four direction
			if(i-1>=0 && matrix[i][j] < matrix[i-1][j]){
			    // up
			    curNode->next.push_back(matrixNode[(i-1)*nCol+j]);
			    //cout << matrixNode[(i-1)*nCol+j]->rowIndex << "," 
			       // << matrixNode[(i-1)*nCol+j]->columnIndex << ":False";
			    matrixNode[(i-1)*nCol+j]->isRoot = false;
			   //cout << i<<","<<j<<":"<<matrix[i][j]<<"->next "<<i-1<<","<<j<<":"<<matrix[i-1][j]<<"\n";
			}
			if(i-1>=0 && matrix[i][j] > matrix[i-1][j]){
			    // up
			    matrixNode[(i-1)*nCol+j]->next.push_back(curNode);
			    curNode->isRoot = false;
			    //cout << curNode->rowIndex << "," << curNode->columnIndex << ":False";
			   //cout << i-1<<","<<j<<":"<<matrix[i-1][j]<<"->next "<<i<<","<<j<<":"<<matrix[i][j]<<"\n";
			}

			 if(j-1>=0 && matrix[i][j] < matrix[i][j-1]){
			    // left
			     int index = i * nCol + j - 1;
			     //cout << "index " << index << "\n";
			    curNode->next.push_back(matrixNode[index]);
			     matrixNode[index]->isRoot = false;
			     //cout << matrixNode[index]->rowIndex << "," << matrixNode[index]->columnIndex << ":False";
			     //cout << i<<","<<j<<":"<<matrix[i][j]<<"->next "<<i<<","<<j-1<<":"<<matrix[i][j-1]<<"\n";
			}
			if(j-1>=0 && matrix[i][j] > matrix[i][j-1]){
			    // left
			    matrixNode[(i)*nCol+j-1]->next.push_back(curNode);
			    curNode->isRoot = false;
			    //cout << curNode->rowIndex << "," << curNode->columnIndex << ":False";
			     //cout << i<<","<<j-1<<":"<<matrix[i][j-1]<<"->next "<<i<<","<<j<<":"<<matrix[i][j]<<"\n";

			}
			//cout << curNode->next.size();
			//cout << "push back index:" << matrixNode.size()<<"\t";
			 matrixNode.push_back(curNode);
			//cout << curNode->rowIndex << "," << curNode->columnIndex << ":" << curNode->isRoot << "\n";
			//cout << "\t[0,0] root " << matrixNode[0]->isRoot << "\n";
		    }
		}
		int ret = 0;
		//cout << "here";
		// calculate the largest depth for tree matrixNode
		for(int i = 0; i < matrixNode.size(); i++){
		    //deque<MatrixNode*> mystack;
		    //cout << "visiting " << matrixNode[i]->rowIndex << "," << matrixNode[i]->columnIndex << ":" << matrixNode[i]->isRoot << "\n";
		    if(!matrixNode[i]->isRoot)
			continue;
		    ///cout << i << "\n";
		    int temp = helper(matrixNode[i]);
		    if(temp > ret)
			ret = temp;
		}
		return ret;
	    }
	// optimized, not necessary to create a tree, just fill the depth for each cell
	int longestIncreasingPath(vector<vector<int>>& matrix) {
		if(matrix.empty()) return 0;
		const int r = matrix.size(), c = matrix[0].size();
		vector<vector<int>> m(r, vector<int>(c, 0));
		int count = 1;
		for(int i = 0; i < r; ++i)
		    for(int j = 0; j < c; ++j)
			if(!m[i][j]) count = max(count, dfs(matrix, m, i, j));
		return count;
	    }
	    static int dfs(vector<vector<int>>& matrix, vector<vector<int>>& m, const int i, const int j) {
		if(m[i][j]) return m[i][j];
		int r = matrix.size(), c = matrix[0].size();
		if(i > 0 && matrix[i-1][j] > matrix[i][j]) m[i][j] = max(m[i][j], dfs(matrix, m, i-1, j));
		if(i < r-1 && matrix[i+1][j] > matrix[i][j]) m[i][j] = max(m[i][j], dfs(matrix, m, i+1, j));
		if(j > 0 && matrix[i][j-1] > matrix[i][j]) m[i][j] = max(m[i][j], dfs(matrix, m, i, j-1));
		if(j < c-1 && matrix[i][j+1] > matrix[i][j]) m[i][j] = max(m[i][j], dfs(matrix, m, i, j+1));
		return ++m[i][j];
	    }
	
	// No.530 Minimum Absolute Difference in BST(Mine)
	// Given a binary search tree with non-negative values, find the minimum absolute difference between values of any two nodes.
	int ret = 1000;
	    int getMinimum(TreeNode * node){
		// return minimum value
		while(node->left)
		    node = node->left;
		return node->val;
	    }
	    int getMaximum(TreeNode* node){
		while(node->right)
		    node = node->right;
		return node->val;
	    }
	    int getMinimumDifference(TreeNode* root) {
		if(ret == 0)
		    return ret;
		// deal with cur node
		if(root->left){
		    ret = min(ret, abs(root->val- getMaximum(root->left)));
		    ret = min(ret, getMinimumDifference(root->left));
		}

		if(root->right){
		    ret = min(ret, abs(root->val- getMinimum(root->right)));
		    ret = min(ret, getMinimumDifference(root->right));
		}
		    return ret;
	    }
	// inspired by inorder traversal solution and optimized it
	int ret = INT_MAX;
	void inorder(TreeNode* root, int& prevVal)
		{
		if(root == nullptr)
		    return;

		inorder(root->left, prevVal);
		ret = min(ret, abs(prevVal - root->val));
		prevVal = root->val;
		inorder(root->right, prevVal);
		 }

		 int getMinimumDifference(TreeNode* root) {
		int temp = INT_MAX;
		inorder(root, temp);
		return ret;   
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
	
	// mine, iterative
	// Encodes a tree to a single string.
	    string serialize(TreeNode* root) {
		string res = "";
		deque<TreeNode*> mystack;
		if(root){
		    mystack.push_back(root);
		    res += std::to_string(root->val);
		}
		while(!mystack.empty()){
		    int len = mystack.size();
		    while(len-- > 0){
			TreeNode* cur = mystack.front();
			mystack.pop_front();
			if(cur->left)    {
			    mystack.push_back(cur->left);
			    res += "," + std::to_string(cur->left->val);
			}else{
			    res += ",n";
			}
			if(cur->right)    {
			    mystack.push_back(cur->right);
			    res += "," + std::to_string(cur->right->val);
			}else{
			    res += ",n";
			}
		    }
		}
		return res;
	    }

	    // Decodes your encoded data to tree.
	    TreeNode* deserialize(string data) {
		if(data.size() == 0){
		    return NULL;
		}

		int curIdx = 0, nextComma = 0;
		nextComma = data.find(",");
		if(nextComma == std::string::npos){
		    // one element
		    TreeNode* root = new TreeNode(stoi(data));
		    return root;
		}
		string curVal = data.substr(curIdx, nextComma);
		curIdx = nextComma+1;
		TreeNode* root = new TreeNode(stoi(curVal));

		int step = 0;//0 - left, 1 - right
		deque<TreeNode*> mystack;
		mystack.push_back(root);
		TreeNode*cur = NULL;

		nextComma = data.find(",", curIdx);    
		while(nextComma != std::string::npos){
		    curVal = data.substr(curIdx, nextComma-curIdx);
		    curIdx = nextComma+1;

		    if(step == 0){
			cur = mystack.front();
			mystack.pop_front();
			if(curVal != "n"){
			    cur->left = new TreeNode(stoi(curVal));
			    mystack.push_back(cur->left);   
			}else{
			    cur->left = NULL;
			}                    
		    }else if(step == 1){
			if(curVal != "n"){
			    cur->right = new TreeNode(stoi(curVal));
			    mystack.push_back(cur->right);
			}else{
			    cur->right = NULL;
			}
		    }
		    step = (step+1) % 2;
		    nextComma = data.find(",", curIdx);
		}
		// last
		curVal = data.substr(curIdx);
		if(step == 0){
		    cur = mystack.front();
		    mystack.pop_front();
		    if(curVal != "n"){
			cur->left = new TreeNode(stoi(curVal));
			mystack.push_back(cur->left);   
		    }else{
			cur->left = NULL;
		    }                    
		}else if(step == 1){
		    if(curVal != "n"){
			cur->right = new TreeNode(stoi(curVal));
			mystack.push_back(cur->right);
		    }else{
			cur->right = NULL;
		    }
		}
		return root;
	    }
};
