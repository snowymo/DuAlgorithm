#pragma once
#include "common.h"

namespace DFSTree {
	int dfsLeafSimilar(vector<TreeNode*>& s) {
		while (true) {
			const auto node = s.back();
			s.pop_back();
			if (node->right) {
				s.emplace_back(node->right);
			}
			if (node->left) {
				s.emplace_back(node->left);
			}
			if (!node->left && !node->right) {
				return node->val;
			}
		}
	}

	bool leafSimilar(TreeNode* root1, TreeNode* root2) {
		vector<TreeNode*> s1{ root1 }, s2{ root2 };
		while (!s1.empty() && !s2.empty()) {
			if (dfsLeafSimilar(s1) != dfsLeafSimilar(s2)) {
				return false;
			}
		}
		return s1.empty() && s2.empty();
	}

	void addOperatorsDFS(string num, int target, long long diff, long long curNum, string out, vector<string> &res) {
		if ((int)num.size() == 0 && curNum == target) res.push_back(out);


		for (int i = 1; i <= (int)num.size(); ++i) {
			string s = num.substr(0, i);
			string next = num.substr(i);
			long long n = stoll(s);
			if (s.size() > 1 && s[0] == '0') return;
			if (out.size() > 0) {
				addOperatorsDFS(next, target, n, curNum + n, out + "+" + s, res);
				addOperatorsDFS(next, target, -n, curNum - n, out + "-" + s, res);
				// 3-5*2
				addOperatorsDFS(next, target, diff * n, (curNum - diff) + diff * n, out + "*" + s, res);
			}
			else {
				addOperatorsDFS(next, target, n, n, s, res);
			}
		}
	}


	vector<string> addOperators(string num, int target) {
		vector<string> res;
		addOperatorsDFS(num, target, 0, 0, "", res);
		return res;
	}
}

class DFSLinear {
public:
	// 39. Combination Sum [M]
	// Given a set of candidate numbers (candidates) (without duplicates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.
	// DFS O(n!)
	vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end());
		vector<vector<int>> ans;
		vector<int> sol;
		combinationSumDFS(candidates, target, sol, ans, 0);
		return ans;
	}

private:
	void combinationSumDFS(vector<int>& candidates, int target, vector<int>& sol, vector<vector<int>> &ans, int pos) {
		if (target == 0) {
			ans.push_back(sol);
			return;
		}
		for (int i = pos; i < (int)candidates.size(); ++i) {
			if (candidates[i] > target) return;
			sol.push_back(candidates[i]);
			combinationSumDFS(candidates, target - candidates[i], sol, ans, i);
			sol.pop_back();
		}
	}

	// 40. Combination Sum II
	// Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sums to target.
public:
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
		sort(candidates.begin(), candidates.end());
		vector<vector<int>> ans;
		vector<int> sol;
		combinationSumDFS2(candidates, target, sol, ans, 0);
		return ans;
	}

private:
	void combinationSumDFS2(vector<int>& candidates, int target, vector<int>& sol, vector<vector<int>> &ans, int pos) {
		if (target == 0) {
			ans.push_back(sol);
			return;
		}
		int previous = INT_MIN;
		for (int i = pos; i < (int)candidates.size(); ++i) {
			if (previous == candidates[i]) continue;
			if (candidates[i] > target) return;
			previous = candidates[i];
			sol.push_back(candidates[i]);
			combinationSumDFS2(candidates, target - candidates[i], sol, ans, i + 1);
			sol.pop_back();
		}
	}

public:
	// 241. Different Ways to Add Parentheses
	// Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *.
	vector<int> diffWaysToCompute(string s) {
		const int n = (int)s.size();
		vector<vector<vector<int>>> d(n + 1, vector<vector<int>>(n + 1));
		return diffWaysToComputeDFS(s, 0, n, d);
	}

