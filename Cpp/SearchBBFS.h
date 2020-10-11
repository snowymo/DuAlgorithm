#pragma once
#include "common.h"

namespace SearchBBFS {
	class Solution {
	public:
		vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
			vector<vector<string>> ans;
			unordered_set<string> dict(wordList.begin(), wordList.end());
			if (!dict.count(endWord)) return ans;

			int l = beginWord.length();

			unordered_set<string> q1{ beginWord };
			unordered_set<string> q2{ endWord };
			unordered_map<string, vector<string>> children;

			bool found = false;
			bool backward = false;

			while (!q1.empty() && !q2.empty() && !found) {
				// Always expend the smaller queue first
				if (q1.size() > q2.size()) {
					std::swap(q1, q2);
					backward = !backward;
				}

				for (const string& w : q1)
					dict.erase(w);
				for (const string& w : q2)
					dict.erase(w);

				unordered_set<string> q;

				for (const string& word : q1) {
					string curr = word;
					for (int i = 0; i < l; i++) {
						char ch = curr[i];
						for (int j = 'a'; j <= 'z'; j++) {
							curr[i] = j;

							const string* parent = &word;
							const string* child = &curr;

							if (backward)
								std::swap(parent, child);

							if (q2.count(curr)) {
								found = true;
								children[*parent].push_back(*child);
							}
							else if (dict.count(curr) && !found) {
								q.insert(curr);
								children[*parent].push_back(*child);
							}
						}
						curr[i] = ch;
					}
				}

				std::swap(q, q1);
			}

			if (found) {
				vector<string> path{ beginWord };
				getPaths(beginWord, endWord, children, path, ans);
			}

			return ans;
		}
	private:
		void getPaths(const string& word,
			const string& endWord,
			const unordered_map<string, vector<string>>& children,
			vector<string>& path,
			vector<vector<string>>& ans) {
			if (word == endWord) {
				ans.push_back(path);
				return;
			}

			const auto it = children.find(word);
			if (it == children.cend()) return;

			for (const string& child : it->second) {
				path.push_back(child);
				getPaths(child, endWord, children, path, ans);
				path.pop_back();
			}
		}
	};
	
	// Mine No.126 [H] Word Ladder II
// 	Given two words (beginWord and endWord), and a dictionary's word list, find all shortest transformation sequence(s) from beginWord to endWord, such that:

// Only one letter can be changed at a time
// Each transformed word must exist in the word list. Note that beginWord is not a transformed word.
// Note:

// Return an empty list if there is no such transformation sequence.
// All words have the same length.
// All words contain only lowercase alphabetic characters.
// You may assume no duplicates in the word list.
// You may assume beginWord and endWord are non-empty and are not the same.
// Example 1:

// Input:
// beginWord = "hit",
// endWord = "cog",
// wordList = ["hot","dot","dog","lot","log","cog"]

// Output:
// [
//   ["hit","hot","dot","dog","cog"],
//   ["hit","hot","lot","log","cog"]
// ]
	vector<vector<string>> findLadders3(string beginWord, string endWord, vector<string>& wordList) {
		if(!count(wordList.begin(),wordList.end(),endWord)) return {};

		map<string,vector<string>>adj;
		int len = beginWord.size();

		// construct adj for begin word in case begin word is not in the dict
		if(!count(wordList.begin(),wordList.end(),beginWord))        {
		    wordList.push_back(beginWord);
		}

		// construct all adj for entire dict
		for(int i=0;i<wordList.size();i++)        {
		    for(int j=i+1;j<wordList.size();j++)            {                
			    int cnt=0;
			    for(int k=0; k < len; k++)                    {
				if(wordList[i][k]!=wordList[j][k]) cnt++;
				if(cnt==2) break;
			    }
			    if(cnt==1)                    {
				adj[wordList[i]].push_back(wordList[j]);
				adj[wordList[j]].push_back(wordList[i]);
			    }

		    }
		}


		map<string,int>vis;// pair of a word and its position in the current ladder
		queue<pair<string,vector<string>>>q; // cur word and its full path to cur word
		vector<vector<string>>res;// results
		q.push({beginWord,{beginWord}});
		vis[beginWord]=1;

		while(!q.empty())        {
		    pair<string,vector<string>> t = q.front();
		    q.pop();
		    // BFS
		    for(int i=0;i<adj[t.first].size();i++)            {                
			if(vis.find(adj[t.first][i])==vis.end() || vis[adj[t.first][i]]==t.second.size()+1)                {
			    vector<string>temp=t.second;
			    temp.push_back(adj[t.first][i]);

			    if(adj[t.first][i]==endWord) res.push_back(temp);
			    else q.push({adj[t.first][i],temp});
			    vis[adj[t.first][i]]=temp.size();
			}
		    }
		}

		return res;
	    }

	    void bfs(string& beginWord, string& endWord, unordered_set<string>& d, unordered_map<string, vector<string>>& neighbors, unordered_map<string, int>& dist){
		queue<string> q;
		q.push(beginWord);
		dist[beginWord] = 0;
		int lvl = 1;
		while(!q.empty()){
		    int q_size = q.size();
		    unordered_set<string> visited;
		    for(int i = 0; i < q_size; i++){
			auto curr = q.front();
			q.pop();
			string nxt = curr;
			// cout << "nxt " << nxt << "\n";
			for(int j = 0; j < nxt.size(); j++){
			    auto tmp = nxt[j];
			    // replace one char by any char
			    for(char c = 'a'; c <= 'z'; c++){
				nxt[j] = c;
				if(d.count(nxt) != 0){
				    // add to neighbour if exists in dict
				    neighbors[curr].push_back(nxt);
				    visited.insert(nxt);
				    if(dist.count(nxt) == 0){
					// such neight has a level number now, which is kinda next level for sure, to be added to queue
					dist[nxt] = lvl;
					q.push(nxt);
				    }
				}
			    }
			    nxt[j] = tmp;
			}
		    }
		    lvl++;
		    for(string w: visited) d.erase(w);
		}
	    }

	    // talk through the tree via dfs and see if it can reach the endword
	    void dfs(string& curr, string& endWord, unordered_map<string, vector<string>>& neighbors, unordered_map<string, int>& dist, vector<string>& path, vector<vector<string>>& res){
		path.push_back(curr);
		if(curr == endWord){
		    res.push_back(path);
		    return;
		}
		for(auto nxt: neighbors[curr]){
		    if(dist[nxt] == dist[curr] + 1){
			dfs(nxt, endWord, neighbors, dist, path, res);
			path.pop_back();
		    }
		}
	    }

	    // create a tree with node beginWord as root following bfs rules first
	    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
		vector<vector<string>> res;
		unordered_set<string> d(wordList.begin(), wordList.end());
		if(d.count(endWord) == 0) return res;
		unordered_map<string, vector<string>> neighbors;
		unordered_map<string, int> dist;
		bfs(beginWord, endWord, d, neighbors, dist);
		// for(auto m:neighbors)
		// {
		//     cout<<m.first<<"-";
		//     for(auto n:m.second)
		//         cout<<n<<" ";
		//     cout<<endl;
		// }
		vector<string> path;
		dfs(beginWord, endWord, neighbors, dist, path, res);
		return res;
	    }
}
