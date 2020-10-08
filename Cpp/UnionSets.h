#pragma once
#include "common.h"

class UnionSets {
public:
	// Union Find Set with Compressed Path in O(alpha)
	int getParent(vector<int>& union_set, int i) {
		while (i != union_set[i]) {
			union_set[i] = union_set[union_set[i]];
			i = union_set[i];
		}
		return i;
	}

	// Test if a graph is a valid tree
	// A tree is n-1 edges and no circle
	bool validTree(int n, vector<pair<int, int>>& edges) {
		vector<int> roots(n);
		for (int i = 0; i < n; ++i)
			roots[i] = i;

		for (auto const &e : edges) {
			int x = getParent(roots, e.first);
			int y = getParent(roots, e.second);
			if (x == y)
				return false;
			roots[x] = y;
		}
		return edges.size() == n - 1;
	}

	// Test if number of Connected Components in an Undirected Graph
	int countComponents(int n, vector<pair<int, int>>& edges) {
		vector<int> union_set(n);
		for (int i = 0; i < n; ++i)
			union_set[i] = i;
		int ans = n;

		for (auto const &e : edges) {
			int x = getParent(union_set, e.first);
			int y = getParent(union_set, e.second);
			// if x and y are not connected, connect them
			if (x != y)
				--ans;
			union_set[x] = y;
		}

		return ans;
	}

	vector<int> numIslands2(int m, int n, vector<pair<int, int>>& positions) {
		vector<int> res;
		if (m <= 0 || n <= 0)
			return res;
		vector<int> roots(m * n, -1);
		int cnt = 0;
		vector<vector<int>> dirs{ { 0, -1 },{ -1, 0 },{ 0, 1 },{ 1, 0 } };
		for (auto const &a : positions) {
			int id = n * a.first + a.second;
			roots[id] = id;
			++cnt;
			for (auto d : dirs) {
				int x = a.first + d[0], y = a.second + d[1];
				int cur_id = n * x + y;
				if (x < 0 || x >= m || y < 0 || y >= n || roots[cur_id] == -1)
					continue;
				int new_id = getParent(roots, cur_id);
				if (id != new_id) {
					roots[id] = new_id;
					id = new_id;
					--cnt;
				}
			}
			res.emplace_back(cnt);
		}
		return res;
	}
// 	Mine No.721 Accounts Merge[M]
// 	Given a list accounts, each element accounts[i] is a list of strings, where the first element accounts[i][0] is a name, and the rest of the elements are emails representing emails of the account.

// Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is some email that is common to both accounts. Note that even if two accounts have the same name, they may belong to different people as people could have the same name. A person can have any number of accounts initially, but all of their accounts definitely have the same name.

// After merging the accounts, return the accounts in the following format: the first element of each account is the name, and the rest of the elements are emails in sorted order. The accounts themselves can be returned in any order.

// Example 1:
// Input: 
// accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John", "johnnybravo@mail.com"], ["John", "johnsmith@mail.com", "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]
// Output: [["John", 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary", "mary@mail.com"]]
// Explanation: 
// The first and third John's are the same person as they have the common email "johnsmith@mail.com".
// The second John and Mary are different people as none of their email addresses are used by other accounts.
// We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'], 
// ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.
// Note:

// The length of accounts will be in the range [1, 1000].
// The length of accounts[i] will be in the range [1, 10].
// The length of accounts[i][j] will be in the range [1, 30].
	vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
		unordered_map<string, vector<string>> ccg;
		unordered_map<string, int> email2name;
		vector<vector<string>> result;
	//         construct adj
		for(int i = 0; i < accounts.size(); i++){
		    // accounts[i][0] = "!" + accounts[i][0]; // to ensure this is the first one after sorting
		    for(int j = 1; j < accounts[i].size()-1; j++){
			ccg[accounts[i][j]].push_back(accounts[i][j+1]);
			ccg[accounts[i][j+1]].push_back(accounts[i][j]);
			email2name[accounts[i][j]] = i;
			email2name[accounts[i][j+1]] = i;
		    }
		    if(accounts[i].size() == 2){
			// only one email here
			result.push_back(accounts[i]);
		    }
		}
	//         connect ccg
		unordered_map<string, bool> visited;
		for(auto iter = ccg.begin(); iter != ccg.end(); ++iter){
		    if(visited.find(iter->first) == visited.end()){
			vector<string> curCCG;
			connect(ccg, visited, iter->first, curCCG);

			sort(curCCG.begin(), curCCG.end());
			//                 email first
			curCCG.insert(curCCG.begin(),accounts[email2name[iter->first]][0]);
			result.push_back(curCCG);
		    }
		}
		return result;
	    }

	    void connect(unordered_map<string, vector<string>>& ccg, unordered_map<string, bool>& visited,
			 string email, vector<string>& curCCG){
		visited[email] = true;        
		curCCG.push_back(email);

		if(ccg.find(email) == ccg.end())
		    return;

		for(auto iter = ccg[email].begin(); iter != ccg[email].end(); iter++){
		    if(visited.find(*iter) == visited.end()){
			connect(ccg, visited, *iter, curCCG);
		    }
		}
	    }
};
