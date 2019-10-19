#pragma once
#include "common.h"

namespace BinaryTreeOrders {
	// 94. Binary Tree Inorder Traversal
	vector<int> inorderTraversal(TreeNode* root) {
		stack<TreeNode*> s;
		typedef unsigned char byte;
		stack<byte> d;

		s.push(root);
		d.push(0);

		vector<int> ans;
		if (root == NULL) return ans;

		while (!s.empty()) {
			TreeNode* node = s.top();
			byte depth = d.top();

			if (depth == 0) {
				// first step, deal with left
				d.top() = 1;
				if (node->left != NULL) {
					s.push(node->left);
					d.push(0);
				}
			}
			else
				if (depth == 1) {
					// left done, deal itself
					ans.push_back(node->val);
					d.top() = 2;
				}
				else {
					d.pop();
					s.pop();
					if (node->right != NULL) {
						s.push(node->right);
						d.push(0);
					}
				}
		}
		return ans;
	}
	// mine
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> ret;
		vector<TreeNode*> nodes;
		TreeNode* iter = root;
		while(iter || !nodes.empty()){
		    if(iter){
			nodes.push_back(iter);
			iter = iter->left;                
		    }                
		    else{
			// left finish, then self
			iter = nodes.back();
			ret.push_back(iter->val);
			nodes.pop_back();

			iter = iter->right;
		    }                
		}
		return ret;
	    }

	// 144. Binary Tree Preorder Traversal
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> ans;
		if (root == nullptr)
			return ans;
		stack<TreeNode*> s;
		s.emplace(root);
		while (!s.empty()) {
			TreeNode* node = s.top();
			s.pop();
			ans.emplace_back(node->val);
			if (node->right) s.emplace(node->right);
			if (node->left) s.emplace(node->left);
		}
		return ans;
	}
	// mine
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> ans;
		vector<TreeNode*> mystack;
		while(root || !mystack.empty()){
		    if(root){
			ans.push_back(root->val);
			mystack.push_back(root->right);
			root = root->left;    
		    }
		    else{
			root = mystack.back();
			mystack.pop_back();
		    }

		}
		return ans;
	    }

	// 145. Binary Tree Postorder Traversal
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> ans;
		if (root == nullptr)
			return ans;

		using DFSNode = pair<TreeNode*, bool>;
		stack<DFSNode> s;
		s.emplace(DFSNode(root, false));

		while (!s.empty()) {
			DFSNode t = s.top();
			s.pop();
			TreeNode* node = t.first;
			bool output = t.second;
			if (output) {
				ans.emplace_back(node->val);
			}
			else {
				s.push(DFSNode(node, true));
				if (node->right) s.emplace(DFSNode(node->right, false));
				if (node->left) s.emplace(DFSNode(node->left, false));
			}
		}
		return ans;
	}
	// mine
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> ans;
		vector<TreeNode*> mystack;

		while(root || !mystack.empty()){
		    if(root){
			if(root->right){
			    mystack.push_back(root->right);
			}
			mystack.push_back(root);
			root = root->left;                
		    }else{
			root = mystack.back();
			mystack.pop_back();

			if(root->right && !mystack.empty() && root->right == mystack.back()){
			    mystack.pop_back();
			    mystack.push_back(root);
			    root = root->right;                    
			} else{
			    ans.push_back(root->val);
			    root = NULL;
			}
		    }
		}
		return ans;
	    }

	// 102. Binary Tree Level Order Traversal [M]
	// Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> res;
		if (root == nullptr) return res;
		using Level = pair<TreeNode*, int>;


		queue<Level> q;
		q.emplace(Level(root, 0));
		int curLevel = -1;

		while (!q.empty()) {
			Level node = q.front();
			q.pop();
			if (node.second > curLevel) {
				++curLevel;
				vector<int> values(1, node.first->val);
				res.emplace_back(values);
			}
			else {
				res[curLevel].emplace_back(node.first->val);
			}
			if (node.first->left != nullptr) q.push(Level(node.first->left, curLevel + 1));
			if (node.first->right != nullptr) q.push(Level(node.first->right, curLevel + 1));
		}
		return res;
	}
	// mine
	vector<vector<int>> levelOrder(TreeNode* root) {
		vector<vector<int>> ans;
		deque<TreeNode*> mystack;
		vector<int> eachLevel;
		if(root){
		    eachLevel.push_back(root->val);
		    mystack.push_back(root);
		    ans.push_back(eachLevel);
		}
		while(!mystack.empty()){
		    int len = mystack.size();
		    eachLevel.clear();
		    while(len-- > 0){
			root = mystack.front();
			mystack.pop_front();    

			if(root->left){
			    eachLevel.push_back(root->left->val);            
			    mystack.push_back(root->left);
			}
			if(root->right){
			    eachLevel.push_back(root->right->val);            
			    mystack.push_back(root->right);
			}
		    }
		    if(eachLevel.size() > 0)
			ans.push_back(eachLevel);            
		}
		return ans;
	    }

	// 107. Binary Tree Level Order Traversal II
	// Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).
	vector<vector<int>> levelOrderBottom(TreeNode* root) {
		vector<vector<int>> res;
		if (root == nullptr) return res;
		typedef pair<TreeNode*, int> Level;


		queue<Level> q;
		q.push(Level(root, 0));
		int curLevel = -1;

		while (!q.empty()) {
			Level node = q.front();
			q.pop();
			if (node.second > curLevel) {
				++curLevel;
				vector<int> values(1, node.first->val);
				res.push_back(values);
			}
			else {
				res[curLevel].push_back(node.first->val);
			}
			if (node.first->left != nullptr) q.push(Level(node.first->left, curLevel + 1));
			if (node.first->right != nullptr) q.push(Level(node.first->right, curLevel + 1));
		}

		for (int i = 0; i < res.size() >> 1; ++i) {
			swap(res[i], res[res.size() - i - 1]);
		}
		return res;
	}
	// mine
	    std::deque<TreeNode*> mystack;
	    vector<vector<int>> result;
	    std::deque<int> steps;
	    void levelOrderBottomHelp(TreeNode* root){
		TreeNode* cur = NULL;
		int curStep, nextStep;
		while(!mystack.empty()){
		    vector<int> curLevel;
		    curStep = steps.front();
		    steps.pop_front();
		    nextStep = 0;
		    while(curStep-- > 0){
			cur = mystack.front();
			mystack.pop_front();
			curLevel.push_back(cur->val);
			if(cur->left){
			    mystack.push_back(cur->left);
			    ++nextStep;
			}    
			if(cur->right){
			    mystack.push_back(cur->right);
			    ++nextStep;
			}
		    }
		    steps.push_back(nextStep);
		    result.insert(result.begin(),curLevel);
		}
	    }
	    vector<vector<int>> levelOrderBottom(TreeNode* root) {
		if(root){
		    mystack.push_back(root);
		    steps.push_back(1);
		    levelOrderBottomHelp(root);
		}

		return result;
	    }
	// optimized
	void levelOrderBottomHelp(TreeNode* root){
		TreeNode* cur = NULL;
		int curStep, nextStep;
		while(!mystack.empty()){
		    vector<int> curLevel;
		    curStep = mystack.size();
		    while(curStep-- > 0){
			cur = mystack.front();
			mystack.pop_front();
			curLevel.push_back(cur->val);
			if(cur->left){
			    mystack.push_back(cur->left);
			}    
			if(cur->right){
			    mystack.push_back(cur->right);
			}
		    }
		    result.push_back(curLevel);
		}
	    }
	    vector<vector<int>> levelOrderBottom(TreeNode* root) {
		if(root){
		    mystack.push_back(root);
		    levelOrderBottomHelp(root);
		    reverse(result.begin(), result.end());
		}
		return result;
	    }

	// 103. Binary Tree Zigzag Level Order Traversal
	// Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		vector<vector<int>> res;
		if (root == nullptr) return res;
		using Level = pair<TreeNode*, int>;

		queue<Level> q;
		q.push(Level(root, 0));
		int curLevel = -1;

		while (!q.empty()) {
			Level node = q.front();
			q.pop();
			if (node.second > curLevel) {
				++curLevel;
				vector<int> values(1, node.first->val);
				res.emplace_back(values);
			}
			else {
				if (curLevel % 2 == 0) {
					res[curLevel].emplace_back(node.first->val);
				}
				else {
					res[curLevel].insert(res[curLevel].begin(), node.first->val);
				}
			}

			if (node.first->left != nullptr) q.push(Level(node.first->left, curLevel + 1));
			if (node.first->right != nullptr) q.push(Level(node.first->right, curLevel + 1));
		}
		return res;
	}
	// Mine
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
		deque<TreeNode*> mystack;
		vector<vector<int>> ret;
		if(!root)
		    return ret;
		mystack.push_back(root);
		bool direction = true;// left to right
		while(!mystack.empty()){
		    int size = mystack.size();
		    vector<int> curPath;
		    while(size-- > 0){
			TreeNode * curNode = mystack.front();
			mystack.pop_front();
			curPath.push_back(curNode->val);
			if(curNode->left)
			    mystack.push_back(curNode->left);
			if(curNode->right)
			    mystack.push_back(curNode->right);

		    }
		    if(!direction)
			reverse(curPath.begin(), curPath.end());
		    ret.push_back(curPath);
		    direction = !direction;
		}
		return ret;
	    }

	// 331. Verify Preorder Serialization of a Binary Tree
	// Given a string of comma separated values, verify whether it is a correct preorder traversal serialization of a binary tree. Find an algorithm without reconstructing the tree.
	bool isValidSerialization(string preorder) {
		if (preorder.empty()) return false;
		istringstream in(preorder);
		vector<string> v;
		string val;
		int d = 0;
		while (getline(in, val, ',')) v.push_back(val);
		for (int i = 0; i < v.size() - 1; ++i) {
			if (v[i] == "#") {
				if (d == 0) return false;
				else --d;
			}
			else ++d;
		}
		return d != 0 ? false : v.back() == "#";
	}
	
	// No.783. Minimum Distance Between BST Nodes (Mine)
	// Given a Binary Search Tree (BST) with the root node root, return the minimum difference between the values of any two different nodes in the tree.
	void findMin(TreeNode* iter, int& smallest){
		if(!iter)
		    return;
		if(iter->left){
		    TreeNode* rightmost = iter->left;
		    while(rightmost->right){
			rightmost = rightmost->right;
		    }
		    int smallest1 = abs(iter->val - rightmost->val);
		    smallest = smallest > smallest1 ? smallest1 : smallest;
		    findMin(iter->left, smallest);
		}
		if(iter->right){
		    TreeNode* leftmost = iter->right;
		    while(leftmost->left){
			leftmost = leftmost->left;
		    }
		    int smallest1 = abs(iter->val - leftmost->val);
		    smallest = smallest > smallest1 ? smallest1 : smallest;     
		    findMin(iter->right, smallest);
		}
	    }

	    int minDiffInBST(TreeNode* root) {
		// the minimum diff is between one node and left largest or right smallest
		int smallest = root->val;
		findMin(root, smallest);
		return smallest;
	    }
	
	// No.589. N-ary Tree Preorder Traversal (Mine)
	// Given an n-ary tree, return the preorder traversal of its nodes' values.
	vector<int> preorder(Node* root) {
		vector<int> ans;
		vector<Node*> mystack;
		while(root || !mystack.empty()){
		    if(root){
			ans.push_back(root->val);
			for(int i = 1; i < root->children.size(); i++){
			    mystack.push_back(root->children[root->children.size() - i]);
			}
			if(root->children.size() > 0)
			    root = root->children[0];
			else
			    root = NULL;
		    }else{
			root = mystack.back();
			mystack.pop_back();
		    }
		}
		return ans;
	    }
	
	// No.590. N-ary Tree Postorder Traversal (Mine)
	// Given an n-ary tree, return the postorder traversal of its nodes' values.
	vector<int> postorder(Node* root) {
		vector<int> ans;
		vector<Node*> mystack;
		Node* nextRoot;
		while(root || !mystack.empty()){
		    if(root){
			for(int i = 1; i < root->children.size(); i++){
			    mystack.push_back(root->children[root->children.size()-i]);
			}
			mystack.push_back(root);
			if(root->children.size() > 0)
			    root = root->children[0];
			else
			    root = NULL;
		    }else{
			root = mystack.back();
			mystack.pop_back();
			if(!mystack.empty() && root->children.size()>1 && 
			   find(root->children.begin(), root->children.end(), mystack.back()) != root->children.end()){
			    nextRoot = mystack.back();
			    mystack.pop_back();
			    mystack.push_back(root);
			    root = nextRoot;
			}
			else{
			    ans.push_back(root->val);
			    root = NULL;
			}
		    }
		}
		return ans;
	    }
	
	// 429. N-ary Tree Level Order Traversal (Mine)
	// Given an n-ary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level).
	vector<vector<int>> levelOrder(Node* root) {
		vector<vector<int>> ans;
		deque<Node*> mystack;
		vector<int> temp;
		if(root){
		    mystack.push_back(root);
		    temp.push_back(root->val);
		    ans.push_back(temp);    
		}        

		while(!mystack.empty()){
		    temp.clear();

		    int len = mystack.size();
		    for(int j = 0; j < len; j++){
			root = mystack.front();
			mystack.pop_front();

			for(int i = 0; i < root->children.size(); i++){
			    mystack.push_back(root->children[i]);
			    temp.push_back(root->children[i]->val);
			}                
		    }
		    if(temp.size() > 0)
			ans.push_back(temp);
		}

		return ans;
	    }
	// No. 1008 Construct Binary Search Tree from Preorder Traversal (Mine)
	// Return the root node of a binary search tree that matches the given preorder traversal.
	TreeNode* bstFromPreorder(vector<int>& preorder) {
		TreeNode* root = new TreeNode(preorder[0]);
		deque<TreeNode*> mystack;
		mystack.push_back(root);
		int index = 1;
		while(index < preorder.size()){
		    TreeNode* curNode = root;
		    bool changed = true;
		    //cout << preorder[index];
		    while(changed){
			changed = false;
			while(curNode->left && preorder[index] < curNode->val){
			    curNode = curNode->left;
			    changed = true;
			}
			while(curNode->right && preorder[index] > curNode->val){
			    curNode = curNode->right;
			    changed = true;
			}
		    }


		    if(!curNode->left && preorder[index] < curNode->val){
			curNode->left = new TreeNode(preorder[index]);
		    }
		    if(!curNode->right && preorder[index] > curNode->val){
			curNode->right = new TreeNode(preorder[index]);
		    }

		    ++index;

		}
		return root;
	    }
	// optimized
	TreeNode* bstFromPreorderHelper(vector<int>& preorder, int start, int end){
		if(end-start < 1)
		    return NULL;
		int right = start+1;
		TreeNode* cur = new TreeNode(preorder[start]);
		while(right < end && preorder[right] < preorder[start])
		    ++right;
		cur->left = bstFromPreorderHelper(preorder, start+1, right);
		cur->right = bstFromPreorderHelper(preorder, right, end);
		return cur;
	    }
	    TreeNode* bstFromPreorder(vector<int>& preorder){
		return bstFromPreorderHelper(preorder, 0, preorder.size());
	    }
};



