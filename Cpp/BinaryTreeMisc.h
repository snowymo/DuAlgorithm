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