private:
	vector<int> diffWaysToComputeDFS(const string& s, const int l, const int r, vector<vector<vector<int>>>& d) {
		if (!d[l][r].empty()) {
			return d[l][r];
		}
		vector<int> res;
		for (int i = l; i < r; ++i) {
			const auto c = s[i];
			if (c == '+' || c == '-' || c == '*') {
				auto left = diffWaysToComputeDFS(s, l, i, d);
				auto right = diffWaysToComputeDFS(s, i + 1, r, d);
				for (const auto& x : left) {
					for (const auto& y : right) {
						if (c == '+') {
							res.emplace_back(x + y);
						}
						else if (c == '-') {
							res.emplace_back(x - y);
						}
						else {
							res.emplace_back(x * y);
						}
					}
				}
			}
		}
		// If the input string contains only number.
		if (res.empty()) {
			res.emplace_back(stoi(s.substr(l, r - l)));
		}
		d[l][r] = res;
		return d[l][r];
	}
	// Mine is in DivideNConquer.cpp
	
	// 1020. Number of Enclaves (Mine)
	// Given a 2D array A, each cell is 0 (representing sea) or 1 (representing land)
	// A move consists of walking from one land square 4-directionally to another land square, or off the boundary of the grid.
	// Return the number of land squares in the grid for which we cannot walk off the boundary of the grid in any number of moves. 

	// Example 1:
	// Input: [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
	// Output: 3
	// Explanation: 
	// There are three 1s that are enclosed by 0s, and one 1 that isn't enclosed because its on the boundary.
	// Example 2:
	// Input: [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
	// Output: 0
	// Explanation: 
	// All 1s are either on the boundary or can reach the boundary.

	// Note:
	// 1 <= A.length <= 500
	// 1 <= A[i].length <= 500
	// 0 <= A[i][j] <= 1
	// All rows have the same size.
	int numEnclaves(vector<vector<int>>& A) {
		vector<vector<int>> B(A.size(), vector<int>(A[0].size()));
		int rowsize = A.size();
		int colsize = A[0].size();
		//cout << "total " << rowsize << " rows and " << colsize << " cols\n";

		for(int j = 0; j < colsize; j++){
		    int i = 0;
		    if(A[i][j] == 1){
			// this is one root, fill the path
			//cout << "fill " << i << "," << j << "\n";
			fillThePath(A, B, i, j);
		    }
		    i = rowsize-1;
		    if(A[i][j] == 1){
			// this is one root, fill the path
			//cout << "fill " << i << "," << j << "\n";
			fillThePath(A, B, i, j);
		    }
		}


		for(int j = 1; j < rowsize-1; j++){
		    int i = 0;
		    if(A[j][i] == 1){
			// this is one root, fill the path
			//cout << "fill " << j << "," << i << "\n";
			fillThePath(A, B, j, i);
		    }
		    i = colsize-1;
		    if(A[j][i] == 1){
			// this is one root, fill the path
			//cout << "fill " << j << "," << i << "\n";
			fillThePath(A, B, j, i);
		    }
		}

		auto sumA = std::accumulate(A.cbegin(), A.cend(), 0, [](auto lhs, const auto& rhs) {
		    return std::accumulate(rhs.cbegin(), rhs.cend(), lhs);
		});
		auto sumB = std::accumulate(B.cbegin(), B.cend(), 0, [](auto lhs, const auto& rhs) {
		    return std::accumulate(rhs.cbegin(), rhs.cend(), lhs);
		});
		return sumA-sumB;

	    }
	    void fillThePath(vector<vector<int>>& A, vector<vector<int>>& B, int row, int col){
		if(B[row][col] == 1 || A[row][col] == 0)
		    return;
		//cout << "assign B " << A[row][col] << "\t" << row << "," << col << "\n";
		B[row][col] = 1;
		if(row >= 1 && A[row-1][col]){
		    fillThePath(A, B, row-1, col);
		}
		if(row < A.size()-1 && A[row+1][col]){
		    fillThePath(A, B, row+1, col);
		}
		if(col >= 1 && A[row][col-1]){
		    fillThePath(A, B, row, col-1);
		}
		if(col < A[0].size()-1 && A[row][col+1]){
		    fillThePath(A, B, row, col+1);
		}
	    }
	
	// Mine No.79 Word Search [M]
	// sol 1. dfs && backtrace, slow
// 	Given a 2D board and a word, find if the word exists in the grid.

// The word can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once.

// Example:

// board =
// [
//   ['A','B','C','E'],
//   ['S','F','C','S'],
//   ['A','D','E','E']
// ]