// 105. Construct Binary Tree from Preorder and Inorder Traversal
// Given preorder and inorder traversal of a tree, construct the binary tree.
// MLR LMR
class preorderInorder {
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		return buildTree(preorder, 0, (int)preorder.size() - 1, inorder, 0, (int)inorder.size() - 1);
	}

	TreeNode* buildTree(vector<int>& preorder, int pl, int pr, vector<int>& inorder, int il, int ir) {
		printf("%d %d %d %d\n", pl, pr, il, ir);
		if (pr - pl != ir - il) return nullptr;
		if (pr - pl < 0 || ir - il < 0) return nullptr;
		int val = preorder[pl];
		TreeNode* root = new TreeNode(val);
		if (pl == pr) return root;
		int j = -1;
		for (int i = il; i <= ir; ++i) if (inorder[i] == val) {
			j = i;
			break;
		}
		// check if finds or not, assume we always find it
		root->left = buildTree(preorder, pl + 1, pl + 1 + (j - 1 - il), inorder, il, j - 1);
		root->right = buildTree(preorder, pr - (ir - j - 1), pr, inorder, j + 1, ir);
		return root;
	}
};

// 106. Construct Binary Tree from Inorder and Postorder Traversal
// Given inorder and postorder traversal of a tree, construct the binary tree.
class InorderPostorder {
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
	// Mine
	TreeNode* buildTree(vector<int>& inorder, int startIndex1, int endIndex1, vector<int>& postorder, int startIndex2, int endIndex2){
		//cout << startIndex1 << ":" << endIndex1 << "\t" << startIndex2 << ":" << endIndex2 << "\n";
		if(startIndex1 >= endIndex1)
		    return NULL;
		if(startIndex2 >= endIndex2)
		    return NULL;
		int rootVal = postorder[endIndex2-1];
		TreeNode* node = new TreeNode(rootVal);        
		int rootIndex = 0;
		// use map could save time by more space
		for(;rootIndex < endIndex1; rootIndex++){
		    if(inorder[rootIndex] == rootVal){
			//cout << "\tcreate " << rootVal << "\n";
			break;
		    }                
		}

		int leftAmount = rootIndex-startIndex1;
		//int rightAmount = endIndex1-1-leftAmount;
		if(rootIndex-startIndex1 > 0){
		    node->left = buildTree(inorder, startIndex1, rootIndex, postorder, startIndex2, startIndex2 + leftAmount);
		}
		if(endIndex1-1-leftAmount > 0){
		    node->right = buildTree(inorder, rootIndex + 1, endIndex1, postorder, startIndex2 + leftAmount, endIndex2-1);
		}
		return node;
	    }
	    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		return buildTree(inorder, 0, inorder.size(), postorder, 0, postorder.size())   ;
	    }
};
