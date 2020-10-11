#pragma once
#include "common.h"

namespace GraphBiparite {
	bool isBipartite(vector<vector<int>>& graph) {
		unordered_map<int, int> col;
		const int n = (int)graph.size();
		for (int i = 0; i < n; ++i) {
			if (col.count(i)) {
				continue;
			}
			stack<int> s;
			s.push(i);
			col[i] = 0;
			while (!s.empty()) {
				int u = s.top();
				s.pop();
				for (auto v : graph[u]) {
					if (!col.count(v)) {
						s.push(v);
						col[v] = col[u] ^ 1;
					}
					else if (col[v] == col[u])
						return false;
				}
			}
		}
		return true;
	}
	// Mine (DFS) No.785 [M] Is Graph Bipartite
	unordered_map<int,int> group;
	    bool isBipartite(vector<vector<int>>& graph) {
		if(graph.size() == 0)
		    return true;
		for(int i = 0; i < graph.size(); i++){
		    bool curRet = isBipartite(graph, i);
		    if(!curRet)
			return false;
		}
		return true;
	    }
	    bool isBipartite(vector<vector<int>>& graph, int vert){
		// cout << "check vert " << vert << "\n";
		if(group.count(vert) == 0){
		    group[vert] = vert+1;
		}
		int groupIdx = group[vert];
		// cout << "cur group " << groupIdx << "\n";

		for(int j = 0; j < graph[vert].size(); j++){
		    if(group.count(graph[vert][j]) > 0){
			// if they are the same, return false
			if(group[graph[vert][j]] == groupIdx){
			    // cout << "same group " << vert << "-" << graph[vert][j] << "\n";
			    return false;
			}                    
			// group[graph[i][j]] should be in the same group groupIdx
			// group[graph[vert][j]] = -groupIdx;
		    }
		    else{
			group[graph[vert][j]] = -groupIdx;
			bool curRet = isBipartite(graph, graph[vert][j]);
			if(!curRet)
			    return false;
		    }
		}
		return true;
	    }
}