// Given word = "ABCCED", return true.
// Given word = "SEE", return true.
// Given word = "ABCB", return false.
	    int width;
	    // vector<vector<char>> globalboard;
	    bool exist2(vector<vector<char>>& board, string word) {
		// create a graph first
		// globalboard = board;
		unordered_map<char, vector<int>> mapCharPos;
		for(int i = 0; i < board.size(); i++){
		    int len = board[i].size();
		    width = len;
		    for(int j = 0; j < len; j++){
			mapCharPos[board[i][j]].push_back(i * len + j);
		    }
		}
		// check if the word exists
		return existHelp(mapCharPos, word, 0, -1);
	    }


	    unordered_map<int,bool> used;
	    bool existHelp(unordered_map<char, vector<int>>& mapCharPos, string& word, int progress, int parent){
		// cout << "progress " << progress << "\n";
		if(progress == word.size())
		    return true;

		vector<int> candidates = mapCharPos[word[progress]];        
		for(int i = 0; i < candidates.size(); i++){
		    int curPos = candidates[i];
		    if(used.count(curPos) > 0 && used[curPos])
			continue;
		    if(parent == -1 || ((abs(curPos-parent) == 1) && (curPos/width == parent/width)) || (abs(curPos-parent) == width) ){
			// the char is acceptable
			// cout << "try " << curPos << " " << globalboard[(int)(curPos/width)][curPos%width] << " with parent " << parent << "\n";
			// mapCharPos[word[progress]].erase(mapCharPos[word[progress]].begin() + i);
			used[curPos] = true;
			bool thisTry= existHelp(mapCharPos, word, progress+1, curPos);
			if(thisTry)
			    return true;
			else
			    used[curPos] = false;
			// cout << "failed and put " << curPos << " back\n";
		    }
		}

		return false;
	    }

	    // sol.2 DP?
	    // sol.2 still dfs and backtracing, however, don't check all the candidates but check four directions.
	    const vector<vector<int>> dirs {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	    bool exist(vector<vector<char>>& board, string word)
	    {
		int row = board.size(), col = board[0].size();
		for (int i = 0; i < row; i++) {
		    for (int j = 0; j < col; j++) {
			if (word[0] == board[i][j] && dfs(board, word, i, j, 0)) {
			    return true;
			}
		    }
		}
		return false;
	    }
	       bool dfs(vector<vector<char>>& board, string word, int row, int col, int index) {
		if (index == word.size()) {
		    return true;
		}

		if (row < 0 || col < 0 || row >= board.size() || col >= board[0].size() || board[row][col] != word[index]) {
		    return false;
		}

		char old = board[row][col];
		board[row][col] = '$';

		// all branches
		for (const auto& dir : dirs) {
		    if (dfs(board, word, row + dir[0], col + dir[1], index + 1)) {
			board[row][col] = old;
			return true;
		    }
		}

		board[row][col] = old;
		return false;
	    }
	
	// Mine No.212 Word Search [H]
// 	Given a 2D board and a list of words from the dictionary, find all words in the board.
// Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word.
// Example:
// Input: 
// board = [
//   ['o','a','a','n'],
//   ['e','t','a','e'],
//   ['i','h','k','r'],
//   ['i','f','l','v']
// ]
// words = ["oath","pea","eat","rain"]

// Output: ["eat","oath"]
	class Trie {
		public:
		    Trie() {
			// next_.reserve(26);
			// for (int i = 0; i < 26; i++) {
			//     next_[i] = nullptr;
			// }
			next = vector<Trie*>(26, NULL);
		    }

		    void insert(const string &word) {
			Trie* curr = this;
			for (int i = 0; i < word.length(); i++) {
			    auto& pros = curr->next[word[i]-'a'];
			    if (pros == nullptr) {
				Trie* new_node = new Trie();
				pros = new_node;
			    }
			    curr = pros;
			}
			curr->is_word = true;
			curr->word = word;
		    }

		    string word = "";
		    bool is_word = false;
		    vector<Trie*> next;
		};
	void dfs(int i, int j, Trie* head, vector<vector<char>>& board, vector<string>* out) {
		if (i >= board.size() || i < 0 || j >= board[i].size() || j < 0) return;

		char c = board[i][j];
		if (c == '.') return;

		Trie* next_trie = head->next[c - 'a'];
		if (next_trie == nullptr) return;

		board[i][j] = '.'; // changes board

		if (next_trie->is_word) {
		    out->push_back(next_trie->word);
		    next_trie->is_word = false; // changes the trie (other option is to use hashset)//the same word in the dict should only appear once
		}

		dfs(i+1, j, next_trie, board, out);
		dfs(i, j+1, next_trie, board, out);
		dfs(i-1, j, next_trie, board, out);
		dfs(i, j-1, next_trie, board, out);

		board[i][j] = c; // reverting board

		return;
	    }   

	    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		if (board.empty()) return vector<string>(); 

		Trie* head = new Trie();
		for (const auto &word : words) {
		    head->insert(word);
		}

		vector<string> out;
		for (int i = 0; i < board.size(); i++) {
		    for (int j = 0; j < board[i].size(); j++) {
			dfs (i, j, head, board, &out);
		    }
		}
		return out;
	    }
};
